#include <LiquidCrystal.h>
const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int num = 5 ;       // Set the number of measurements
int soundPin = A3;
int detectPin = 11;
int LedG = 12;
int LedR = 13;
long sound;        // Store the value read Sound Sensor
long sum = 0 ;     // Store the total value of n measurements
long DbLevel = 0 ; // Store the average value
int soundlow = 40;
int soundmedium = 60;
int soundDiff =83.2073 ;
int interval = 150;// Delay we are giving using Millis()
int previousT = 0;
int currentT;      // To store the current value of millis()

void setup ()
{
  pinMode (soundPin, INPUT);
  pinMode (detectPin, INPUT);// Set the signal pin as input
  Serial.begin (9600);
  lcd.begin(16, 2);
}

void loop ()
{ int detect = digitalRead(detectPin);
  //  Serial.print(detect);
  if (detect == 1)
  { digitalWrite(LedG, HIGH);
    
  }
  else
  { digitalWrite(LedG, LOW);
    
  }

  currentT = millis();
  if (currentT - previousT >= interval)
  { previousT = millis();

    
    for ( int i = 0 ; i < num; i ++)
    { sound = analogRead (soundPin);
      sum = sum + sound;
    }
    DbLevel = int(((sum / num) + soundDiff) / 10); // Calculate the average value
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sound Level = ");
    if(DbLevel>0)
    {lcd.print(DbLevel);}

    Serial.print("Sound Level: ");
    if(DbLevel>0)
    {Serial.println (DbLevel);}
    

    if (DbLevel <=0)
    {
      lcd.setCursor(0, 1);
      lcd.print("Intensity =    ");
      
    }
    if (0<DbLevel < soundlow)
    {
      lcd.setCursor(0, 1);
      lcd.print("Intensity = LOW");
      Serial.println ("Intensity = LOW");
    }
    if (DbLevel > soundlow && DbLevel < soundmedium)
    {
      lcd.setCursor(0, 1);
      lcd.print("Intensity = MID");
      Serial.println ("Intensity = MID");

    }
    if (DbLevel > soundmedium)
    {
      lcd.setCursor(0, 1);
      lcd.print("Intensity = HIGH");
      Serial.println ("Intensity = HIGH");
      digitalWrite(LedR, HIGH);
    }
    else
    {digitalWrite(LedR, LOW);}


    sum = 0 ;
  }

  
}
