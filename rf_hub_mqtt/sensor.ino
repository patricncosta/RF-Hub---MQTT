//typedef struct Sensor Sensor;
const uint8_t MAX_SENSORS_ARRAY_SIZE = 255;
int SENSORS_ARR_SIZE = -1;
// Hub Name
static const String HUB_NAME = "RfHub";
// Divisions
static const String OFFICE = "office";
static const String KITCHEN = "kitchen";
static const String BEDROOM_CARINA = "bedroom_carina";
static const String BEDROOM_PATRIC = "bedroom_patric";
// Device Classes
static const String OPENING = "opening";
static const String MOTION = "motion";
static const String WINDOW = "window";
static const String DOOR = "door";

Sensor arrSensor[MAX_SENSORS_ARRAY_SIZE];

Sensor getNewSensor() {
  Sensor sensor;
  sensor.name = "";
  sensor.division = "";
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
  sensor.enabled = false;
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

  /***********************/
  /******* WINDOWS *******/
  /***********************/

  // 1
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 495987;
  sensor.payload_off = 495993;
  addSensor(sensor);

  // 2
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 614627;
  sensor.payload_off = 614633;
  addSensor(sensor);

  // 3
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 546691;
  sensor.payload_off = 546697;
  addSensor(sensor);
  
  // 4
  sensor = getNewSensor();
  sensor.name = "Fridge Door";
  sensor.unique_id = "fridge_door";
  sensor.division = KITCHEN;
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 614627;
  sensor.payload_off = 614633;
  sensor.enabled = true;
  addSensor(sensor);

  // 5
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 554243;
  sensor.payload_off = 554249;
  addSensor(sensor);

  // 6
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 526115;
  sensor.payload_off = 526121;
  addSensor(sensor);

  // 7
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 634835;
  sensor.payload_off = 634841;
  addSensor(sensor);

  // 8
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 596083;
  sensor.payload_off = 596089;
  addSensor(sensor);

  // 9
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 586723;
  sensor.payload_off = 586729;
  addSensor(sensor);

  // 10
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 359267;
  sensor.payload_off = 359273;
  addSensor(sensor);

  // 11
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 549123;
  sensor.payload_off = 549129;
  addSensor(sensor);

  // 12
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 618531;
  sensor.payload_off = 618537;
  addSensor(sensor);

  // 13
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 546675;
  sensor.payload_off = 546681;
  addSensor(sensor);

  // 14
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 467091;
  sensor.payload_off = 467097;
  addSensor(sensor);

  // 15
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 506755;
  sensor.payload_off = 506761;
  addSensor(sensor);

  // 16
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 606819;
  sensor.payload_off = 606825;
  addSensor(sensor);

  // 17
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 584419;
  sensor.payload_off = 584425;
  addSensor(sensor);

  // 18
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 425267;
  sensor.payload_off = 425273;
  addSensor(sensor);

  // 19
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = OPENING;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 603331;
  sensor.payload_off = 603337;
  addSensor(sensor);

  // 20
  sensor.name = "Office Door";
  sensor.unique_id = "office_door";
  sensor.division = OFFICE;
  sensor.device_class = DOOR;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 9635587;
  sensor.payload_off = 9635593;
  sensor.enabled = true;
  addSensor(sensor);


  /***********************/
  /******** DOORS ********/
  /***********************/
  // 1
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = MOTION;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 3100774;
  addSensor(sensor);

  // 2
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = MOTION;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 6181478;
  addSensor(sensor);

  // 3
  sensor = getNewSensor();
  sensor.name = "[SENSOR NAME]";
  sensor.unique_id = "[SENSOR UNIQUE ID]]";
  sensor.division = "[SENSOR DIVISION]";
  sensor.device_class = MOTION;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 3072102;
  addSensor(sensor);

  // 4
  sensor = getNewSensor();
  sensor.name = "Bedroom Patric";
  sensor.unique_id = "bedroom_patric";
  sensor.division = BEDROOM_PATRIC;
  sensor.device_class = MOTION;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 6380198;
  sensor.enabled = true;
  addSensor(sensor);

  // 5
  sensor = getNewSensor();
  sensor.name = "Bedroom Carina";
  sensor.unique_id = "bedroom_carina";
  sensor.division = BEDROOM_CARINA;
  sensor.device_class = MOTION;
  sensor.mqtt_status_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/state";
  sensor.mqtt_info_topic = "home/" + sensor.division + "/" + sensor.unique_id + "/info";
  sensor.parent_device = HUB_NAME;
  sensor.payload_on = 292902;
  sensor.enabled = true;
  addSensor(sensor);

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
  
  payload.replace("[SENSOR_NAME]", sensor.name);
  payload.replace("[UNIQUE_ID]", sensor.unique_id);
  payload.replace("[MQTT_TOPIC]", sensor.mqtt_status_topic);
  payload.replace("[PAYLOAD_ON]", String(sensor.payload_on));
  payload.replace("[PAYLOAD_OFF]", String(sensor.payload_off));
  payload.replace("[DEVICE_CLASS]", sensor.device_class);
  //payload.replace("[DEVICE_INFO]", "\"ids\":\"" + sensor.unique_id + "\",\"via_device\":\"" + HUB_NAME + "\"");
  welcome_topic.replace("[DIVISION]", sensor.division + "/" + sensor.unique_id);
  publishToMqtt(welcome_topic, payload);
}

void publishDiscoveryMsgs() {
  for (uint16_t i = 0; i <= SENSORS_ARR_SIZE; i++) {
    if(!arrSensor[i].enabled) {
      continue;
    }
    
    publishDiscoveryMsg(arrSensor[i]);
  };
}