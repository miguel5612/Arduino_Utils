/*
  GLCD Library - Hello World
 
  This sketch prints "Hello World!" to the LCD
  and shows the time in seconds since reset.
 
  The circuit:
  See the inlcuded documentation in glcd/doc directory for how to wire
  up the glcd module. glcd/doc/GLCDref.htm can be viewed in your browser
  by clicking on the file.
 */

// include the library header
#include <glcd.h>
#include "config/ks0108_Mega.h" // Para Arduino Mega

// include the Fonts
#include <fonts/allFonts.h>

void setup() 
{
  // Initialize the GLCD 
  GLCD.Init();

  // Select the font for the default text area
  GLCD.SelectFont(System5x7);

 GLCD.ClearScreen();
 GLCD.CursorTo(0, 0);
  // GLCD.print("LCD Grafico!");
  //GLCD.print("123456789012345678901");
  GLCD.print("Hello, Word!");
  //delay(3000);
}


void loop() 
{
  //GLCD.ClearScreen();
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  GLCD.CursorTo(0, 1);

  // print the number of seconds since reset:
  GLCD.print(millis()/1000);

  delay(1000);
}
