#include <LinkedList.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LinkedList<int> alarms = LinkedList<int>();

String string;
String last_string = "Random stuff";
String MinuteString;
String HourString;
String changing_string;
int changing_option = 1;
String menu = "main";
int button1 = 6;
int button2 = 7;
int button3 = 8;
int view_num = 0;
bool pressed1 = false;
bool pressed2 = false;
bool pressed3 = false;
bool pressed4 = false;
bool config = false;
int Minute = 0;
int Hour = 0;










// Fuction to set the time -----------------------------------------------------------------------------------------
void menuSetTime() {
  tmElements_t tm;
    
  if (RTC.read(tm)) {
    if (tm.Minute < 10) {
      MinuteString = "0" + String(tm.Minute);
    } else {
      MinuteString = String(tm.Minute);
    }
    if (tm.Hour < 10) {
      HourString = "0" + String(tm.Hour);
    } else {
      HourString = String(tm.Hour);
    }
    if (changing_option == 1) {
      changing_string = "Hr";
    } else if (changing_option == -1) {
      changing_string = "Min";
    }

    string = HourString + ":" + MinuteString + " Change:" + changing_string;

    if (string != last_string) {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Back   +   OK");
      lcd.setCursor(0, 0);
      lcd.print(string);
    }
    last_string = string;
  }

// Changing the hour
  if (changing_option == 1) {
    if (digitalRead(button2) == HIGH) {
      pressed2 = true;
    } else if (digitalRead(button2) == LOW && pressed2 == true) {
      pressed2 = false;
      tm.Hour = tm.Hour + 1;
      if (tm.Hour == 24) {
        tm.Hour = 0;
      }
      if (RTC.write(tm)) {
        config = true;
      }
    }
    
// Changing the minute
  } else if (changing_option == -1) {
    if (digitalRead(button2) == HIGH) {
      pressed2 = true;
    } else if (digitalRead(button2) == LOW && pressed2 == true) {
      pressed2 = false;
      tm.Minute = tm.Minute + 1;
      if (tm.Minute == 60) {
        tm.Minute = 0;
      }
      if (RTC.write(tm)) {
        config = true;
      }
    }
  }

// Switch to and from minute etc
  if (digitalRead(button3) == HIGH) {
    pressed3 = true;
  } else if (digitalRead(button3) == LOW && pressed3 == true) {
    pressed3 = false;
    changing_option = changing_option * -1;
  }
// If back is pressed, switch to the main menu
  if (digitalRead(button1) == HIGH) {
    pressed1 = true;
  } else if (digitalRead(button1) == LOW && pressed1 == true) {
    pressed1 = false;
    menu = "main";
  }
}














// Fuction to add alarms -------------------------------------------------------------------------------------------
void addAlarms() {

  if (Minute < 10) {
    MinuteString = "0" + String(Minute);
  } else {
    MinuteString = String(Minute);
  }
  if (Hour < 10) {
    HourString = "0" + String(Hour);
  } else {
    HourString = String(Hour);
  }
  if (changing_option == 1) {
    changing_string = "Hr";
  } else if (changing_option == 2) {
    changing_string = "Min";
  }

  string = HourString + ":" + MinuteString + " Change:" + changing_string;

  if (string != last_string) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Back   +   OK");
    lcd.setCursor(0, 0);
    lcd.print(string);    }
  last_string = string;
  

// Changing the hour
  if (changing_option == 1) {
    if (digitalRead(button2) == HIGH) {
      pressed2 = true;
    } else if (digitalRead(button2) == LOW && pressed2 == true) {
      pressed2 = false;
      Hour = Hour + 1;
      if (Hour == 24) {
        Hour = 0;
      }
    }
    
// Changing the minute
  } else if (changing_option == 2) {
    if (digitalRead(button2) == HIGH) {
      pressed2 = true;
    } else if (digitalRead(button2) == LOW && pressed2 == true) {
      pressed2 = false;
      Minute = Minute + 1;
      if (Minute == 60) {
        Minute = 0;
      }
    }
  } else if (changing_option == 3) {
    alarms.add((Hour * 100) + Minute);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(String(alarms.get(view_num)) + " " + String(alarms.get(view_num + 1)));
    lcd.setCursor(0, 1);
    lcd.print("Back    <     >");

    if (digitalRead(button2) == HIGH) {
      pressed2 = true;
    } else if (digitalRead(button2) == LOW && pressed2 == true) {
      pressed2 = false;
      if (view_num > 1) {
        view_num = view_num - 1;
      }
    }
    
    if (digitalRead(button3) == HIGH) {
      pressed3 = true;
    } else if (digitalRead(button3) == LOW && pressed3 == true) {
      pressed3 = false;
      if (view_num < alarms.size() - 1) {
        view_num = view_num + 1;
      } else {
        lcd.setCursor(0, 6);
        lcd.print("Thats it");
      }
    }
  }

// Switch to and from minute etc
  if (digitalRead(button3) == HIGH) {
    pressed3 = true;
  } else if (digitalRead(button3) == LOW && pressed3 == true) {
    pressed3 = false;
    changing_option = changing_option + 1;
  }
  if (digitalRead(button1) == HIGH) {
    pressed1 = true;
  } else if (digitalRead(button1) == LOW && pressed1 == true) {
    pressed1 = false;
    menu = "main";
    view_num = 0;
    changing_option = 1;
    Hour = 0;
    Minute = 0;
  }
}
















void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
}















void loop() {
  delay(100);


// Main menu
  if (menu == "main") {
    menuMain();

  } else if (menu == "menu") {
    menuMenu();

  } else if (menu == "time-set") {
    menuSetTime();
    
  } else if (menu == "add-alarms") {
    addAlarms();
    
  }
}












// Fuction for main main menu --------------------------------------------------------------------------------------
void menuMain() {
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
    } else {
      HourString = String(tm.Hour);
    }

    string = HourString + ":" + MinuteString;
    if (string != last_string) {
      lcd.clear();
      lcd.print(string);
      lcd.setCursor(0, 1);
      lcd.print("Menu");
      lcd.setCursor(7, 1);
      lcd.print("Took-Att.");
    }

    if (digitalRead(button1) == 1) {
      pressed1 = true;
    } else if (digitalRead(button1) == 0 && pressed1 == true) {
      pressed1 = false;
      menu = "menu";
      lcd.clear();
    }
  }
}


















// Fuction for main menu -------------------------------------------------------------------------------------------
void menuMenu() {
  lcd.setCursor(0, 1);
  lcd.print("Time    Alarms");

  if (digitalRead(button1) == 1) {
    pressed1 = true;
  } else if (digitalRead(button1) == 0 && pressed1 == true) {
    pressed1 = false;
    menu = "time-set";
    lcd.clear();
  }

  if (digitalRead(button3) == 1) {
    pressed3 = true;
  } else if (digitalRead(button3) == 0 && pressed3 == true) {
    pressed3 = false;
    menu = "add-alarms";
    lcd.clear();
  }
}
