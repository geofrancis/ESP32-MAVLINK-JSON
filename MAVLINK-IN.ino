
void FetchMavlink() {
  mavlink_message_t msg;
  mavlink_status_t status;

  while (Serial.available()) {
    uint8_t c = Serial.read();

    //Get new message
    if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {

      //Handle new message from autopilot
      switch (msg.msgid) {

        case MAVLINK_MSG_ID_GPS_RAW_INT:
          {
            mavlink_gps_raw_int_t packet;
            mavlink_msg_gps_raw_int_decode(&msg, &packet);

            mavlink_gps_raw_int_t datagps;
            mavlink_msg_gps_raw_int_decode(&msg, &datagps);
            //Serial.println("PX HB");
            // Serial.println("GPS Data ");
            //  Serial.print("time usec: ");
            // Serial.println(datagps.time_usec);
            //  Serial.print("lat: ");
            //  Serial.println(datagps.lat);
            GPSLAT = (datagps.lat);
            Serial.print("lon: ");
            Serial.println(datagps.lon);
            GPSLON = (datagps.lon);
            Serial.print("alt: ");
            //   Serial.println(datagps.alt);
            //  Serial.print("Sattelite visible: ");
            //   Serial.println(datagps.satellites_visible);
            satelites = (datagps.satellites_visible);
            //   Serial.println(datagps.eph);
            HDOP = (datagps.eph);
            //Serial.println(datagps.epv);
          }
          break;

        case MAVLINK_MSG_ID_SYS_STATUS:  // #1: SYS_STATUS
          {
            //mavlink_message_t* msg;
            mavlink_sys_status_t sys_status;
            mavlink_msg_sys_status_decode(&msg, &sys_status);
            //   Serial.print("PX SYS STATUS: ");
            //   Serial.print("[Bat (V): ");
            //   Serial.print(sys_status.voltage_battery);
            VOLTS = (sys_status.voltage_battery);
            //   Serial.print(sys_status.voltage_battery / 1000);
            //   Serial.print("], [Bat (A): ");
            //   Serial.print(sys_status.current_battery);
            AMPS = (sys_status.current_battery);
            //   Serial.print("], [Comms loss (%): ");
            //   Serial.print(sys_status.drop_rate_comm);
            //comdroprate = (sys_status.drop_rate_comm);
            //      Serial.println("]");
          }


          break;

        case MAVLINK_MSG_ID_ATTITUDE:  // #30
          {

            mavlink_attitude_t attitude;
            mavlink_msg_attitude_decode(&msg, &attitude);
            //    Serial.println("PX ATTITUDE");
            //     Serial.println(attitude.roll);
            roll = (attitude.roll);
            pitch = (attitude.pitch);
            yaw = (attitude.yaw);
            //if (attitude.roll > 1) leds_modo = 0;
            //else if (attitude.roll < -1) leds_modo = 2;
            //else leds_modo = 1;
          }

          break;

        case MAVLINK_MSG_ID_RC_CHANNELS_RAW:  // #35
          {
            mavlink_rc_channels_raw_t chs;
            mavlink_msg_rc_channels_raw_decode(&msg, &chs);
            //   Serial.print("Chanel 6 (3-Kanal Schalter): ");
            //    Serial.println(chs.chan6_raw);
          }

          break;

        case MAVLINK_MSG_ID_RC_CHANNELS_SCALED:  // #35
          {
            mavlink_rc_channels_scaled_t RCCHANNEL;
            mavlink_msg_rc_channels_scaled_decode(&msg, &RCCHANNEL);
            //  Serial.print("Chanel 6 (3-Kanal Schalter): ");
            // int RAW_SERVO = RCCHANNEL.chan6_scaled;
            // Serial.println(RAW_SERVO);
            // Serial.print("Chanel 5 (Schub): ");
            //  Serial.println(RCCHANNEL.chan5_scaled);
            //  Serial.print("Drei Kanal: ");
            //  Serial.println(mavlink_msg_rc_channels_scaled_get_chan6_scaled(&msg));
            //  Serial.print("Schub: ");
            //  Serial.println(mavlink_msg_rc_channels_scaled_get_chan5_scaled(&msg));
          }

          break;

        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:  // #30
          {
            mavlink_global_position_int_t Position;
            //mavlink_msg_attitude_decode(&msg, &attitude);
            mavlink_msg_global_position_int_decode(&msg, &Position);
          }
          break;

        case MAVLINK_MSG_ID_HEARTBEAT:  // #0: Heartbeat
          {

            mavlink_heartbeat_t hb;
            mavlink_msg_heartbeat_decode(&msg, &hb);
            //Serial.print("Flight Mode: ");
            // Serial.println(hb.custom_mode);
            // Serial.print("Type: ");
            // Serial.println(hb.type);
            //  Serial.print("Autopilot: ");
            //  Serial.println(hb.autopilot);
            //   Serial.print("Base Mode: ");
            //   Serial.println(hb.base_mode);
            fcmodein = (hb.custom_mode);
            //  Serial.print("System Status: ");
            //  Serial.println(hb.system_status);
            //     Serial.print("Mavlink Version: ");
            //     Serial.println(hb.mavlink_version);
            Serial.println();
          }
          break;

       
        case MAVLINK_MSG_ID_RC_CHANNELS:  // #35
          {
            mavlink_rc_channels_t chs;
            mavlink_msg_rc_channels_decode(&msg, &chs);
            Serial.print("Chanel 8: ");
            RCIN = (chs.chan8_raw);
            Serial.println(chs.chan1_raw);
          }
          break;
        case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:  // #35
          {
            mavlink_servo_output_raw_t SERVOCHANNEL;
            mavlink_msg_servo_output_raw_decode(&msg, &SERVOCHANNEL);
            //  Serial.println(SERVOCHANNEL.servo1_raw);
            //  Serial.println(SERVOCHANNEL.servo2_raw);
            //  Serial.println(SERVOCHANNEL.servo3_raw);
            //  Serial.print("Chanel 1 (raw): ");
          }
          break;

        case MAVLINK_MSG_ID_MISSION_CURRENT:
          {
            mavlink_mission_current_t RPNUM;
            mavlink_msg_mission_current_decode(&msg, &RPNUM);
            wp_number = (RPNUM.seq);
            Serial.print("wp_number ");
            Serial.println(wp_number);
            break;

            case MAVLINK_MSG_ID_VFR_HUD:
              {
                mavlink_vfr_hud_t vfrhud;
                mavlink_msg_vfr_hud_decode(&msg, &vfrhud);
                Serial.print("Ground Speed: ");
                Serial.println(vfrhud.groundspeed);
                Serial.print("Heading ");
                Serial.println(vfrhud.heading);
                gps_Vel = vfrhud.groundspeed;
                gps_Head = vfrhud.heading;
              }
            case MAVLINK_MSG_ID_STATUSTEXT:  //  #253  https://mavlink.io/en/messages/common.html#STATUSTEXT
              {
                mavlink_statustext_t packet;
                mavlink_msg_statustext_decode(&msg, &packet);
                Serial.print("=STATUSTEXT");
                Serial.print(" severity:");
                Serial.print(packet.severity);
                Serial.print(" text:");
                Serial.print(packet.text);
                message=(packet.text);
                break;
              }
          }
      }
    }
  }
}
/*








              /*
case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:  // #35
  {
    mavlink_servo_output_raw_t SERVOCHANNEL;
    mavlink_msg_servo_output_raw_decode(&msg, &SERVOCHANNEL);
    Serial.println(SERVOCHANNEL.servo1_raw);
    Serial.println(SERVOCHANNEL.servo2_raw);
    Serial.println(SERVOCHANNEL.servo3_raw);
    servo1 = (SERVOCHANNEL.servo1_raw);
    servo2 = (SERVOCHANNEL.servo2_raw);
    servo3 = (SERVOCHANNEL.servo3_raw);
    Serial.print("Chanel 1 (raw): ");
  }

*/

