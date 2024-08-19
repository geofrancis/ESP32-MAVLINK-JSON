
void loop() {

  //sendtext();
  FetchMavlink();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    //domoticz
    sensors();
    MAVLINK_HB();
    Fetchdomoticz();
    senddomoticz();
    setMODE();
    setRELAY();
    wificheck();


   
  }
}


void wificheck(){

  unsigned long wificurrent = millis();
// if WiFi is down, try reconnecting
if ((WiFi.status() != WL_CONNECTED) && (wificurrent - wifimillis >=wifiinterval)) {
  Serial.print(millis());
  Serial.println("Reconnecting to WiFi...");
  WiFi.disconnect();
  WiFi.reconnect();
  wifimillis = wificurrent;


 

  uint8_t system_id = 1;
  uint8_t component_id = 191;
  uint8_t severity = 1;
  uint16_t id = 0;
  uint8_t chunk_seq = 0;

  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  mavlink_msg_statustext_pack(system_id, component_id, &msg, 0, "WIFI Reconnect", id, chunk_seq);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial2.write(buf, len);




}
}