#include <RCSwitch.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

#define DEBUG 1

/****** MQTT TOPICS *******/
const String welcome_topic_template = "homeassistant/binary_sensor/[DIVISION]/config ";
const String unknown_code_topic = "home/other/unknown";
const String mqttTopicWindow = "home/[DIVISION]/window";
const String mqttTopicDoor = "home/[DIVISION]/door";
const String mqttTopicStateSuffix = "/state";
//const String mqttTopicInfoSuffix = "/info";
const String door_window_sensor_info = "{\"name\":\"Alfawise 433MHz Wireless Magnetic Door/Window Sensor - White\",\"sw_version\":\"rf_hub_mqtt 1.0.0 by Patric\",\"model\":\"433MHz Wireless Magnetic Door/Window Sensor - White\",\"manufacturer\":\"Alfawise\",\"via_device\":\"RfHub\"}";
const String discovery_payload_template = "{\"name\": \"[SENSOR_NAME]\", \"unique_id\": \"[UNIQUE_ID]\", \"device_class\": \"opening\", \"state_topic\": \"[MQTT_TOPIC]" + mqttTopicStateSuffix + "\", \"payload_on\": \"[PAYLOAD_ON]\", \"payload_off\": \"[PAYLOAD_OFF]\", \"device\": \"[DEVICE_INFO]\"}";
/***** NTP *****/
const long utcOffsetInSeconds = 0;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

long timeBetweenMessages = 1000 * 1; // Interval between messages sent to MQTT with the same code (1 second)
long lastMsg = 0;
long lastCodeSent = 0;

RCSwitch mySwitch = RCSwitch();
WiFiClient espClient;
PubSubClient client(espClient);

char* getMqttUser();
char* getMqttPwd();
char* getMqttServer();
uint16_t getMqttPort();
char* getWifiSsid();
char* getWifiPwd();

void setup() {   
  
  #ifdef DEBUG
    Serial.begin(115200);
  #endif

  mySwitch.enableReceive(D2);
  setup_wifi();
  client.setServer(getMqttServer(), getMqttPort());
  timeClient.begin();
}

String getTopicByCode(long code) {
  String topic = "";
  String division = "";
  
  /***** Opened Doors *****/
  topic = mqttTopicDoor;
  division = "office";
    
  if (code == 9635587) {
    topic.replace("[DIVISION]", division);
    return topic;
  }
  
  /***** Closed Doors *****/  
  if (code == 9635593) {
    topic.replace("[DIVISION]", division);
    return topic;
  }

  /***** Other *****/
  // ...

  // Unknown codes
  return unknown_code_topic;
}

void publishToMqtt(String topic, String payload) {
  
  #ifdef DEBUG
    Serial.print("Publishing payload ");
    Serial.print(payload);
    Serial.print(" to ");
    Serial.println(topic);
  #endif
  
  client.publish((char*) topic.c_str(), (char*) payload.c_str());
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
    long decimal = mySwitch.getReceivedValue();
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

      // Publish state      
      String payload = String(decimal);
      String stateTopic = topic + mqttTopicStateSuffix;
      publishToMqtt(stateTopic, payload);

      // Publish info on different topic
      /*payload = "{\"timestamp\": " + timeClient.getFormattedTime() + "\"}";
      String infoTopic = topic + mqttTopicInfoSuffix;
      publishToMqtt(infoTopic, payload);
      */

      lastCodeSent = decimal;
    }
  }
}

/*
 * Location: door, window, etc
 * Division: office, kitchen, etc
 * Name: Office Door
 * Payload On: RF code that sets the sensor on
 * Payload Off: RF code that sets the sensor off
 */
void publishDiscoveryMsg(String sensorDivision, String sensorLocation, String sensorName, String payloadOn, String payloadOff, String deviceInfo) {
  String payload = discovery_payload_template;
  String welcome_topic = welcome_topic_template;
  const String mqttTopicState = "home/" + sensorDivision + "/" + sensorLocation;
  
  payload.replace("[SENSOR_NAME]", sensorName);
  payload.replace("[UNIQUE_ID]", sensorDivision + "_" + sensorLocation);
  payload.replace("[MQTT_TOPIC]", mqttTopicState);
  payload.replace("[PAYLOAD_ON]", payloadOn);
  payload.replace("[PAYLOAD_OFF]", payloadOff);
  payload.replace("[DEVICE_INFO]", deviceInfo);
  welcome_topic.replace("[DIVISION]", sensorDivision + "/" + sensorLocation);
  publishToMqtt(welcome_topic, payload);
}

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
      // Office door
      publishDiscoveryMsg("office", "door", "Office Door", "9635587", "9635593", door_window_sensor_info);
      // ...
      
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
