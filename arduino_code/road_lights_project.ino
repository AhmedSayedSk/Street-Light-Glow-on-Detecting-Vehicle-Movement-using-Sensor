const int NumberOfLights = 2; /* 1~3, Default=2 */
const int lightSmooth = 255; /* 1~255 */

// LED pins:
#define LED1 3
#define LED2 5
#define LED3 6
#define LED4 9
#define LED5 10
#define LED6 11

int carDirection = 0; /* 0=none, 1=forward, 2=back */
int existSensor = 0; /* 0=none, 1=sensor1, 2=sensor2 etc... */
boolean light1 = false;
boolean light2 = false;
boolean light3 = false;
boolean light4 = false;
boolean light5 = false;
boolean light6 = false;
int lightValue1 = 0;
int lightValue2 = 0;
int lightValue3 = 0;
int lightValue4 = 0;
int lightValue5 = 0;
int lightValue6 = 0;
int A_0 = 0;
int A_1 = 0;
int A_2 = 0;
int A_3 = 0;
int A_4 = 0;
int A_5 = 0;


int analogMinVal = 1023;
int analogMaxVal = 0;
int sensorTrimAlalogValue = 55;


void setup() {
  Serial.begin(9600);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(LED6,OUTPUT);
  analogWrite(LED1, 255);
  delay(100);
  analogWrite(LED1, 0);
  delay(200);
  analogWrite(LED2, 255);
  delay(100);
  analogWrite(LED2, 0);
  delay(200);
  analogWrite(LED3, 255);
  delay(100);
  analogWrite(LED3, 0);
  delay(200);
  analogWrite(LED4, 255);
  delay(100);
  analogWrite(LED4, 0);
  delay(200);
  analogWrite(LED5, 255);
  delay(100);
  analogWrite(LED5, 0);
  delay(200);
  analogWrite(LED6, 255);
  delay(100);
  analogWrite(LED6, 0);
  delay(2000);
}

void loop() {
  A_0 = analogRead(A0);
  A_1 = analogRead(A1);
  A_2 = analogRead(A2);
  A_3 = analogRead(A3);
  A_4 = analogRead(A4);
  A_5 = analogRead(A5);
  
  
  analogMinVal = 1023;
  analogMaxVal = 0;
  if(analogMinVal>A_0)analogMinVal=A_0;
  if(analogMaxVal<A_0)analogMaxVal=A_0;
  if(analogMinVal>A_1)analogMinVal=A_1;
  if(analogMaxVal<A_1)analogMaxVal=A_1;
  if(analogMinVal>A_2)analogMinVal=A_2;
  if(analogMaxVal<A_2)analogMaxVal=A_2;
  if(analogMinVal>A_3)analogMinVal=A_3;
  if(analogMaxVal<A_3)analogMaxVal=A_3;
  if(analogMinVal>A_4)analogMinVal=A_4;
  if(analogMaxVal<A_4)analogMaxVal=A_4;
  if(analogMinVal>A_5)analogMinVal=A_5;
  if(analogMaxVal<A_5)analogMaxVal=A_5;
  sensorTrimAlalogValue = ((analogMaxVal-analogMinVal)/2)+analogMinVal;
  
  Serial.println(String(A_0)+" - "+String(A_1)+" - "+String(A_2)+" - "+String(A_3)+" - "+String(A_4)+" - "+String(A_5));
  
  Serial.println("min="+String(analogMinVal)+", max="+String(analogMaxVal)+", sensorTrimAlalogValue: "+String(sensorTrimAlalogValue));
  
  sense();
  if(existSensor == 0)carDirection=0;
  Serial.print("sensor = " );
  Serial.println(existSensor);
  
  switch(existSensor){
    case 1:
      if(carDirection==0){ //forward
          carDirection=1;
          light1 = true;
          if(NumberOfLights==2){light2 = true;}
          else if(NumberOfLights==3){light2 = true; light3 = true;}
       }else if(carDirection==2){ //back
          light2 = false;
          light1 = true;
       }
    break;
    case 2:
      if(carDirection==1){ //forward
          light1 = false;
          light2 = true;
          if(NumberOfLights==2){light3 = true;}
          else if(NumberOfLights==3){light3 = true; light4 = true;}
       }else if(carDirection==2){ //back
          light3 = false;
          light2 = true;
          if(NumberOfLights>=2){light1 = true;}
       }
    break;
    case 3:
      if(carDirection==1){ //forward
          light2 = false;
          light3 = true;
          if(NumberOfLights==2){light4 = true;}
          else if(NumberOfLights==3){light4 = true; light5 = true;}
       }else if(carDirection==2){ //back
          light4 = false;
          light3 = true;
          if(NumberOfLights==2){light2 = true;}
          else if(NumberOfLights==3){light2 = true; light1 = true;}
       }
    break;
    case 4:
      if(carDirection==1){ //forward
          light3 = false;
          light4 = true;
          if(NumberOfLights==2){light5 = true;}
          else if(NumberOfLights==3){light5 = true; light6 = true;}
       }else if(carDirection==2){ //back
          light5 = false;
          light4 = true;
          if(NumberOfLights==2){light3 = true;}
          else if(NumberOfLights==3){light3 = true; light2 = true;}
       }
    
    break;
    case 5:
      if(carDirection==1){ //forward
          light4 = false;
          light5 = true;
          if(NumberOfLights==2){light6 = true;}
       }else if(carDirection==2){ //back
          light6 = false;
          light5 = true;
          if(NumberOfLights==2){light4 = true;}
          else if(NumberOfLights==3){light4 = true; light3 = true;}
       }
       
    break;
    case 6:
        if(carDirection==1){ //forward
          light5 = false;
          light6 = true;
       }else if(carDirection==0){ //back
          carDirection=2;
          light6 = true;
          if(NumberOfLights==2){light5 = true;}
          else if(NumberOfLights==3){light5 = true; light4 = true;}
       }
    break;
    default:
      carDirection=0;
      light1 = false;//true;
      light2 = false;//true;
      light3 = false;//true;
      light4 = false;//true;
      light5 = false;//true;
      light6 = false;//true;
    break;
  }
  
  updateLights();
  Serial.print("direction = " );
  Serial.println(carDirection);
  Serial.println("----------------------------------------------------------------");

  delay(2);
}

