#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String string;
String MinuteString;
String HourString;
int changing_option = 1;
String menu = "main";
int button1 = 6;
int button2 = 7;
int button3 = 8;
int button4 = 9;
bool pressed1 = false;
bool pressed2 = false;
bool pressed3 = false;
bool pressed4 = false;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
}

void loop() {
  Serial.println(String(digitalRead(button2)) + " " + menu);
  delay(10);


// Main menu
  if (menu == "main") {
    tmElements_t tm;

    if (RTC.read(tm)) {
      lcd.setCursor(0, 0);
      if (tm.Minute < 10) {
        MinuteString = "0" + String(tm.Minute);
      } else {
        MinuteString = String(tm.Minute);
      }
      if (tm.Hour < 10) {
        HourString = "0" + String(tm.Hour);
      } else if (tm.Hour > 12) {
        HourString = "0" + String(tm.Hour - 12);
      }

      string = HourString + ":" + MinuteString;
      lcd.print(string);

      lcd.setCursor(0, 1);
      lcd.print("Menu");

      lcd.setCursor(7, 1);
      lcd.print("Took-Att.");

      if (digitalRead(button1) == 1) {
        pressed1 = true;
      }
      if (digitalRead(button1) == 0 && pressed1 == true) {
        pressed1 = false;
        menu = "menu";
        lcd.clear();
      }
    } else {
      Serial.print("No RTC reading");
    }


// Change things menu
  } else if (menu == "menu") {
    lcd.setCursor(0, 1);
    lcd.print("Set Time");

    if (digitalRead(button1) == 1) {
      pressed1 = true;
    }
    if (digitalRead(button1) == 0 && pressed1 == true) {
      pressed1 = false;
      menu = "time-set";
      lcd.clear();
    }


// Change time menu
  } else if (menu = "time-set") {
    tmElements_t tm;
    
    if (RTC.write(tm)) {
      lcd.setCursor(0, 1);
      lcd.print("Back B+  G- OK");
  
      if (digitalRead(button1) == 1) {
        pressed1 = true;
      }
      if (digitalRead(button1) == 0 && pressed1 == true) {
        pressed1 = false;
        menu = "main";
        lcd.clear();
      }
  // Changing the hour
      if (changing_option == 1) {
        if (digitalRead(button2) == 1) {
          pressed2 = true;
        }
        if (digitalRead(button2) == 0 && pressed2 == true) {
          pressed2 = false;
          tm.Hour = tm.Hour + 1;
        }
    
        if (digitalRead(button3) == 1) {
          pressed3 = true;
        }
        if (digitalRead(button3) == 0 && pressed3 == true) {
          pressed3 = false;
          tm.Hour = tm.Hour - 1;
        }
  // Changing the minute
      } else if (changing_option == -1) {
        if (digitalRead(button2) == 1) {
          pressed2 = true;
        }
        if (digitalRead(button2) == 0 && pressed2 == true) {
          pressed2 = false;
          tm.Minute = tm.Minute + 1;
        }
    
        if (digitalRead(button3) == 1) {
          pressed3 = true;
        }
        if (digitalRead(button3) == 0 && pressed3 == true) {
          pressed3 = false;
          tm.Minute = tm.Minute - 1;
        }
      }
  
  // Switch to and from minute etc
      if (digitalRead(button4) == 1) {
        pressed4 = true;
      }
      if (digitalRead(button4) == 0 && pressed4 == true) {
        pressed4 = false;
        changing_option = changing_option * -1;
      }
    }
    if (RTC.read(tm)) {
      Serial.print("HEElo");
      if (tm.Minute < 10) {
        MinuteString = "0" + String(tm.Minute);
      } else {
        MinuteString = String(tm.Minute);
      }
      if (tm.Hour < 10) {
        HourString = "0" + String(tm.Hour);
      } else if (tm.Hour > 12) {
        HourString = "0" + String(tm.Hour - 12);
      }

      string = HourString + ":" + MinuteString;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(string);
    } else {
      Serial.print("EEEhelo");
    }
  }
}
