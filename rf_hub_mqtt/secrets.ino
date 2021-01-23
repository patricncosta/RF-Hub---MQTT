/******* WIFI ********/
#define wifi_ssid ""
#define wifi_password ""
/*******  MQTT CONNECTION *******/
#define mqtt_user ""
#define mqtt_password ""
#define mqtt_server ""
const uint16_t mqtt_port = 1883;

char* getMqttUser() {
  return mqtt_user;
}

char* getMqttPwd() {
  return mqtt_password;
}

char* getMqttServer() {
  return mqtt_server;
}

uint16_t getMqttPort() {
  return mqtt_port;
}

char* getWifiSsid() {
  return wifi_ssid;
}

char* getWifiPwd() {
  return wifi_password;
}
