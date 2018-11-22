//#include <Key.h>
#include <Keypad.h>
#include <glcd.h>
#include "fonts/allFonts.h"        
#include "bitmaps/allBitmaps.h"    

// IMPORTANT, DO NOT CHANGE!
char lastKey, Character;
byte K_count = 0;
unsigned long timer, interval = 2 * 100000UL; // interval = 2 seconds
bool lockout = true;
int cuenta=0;
int fila=0;
Image_t icon;

gText textArea;              
gText textAreaArray[3];     
gText countdownArea =  gText(GLCD.CenterX, GLCD.CenterY, 1, 1, Arial_14); 
         
const byte ROWS = 4; //cuatro filas, definidas dependiendo del teclado
const byte COLS = 3; //cuatro columnas, definidas dependiendo del teclado

// This array is used to change between the characters in the second array
// IMPORTANT, DO NOT CHANGE!
char Keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
 };

// The following array is what is printed when a key is pressed
// Format: { string of characters to be shown }
char * CharacterMask[ROWS][COLS] = {
  { "1", "2ABC", "3DEF" },
  { "4GHI", "5JKL", "6MNO" },
  { "7PQRS", "8TUV", "9WXYZ"},
  { "*", "0", "#" }
};

byte rowPins[ROWS] = {7,6,5,4}; //pines asignados a las filas del teclado
byte colPins[COLS] = {9,10,11}; //pines asignados a las columnas del teclado

//inicializar una instancia d la clase New Keypad
Keypad customKeypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS);


void setup()
{
  GLCD.Init();
  if(GLCD.Height >= 64)   
    icon = ArduinoIcon64x64;  
  else
    icon = ArduinoIcon64x32;  

  GLCD.ClearScreen(); 

  GLCD.SelectFont(System5x7, BLACK);  
  GLCD.CursorTo(0, 0);
}


void  loop()
{
  char customKey = customKeypad.getKey();
 if(cuenta>=21){fila++;
 cuenta=0;}
  //Check the key pressed. If the key is different, show it on a new line
  if (customKey && customKey != lastKey)
  {
    lastKey = customKey; // update lastKey
    K_count = 0; // This resets the counter so when a different key is pressed, you only see the NUMBER associated with that key.
    cuenta++;
  }
  else if (customKey=='1'){
    GLCD.CursorTo(cuenta, fila);
    GLCD.print(Character);
    cuenta++;
  }
  else{
   GLCD.CursorTo(cuenta, fila);
   GLCD.print(Character); 
  }
 
  if (customKey)
  {
    timer = micros(); // start a timer, when a key is pressed
    lockout = false; // allow the lockout timer to be checked
    lastKey = customKey; // update lastKey
    switch (customKey)
    {
      case '1':
        Character = *CharacterMask[0][0];                                                              // Character = '1'
        break;

      case '2':
      case '3':
        Character = *(CharacterMask[0][(customKey - '0') - 1] + K_count);                              // Character = '2' - ABC and '3' - DEF
        K_count++;
       if (K_count >= (byte)(strlen(CharacterMask[0][(customKey - '0') - 1])))
       K_count = 0;                                                                                 // Update the counter if the same key is pressed (counter rolls over)
        break;

      case '4':
      case '5':
      case '6':
        Character = *(CharacterMask[1][(customKey - '0') - 4] + K_count);
        K_count++;
        if (K_count >= (byte)(strlen(CharacterMask[1][(customKey - '0') - 4])))
          K_count = 0;
        break;

      case '7':
      case '8':
      case '9':
        Character = *(CharacterMask[2][(customKey - '0') - 7] + K_count);
        K_count++;
        if (K_count >= (byte)(strlen(CharacterMask[2][(customKey - '0') - 7])))
          K_count = 0;
        break;

      case '*':
        Character = *CharacterMask[3][0]; // shows *
        break;

      case '0':
        Character = *CharacterMask[3][1]; // shows 0
        break;

      case '#':
        Character = *CharacterMask[3][2]; // shows #
        break;

      default: // if something unexpected happens, set Character to 0
        Character = 0;
        break;
    }
  
  }
 
 
  
  if ((micros() - timer >= interval) && !lockout) //If a key was pressed and then 2 seconds has past, reset the lastKey and counter.
  {
    lastKey = '~'; //dummy character;
    K_count = 0; // Resets the counter
    lockout = true; // lockout is set to true, thus this IF statement does not continue to execute
  }
}
