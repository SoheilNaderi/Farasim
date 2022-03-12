#include "pitches.h"
#include <SoftwareSerial.h>
SoftwareSerial esp8266(8, 9); //2 -->rx  ,3 -->tx
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11, 4, 5, 6, 7); // LiquidCrystal lcd(rs, enable, D4, D5, D6, D7);
char c;
char a [15];

int mobile_notes[] = {NOTE_C4, NOTE_DS4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_G4, NOTE_F4, NOTE_DS4, NOTE_F4, NOTE_DS4};
int mobile_durations[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4}; // 4= Note Siah   8= Note Chang

void setup() {

  esp8266.begin(9600);

  pinMode(10, INPUT);
  pinMode(2, OUTPUT);

  //  pinMode(7, OUTPUT);
  //  pinMode(6, OUTPUT);
  //  pinMode(5, OUTPUT);

  digitalWrite(2, HIGH);

lcd.begin(16,2); // (Sotoon, Satr);

  // Turn on the blacklight and print a message.
  //lcd.backlight();
  lcd.setCursor(7, 0);
  lcd.print("S");// Ready to use
  delay(1000);

  for (int e = 0; e <= 5; e++) {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("S");// Ready to use
    lcd.setCursor(e, 0);
    lcd.print("LA");// Ready to use!
    delay(150);
  }

  for (int r = 15; r >= 8; r--) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("LAS");// Ready to use
    lcd.setCursor(r, 0);
    lcd.print("NA");// Ready to use!
    delay(150);
  }

  //  lcd.setCursor(4, 1);
  //  lcd.print("COMPONY");// Ready to use

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Farasim1");// Hello
  lcd.setCursor(0, 1);
  lcd.print("Wireless Control");
  delay(3500);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Preparing...");// Ready to use!
  lcd.setCursor(0, 1);

  for (int i = 0; i < 16; i++) {

    lcd.print("=");// Ready to use!
    delay(150);
  }


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Device IP: ");// Ready to use!

  

   


  
}

void loop() {

  int r = digitalRead(10);

  if (r == LOW) {
    digitalWrite(2, HIGH);
  }
  else if (r == HIGH) {
    digitalWrite(2, LOW);
  }



 if (esp8266.available() > 0)
    {

      for (int i = 0; i < 15; i++) {
        c = esp8266.read();
        a[i] = c;
      }
      //lcd.clear();
    }

   lcd.setCursor(0, 1);
    //lcd.print(1);

    for (int i = 0; i < 14; i++) {
      lcd.print(a[i]);
    }
    lcd.setCursor(13, 1);
    lcd.print(" ");

  
}
