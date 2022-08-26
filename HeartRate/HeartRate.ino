unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 10;           // interval at which to blink (milliseconds)

#define pin_sinyal A0
int BPM;

int prev = 0;
int current;
int TT = 5000;
int dura =0;


float finalAv;
int forL=6;
int avArr[6];
void setup()
{
  Serial.begin(9600);
  avArr[0] = 0;
}



void loop()
{
  
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    hitung_HR(analogRead(pin_sinyal));
    //    Serial.println(analogRead(pin_sinyal));
  }

  //Serial.println(BPM);
  
}

unsigned long oldtime = 0;
unsigned long newtime = 0;
unsigned long beat_time = 0;
unsigned long cek_beat_time = 0;
int data_now, data_old, delta_data;
bool flag_detek = false;
float HR, HR_old;
void hitung_HR(int data_pulse)
{
  data_now = data_pulse;
  delta_data = data_now - data_old;
  if (delta_data < 0)
    delta_data = delta_data * -1;
  data_old = data_now;

  //Serial.println(data_now);
  //Serial.println(delta_data);
  if (delta_data > 140) // detek pertama
  {
    if (flag_detek == false)
    {
      flag_detek = true;
      newtime = millis();
    }
    else
    {
      beat_time = millis() - newtime;
      if (beat_time < 400)
      {
        newtime = millis();
//        beat_time = millis();
      }
      else
      {
        HR = 60 / (((float) beat_time) / 1000);
        HR = HR * 0.6 + HR_old * 0.4;
        if (abs(HR - HR_old) > 10)
        {
          HR = 60 / (((float) beat_time) / 1000);
          HR = HR * 0.1 + HR_old * 0.9;
        }
        //Serial.println(beat_time);
        flag_detek = false;
        HR_old = HR;
      }
    }

  }

  // cancel pertitungan
  // 150 BPM = 400 ms dan 40 BPM = 1500 ms
  cek_beat_time = millis() - newtime;
  if (cek_beat_time > 10000)
  {
    newtime = millis();
    HR = 0;
  }

  BPM = HR;
    current = millis();

    if(dura > 0 && dura <forL){
      avArr[dura] = BPM;
      dura++;
    }else{
      dura = 0;
      for(int i = 0; i < forL; i++){
        finalAv += avArr[i];
      }
      finalAv = finalAv/(forL-1);
    }

  
  if(current - prev >= TT && dura == 0){
    Serial.println(finalAv);
    finalAv = 0;
    prev = current;
    dura++;
  }
  
  


}
