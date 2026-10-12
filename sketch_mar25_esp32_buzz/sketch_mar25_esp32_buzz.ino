#include <Arduino.h>

// ================= PIN CONFIG =================
#define LED_PIN 25
#define BUZZER_PIN 26

// ================= THRESHOLDS =================
float TEMP_WARN = 30.0;
float TEMP_CRIT = 35.0;

float VOLT_WARN = 2.5;
float VOLT_CRIT = 3.0;

// ================= SHARED VARIABLES =================
float temperature = 0;
float voltage = 0;

// ================= LOCK SYSTEM =================
bool criticalActive = false;
unsigned long criticalStartTime = 0;
bool systemLocked = false;

#define CRITICAL_DURATION 30000  // 30 sec

// ================= SYSTEM STATE =================
enum SystemState { NORMAL, WARNING, CRITICAL, LOCKED };
SystemState currentState = NORMAL;
SystemState lastState = NORMAL;

// ================= UART TASK =================
void uartTask(void *pvParameters) {

  while (1) {

    if (Serial2.available()) {

      String line = Serial2.readStringUntil('\n');

      Serial.println("RAW -> " + line);

      int nodeID;
      float t, v;

      int parsed = sscanf(line.c_str(),
                          "ID:%d,T:%f,V:%f,END",
                          &nodeID, &t, &v);

      if (parsed == 3) {
        temperature = t;
        voltage = v;

        Serial.print("Parsed -> Temp=");
        Serial.print(temperature);
        Serial.print(" Voltage=");
        Serial.println(voltage);
      }
      else {
        Serial.println("Parse Error");
      }
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

// ================= ALERT TASK =================
void alertTask(void *pvParameters) {

  while (1) {

    // ===== SYSTEM LOCK =====
    if (systemLocked) {
      currentState = LOCKED;

      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);

      if (currentState != lastState) {
        Serial.println("STATE -> LOCKED");
        lastState = currentState;
      }

      vTaskDelay(1000 / portTICK_PERIOD_MS);
      continue;
    }

    // ===== CRITICAL =====
    if (temperature > TEMP_CRIT || voltage > VOLT_CRIT) {

      currentState = CRITICAL;

      digitalWrite(LED_PIN, HIGH);

      // Start timer
      if (!criticalActive) {
        criticalActive = true;
        criticalStartTime = millis();
      }

      // Check 30 sec condition
      if (millis() - criticalStartTime >= CRITICAL_DURATION) {
        Serial.println("SYSTEM LOCKED (30s Critical)");
        systemLocked = true;
        continue;
      }

      if (currentState != lastState) {
        Serial.println("STATE -> CRITICAL (Above threshold)");
        lastState = currentState;
      }

      // Fast beep
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      digitalWrite(BUZZER_PIN, LOW);
      vTaskDelay(200 / portTICK_PERIOD_MS);
    }

    // ===== WARNING =====
    else if (temperature > TEMP_WARN || voltage > VOLT_WARN) {

      currentState = WARNING;

      digitalWrite(LED_PIN, HIGH);
      criticalActive = false;

      if (currentState != lastState) {
        Serial.println("STATE -> WARNING (Above warning threshold)");
        lastState = currentState;
      }

      // Slow beep
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(600 / portTICK_PERIOD_MS);
      digitalWrite(BUZZER_PIN, LOW);
      vTaskDelay(600 / portTICK_PERIOD_MS);
    }

    // ===== NORMAL =====
    else {

      currentState = NORMAL;

      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      criticalActive = false;

      if (currentState != lastState) {
        Serial.println("STATE -> NORMAL (Below threshold)");
        lastState = currentState;
      }

      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
  }
}

// ================= SETUP =================
void setup() {

  Serial.begin(115200);

  // UART2 (RX=16, TX=17)
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Create RTOS Tasks
  xTaskCreate(uartTask, "UART Task", 4096, NULL, 1, NULL);
  xTaskCreate(alertTask, "Alert Task", 4096, NULL, 1, NULL);
}

// ================= LOOP =================
void loop() {
  // Empty (RTOS handles everything)
}