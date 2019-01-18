#include <Keypad.h>

/*
 * Return:
 *      @value
 * Press numbers to add value.
 * Press '*' to return a negative value. 
 * Press '#' to return a possitive value.
 * Press 'A' to see the value without its returning.
 * Press 'B' to clear value.
 * 
 * Return 0 if unknown symbol ('*' or '#' standalone or symbols 'C', 'D').
 */

String line = "";
long value;

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

void setup()
{
   Serial.begin(9600);
   Serial.println("Start!");
}
  
void loop()
{
  char key = keypad.getKey();
  if (key)
  {
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
        Serial.print("Value is: ");
        Serial.println(value);
        line = "";
      }
      if (key == '#')
      {
        value = line.toInt();
        Serial.print("Value is: ");
        Serial.println(value);
        line = "";
      }
      if (key == 'A')
      {
        Serial.print("Not ready value: ");
        Serial.println(line);
      }
      if (key == 'B')
      {
        Serial.println("\tClear");
        line = "";
      }
    }
  }
}
