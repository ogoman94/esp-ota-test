#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

const char* ssid = "Hozen";
const char* password = "5324453205HoZeNn";

const char* version_url = "https://raw.githubusercontent.com/ogoman94/esp-ota-test/main/version.txt";
const char* firmware_url = "https://raw.githubusercontent.com/ogoman94/esp-ota-test/main/firmware.bin";

String current_version = "2.0.0";  // 1.0.0 → 2.0.0

void checkOTA() {
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    http.begin(client, version_url);
    int code = http.GET();

    if (code == 200) {
        String new_version = http.getString();
        new_version.trim();
        Serial.println("Sunucu: " + new_version);
        Serial.println("Cihaz: " + current_version);

        if (new_version != current_version) {
            Serial.println("Guncelleniyor...");
            ESPhttpUpdate.update(client, firmware_url);
        } else {
            Serial.println("Guncel, islem yok.");
        }
    } else {
        Serial.println("Versiyon kontrol hatasi: " + String(code));
    }
    http.end();
}

void setup() {
    Serial.begin(115200);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi baglandi!");
    Serial.println("Bu versiyon 2.0.0!");

    checkOTA();
}

void loop() {
    delay(3600000);
    checkOTA();
}