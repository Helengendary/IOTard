#include <Arduino.h>

void setup() {
  pinMode(7, INPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (digitalRead(7))
  {
    digitalWrite(6, HIGH);
    Serial.println("tao_tocando");
  } else {
    digitalWrite(6, LOW);
    Serial.println("nao_tocando");
  }
  
  delay(200);
}
