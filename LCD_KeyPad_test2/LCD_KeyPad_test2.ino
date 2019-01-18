#include <LiquidCrystal.h>
#include <Keypad.h>
#include <AccelStepper.h>

/*
 * Return:
 *      @value
 * Press numbers to add value.
 * Press '*' to return a negative value. 
 * Press '#' to return a possitive value.
 * Press 'A' to see the value without its returning.
 * Press 'B' to see previous 2 values.
 * Press 'C' to clear value.
 * Press 'D' to move Stepper motor.
 * 
 * Return 0 if unknown symbol ('*' or '#' standalone or symbols 'C', 'D').
 */

String line = "";
long value;
long prevValue1;
long prevValue2;

long steps;

bool firstOrSecond = true;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A2, A3, A4, A5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

AccelStepper Stepper1(1, 3, 2); //использует пин A0 и A1 для dir и step, 1 - режим "external driver" (A4988)

void setup() 
{
  Serial.begin(9600);
  Serial.println("Ready!");
  lcd.begin(16, 2);
  lcd.print("Ready!");

  Stepper1.setSpeed(25);
  Stepper1.setMaxSpeed(50); //устанавливаем максимальную скорость вращения ротора двигателя (шагов/секунду)
  Stepper1.setAcceleration(100); //устанавливаем ускорение (шагов/секунду^2)
}

void loop()
{
  char key = keypad.getKey();
  if (key)
  {
    lcd.command(0b101000);
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Pressed key: ");
    lcd.print(key);
    
    if ( isDigit(key) )
    {
      line += key;
      Serial.print("\tadded: ");
      Serial.println(key);
    }
    else
    {
      if (key == '*')
      {
        value = line.toInt();
        value *= -1;
        line = "";
        Serial.print("Value is: ");
        Serial.println(value);

        lcd.setCursor(0, 1);
        lcd.print("V = ");
        lcd.print(value);

        if (firstOrSecond)
        {
          prevValue1 = value;
          firstOrSecond = false;
        }
        else
        {
          prevValue2 = value;
          firstOrSecond = true;
        }
      }
      
      if (key == '#')
      {
        value = line.toInt();
        line = "";
        Serial.print("Value is: ");
        Serial.println(value);

        lcd.setCursor(0, 1);
        lcd.print("V = ");
        lcd.print(value);

        if (firstOrSecond)
        {
          prevValue1 = value;
          firstOrSecond = false;
        }
        else
        {
          prevValue2 = value;
          firstOrSecond = true;
        }
      }
      
      if (key == 'A')
      {
        Serial.print("Not ready value: ");
        Serial.println(line);
        
        lcd.setCursor(0, 1);
        lcd.print("Not ready: ");
        lcd.print(line);
      }
      
      if (key == 'B')
      {
        lcd.command(0b101010);
        lcd.clear();

        Serial.print("Previous value1 is: ");
        Serial.println(prevValue1);
        
        lcd.setCursor(0,0);
        lcd.print("V1 = ");
        lcd.print(prevValue1);

        Serial.print("Previous value2 is: ");
        Serial.println(prevValue2);
        
        lcd.setCursor(0,1);
        lcd.print("V2 = ");
        lcd.print(prevValue2);
      }
      
      if (key == 'C')
      {
        Serial.println("\tClear");
        line = "";

        lcd.setCursor(0, 1);
        lcd.print("Clear!");
      }
      
      if (key == 'D')
      {
        steps = value*1.38;
        Serial.print("\tSteps: ");
        Serial.println(steps);
        
        lcd.setCursor(0, 1);
        lcd.print("Steps:");
        lcd.print(steps);

        if(Stepper1.distanceToGo()==0)
        {
          Stepper1.move(steps);
        }
      }
    }
  }
  Stepper1.run();
}
