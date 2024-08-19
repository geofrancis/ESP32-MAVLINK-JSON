
void sensors(){

ADC1 = analogRead(35);
MAINBATT = map(ADC1,1563,2942,300,530);
if (MAINBATT < 5){MAINBATT=0;}
//Serial.println(ADC1);
////Serial.println(MAINBATT/10);


ADC2 = analogRead(34);
BATT1 = map(ADC2,0,2385,0,415);
//Serial.println(ADC2);
//Serial.println(BATT1/100);


ADC3 = analogRead(32);
BATT2 = map(ADC3,0,2385,0,415);
//Serial.println(ADC3);
//Serial.println(BATT2/10);


}