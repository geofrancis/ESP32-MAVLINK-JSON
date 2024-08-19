



void setMODE() {

  if (mode > 1)
  {
    Serial.println("mode change");

    if (mode == 10) { fcmode = 0; }
    if (mode == 20) { fcmode = 1; }
    if (mode == 30) { fcmode = 3; }
    if (mode == 40) { fcmode = 4; }
    if (mode == 50) { fcmode = 5; }
    if (mode == 60) { fcmode = 6; }
    if (mode == 70) { fcmode = 10; }
    if (mode == 80) { fcmode = 11; }
    if (mode == 90) { fcmode = 12; }
    if (mode == 100) { fcmode = 15; }

    Serial.print("MODE ");
    Serial.println(MODE);
   // Serial.print("mode ");
 //   Serial.println(mode);
    //Serial.print("fc mode ");
   // Serial.println(fcmode);
   // Serial.print("fc modein ");
   // Serial.println(fcmodein);


    //Set message variables
    uint8_t _system_id = 255;    // id of computer which is sending the command (ground control software has id of 255)
    uint8_t _component_id = 1;   // seems like it can be any # except the number of what Pixhawk sys_id is
    uint8_t _target_system = 1;  // Id # of Pixhawk (should be 1)
    uint8_t _base_mode = 1;
    uint32_t _custom_mode = fcmode;  //10 = auto mode

    // Initialize the required buffers
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    // Pack the message
    mavlink_msg_set_mode_pack(_system_id, _component_id, &msg, _target_system, _base_mode, _custom_mode);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);  // Send the message (.write sends as bytes)

    Serial.write(buf, len);  //Write data to serial port


    if (fcmode == fcmodein)
      ;
    {
      //mode = 0;
      sendflightmode();
      confirmmodechange();
    }
  }
}
