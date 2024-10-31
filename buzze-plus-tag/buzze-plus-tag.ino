
#include <SPI.h>

#include <RFID.h>

#define SDA_DIO 9
#define RESET_DIO 8
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 

void tom(char pino, int frequencia, int duracao);
void mario(int pino, int tempo);  // Declaração da função mario
void largada(int pino, int tempo); // Declaração da função largada

boolean ganhou = false;

int pino = 2;
int tempo = 150; // Tempo de cada nota

String cartao = "22822721020726";

int cartaoTimes = 0;
int azulTimes = 0;

void setup()
{ 
  pinMode(pino, OUTPUT);
  
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();

  Serial.println("Largada");
  largada(pino, tempo);
}



void loop()
{

  /* Has a card been detected? */
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();
    Serial.println("Card detected:");

    String atual;
    for(int i=0;i<5;i++)
    {
      atual += String(RC522.serNum[i], DEC);
    }
    
    if (atual == cartao) {
      cartaoTimes++;
    } else {
      azulTimes++;
    }

    Serial.print(atual);
    Serial.print(cartao);
    Serial.println();
    Serial.println();
  }

  if (cartaoTimes == 3 || azulTimes == 3 && !ganhou) {
    Serial.println("Vitoria");
    mario(pino, tempo);
    ganhou = true;
  }

  delay(20);
}


void tom(char pino, int frequencia, int duracao) {
  float periodo = 1000000.0 / frequencia;
  for (int i = 0; i < duracao / (periodo / 1000); i++) {
    digitalWrite(pino, HIGH);
    delayMicroseconds(periodo / 2);
    digitalWrite(pino, LOW);
    delayMicroseconds(periodo / 2);
  }
}

void mario(int pino, int tempo) {
  tom(pino, 659, tempo); // Mi
  delay(tempo);

  tom(pino, 659, tempo); // Mi
  delay(tempo);

  tom(pino, 659, tempo); // Mi
  delay(tempo * 2);

  tom(pino, 523, tempo); // Dó
  delay(tempo);

  tom(pino, 659, tempo); // Mi
  delay(tempo * 2);

  tom(pino, 784, tempo); // Sol
  delay(tempo * 4);

  tom(pino, 392, tempo); // Sol grave
  delay(tempo * 4);

  tom(pino, 523, tempo); // Dó
  delay(tempo * 2);

  tom(pino, 392, tempo); // Sol grave
  delay(tempo * 2);

  tom(pino, 330, tempo); // Mi grave
  delay(tempo * 2);

  tom(pino, 440, tempo); // Lá
  delay(tempo);

  tom(pino, 494, tempo); // Si
  delay(tempo);

  tom(pino, 466, tempo); // Lá#
  delay(tempo);

  tom(pino, 440, tempo); // Lá
  delay(tempo);

  tom(pino, 392, tempo); // Sol
  delay(tempo);

  tom(pino, 659, tempo); // Mi
  delay(tempo);

  tom(pino, 784, tempo); // Sol agudo
  delay(tempo);

  tom(pino, 880, tempo); // Lá agudo
  delay(tempo * 2);

  tom(pino, 698, tempo); // Fá agudo
  delay(tempo);

  tom(pino, 784, tempo); // Sol agudo
  delay(tempo);

  tom(pino, 659, tempo); // Mi
  delay(tempo * 2);

  tom(pino, 523, tempo); // Dó
  delay(tempo);

  tom(pino, 587, tempo); // Ré
  delay(tempo);

  tom(pino, 494, tempo); // Si
  delay(tempo * 2);

  delay(2000);
}

void largada(int pino, int tempo) {
  tom(pino, 392, tempo); // SOL
  delay(1000);

  tom(pino, 440, tempo); // LÁ
  delay(1000);

  tom(pino, 494, tempo); // SI
  delay(1000);

  tom(pino, 523, tempo * 2); // DÓ (mais longo)
  delay(1000);

  delay(2000);
}
