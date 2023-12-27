#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "mavlink/common/mavlink.h"
#include "mavlink/common/mavlink_msg_rc_channels.h"


const char* ssid     = "xxxxxx";
const char* password = "xxxxxxxxx";

//int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiClient client;  // or WiFiClientSecure for HTTPS
HTTPClient http;


unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 3000;           // inte

// domoticz
const char * domoticz_server = "10.0.0.20"; //Domoticz port
int port = 8080; //Domoticz port
int idx = 366; //IDX for virtual sensor, found in Setup -> Devices

int voltidx = 366;
int currentidx = 31;
int flightmodeidx = 32;
int GPSLATidx = 33;
int SATidx = 34;
int comdroprateidx = 35;
int rollidx = 36;
int pitchidx = 37;

float VOLTAGE = 12;
float amps = 23;
int flightmode = 99;
double GPSLAT = 0.000001;
double GPSLON = 0.000001;
int satelites  = 15 ;
int comdroprate = 60;

float roll   = 0;
float pitch = 0;
int rangefinder1 = 0;
int rangefinder2 = 0;


int servo1 = 0;
int servo2 = 0;
int servo3 = 0;

int test;



void setup()
{
  //Initialize the I2C sensors and ping them
  WiFi.begin(ssid, password);
  Serial2.begin(115200); //RXTX from Pixhawk (Port 19,18 Arduino Mega)
  Serial.begin(115200); //Main serial port for console output
  request_datastream();
}

void loop()
{
  //Get readings from all sensors

  MavLink_receive();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    getWeather();
//    getsunrise();
  //  getwaypoint()
    sendvoltage();
    sendcurrent();
    sendflightmode();
    sendGPSLAT();
    sendGPSLAT();

    //setmode_Auto();
  }


}

void getWeather()
{
  


// Send request
http.useHTTP10(true);
http.begin(client, "http://10.0.0.20:8000/json.htm?type=command&param=getdevices&rid=97");
http.GET();

// Parse response
DynamicJsonDocument doc(2048);
deserializeJson(doc, http.getStream());

// Read values
test = doc["result"][0]["BatteryLevel"];
Serial.println(test);



// Disconnect
http.end();

}


void sendvoltage()
{
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VOLTAGE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(idx);
    client.print("&nvalue=0&svalue=");
    client.print(VOLTAGE);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}

void sendcurrent()
{
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(idx);
    client.print("&nvalue=0&svalue=");
    client.print(amps);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}

void sendflightmode()
{
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(idx);
    client.print("&nvalue=0&svalue=");
    client.print(flightmode);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}

void sendGPSLAT()
{
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(idx);
    client.print("&nvalue=0&svalue=");
    client.print(GPSLAT,7);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}
void sendGPSLON()
{
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(idx);
    client.print("&nvalue=0&svalue=");
    client.print(GPSLON,7 );
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}


