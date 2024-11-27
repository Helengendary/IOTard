#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 

#define col 16
#define lin 2
#define ende 0x27

int canalAtual = 12;

Servo servo;

LiquidCrystal_I2C lcd(ende, col, lin);

byte bonecoParado[8] = {
  B00100,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B10001
};

byte bonecoAndando1[8] = {
  B00100,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B00100
};

byte bonecoAndando2[8] = {
  B00100,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B10001,
  B01010
};

byte bonecoCaindo[8] = {
  B00000,
  B01110,
  B00100,
  B00100,
  B01110,
  B00010,
  B00101,
  B01000
};

byte bonecoCaido[8] = {
  B00000,
  B00000,
  B01110,
  B00101,
  B00101,
  B00010,
  B01000,
  B00000
};

byte obstaculo[8] = {
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110
};

void setup() {
  pinMode(2, INPUT); // televisão
  pinMode(3, INPUT); // alarme
  pinMode(5, INPUT); // LDR
  pinMode(6, INPUT); // LDR
  pinMode(7, INPUT); // Porta
  pinMode(10, OUTPUT); // Buzzer
  servo.attach(8); // servo motor
  servo2.attach(9); // servo motor

  bool fechada = true;

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.createChar(0, bonecoParado);
  lcd.createChar(1, bonecoAndando1);
  lcd.createChar(2, bonecoAndando2);
  lcd.createChar(3, bonecoCaindo);
  lcd.createChar(4, bonecoCaido);
  lcd.createChar(5, obstaculo);
}

void loop() {
    
    // canal da tv
    if (digitalRead(2)) {
        canalTrue();
    } else {
        canalFalse();
    }

    // alarme
    if (digitalRead(3)) {
        if (!digitalRead(5) || !digitalRead(6)) {
            digitalWrite(10, HIGH);
        }
    } else {
        digitalWrite(10, LOW);
    }

    if (digitalRead(7)) {
        for(int i = 0; i < 90; i++) {
            servo.write(i);
            servo2.write(i+90);
        }
        fechada = false
    } else {
        if (!fechada) {
            for(int i = 90; i > 0; i--) {
                servo.write(i+90);
                servo2.write(i);
            }
        }
    }
}

// Função para rolar o texto na segunda linha
void rolarTexto(String texto) {
  String espaco = "                "; // Espaço vazio para limpar a linha
  String mensagem = texto + espaco;  // Adiciona espaços ao final da mensagem

  for (int i = 0; i < mensagem.length(); i++) {
    lcd.setCursor(0, 1);
    lcd.print(mensagem.substring(i, i + col));  // Exibe um "pedaço" da mensagem
    delay(300);  // Controle da velocidade da rolagem
  }
}

void canalTrue() {
    for (int i = 0; i < 10; i++) {
      lcd.clear();
      lcd.setCursor(i, 1);  // Posição do boneco
      lcd.write((i % 2 == 0) ? 1 : 2);  // Alterna entre os passos

      delay(200);
    }

    // Obstáculo aparece
    lcd.setCursor(10, 1);
    lcd.write(5);  // Obstáculo
    delay(200);

    // Boneco tropeça e cai
    lcd.setCursor(9, 1);
    lcd.write(3);  // Boneco caindo
    delay(500);

    lcd.setCursor(9, 1);
    lcd.write(4);  // Boneco caído
    delay(1000);

    // Mensagem de queda
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Ops! Caiu...");
    delay(1000);

    // Boneco se levanta
    lcd.clear();
    lcd.setCursor(9, 1);
    lcd.write(0);  // Boneco parado
    lcd.setCursor(3, 0);
    lcd.print("Levanta!");
    delay(1000);

    // Continuação da caminhada
    for (int i = 10; i < 16; i++) {
      lcd.clear();
      lcd.setCursor(i, 1);
      lcd.write((i % 2 == 0) ? 1 : 2);  // Alterna os passos
      delay(200);
    }

    // Finaliza com uma mensagem
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Persistencia!");
    delay(2000);
}

void canalFalse() {

    // Manchetes para exibir
    String manchetes[] = {
        "Nova tecnologia 2024!",
        "Robotica em alta!",
        "Mercado de IA cresce.",
        "Sucesso dos makers!",
        "Fique ligado na CASA."
    };

    lcd.setCursor(0, 0);
    lcd.print(">> CASA NEWS <<");
    delay(500);
    // Loop pelas manchetes
    for (int i = 0; i < 5; i++) {
      rolarTexto(manchetes[i]);
    }

    // Pausa antes de repetir
    delay(500);
}