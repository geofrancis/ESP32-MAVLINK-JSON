#include <Wire.h>
#include <WiFi.h>

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "mavlink/common/mavlink.h"
#include "mavlink/common/mavlink_msg_rc_channels.h"
#include "mavlink/common/mavlink_msg_mission_current.h"

// WiFi settings
const char ssid[] = "xxxxx";
const char password[] = "xxxxxxx";

char* message;


//int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiClient client;  // or WiFiClientSecure for HTTPS
HTTPClient http;


unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 2000;        // inte

// domoticz

const char* domoticz_server = "youdomain.org";  //Domoticz port
int port = 9999;                                          //Domoticz port


int ADC1 = 0;
int ADC2 = 0;
int ADC3 = 0;

int RCIN =1500;
int MODE =0;


int MAINBATTAVG;
float MAINBATT = 0;
float BATT1 = 0;
float BATT2 = 0;
float VOLTS = 0;
float AMPS = 0;
int flightmode = 0;
double GPSLAT = 0;
double GPSLON = 0;
int satelites = 0;
int comdroprate = 60;

float roll = 0;
float pitch = 0;
float yaw = 0;
float speed = 0;
float heading = 0;
int rangefinder1 = 0;
int rangefinder2 = 0;


int servo1 = 0;
int servo2 = 0;
int servo3 = 0;


int wp_number;
int wp_total;
int mission_state;
int mission_mode;



float HDOP;
//MODE CHANGE
int mode;
int fcmode;
int fcmodein;

uint8_t gps_Fix = 0;
int32_t gps_Lat = 0;
int32_t gps_Long = 0;
uint16_t gps_Vel = 0;
uint16_t gps_Head = 0;
uint16_t sys_Bat = 0;
uint16_t sys_Bcur = 0;
int8_t sys_Brem = 0;




//relay control
int powerselect = 0;
int FCPOWER = 0;
int WIFICAM = 0;
int PROX = 0;
int MAINPOWER = 0;
int MOTPOWER = 0;
int LIGHTS = 0;
int INDICATOR = 0;
int horn = 0;


//wifireconnect 

unsigned long wifimillis = 0;
unsigned long wifiinterval = 30000;