void MavLink_receive()
{
  mavlink_message_t msg;
  mavlink_status_t status;

  while (Serial2.available())
  {
    uint8_t c = Serial2.read();

    //Get new message
    if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status))
    {

      //Handle new message from autopilot
      switch (msg.msgid)
      {

        case MAVLINK_MSG_ID_GPS_RAW_INT:
          {
            mavlink_gps_raw_int_t packet;
            mavlink_msg_gps_raw_int_decode(&msg, &packet);

            mavlink_gps_raw_int_t datagps;
            mavlink_msg_gps_raw_int_decode (&msg, &datagps);
            //Serial.println("PX HB");
            Serial.println("GPS Data ");
            Serial.print("time usec: ");
            Serial.println(datagps.time_usec);
            Serial.print("lat: ");
            Serial.println(datagps.lat);
            GPSLAT = (datagps.lat);
            Serial.print("lon: ");
            Serial.println(datagps.lon);
            GPSLON = (datagps.lon);
            Serial.print("alt: ");
            Serial.println(datagps.alt);
            Serial.print("Sattelite visible: ");
            Serial.println(datagps.satellites_visible);
            satelites = (datagps.satellites_visible);
            //Serial.println(datagps.eph);
            //Serial.println(datagps.epv);

          }
          break;

        case MAVLINK_MSG_ID_SYS_STATUS:  // #1: SYS_STATUS
          {
            //mavlink_message_t* msg;
            mavlink_sys_status_t sys_status;
            mavlink_msg_sys_status_decode(&msg, &sys_status);
            Serial.print("PX SYS STATUS: ");
            Serial.print("[Bat (V): ");
            Serial.print(sys_status.voltage_battery);
            Serial.print("], [Bat (A): ");
            Serial.print(sys_status.current_battery);
            Serial.print("], [Comms loss (%): ");
            Serial.print(sys_status.drop_rate_comm);
            comdroprate = (sys_status.drop_rate_comm);
            Serial.println("]");
          }


          break;

        case MAVLINK_MSG_ID_ATTITUDE:  // #30
          {

            mavlink_attitude_t attitude;
            mavlink_msg_attitude_decode(&msg, &attitude);
            Serial.println("PX ATTITUDE");
            Serial.println(attitude.roll);
            roll = (attitude.roll);
            pitch = (attitude.pitch);
            //if (attitude.roll > 1) leds_modo = 0;
            //else if (attitude.roll < -1) leds_modo = 2;
            //else leds_modo = 1;
          }

          break;

        case MAVLINK_MSG_ID_RC_CHANNELS_RAW:  // #35
          {
            mavlink_rc_channels_raw_t chs;
            mavlink_msg_rc_channels_raw_decode(&msg, &chs);
            Serial.print("Chanel 6 (3-Kanal Schalter): ");
            Serial.println(chs.chan6_raw);
          }

          break;

        case MAVLINK_MSG_ID_RC_CHANNELS_SCALED:  // #35
          {
            mavlink_rc_channels_scaled_t RCCHANNEL;
            mavlink_msg_rc_channels_scaled_decode(&msg, &RCCHANNEL);
            Serial.print("Chanel 6 (3-Kanal Schalter): ");
            int RAW_SERVO = RCCHANNEL.chan6_scaled;
            Serial.println(RAW_SERVO);
            Serial.print("Chanel 5 (Schub): ");
            Serial.println(RCCHANNEL.chan5_scaled);
            Serial.print("Drei Kanal: ");
            Serial.println(mavlink_msg_rc_channels_scaled_get_chan6_scaled(&msg));
            Serial.print("Schub: ");
            Serial.println(mavlink_msg_rc_channels_scaled_get_chan5_scaled(&msg));
          }

          break;

        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:  // #30
          {
            mavlink_global_position_int_t Position;
            //mavlink_msg_attitude_decode(&msg, &attitude);
            mavlink_msg_global_position_int_decode(&msg, &Position);

            break;

          case MAVLINK_MSG_ID_HEARTBEAT:  // #0: Heartbeat
            {

              mavlink_heartbeat_t hb;
              mavlink_msg_heartbeat_decode(&msg, &hb);

              Serial.print("\nFlight Mode: (10 ");
              Serial.println(hb.custom_mode);
              Serial.print("Type: ");
              Serial.println(hb.type);
              Serial.print("Autopilot: ");
              Serial.println(hb.autopilot);
              Serial.print("Base Mode: ");
              Serial.println(hb.base_mode);
              Serial.print("System Status: ");
              Serial.println(hb.system_status);
              Serial.print("Mavlink Version: ");
              Serial.println(hb.mavlink_version);
              Serial.println();
            }
            break;

          case MAVLINK_MSG_ID_STATUSTEXT: //  #253  https://mavlink.io/en/messages/common.html#STATUSTEXT
            {
              mavlink_statustext_t packet;
              mavlink_msg_statustext_decode(&msg, &packet);
              Serial.print("=STATUSTEXT");
              Serial.print(" severity:");
              Serial.print(packet.severity);
              Serial.print(" text:");
              Serial.print(packet.text);
              break;
            }
          case MAVLINK_MSG_ID_RC_CHANNELS:  // #35
            {
              mavlink_rc_channels_t chs;
              mavlink_msg_rc_channels_decode(&msg, &chs);
              Serial.print("Chanel 1: ");
              Serial.println(chs.chan1_raw );
            }
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

            /*      case MAVLINK_MSG_ID_RANGEFINDER :  // #173
                 {
                   mavlink_rangefinder_t  packet;
                   mavlink_msg_rangefinder_get_distance(&msg, &packet);
                   Serial.println(packet.distance);
                   Serial.print("packet distance ");
               }
            */
          }
      }
    }
  }
}








void request_datastream() {
  //Request Data from Pixhawk
  uint8_t _system_id = 255; // id of computer which is sending the command (ground control software has id of 255)
  uint8_t _component_id = 2; // seems like it can be any # except the number of what Pixhawk sys_id is
  uint8_t _target_system = 1; // Id # of Pixhawk (should be 1)
  uint8_t _target_component = 0; // Target component, 0 = all (seems to work with 0 or 1
  uint8_t _req_stream_id = MAV_DATA_STREAM_ALL;
  uint16_t _req_message_rate = 0x08; //number of times per second to request the data in hex
  uint8_t _start_stop = 1; //1 = start, 0 = stop



  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_request_data_stream_pack(_system_id, _component_id, &msg, _target_system, _target_component, _req_stream_id, _req_message_rate, _start_stop);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);  // Send the message (.write sends as bytes)

  Serial2.write(buf, len); //Write data to serial port
}


/*
  void setmode_Auto() {
  //Set message variables
  uint8_t _system_id = 255; // id of computer which is sending the command (ground control software has id of 255)
  uint8_t _component_id = 2; // seems like it can be any # except the number of what Pixhawk sys_id is
  uint8_t _target_system = 1; // Id # of Pixhawk (should be 1)
  uint8_t _base_mode = 1;
  uint32_t _custom_mode = 10; //10 = auto mode


    Flight / Driving Modes (change custom mode above)
    0 - Manual
    1 - Acro
    3 - Steering
    4 - Hold
    5 - Loiter
    6 - Follow
    7 - Simple
    10  Auto
    11  RTL
    12  SmartRTL
    15  Guided


  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_set_mode_pack(_system_id, _component_id, &msg, _target_system, _base_mode, _custom_mode);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);  // Send the message (.write sends as bytes)
  Serial.print("\nsending set mode command...");
  Serial2.write(buf, len); //Write data to serial port
  }




  void sendtext() {


  uint8_t system_id = 1;
  uint8_t component_id = 2;
  uint8_t severity = 1;

  uint16_t id = 0;
  uint8_t chunk_seq = 0;



  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  mavlink_msg_statustext_pack(system_id, component_id, &msg, 0, "TEST", id, chunk_seq);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial2.write(buf, len);
  }
*/
