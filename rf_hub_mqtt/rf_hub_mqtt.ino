#include <RCSwitch.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

#define DEBUG 1

/****** MQTT TOPICS *******/
const String welcome_topic_template = "homeassistant/binary_sensor/[DIVISION]/config";
const String unknown_code_topic = "home/other/unknown";
const String disabled_code_topic = "home/other/disabled";
const String mqttTopicStateSuffix = "/state";
const String mqttTopicInfoSuffix = "/info";
const String discovery_payload_template = "{\"name\":\"[SENSOR_NAME]\",\"uniq_id\":\"[UNIQUE_ID]\",\"dev_cla\":\"[DEVICE_CLASS]\",\"stat_t\":\"[MQTT_TOPIC]\",\"pl_on\":\"[PAYLOAD_ON]\",\"pl_off\":\"[PAYLOAD_OFF]\"}"; //,\"dev\":{[DEVICE_INFO]}
/***** NTP *****/
const long utcOffsetInSeconds = 0;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

long timeBetweenMessages = 1000 * 5; // Interval between messages sent to MQTT with the same code (5 seconds)
long lastMsg = 0;
uint32_t lastCodeSent = 0;

typedef struct { 
  String name;
  String unique_id;
  String division;
  String location;
  String device_class;
  String mqtt_status_topic;
  String mqtt_info_topic;
  String mqtt_availability_topic;
  String parent_device;
  uint32_t payload_on;
  uint32_t payload_off;
  uint32_t payload_low_battery;
  String extra_attributes_json;
  bool enabled;
} Sensor;

RCSwitch mySwitch = RCSwitch();
WiFiClient espClient;
PubSubClient client(espClient);

// Secrets
char* getMqttUser();
char* getMqttPwd();
char* getMqttServer();
uint16_t getMqttPort();
char* getWifiSsid();
char* getWifiPwd();
// Sensor
void addSensor(Sensor sensor);
void createSensors();

void setup() {   
  
  #ifdef DEBUG
    Serial.begin(115200);
  #endif

  mySwitch.enableReceive(D2);
  setup_wifi();
  client.setServer(getMqttServer(), getMqttPort());
  timeClient.begin();
  createSensors();
}

String getTopicByCode(uint32_t code);

void publishToMqtt(String topic, String payload) {
  
  #ifdef DEBUG
    Serial.print("Publishing payload ");
    Serial.print(payload);
    Serial.print(" to ");
    Serial.println(topic);
  #endif

  boolean published = client.publish((char*) topic.c_str(), (char*) payload.c_str(), true);
  #ifdef DEBUG
    if(!published) {
      Serial.print("Payload was not published. The client was not currently connected to the server, or the resulting MQTT packet to exceeded the library's maximum packet size");
    }
  #endif
}

void loop() {

  // Confirm if we are still connected to MQTT server
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  long now = millis();
  if (mySwitch.available()) {

    // RF code received
    uint32_t decimal = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();
    
    #ifdef DEBUG
        Serial.print("Decimal code received: ");
        Serial.println(decimal);
    #endif

    // Send MQTT message
    if (now - lastMsg > timeBetweenMessages || lastCodeSent != decimal) {
      lastMsg = now;

      // Sometimes the NTP Client retrieves 1970. To ensure that doesn’t happen we need to force the update
      while(!timeClient.update()) {
        timeClient.forceUpdate();
      }

      String topic = getTopicByCode(decimal);
      topic.replace("/state", "");

      if(unknown_code_topic == topic) {
        String payload = String(decimal);
        publishToMqtt(topic, payload);
      } else {
        // Publish state      
        String payload = String(decimal);
        String stateTopic = topic + mqttTopicStateSuffix;
        publishToMqtt(stateTopic, payload);

        // Publish info on different topic
        /*
        payload = "{\"timestamp\":" + String(timeClient.getEpochTime()) + "\"}";
        String infoTopic = topic + mqttTopicInfoSuffix;
        publishToMqtt(infoTopic, payload);
        */
      }
     
      lastCodeSent = decimal;
    }
  }
}

void publishDiscoveryMsg(Sensor sensor);

void publishDiscoveryMsgs();

void reconnect() {
  
  while (!client.connected()) {
    
    #ifdef DEBUG
      Serial.println("Connecting to MQTT broker...");
    #endif

    if (client.connect("RFHub", getMqttUser(), getMqttPwd())) {
      #ifdef DEBUG
        Serial.println("Connected");
      #endif
      
      // Once connected, publish an announcement for each sensor...
      publishDiscoveryMsgs();
      
    } else {
      #ifdef DEBUG
        Serial.print("Failed. Error: ");
        Serial.print(client.state());
        Serial.print(" WiFi=");
        Serial.print(WiFi.status());
        Serial.println(" Trying again in 5 seconds");
      #endif
      delay(5000);
    }
  }
}

void setup_wifi() {
  delay(10);

  #ifdef DEBUG
    delay(1000);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(getWifiSsid());
  #endif

  WiFi.hostname("RfHub");
  WiFi.begin(getWifiSsid(), getWifiPwd());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
    #ifdef DEBUG
      Serial.print(".");
    #endif
  }

  #ifdef DEBUG
    Serial.println("");
    Serial.println("Connected to WiFi");
    Serial.print(WiFi.hostname());
    Serial.print(" IP address: ");
    Serial.println(WiFi.localIP());
  #endif
}
