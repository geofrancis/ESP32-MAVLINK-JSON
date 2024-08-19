

/*
#define Relay1 32;
#define Relay2 33;
#define Relay3 25;
#define Relay4 26;
#define Relay5 27;
#define Relay6 14;
#define Relay7 12;
#define Relay8 13;
*/
void setRELAY() {

    if (MAINPOWER == 10) {
      digitalWrite(17, 0);
      Serial.println("MAINPOWER OFF");
    }
    if (MAINPOWER == 20) {
      digitalWrite((17), 1);
      Serial.println("MAINPOWER ON");
    }
  


  if (FCPOWER == 10) {
    digitalWrite(33, 0);
    Serial.println("AUX12v on");
  }
  if (FCPOWER == 20) {
    digitalWrite(33, 1);
    Serial.println("AUX12v off");
  }

  if (PROX == 10) {
    digitalWrite(25, 0);
    Serial.println("Camera OFF");
  }

  if (PROX == 20) {
    digitalWrite(25, 1);
    Serial.println("Camera ON");
  }


  if (WIFICAM == 10) {
    digitalWrite(26, 0);
    // Serial.println("Camera OFF");
  }
  if (WIFICAM == 20) {
    digitalWrite(26, 1);
    // Serial.println("Camera ON");
  }


  if (MOTPOWER == 10) {
    digitalWrite(23, 0);
    //  Serial.println("MOTPOWER OFF");
  }
  if (MOTPOWER == 20) {
    digitalWrite(23, 1);
    //  Serial.println("MOTPOWER ON");
  }




  if (LIGHTS == 10) {
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    // Serial.println("LIGHTS OFF");
  }
  if (LIGHTS == 20) {
    digitalWrite(4, 1);
    digitalWrite(5, 0);
    //   Serial.println("LOW ON");
  }
  if (LIGHTS == 30) {
    digitalWrite(4, 1);
    digitalWrite(5, 1);
    //  Serial.println("HIGH + LOW ON");
  }
  if (LIGHTS == 40) {
    digitalWrite(4, 0);
    digitalWrite(5, 1);
    // Serial.println("HIGH ON");
  }




  if (INDICATOR == 10) {
    digitalWrite(2, 0);
    digitalWrite(15, 0);
    //  Serial.println("INDICATOR OFF");
  }
  if (INDICATOR == 20) {
    digitalWrite(2, 0);
    digitalWrite(15, 1);
    // Serial.println("INDICATOR left");
  }
  if (INDICATOR == 30) {
    digitalWrite(2, 1);
    digitalWrite(15, 0);
    //  Serial.println("INDICATOR RIGHT");
  }
  if (INDICATOR == 40) {
    digitalWrite(2, 1);
    digitalWrite(15, 1);
    //  Serial.println("INDICATOR HAZARD");
  }






  Serial.println("           ");
  Serial.println("           ");
  Serial.println("           ");
  Serial.println("           ");
  Serial.println("           ");
}
