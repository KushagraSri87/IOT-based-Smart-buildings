
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

// ====== USER SETTINGS ======
const char* ssid     = "ISHAN";          // Your Wi-Fi Name
const char* password = "123456789";               // Your Wi-Fi Password
const char* apiKey   = "FU28DA28IIWD88BY"; // Your ThingSpeak Write API Key
const float VOLTAGE  = 230.0;            // Local AC voltage for power calculation
const uint16_t UPLOAD_INTERVAL_S = 16;   // ThingSpeak rate limit (15-16s)

const char* server = "api.thingspeak.com";
WiFiClient client;

// --- Energy Persistence Variables ---
float energy_kWh = 0.0f;                
const int EEPROM_SIZE = 64;
const int EEPROM_ADDR = 0;              
uint16_t persist_counter = 0;         

// --- Latest Sensor Data Storage ---
float latest_t = 0;
float latest_h = 0;
int latest_m = 0;
float latest_c = 0;

unsigned long previousUploadMillis = 0;

void saveEnergyToEEPROM() {
  EEPROM.put(EEPROM_ADDR, energy_kWh);
  EEPROM.commit();
}

void loadEnergyFromEEPROM() {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(EEPROM_ADDR, energy_kWh);
  // Reset if memory is corrupt or negative
  if (!isfinite(energy_kWh) || energy_kWh < 0) energy_kWh = 0.0f;
}

void setup() {
  // ESP8266 Hardware Serial connected to Arduino SoftwareSerial
  Serial.begin(9600); 
  delay(1000);
  Serial.println("\n--- NodeMCU Cloud Gateway Booting ---");

  // Load previous energy usage
  loadEnergyFromEEPROM();
  Serial.print("Restored Total Energy (kWh): ");
  Serial.println(energy_kWh, 6);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // ==========================================
  // 1. LISTEN TO ARDUINO (Runs continuously)
  // ==========================================
  if (Serial.available()) {
    String inputData = Serial.readStringUntil('\n');
    inputData.trim();
    
    if (inputData.length() > 0) {
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, inputData);

      if (!error) {
        // Successfully parsed JSON, update our global variables
        latest_t = doc["t"];
        latest_h = doc["h"];
        latest_m = doc["m"];
        latest_c = doc["c"];
      } else {
        Serial.print("❌ JSON Parse Error: ");
        Serial.println(error.c_str());
      }
    }
  }

  // ==========================================
  // 2. THINGSPEAK UPLOAD (Runs every 16 seconds)
  // ==========================================
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousUploadMillis >= (UPLOAD_INTERVAL_S * 1000UL)) {
    previousUploadMillis = currentMillis;

    // Calculate Power (W) & Energy (kWh)
    float absCurrent = fabs(latest_c);                  
    float power_W    = absCurrent * VOLTAGE;            
    float dt_h       = UPLOAD_INTERVAL_S / 3600.0f;     
    energy_kWh      += (power_W * dt_h) / 1000.0f;      

    Serial.print("Live Power (W): "); Serial.print(power_W, 2);
    Serial.print(" | Total Energy (kWh): "); Serial.println(energy_kWh, 6);

    // Save to EEPROM every ~8 minutes (30 cycles * 16s) to prevent flash wear
    if (++persist_counter >= 30) {
      saveEnergyToEEPROM();
      persist_counter = 0;
      Serial.println("💾 Energy saved to EEPROM.");
    }

    // Upload to Cloud
    if (WiFi.status() == WL_CONNECTED && client.connect(server, 80)) {
      String url = "/update?api_key=" + String(apiKey) +
                   "&field1=" + String(latest_t, 2) +
                   "&field2=" + String(latest_h, 2) +
                   "&field3=" + String(latest_m) +
                   "&field4=" + String(latest_c, 3) +
                   "&field5=" + String(power_W, 2) +
                   "&field6=" + String(energy_kWh, 6);

      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + server + "\r\n" +
                   "Connection: close\r\n\r\n");
      client.stop();
      Serial.println("✅ Data successfully uploaded to ThingSpeak!");
    } else {
      Serial.println("❌ Wi-Fi disconnected or ThingSpeak unreachable.");
    }
  }
}
