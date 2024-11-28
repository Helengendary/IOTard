#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
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

    // Configuração Alexa
    Alexa.addDevice("alarme da casa", alarme);
    Alexa.addDevice("luz do banheiro", banheiro);
    Alexa.addDevice("luz da sala", luzSala);
    Alexa.addDevice("luz da cozinha", luzCoz);
    Alexa.addDevice("luz do quarto", luzBed);
    // Alexa.addDevice("luz da garagem", luzGar);
    Alexa.addDevice("cascata", luzPis);
    // Alexa.addDevice("ventilador da sala", venSala);
    // Alexa.addDevice("ventilador do quarto", venBed);
    Alexa.addDevice("televisão", tv);
    Alexa.addDevice("porta principal", abrePorta);
    Alexa.begin();
}

void loop() {
    Alexa.loop(); // Controle Alexa
    delay(500); // Ajuste o delay conforme necessário
}