/*
case MAVLINK_MSG_ID_RANGEFINDER:  // #17
  {
    mavlink_rangefinder_t packet;
    mavlink_msg_rangefinder_get_distance(&msg, &packet);
    Serial.println(packet.distance);
    Serial.print("packet distance ");
  }
  



              void pixhawk_Watchdog()  //Request Pixhawk to send HeartBeats and check for response
              {
                unsigned long current_hb_Millis = millis();

                if (pixhawk_Watchdog_switch == 1 && pixhawk_HBsatswitch == 1) {

                  //Non-blocking timer function
                  if (current_hb_Millis - previous_hb_Millis >= HB_Interval) {
                    previous_hb_Millis = current_hb_Millis;  // save the last time you collected data

                    //Check for Pixhawk heartbeats
                    Serial.println("\nChecking for Pixhawk Heartbeats... ");
                    hb_collection_flag = 1;
                    mavLinkHB_switch = 1;
                  }

                  //Non-blocking timer function
                  //Turn off watchdog routine according to HB_Turnoff_interval variable
                  if (((current_hb_Millis - previous_hb_Millis) >= hb_Turnoff_interval) && (hb_collection_flag == 1)) {
                    Serial.println("\nEnding HB watchdog... ");
                    hb_collection_flag = 0;
                    mavLinkHB_switch = 0;

                    //check to see if HB collected is more than 0
                    if (px4_Hb > 0) {
                      Serial.print("\nHBs received: ");
                      Serial.println(px4_Hb);
                      px4_Hb = 0;
                      HBwatchdog_Counter = 0;  //reset watchdog reset counter
                    }

                    else {
                      HBwatchdog_Counter++;
                      Serial.println("\nNO HBs received setting counter: ");
                      Serial.println(HBwatchdog_Counter);

                      //If havent received HBs 3x then POWER CYLE Relay
                      if (HBwatchdog_Counter >= 3) {
                        Serial.println("\nPower cycling Pixhawk and resetting counter");
                        HBwatchdog_Counter = 0;

                        //Begin Pixhawk and Servo power cycle
                        previous_pixhawk_servo_Millis = millis();
                        digitalWrite(19, LOW);  //Turn off power to pixhawk
                        pixhawk_servo_Switch = 1;
                        Serial.println("Pixhawk and Servo Power Off");

                        px4_Resetcounter++;
                        Serial.print("\nIncrementing Total number of HB Failures: ");
                        Serial.println(px4_Resetcounter);

                        //Reset global variable to 0 if too large (sent via modem)
                        if (px4_Resetcounter >= 99) {
                          Serial.println("\nresetting global HB failure counter");
                          px4_Resetcounter = 0;
                        }
                      }
                    }
                  }
                }
              }


*/