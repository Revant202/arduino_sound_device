#include <LiquidCrystal.h>
const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int num = 5 ; // Set the number of measurements
int soundPin = A3;
int detectPin = 11;
int LedG = 12;
int LedR = 13;
long sound;    // Store the value read Sound Sensor
long sum = 0 ; // Store the total value of n measurements
long DbLevel = 0 ; // Store the average value
int soundlow = 40;
int soundmedium = 60;
int soundDiff = 507  ;
int interval = 150;
int previousT = 0;
int currentT;

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
    digitalWrite(LedR, HIGH);
  }
  else
  { digitalWrite(LedG, LOW);
    digitalWrite(LedR, LOW);
  }

  currentT = millis();
  if (currentT - previousT >= interval)
  { previousT = millis();

    
    for ( int i = 0 ; i < num; i ++)
    { sound = analogRead (soundPin);
      sum = sum + sound;
    }
    DbLevel = ((sum / num) - soundDiff) * 10; // Calculate the average value
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
    }
    if (DbLevel > soundlow && DbLevel < soundmedium)
    {
      lcd.setCursor(0, 1);
      lcd.print("Intensity = MID");

    }
    if (DbLevel > soundmedium)
    {
      lcd.setCursor(0, 1);
      lcd.print("Intensity = HIGH");

    }


    sum = 0 ;
  }

  
}
