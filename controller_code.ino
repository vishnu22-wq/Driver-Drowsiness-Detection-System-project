#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

// ================= WIFI =================
const char* ssid = "advprojectshub";
const char* password = "advprojectshub";

// ================= TELEGRAM =================
#define BOTtoken "7659361835:AAGD_1PqIP0F088jXnAACZT4EbbXFrm7BUQ" // 8168721639:AAFzYKpLRG7KIO6JdTJO-U222qn7Z26v8NI
#define CHAT_ID  "2107657881" // 6470916412

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// ================= LCD =================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================= VARIABLES =================
char incomingData;
int buzzer = 16;

unsigned long alertStart = 0;
bool alertActive = false;

unsigned long lastTelegramTime = 0;
const unsigned long telegramCooldown = 10000;  // 10 sec anti-spam

// ==================================================

void setup() {

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  pinMode(buzzer, OUTPUT);

  // Secure client
  client.setInsecure();   // Skip certificate validation

  // Connect WiFi
  WiFi.begin(ssid, password);
  lcd.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1500);
  lcd.clear();

  bot.sendMessage(CHAT_ID, "🚗 Drowsiness System Started", "");

  lcd.print("System Ready");
  delay(1500);
  lcd.clear();
}

// ==================================================

void loop() {

  // ===== READ FROM PYTHON =====
  if (Serial.available() > 0) {
    incomingData = Serial.read();

    if (incomingData == '1' && !alertActive) {

      unsigned long currentTime = millis();

      if (currentTime - lastTelegramTime > telegramCooldown) {

        lastTelegramTime = currentTime;

        // Start alert mode
        alertActive = true;
        alertStart = millis();

        digitalWrite(buzzer, HIGH);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DROWSINESS");
        lcd.setCursor(0, 1);
        lcd.print("DETECTED!");

        // SEND TELEGRAM ALERT
        bot.sendMessage(
          CHAT_ID,
          "Alert from device\nDriver in drowsiness mode....!",
          ""
        );

        Serial.println("Telegram Alert Sent");
      }
    }
  }

  // ===== STOP BUZZER AFTER 3 SECONDS =====
  if (alertActive) {
    if (millis() - alertStart >= 3000) {

      digitalWrite(buzzer, LOW);
      lcd.clear();
      alertActive = false;
    }
  }
}