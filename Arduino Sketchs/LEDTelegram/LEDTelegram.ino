

#include <OTALabDevice.h>

String id = "15";
OTALabDevice* device = new OTALabDevice();

// Mude as variáveis a seguir de acordo com a rede que você vai conectar o seu ESP8266
// Aqui você deve modificar de acordo com o servidor que você irá utilizar, será o mesmo endereço que você colocou no nó 'mqtt' no Node-RED
const char* mqtt_server = "broker.mqtt-dashboard.com";


// Inicializa o ESP8266 como cliente
WiFiClient espClient;
PubSubClient client(espClient);

// No nosso circuito o LED está conectado no pino D6 que é o GPIO12 na placa D1 mini
const int lamp = 2;

// Quando alguma mensagem é publicada em algum tópico que o ESP8266 estiver inscrito esta função é executada,
// portanto ela é alterada de acordo com a lógica que o programador deseja.
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Chegou uma mensagem no tópico: ");
  Serial.print(topic);
  Serial.print(". Mensagem: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    //Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println(messageTemp);
  //
  
  // Aqui é checada se a mensagem que chegou foi no tópico 'iotufes/led', se sim checa se a mensagem é 'acende' ou 'apaga'. E realiza a ação.
  if(topic=="tcc/iot/mqtt/led"){
      if(messageTemp == "acende" || messageTemp == "Acende"|| messageTemp == "Acender"|| messageTemp == "acender"){
        Serial.print("Acendendo LED");
        digitalWrite(lamp, LOW);
      }
      else if(messageTemp == "apaga" || messageTemp == "Apaga" || messageTemp == "Apagar" || messageTemp == "apagar"){
        Serial.print("Apagando LED");
        digitalWrite(lamp, HIGH);
      }
  }
  Serial.println();
}

// Esta função reconecta o ESP8266 ao servidor MQTT
void reconnect1() {
  // Fica em loop até conectar novamente
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    // Tentativa de conexão. O argumento passado na função 'connect' é o id da conexão MQTT, este deve ser único em um servidor.
    if (client.connect("EspClientIot")) {
      Serial.println("connectado");
      // Aqui nos increvemos ou reinscrevemos nos tópicos
      // Você pode se inscrever em mais de um tópico com o mesmo ESP8266
      client.subscribe("tcc/iot/mqtt/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// O setup simplesmente inicializa o pino D6 como saída e inicia uma comunicação serial com baud rate de 115200
// Essa comunicação serial pode ser utilizada para visualizar as mensagens impressas
// Aqui também é inicializado qual servidor MQTT e a função callback, é ela que recebe as mensagens do MQTT e controla o LED
void setup() {
  //EEPROM_clear();
  pinMode(lamp, OUTPUT);
  digitalWrite(lamp, LOW);
  
  Serial.begin(115200);
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  device->setup(id);
}

void loop() {
  if (!client.connected()) {
    reconnect1();
    delay(5000);
  }
  if(!client.loop())
    client.connect("EspClientIot");
  device->handle();
} 
