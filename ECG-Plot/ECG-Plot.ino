
//ECG variables
const int ECGsignal = A0;
const int LOplus = 10;
const int LOminus = 11;

void setup() {
  Serial.begin(9600);

  
  //LO+ & LO- pins
  pinMode(LOplus, INPUT);
  pinMode(LOminus, INPUT);

}

void loop() {
  printing ECG Signal
  if(digitalRead(10) == 1 || digitalRead(11) == 1)
  {
    Serial.println('!');
  }else{
 //Sends ECG value to pin A0
  
    
    Serial.println(analogRead(ECGsignal));
  }

  delay(1);

}
