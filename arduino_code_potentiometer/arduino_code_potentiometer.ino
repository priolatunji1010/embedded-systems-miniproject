#define POT_PIN A0

void setup() {
  Serial.begin(9600);
}

void loop() {

  int raw = analogRead(POT_PIN);  // 0–1023

  // Convert to meaningful values
  float temperature = (raw / 1023.0) * 50.0;   // 0–50°C
  float voltage = (raw / 1023.0) * 3.3;        // 0–3.3V

  int nodeID = 1;

  // CAN-style formatted message
  Serial.print("ID:");
  Serial.print(nodeID);
  Serial.print(",T:");
  Serial.print(temperature);
  Serial.print(",V:");
  Serial.print(voltage);
  Serial.println(",END");

  delay(1000);
}