
void Fetchdomoticz() {

  // READ FLIGHT MODE
  http.useHTTP10(true);
  http.begin(client, "http://yourserver:port/json.htm?type=command&param=getdevices&rid=324");
  http.GET();
  // Parse response
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, http.getStream());

  // Read values
  mode = doc["result"][0]["Level"];
  //Serial.print("dmmode ");
  //Serial.println(mode);
  http.end();

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(397);
    client.print("&nvalue=0&svalue=");
    client.print(mode);
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




 //Flight Controller
  http.useHTTP10(true);
  http.begin(client, "yourserver:port/json.htm?type=command&param=getdevices&rid=1");
  http.GET();
  deserializeJson(doc, http.getStream());
  FCPOWER = doc["result"][0]["Level"];
 // Serial.print("FCPOWER ");
 // Serial.println(FCPOWER);
  http.end();


  
 //Camera
  http.useHTTP10(true);
  http.begin(client, "http://yourserver:port/json.htm?type=command&param=getdevices&rid=2");
  http.GET();
  deserializeJson(doc, http.getStream());
  WIFICAM = doc["result"][0]["Level"];
  //Serial.print("WIFICAM ");
 // Serial.println(WIFICAM);
  http.end();

  
 //LIDAR
  http.useHTTP10(true);
  http.begin(client, "http://yourserver:port/json.htm?type=command&param=getdevices&rid=3");
  http.GET();
  deserializeJson(doc, http.getStream());
  PROX = doc["result"][0]["Level"];
  Serial.print("PROX ");
  Serial.println(PROX);
  http.end();

 //Main Power
  http.useHTTP10(true);
  http.begin(client, "http://yourserver:port/json.htm?type=command&param=getdevices&rid=4");
  http.GET();
  deserializeJson(doc, http.getStream());
  MAINPOWER = doc["result"][0]["Level"];
  //Serial.print("MAINPOWER ");
  //Serial.println(MAINPOWER);
  http.end();



//Motor power
  http.useHTTP10(true);
  http.begin(client, "http://yourserver:port/json.htm?type=command&param=getdevices&rid=5");
  http.GET();
  deserializeJson(doc, http.getStream());
  MOTPOWER = doc["result"][0]["Level"];
  //Serial.print("MOTPOWER ");
  //Serial.println(MOTPOWER);
  http.end();



//Lights

  http.useHTTP10(true);
  http.begin(client, "http://yourserver:port/json.htm?type=command&param=getdevices&rid=6");
  http.GET();
  deserializeJson(doc, http.getStream());
  LIGHTS = doc["result"][0]["Level"];
 //Serial.print("LIGHTS ");
 // Serial.println(LIGHTS);
  http.end();

//Indicators

  http.useHTTP10(true);
  http.begin(client, "http://yourserver:port/json.htm?type=command&param=getdevices&rid=7");
  http.GET();
  deserializeJson(doc, http.getStream());
  INDICATOR = doc["result"][0]["Level"];
 // Serial.print("INDICATOR ");
 // Serial.println(INDICATOR);
  http.end();


}
