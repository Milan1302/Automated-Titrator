const int stepPin = 5; 
const int dirPin = 2; 
const int enPin = 8;
float calibration = 26.842;
const int analogInPin = A1;
int sensorValue = 0;
const int s1 = 12;
const int pump = 11;
const int s2 = 7;
float b;

void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  initialize();
  flush(3);
  Serial.println("TITRATION STARTS");
}
void loop() {

//   float* pH = getPh(calibration);
//   float ph_derivative = derivative(pH[0], pH[2]);
//   float ph_dderivative = dderivative(pH[0],pH[1], pH[2]);
//   int num = Serial.read();
//   if(num == 1)
//   {
//     int epsilon = 1;
//     if(ph_dderivative<epsilon)
//     {
//       int delay = 250;
//       if(!forward(delay))
//         goBack();
//       delay = delay+10;
//     }
//     else
//     {
//       if(!forward())
//         goBack();
//     }
//   }
//   else
//   {
//     int epsilon = 1;
//     if(ph_derivative>epsilon)
//     {
//       int delay = 250;
//       if(!forward(delay))
//         goBack();
//       delay = delay+10;
//     }
//     else
//     {
//       if(!forward())
//         goBack();
//     }
//   }
// }
// float derivative(float pH1, float pH3)
// {
//   return (pH3 - pH1)*1000/(60);
// }
// float dderivative(float pH1, float pH2, float pH3)
// {
//   return (pH3 - 2*pH2 + pH1)*10/9;
// }
// float* getPh(int calibration)
// {
//   int temp;
//   int buf[10];
//   for(int i=0;i<10;i++)
//   {
//     buf[i]=analogRead(analogInPin);
//     delay(30);
//   }
//   for(int i=0;i<9;i++)
//   {
//     for(int j=i+1;j<10;j++)
//     {
//       if(buf[i]>buf[j])
//       {
//         temp=buf[i];
//         buf[i]=buf[j];
//         buf[j]=temp;
//       }
//     }
//   }
//   unsigned long int avgValue1=0, avgValue2=0, avgValue3=0;
//   for(int i=1;i<7;i++)
//   {
//     avgValue1+=buf[i];
//     avgValue2+=buf[i+1];
//     avgValue3+=buf[i+2];
//   }
    
//   float pHVol1=(float)avgValue1*(4.93)/1024/6;
//   float pHVol2=(float)avgValue2*(4.93)/1024/6;
//   float pHVol3=(float)avgValue3*(4.93)/1024/6;
//   float phValue1 = -5.263* pHVol1 + calibration;
//   float phValue2 = -5.263* pHVol2 + calibration;
//   float phValue3 = -5.263* pHVol3 + calibration;
//   float phVal[] = {phValue1, phValue2, phValue3};
//   return phVal;
  if(!forward())
    goBack();

}
void initialize()
{
  int switch1 = digitalRead(s1);
  while(switch1==1)
  {
    forward(500);
    switch1 = digitalRead(s1);
    Serial.println(switch1);
  }
}

void flush(int n)
{
  int switch1 = digitalRead(s1);
  int switch2 = digitalRead(s2);
  for(int i=1;i<=n;i++)
  {

    switch2 = digitalRead(s2);
    while(switch2==1)
    {
      backward();
      switch2 = digitalRead(s2);
    }
    switch1 = digitalRead(s1);
    while(switch1==1)
    {
      forward();
      switch1 = digitalRead(s1);
    }  
  }
}

void goBack()
{
  // digitalWrite(pump, HIGH);
  int switcher = digitalRead(s2);
  while(switcher==1)
  {
    backward();
    switcher = digitalRead(s2);
  }
  // digitalWrite(pump, LOW);
}

int backward()
{
  digitalWrite(dirPin,LOW); //Changes the direction of rotation
  for(int x = 0; x < 800; x++) {
    int switcher = digitalRead(s2);
    if(switcher==0)
      return 0;
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(400);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(400);
  }
  return 1;
}

int forward()
{
  digitalWrite(dirPin,HIGH); 
  for(int x = 0; x < 800; x++)
  {
    int switcher = digitalRead(s1);
    if(switcher==0)
      return 0;
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1500); 
  }
  return 1;
}

int forward(int d)
{
  digitalWrite(dirPin,HIGH); 
  for(int x = 0; x < 800; x++)
  {
    int switcher = digitalRead(s1);
    if(switcher==0)
      return 0;
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(d); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(d); 
  }
  return 1;
}







