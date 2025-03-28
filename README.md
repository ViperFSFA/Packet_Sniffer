# WiFi Packet Sniffer & Analyzer  

This repository contains an **ESP32-based WiFi packet sniffer** that captures and analyzes management frames (EAPOL & Probe Requests) in monitor mode.  

## Features  
- Captures **EAPOL frames** (used in WPA/WPA2 handshakes)  
- Logs **Probe Requests** from nearby devices  
- Supports **channel hopping** for broader coverage  
- Saves raw packet data to SPIFFS (`/packets.bin`)  
- Lightweight and optimized for ESP32  

## How It Works  
1. Initializes ESP32 in **promiscuous mode** to monitor WiFi traffic.  
2. **Sniffs management packets** (EAPOL & Probe Requests).  
3. **Hops channels** periodically to scan all 2.4GHz frequencies.  
4. Logs detected MAC addresses and saves raw packets.  

## Use Cases  
- **WiFi security research** (ethical hacking)  
- **Network diagnostics** (packet analysis)  
- **Penetration testing** (handshake capture)  

⚠️ **Warning:** Use responsibly and only on networks you own/have permission to test. Unauthorized scanning may violate laws.  

### Credits  
Developed by **ViperFSFA** – #HackThePlanet  

---  
*For educational purposes only. Ethical use is mandatory.*
