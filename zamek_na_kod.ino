/* 
prosty zamek na kod z keypada 4x4, z wyswietlaniem LCD i LED
*/
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define GREEN_LED 3
#define RED_LED 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {10, 13, 12, 11}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int slowolen = 0;
String slowo;
int i = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Podaj kod: ");
  lcd.init();         // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Podaj kod: ");
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}
  
void loop(){
  lcd.setCursor(0, 0);
  lcd.print("Podaj kod: ");
  lcd.setCursor(0, 1);
  char key = keypad.getKey();
  if (key){
    
    lcd.setCursor(i, 1);
    lcd.print(key);
    Serial.println(key);
    slowo += key;
    slowolen++;
    i++;
  }
  if (slowolen == 4 && slowo == "0000")
  {
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wpisane Haslo: ");
    lcd.setCursor(0,1);
    Serial.println(slowo);
    lcd.print(slowo);
    digitalWrite(GREEN_LED, HIGH);
    slowo = "";
    slowolen = 0 ;
    i=0;
    delay(5000);
    lcd.clear();
    digitalWrite(GREEN_LED, LOW);
  }
  if (slowolen == 4 && slowo != "0000") 
  {
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Wpisane Haslo: ");
      lcd.setCursor(0,1);
      Serial.println(slowo);
      lcd.print(slowo);
      digitalWrite(RED_LED, HIGH);
      slowo = "";
      slowolen = 0 ;
      i=0;
      delay(5000);
      lcd.clear();
      digitalWrite(RED_LED, LOW);
  }
 
  
  
  
}
