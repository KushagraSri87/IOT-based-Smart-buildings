
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

// --- Pin Definitions ---
#define DHTPIN 2
#define DHTTYPE DHT11
#define PIRPIN 3
#define RELAY1 7 // Light Relay
#define RELAY2 8 // Fan Relay

// --- Object Initialization ---
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); 
SoftwareSerial espSerial(10, 11);   // RX (Pin 10), TX (Pin 11)

// --- Timers & States ---
unsigned long previousMillis = 0;
const long interval = 2000; 
bool fanState = false;

// Dummy current value
float current_A = 0.55; 

void setup() {
  Serial.begin(9600);      
  espSerial.begin(9600);   
  dht.begin();
  
  lcd.init(); 
  lcd.backlight();
  
  pinMode(PIRPIN, INPUT);
  
  pinMode(RELAY1, OUTPUT); digitalWrite(RELAY1, HIGH); 
  pinMode(RELAY2, OUTPUT); digitalWrite(RELAY2, HIGH); 
  
  Serial.println("Arduino Booted. System Ready.");
}

void loop() {
  // ==========================================
  // 1. FAST TASKS (Instant Motion & Light)
  // ==========================================
  int motion = digitalRead(PIRPIN);
  bool occupied = (motion == HIGH);

  if (occupied) {
    digitalWrite(RELAY1, LOW); // Light ON
  } else {
    digitalWrite(RELAY1, HIGH); // Light OFF
  }

  // ==========================================
  // 2. SLOW TASKS (Sensors, LCD, Wi-Fi)
  // ==========================================
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (isnan(t) || isnan(h)) {
      Serial.println("Warning: Failed to read from DHT11!");
      return; 
    }

    // Fan Logic (Hysteresis)
    if (occupied) {
      if (t >= 30.0) {
        fanState = true;  
      } else if (t <= 28.0) {
        fanState = false; 
      }
    } else {
      fanState = false; 
    }
    digitalWrite(RELAY2, fanState ? LOW : HIGH);

    // ==========================================
    // --- NEW: Updated 16x2 LCD Screen Logic ---
    // ==========================================
    lcd.setCursor(0, 0);
    lcd.print("T:"); lcd.print(t, 1); lcd.print("C H:"); lcd.print(h, 0); lcd.print("%   "); 
    
    lcd.setCursor(0, 1);
    // Pad with spaces to ensure exactly 16 characters are written, 
    // which clears out old text without needing lcd.clear()
    lcd.print(occupied ? "M:Y L:ON  " : "M:N L:OFF ");
    lcd.print(fanState ? "F:ON  " : "F:OFF ");

    // Create JSON Payload
    StaticJsonDocument<200> doc;
    doc["t"] = t;
    doc["h"] = h;
    doc["m"] = occupied ? 1 : 0;
    doc["c"] = occupied ? current_A : 0.0; 

    // Transmit to ESP
    serializeJson(doc, espSerial);
    espSerial.println(); 
    
    Serial.print("TX to ESP: ");
    serializeJson(doc, Serial);
    Serial.println();
  }
}
