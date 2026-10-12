#include <Arduino.h>

#define BUZZER_PIN 21   // 🔁 changed from 25 → 21

float voltage = 0.0;

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  randomSeed(analogRead(0));
}

void loop() {

  // Generate random voltage (10–14V)
  voltage = random(100, 140) / 10.0;

  Serial.print("Simulated Voltage: ");
  Serial.println(voltage);

  if (abs(voltage - 12.0) > 1.0) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000);
}