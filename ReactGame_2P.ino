#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Using a 1602 display connected via I2C ()
LiquidCrystal_I2C lcd(0x27, 16, 2); // Setting the I2C address of the display.
int Player1 = 11; //Button 1 connected to pin 11
int Player2 = 12; //Button 2 connected to pin 12
int GameLED = 13; //LED connected to pin 13 using resistor 220Ω, you can use builtin LED
unsigned long waitTime;
unsigned long startTime;
unsigned long reactTime_P1;
unsigned long timeP1;
unsigned long reactTime_P2;
void(* resetFunc) (void) = 0; // Resetting code function

void setup() {
  pinMode(GameLED, OUTPUT);
  digitalWrite (GameLED, LOW);
  pinMode(Player1, INPUT_PULLUP);
  pinMode(Player2, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.print("Welcome to      ");
  lcd.setCursor(0, 1);
  lcd.print("Reaction Game   ");
  delay(1600);
  lcd.setCursor(0, 0);
  lcd.print("Reaction Game   ");
  lcd.setCursor(0, 1);
  lcd.print("by BurAndBY     ");
  delay(1600);
  lcd.setCursor(0, 0);
  lcd.print("How to play:    ");
  lcd.setCursor(0, 1);
  lcd.print("If the LED is ON,");
  delay(1600);
  lcd.setCursor(0, 0);
  lcd.print("If the LED is ON,");
  lcd.setCursor(0, 1);
  lcd.print("Press the button");
  delay(1600);
}

void loop() {
  digitalWrite(GameLED, LOW);
  lcd.setCursor(0, 0);
  lcd.print("     Start?     ");
  lcd.setCursor(0, 1);
  lcd.print("Player1  Player2");
  while (digitalRead(Player1) == HIGH and digitalRead(Player2) == HIGH) {  //To start game any of players have to push the button
  }
  while (digitalRead(Player1) == LOW or digitalRead(Player2) == LOW) { //And then release the button
  }
  lcd.setCursor(0, 1);
  lcd.print("    Ready!!!    ");
  timeP1 = millis();
  reactTime_P1 = 0; //Resetting reaction time variable, value = 0 will be used to wait until both players will push the button
  reactTime_P2 = 0; //Resetting reaction time variable, value = 0 will be used to wait until both players will push the button
  waitTime = random(2000, 4000);
  delay(100); //Easy debounce fix to avoid false anti-cheat trigger
  while (millis() < (timeP1 + waitTime)) { //delay() using millis()
    if (digitalRead(Player1) == LOW) //Anti-Cheat for Player 1 (Anti-spam)
    {
      lcd.setCursor(0, 0);
      lcd.print("Player 1: CHEATS!");
      lcd.setCursor(0, 1);
      lcd.print("Player 2: WINS! ");
      delay(3000);
      resetFunc();
    }
    if (digitalRead(Player2) == LOW) //Anti-Cheat for Player 2 (Anti-spam)
    {
      lcd.setCursor(0, 1);
      lcd.print("Player 2: CHEATS!");
      lcd.setCursor(0, 0);
      lcd.print("Player 1: WINS! ");
      delay(3000);
      resetFunc();
    }
  }
  digitalWrite(13, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("      GO!!!     ");
  startTime = millis();
  while (reactTime_P1 == 0 or reactTime_P2 == 0) { 
    if (digitalRead(Player1) == LOW) {  
      reactTime_P1 = millis() - startTime; //Calculation of 1'st player reaction time
    }
    if (digitalRead(Player2) == LOW) {
      reactTime_P2 = millis() - startTime; //Calculation of 2'nd player reaction time
    }
  }
  digitalWrite(GameLED, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Player 1:      ");
  lcd.setCursor(10, 0);
  lcd.print(reactTime_P1);
  lcd.setCursor(0, 1);
  lcd.print("Player 2:      ");
  lcd.setCursor(10, 1);
  lcd.print(reactTime_P2);
  delay(3000);
  if (reactTime_P1 < reactTime_P2) {
    lcd.setCursor(10, 0);
    lcd.print("Wins! ");
    lcd.setCursor(10, 1);
    lcd.print("      ");
  }
  if (reactTime_P1 > reactTime_P2) {
    lcd.setCursor(10, 1);
    lcd.print("Wins! ");
    lcd.setCursor(10, 0);
    lcd.print("      ");
  }
  if (reactTime_P1 == reactTime_P2) {
    lcd.setCursor(10, 1);
    lcd.print("TIE   ");
    lcd.setCursor(10, 0);
    lcd.print("TIE   ");
  }
  delay(3000);
}
