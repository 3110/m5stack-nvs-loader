#include <Arduino.h>
#include <WiFi.h>

#include "NVSLoader.h"

const char* NS = "NVSLoader";
const char* WIFI_CONFIG = "/wifi.json";
const char* KEY_SSID = "ssid";
const char* KEY_PASSWORD = "password";

char ssid[32 + 1] = {0};
char password[64 + 1] = {0};

NVSLoader loader(NS);

void setup(void) {
    SERIAL_BEGIN(115200);
    if (loader.begin(WIFI_CONFIG)) {
        if (loader.get(KEY_SSID, ssid, sizeof(ssid))) {
            SERIAL_PRINTF_LN("SSID: %s", ssid);
        }
        if (loader.get(KEY_PASSWORD, password, sizeof(password))) {
            SERIAL_PRINTF_LN("Password: %s", password);
        }
        if (strlen(ssid) > 0 && strlen(password)) {
            WiFi.begin(ssid, password);
            SERIAL_PRINT("Connecting");
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                SERIAL_PRINT(".");
            }
            SERIAL_PRINTLN();
            if (WiFi.status() == WL_CONNECTED) {
                SERIAL_PRINTF_LN("Connected: IP address %s",
                                 WiFi.localIP().toString());
            }
        }
    } else {
        SERIAL_PRINTF_LN("Failed to load %s", WIFI_CONFIG);
    }
}

void loop(void) {
}