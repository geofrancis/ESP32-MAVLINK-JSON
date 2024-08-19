
void senddomoticz() {

  sendvoltage();
  sendcurrent();
  sendflightmode();
  sendGPSLAT();
  sendGPSLON();
  sendPITCH();
  sendROLL();
  sendYAW();
  sendSATS();
  sendHDOP();
  sendSPD();
  sendWP();
  send_Main_Batt();
  send_batt1();
  send_batt2();
  modeselect();
  send_text();
}




void sendvoltage() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VOLTAGE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(8);
    client.print("&nvalue=0&svalue=");
    client.print(VOLTS / 1000);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}


void sendcurrent() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(9);
    client.print("&nvalue=0&svalue=");
    client.print(AMPS / 100);
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

void sendflightmode() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(10);
    client.print("&nvalue=0&svalue=");
    client.print(fcmodein);
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

void confirmmodechange() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(11);
    client.print("&nvalue=0&svalue=");
    client.print(0);
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



void send_text() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(12);
    client.print("&nvalue=0&svalue=");
    client.print(message);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}



void sendGPSLAT() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(13);
    client.print("&nvalue=0&svalue=");
    client.print((GPSLAT/10000000), 7);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}

void sendGPSLON() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(14);
    client.print("&nvalue=0&svalue=");
    client.print((GPSLON/10000000), 7);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}



void sendPITCH() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(15);
    client.print("&nvalue=0&svalue=");
    client.print(pitch, 3);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}


void sendROLL() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(16);
    client.print("&nvalue=0&svalue=");
    client.print(roll, 3);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}




void sendYAW() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(17);
    client.print("&nvalue=0&svalue=");
    client.print(yaw, 3);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}


void sendSATS() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(18);
    client.print("&nvalue=0&svalue=");
    client.print(satelites, 0);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}



void sendHDOP() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(19);
    client.print("&nvalue=0&svalue=");
    client.print(HDOP, 0);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}




void sendSPD() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(20);
    client.print("&nvalue=0&svalue=");
    client.print(gps_Vel, 0);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}





void sendWP() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(21);
    client.print("&nvalue=0&svalue=");
    client.print(wp_number, 0);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}


void send_Main_Batt() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(22);
    client.print("&nvalue=0&svalue=");
    client.print((MAINBATT / 10));
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}


void send_batt1() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(23);
    client.print("&nvalue=0&svalue=");
    client.print((BATT1 / 100));
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}



void send_batt2() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(24);
    client.print("&nvalue=0&svalue=");
    client.print((BATT2 / 100));
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}




void modeselect() {

  if (RCIN <= 1000) { MODE = 0; }
  if (RCIN > 1001 && RCIN < 1100) { MODE = 10; }
  if (RCIN > 1101 && RCIN < 1200) { MODE = 20; }
  if (RCIN > 1201 && RCIN < 1300) { MODE = 30; }
  if (RCIN > 1301 && RCIN < 1400) { MODE = 40; }
  if (RCIN > 1401 && RCIN < 1500) { MODE = 50; }
  if (RCIN > 1501 && RCIN < 1600) { MODE = 60; }
  if (RCIN > 1601 && RCIN < 1700) { MODE = 70; }
  if (RCIN > 1701 && RCIN < 1800) { MODE = 80; }
  if (RCIN > 1801 && RCIN < 1900) { MODE = 90; }
  if (RCIN > 1901 && RCIN < 2000) { MODE = 100;}
   else if (RCIN >= 2000) {
    MODE = 110;
  }


  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(25);
    client.print("&nvalue=0&svalue=");
    client.print(MODE);
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