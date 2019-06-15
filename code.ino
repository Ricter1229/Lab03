const int ledpin = 7;
const double MAX_Vin = 2.5;
const int MAX_Resolution = 4095;
const int R = 1000000;
const int R_Cds = 1000;

void setup()
{
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
  Serial.println("Welcome to the Arduino !");
  Serial.println("hello world");
}

double Analogin_VIN = 0;
double Vin = 0;
double Potentiometer_Voltage = 0;
double Analogin_Potentiometer = 0;
double Potentiometer_Rx = 0;
double Potentiometer_R1 = 0;
double Cds_Voltage = 0;
double Analogin_Cds = 0;
double Cds_R = 0;


void loop()
{
  delay(10); // Delay a little bit to improve simulation performance
  
  //LED連接確認
  if(Serial.available()){
    int read = Serial.read();
    if(read == '1'){
      Serial.println("LED is on !");
      digitalWrite(ledpin,HIGH);
    }
    else if(read == '0'){
      Serial.println("LED is off !");
      digitalWrite(ledpin,LOW);
    }
  }
  
  //測量電壓
  for(int i=0; i<5; i++){
    Analogin_VIN = 0.7* Analogin_VIN+ 0.3* analogRead(A0);
  }
  Vin = Analogin_VIN*MAX_Vin/MAX_Resolution;
  
  //測量可變電阻
  for(int i=0; i<5; i++){
    Analogin_Potentiometer = 0.7* Analogin_Potentiometer+ 0.3* analogRead(A1);
  }
  Potentiometer_Voltage = Analogin_Potentiometer*MAX_Vin/MAX_Resolution;
  Potentiometer_Rx = Potentiometer_Voltage*R/Vin ;
  Potentiometer_R1 = R-Potentiometer_Rx;
  
  //測量光敏電阻
  for(int i=0; i<5; i++){
    Analogin_Cds = 0.7* Analogin_Cds+ 0.3* analogRead(A2);
  }
  Cds_Voltage = Analogin_Cds*MAX_Vin/MAX_Resolution;
  Cds_R = (Cds_Voltage*R_Cds*2)/(-2*Cds_Voltage+5);
  
  //print
  Serial.print("Vin="); 
  Serial.print(Vin);
  Serial.print("\t");  
  Serial.print("analog_VIN=");
  Serial.print(Analogin_VIN);
  Serial.print("\t");  
  
  Serial.print("Potentiometer_Voltage="); 
  Serial.print(Potentiometer_Voltage);
  Serial.print("\t");
  Serial.print("analog_Potentiometer=");
  Serial.print(Analogin_Potentiometer);
  Serial.print("\t");
  Serial.print("Potentiometer_R1=");
  Serial.print(Potentiometer_R1);
  Serial.print("\t");
  Serial.print("Potentiometer_Rx=");
  Serial.print(Potentiometer_Rx);
  Serial.print("\t");

  Serial.print("Cds_Voltage="); 
  Serial.print(Cds_Voltage);
  Serial.print("\t");
  Serial.print("analog_Cds=");
  Serial.print(Analogin_Cds);
  Serial.print("\t");
  Serial.print("Cds_R=");
  Serial.print(Cds_R);
  
  Serial.print("\n");

  delay(200);
}
