#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
#include <ESP32Servo.h>
#include <FirebaseESP32.h>

// Configuração do Wi-Fi
const char * ssid = "alexaamilton";
const char * password = "87654321";

// Configuração do Firebase
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;
FirebaseData firebaseData;

// Controle Alexa
Espalexa Alexa;


// Funções de dispositivos
void banheiro(uint8_t State) {
  Firebase.setBool(firebaseData, "/home/bathroom/light", State & 1);
}

void abrePorta(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/door", State & 1);
}

void luzSala(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/livingroom/light", State & 1);
}

void luzCoz(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/kitchen/light", State & 1);
}

void luzBed(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/bedroom/light", State & 1);
}

void luzGar(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/garage/light", State & 1);
}

void luzPis(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/pool/light", State & 1);
}

void tv(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/livingroom/canal", State & 1);
}

void canal(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/livingroom/tv", State & 1);
}

void alarme(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/alarm", State & 1);
}

void venSala(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/livingroom/air", State & 1);
}

void venBed(uint8_t State) {
    Firebase.setBool(firebaseData, "/home/bedroom/air", State & 1);
}

void atualizaEstadoPinos() {
    // Atualiza o pino do ventilador da sala
    if (Firebase.getBool(firebaseData, "/home/livingroom/air")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(32, firebaseData.boolData());
            Serial.println("Estado do ventilador atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/livingroom/air");
        Serial.println(firebaseData.errorReason());
    }
    
    // Atualiza o pino da porta
    if (Firebase.getBool(firebaseData, "/home/door")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(6, firebaseData.boolData());
            Serial.println("Estado do ventilador atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/door");
        Serial.println(firebaseData.errorReason());
    }

    // Atualiza o pino do ventilador do quarto
    if (Firebase.getBool(firebaseData, "/home/bedroom/air")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(11, firebaseData.boolData());
            Serial.println("Estado do ventilador atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/bedroom/air");
        Serial.println(firebaseData.errorReason());
    }
   
    // Atualiza o pino da luz do banheiro
    if (Firebase.getBool(firebaseData, "/home/bathroom/light")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(12, firebaseData.boolData());
            Serial.println("Estado do ventilador atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/bathroom/light");
        Serial.println(firebaseData.errorReason());
    }

    // Atualiza o pino da luz da sala
    if (Firebase.getBool(firebaseData, "/home/livingroom/light")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(13, firebaseData.boolData());
            Serial.println("Estado da luz da sala atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/livingroom/light");
        Serial.println(firebaseData.errorReason());
    }

    // Atualiza o pino da luz do quarto
    if (Firebase.getBool(firebaseData, "/home/bedroom/light")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(26, firebaseData.boolData());
            Serial.println("Estado da luz da sala atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/bedroom/light");
        Serial.println(firebaseData.errorReason());
    }

    // Atualiza o pino da luz da cozinha
    if (Firebase.getBool(firebaseData, "/home/kitchen/light")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(27, firebaseData.boolData());
            Serial.println("Estado da luz da sala atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/kitchen/light");
        Serial.println(firebaseData.errorReason());
    }

    // Atualiza o pino da luz da garagem
    if (Firebase.getBool(firebaseData, "/home/garage/light")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(25, firebaseData.boolData());
            Serial.println("Estado da luz da sala atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/garage/light");
        Serial.println(firebaseData.errorReason());
    }

    // Atualiza o pino da luz da piscina
    if (Firebase.getBool(firebaseData, "/home/pool/light")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(33, firebaseData.boolData());
            Serial.println("Estado da luz da sala atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/pool/light");
        Serial.println(firebaseData.errorReason());
    }

    // Atualiza o pino da TV
    if (Firebase.getBool(firebaseData, "/home/livingroom/tv")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(10, firebaseData.boolData());
            Serial.println("Estado da TV atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/livingroom/tv");
        Serial.println(firebaseData.errorReason());
    }

    // Atualiza o pino do canal da TV 
    if (Firebase.getBool(firebaseData, "/home/livingroom/canal")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(9, firebaseData.boolData());
            Serial.println("Estado da TV atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/livingroom/canal");
        Serial.println(firebaseData.errorReason());
    }

    // Atualiza o pino do alarme
    if (Firebase.getBool(firebaseData, "/home/alarm")) {
        if (firebaseData.dataType() == "boolean") {
            digitalWrite(14, firebaseData.boolData());
            Serial.println("Estado do alarme atualizado.");
        }
    } else {
        Serial.println("Erro ao ler /home/alarm");
        Serial.println(firebaseData.errorReason());
    }
}

void setup() {
    Serial.begin(9600);

    // Configurar Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao Wi-Fi...");
    }
    Serial.println("Wi-Fi conectado!");

    // Configuração do Firebase
    firebaseConfig.host = "myhome-c70d1-default-rtdb.firebaseio.com";
    firebaseConfig.signer.tokens.legacy_token = "AIzaSyCnwabS06sBoO3u5CPiFmNiSjcSib5MaRw"; 
    Firebase.begin(&firebaseConfig, &firebaseAuth);
    Firebase.reconnectWiFi(true);
    Serial.println("Conexão ao Firebase bem-sucedida!");

    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(32, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(23, OUTPUT);
    pinMode(6, OUTPUT);

    // Configuração Alexa
    Alexa.addDevice("alarme da casa", alarme);
    Alexa.addDevice("luz do banheiro", banheiro);
    Alexa.addDevice("luz da sala", luzSala);
    Alexa.addDevice("luz da cozinha", luzCoz);
    Alexa.addDevice("luz do quarto", luzBed);
    Alexa.addDevice("luz da garagem", luzGar);
    Alexa.addDevice("luz da piscina", luzPis);
    Alexa.addDevice("ventilador da sala", venSala);
    Alexa.addDevice("ventilador do quarto", venBed);
    Alexa.addDevice("televisão", tv);
    Alexa.addDevice("porta principal", abrePorta);
    Alexa.begin();
}

void loop() {
    Alexa.loop(); // Controle Alexa
    
    atualizaEstadoPinos(); // Atualiza os estados dos pinos com base no Firebase
    delay(500); // Ajuste o delay conforme necessário
}