void sense(){
  existSensor = 0;
  if(A_0>sensorTrimAlalogValue&&(A_0-sensorTrimAlalogValue>2)){
    existSensor = 1;
  }else if(A_5>sensorTrimAlalogValue&&(A_5-sensorTrimAlalogValue>2)){
    existSensor = 6;
  }
  
  if(carDirection==1){
    if(A_1>sensorTrimAlalogValue&&(A_1-sensorTrimAlalogValue>2))existSensor = 2;
    if(A_2>sensorTrimAlalogValue&&(A_2-sensorTrimAlalogValue>2))existSensor = 3;
    if(A_3>sensorTrimAlalogValue&&(A_3-sensorTrimAlalogValue>2))existSensor = 4;
    if(A_4>sensorTrimAlalogValue&&(A_4-sensorTrimAlalogValue>2))existSensor = 5;
  }else if(carDirection==2){
    if(A_4>sensorTrimAlalogValue&&(A_4-sensorTrimAlalogValue>2))existSensor = 5;
    if(A_3>sensorTrimAlalogValue&&(A_3-sensorTrimAlalogValue>2))existSensor = 4;
    if(A_2>sensorTrimAlalogValue&&(A_2-sensorTrimAlalogValue>2))existSensor = 3;
    if(A_1>sensorTrimAlalogValue&&(A_1-sensorTrimAlalogValue>2))existSensor = 2;
  }
  
  
  //temp:
  /*if(existSensor == 1)analogWrite(LED1, 255);else analogWrite(LED1, 0);
  if(existSensor == 2)analogWrite(LED2, 255);else analogWrite(LED2, 0);
  if(existSensor == 3)analogWrite(LED3, 255);else analogWrite(LED3, 0);
  if(existSensor == 4)analogWrite(LED4, 255);else analogWrite(LED4, 0);
  if(existSensor == 5)analogWrite(LED5, 255);else analogWrite(LED5, 0);
  if(existSensor == 6)analogWrite(LED6, 255);else analogWrite(LED6, 0);*/
}

void updateLights(){
  
  /*light1 = true;
  light2 = true;
  light3 = true;
  light4 = true;
  light5 = true;
  light6 = true;*/
  
  
  if(light1==false)lightValue1-=lightSmooth;
  else lightValue1+=lightSmooth;
  
  if(light2==false)lightValue2-=lightSmooth;
  else lightValue2+=lightSmooth;
  
  if(light3==false)lightValue3-=lightSmooth;
  else lightValue3+=lightSmooth;
  
  if(light4==false)lightValue4-=lightSmooth;
  else lightValue4+=lightSmooth;
  
  if(light5==false)lightValue5-=lightSmooth;
  else lightValue5+=lightSmooth;
  
  if(light6==false)lightValue6-=lightSmooth;
  else lightValue6+=lightSmooth;
  
  
  if(lightValue1>=255)lightValue1=255;
  if(lightValue1<=0)lightValue1=0;
  
  if(lightValue2>=255)lightValue2=255;
  if(lightValue2<=0)lightValue2=0;
  
  if(lightValue3>=255)lightValue3=255;
  if(lightValue3<=0)lightValue3=0;
  
  if(lightValue4>=255)lightValue4=255;
  if(lightValue4<=0)lightValue4=0;
  
  if(lightValue5>=255)lightValue5=255;
  if(lightValue5<=0)lightValue5=0;
  
  if(lightValue6>=255)lightValue6=255;
  if(lightValue6<=0)lightValue6=0;
  
  analogWrite(LED1, lightValue1);
  analogWrite(LED2, lightValue2);
  analogWrite(LED3, lightValue3);
  analogWrite(LED4, lightValue4);
  analogWrite(LED5, lightValue5);
  analogWrite(LED6, lightValue6);
}
