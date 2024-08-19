void setup() {

  //Serial2.begin(115200, SERIAL_8N1, 5, 4);  //RXTX from Pixhawk (Port 19,18 Arduino Mega)
  Serial.begin(115200);                           //Main serial port for console output

  

  pinMode(17, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(23, OUTPUT);
  

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);

  request_datastream();

  // Connecting to a WiFi AP
  WiFi.begin(ssid, password);

  // Waiting until we connect to WiFi
  while (!WiFi.isConnected()) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print the IP address in the local network
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());



  // Synchronize system time via NTP
  configTime(9 * 60 * 60, 0, "time.google.com", "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");

  //Serial1.begin(9600);  //GPS
  //Serial2.begin(9600);        //Bluetooth



  digitalWrite(32, 0);
  digitalWrite(33, 0);
  digitalWrite(25, 0);
  digitalWrite(26, 0);
  digitalWrite(27, 0);
  digitalWrite(14, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
  //digitalWrite(19, 0);
  digitalWrite(23, 0);

  
  uint8_t system_id = 1;
  uint8_t component_id = 191;
  uint8_t severity = 1;
  uint16_t id = 0;
  uint8_t chunk_seq = 0;

  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  mavlink_msg_statustext_pack(system_id, component_id, &msg, 0, "ESP32 Relay Startup", id, chunk_seq);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial.write(buf, len);


}
