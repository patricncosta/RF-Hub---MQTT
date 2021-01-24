//typedef struct Sensor Sensor;
const uint8_t MAX_SENSORS_ARRAY_SIZE = 255;
int SENSORS_ARR_SIZE = -1;
// Hub Name
static const String HUB_NAME = "RfHub";
// Locations
static const String DOOR = "door";
static const String WINDOW = "window";
static const String FRIDGE_DOOR = "fridge_door";
// Divisions
static const String OFFICE = "office";
static const String KITCHEN = "kitchen";
// Device Classes
static const String OPENING = "opening";

Sensor arrSensor[MAX_SENSORS_ARRAY_SIZE];

Sensor getNewSensor() {
  Sensor sensor;
  sensor.name = "";
  sensor.division = "";
  sensor.location = "";
  sensor.unique_id = "";
  sensor.device_class = "";
  sensor.mqtt_status_topic = "";
  sensor.mqtt_info_topic = "";
  sensor.mqtt_availability_topic = "";
  sensor.parent_device = "";
  sensor.payload_on = 0;
  sensor.payload_off = 0;
  sensor.payload_low_battery = 0;
  sensor.extra_attributes_json = "";
  return sensor;
}

void addSensor(Sensor sensor) {
    if(SENSORS_ARR_SIZE == MAX_SENSORS_ARRAY_SIZE) {
        #ifdef DEBUG
            Serial.print("No more sensors can be added. Limit reached!");
        #endif
        return;
    };

    arrSensor[++SENSORS_ARR_SIZE] = sensor;

    #ifdef DEBUG
        Serial.print("Sensor ");
        Serial.print(sensor.name);
        Serial.print(" added to ");
        Serial.println(sensor.division);
    #endif
}

void createSensors() {
  int i = 0;
  Sensor sensor;

  sensor.name = "Office Door";
  sensor.unique_id = "office_door";
  sensor.division = OFFICE;
  sensor.location = DOOR;
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.location + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.location + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 495987;
  sensor.payload_off = 495993;
  addSensor(sensor);

  sensor = getNewSensor();
  sensor.name = "Fridge Door";
  sensor.unique_id = "fridge_door";
  sensor.division = KITCHEN;
  sensor.location = FRIDGE_DOOR;
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.location + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.location + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 614627;
  sensor.payload_off = 614633;
  addSensor(sensor);

  // ...

}

String getTopicByCode(uint32_t code) {

  String topic;
  uint16_t i = 0;
  while (i++ <= SENSORS_ARR_SIZE){
    Sensor sensor = arrSensor[i];
    if(code == sensor.payload_on || code == sensor.payload_off || code == sensor.payload_low_battery) {
      return sensor.mqtt_status_topic;
    };
  }

  // Unknown codes
  return unknown_code_topic;
}

void publishDiscoveryMsg(Sensor sensor) {
  // Check fields
  if(sensor.name == "") {
      #ifdef DEBUG
        Serial.println("Attempt to publish discovery of unnamed sensor");
      #endif

      return;
  }

  String payload = discovery_payload_template;
  String welcome_topic = welcome_topic_template;
  const String mqttTopicState = "home/" + sensor.division + "/" + sensor.location;
  
  payload.replace("[SENSOR_NAME]", sensor.name);
  payload.replace("[UNIQUE_ID]", sensor.division + "_" + sensor.location);
  payload.replace("[MQTT_TOPIC]", mqttTopicState);
  payload.replace("[PAYLOAD_ON]", String(sensor.payload_on));
  payload.replace("[PAYLOAD_OFF]", String(sensor.payload_off));
  //payload.replace("[DEVICE_INFO]", "\"ids\":\"" + sensor.division + "_" + sensor.location + "\",\"via_device\":\"" + HUB_NAME + "\"");
  welcome_topic.replace("[DIVISION]", sensor.division + "/" + sensor.location);
  publishToMqtt(welcome_topic, payload);
}

void publishDiscoveryMsgs() {
  for (uint16_t i = 0; i <= SENSORS_ARR_SIZE; i++){
    publishDiscoveryMsg(arrSensor[i]);
  };
}