
bool ativou = false;
int tempo = 150;

int pino = 6;

void setup() {
  pinMode(12, INPUT);
  pinMode(pino, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  Serial.println(digitalRead(12));

  if (digitalRead(12)) {
    ativou = true;
  }

  if (ativou) {
   for (int i = 0; i < 3; i++) {        // Repetir o alarme 3 vezes
    tone(pino, 1000);              // Emitir um som de 1000 Hz
    delay(500);                         // Pausar por 500ms
    noTone(pino);                  // Parar o som
    delay(500);                         // Pausar por 500ms
  }
  delay(2000); 
  }
}
