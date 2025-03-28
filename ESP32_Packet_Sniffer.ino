#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_log.h"


// A code created by ViperFSFA
// Unethical use is Illigal!!
// #Hacktheplanet


#define MAX_PACKETS 1000
#define CHANNEL_HOP_INTERVAL 500 

uint8_t target_bssid[6] = {0}; 
uint16_t packet_count = 0;
uint8_t channel = 1;

void sniffer(void* buf, wifi_promiscuous_pkt_type_t type) {
    wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*)buf;
    wifi_pkt_rx_ctrl_t ctrl = (wifi_pkt_rx_ctrl_t)pkt->rx_ctrl;

    if (type == WIFI_PKT_MGMT && pkt->payload[0] == 0x80) {
        Serial.printf("[EAPOL] BSSID: %02X:%02X:%02X:%02X:%02X:%02X\n",
            pkt->payload[10], pkt->payload[11], pkt->payload[12],
            pkt->payload[13], pkt->payload[14], pkt->payload[15]);
    }

    if (type == WIFI_PKT_MGMT && pkt->payload[0] == 0x40) {
        Serial.printf("[PROBE] MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
            pkt->payload[10], pkt->payload[11], pkt->payload[12],
            pkt->payload[13], pkt->payload[14], pkt->payload[15]);
    }

    if (packet_count++ < MAX_PACKETS) {
        File file = SPIFFS.open("/packets.bin", FILE_APPEND);
        file.write((uint8_t*)pkt->payload, ctrl.sig_len);
        file.close();
    }
}

void channel_hop() {
    channel = (channel % 13) + 1;
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    delay(CHANNEL_HOP_INTERVAL);
}

void setup() {
    Serial.begin(115200);
    SPIFFS.begin(true);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_NULL);
    esp_wifi_start();
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(&sniffer);
}

void loop() {
    channel_hop();
}
