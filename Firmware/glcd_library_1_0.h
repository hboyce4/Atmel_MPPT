//***************************************************************************
//                     glcd_library.h
//
//  This file contains a library of routines for handling a graphics LCD
//
//
//****************************************************************************
//
//   GRAPHICS ROUTINES
//
//   glcd_line(x1,y1,x2,y2,colour)
//      * Draws a line from the first point to the second point
//        with the given colour.
//        - colour can be ON or OFF
//
//   glcd_rect(x1,y1,x2,y2,fill,colour)
//      * Draws a rectangle with upper left point (x1,y1) and lower
//        right point (x2,y2).
//        - fill can be YES or NO
//        - colour can be ON or OFF
//
//   glcd_bar(x1,y1,x2,y2,width,colour)
//      * Draws a bar (wide line) from the first point to the
//        second point.
//        - width is the number of pixels wide
//        - colour is ON or OFF
//
//   glcd_circle(x,y,radius,fill,colour)
//      * Draws a circle with center at (x,y)
//        - fill can be YES or NO
//        - colour can be ON or OFF
//
//******************************************************************************
//
//  TEXT WRITING ROUTINES
//
//  There are 5 fonts:
//
//   - 3x6 font and the associated code occupies approx 850 uint8_ts
//     This is numeric and uppercase only and is very hard to read
//
//   - 5x7 font and the associated code occupies approx 1.2k uint8_ts
//     This is a small but readable font giving 8 lines & 20 char per line
//
//   - 8x12 font and the associated code occupies approx 2K uint8_ts
//     This is good for readability and gives 5 lines
//     at 16 characters per line (with size = 1).
// 
//   - 9x16 font and the associated code occupies approx 2.7K uint8_ts
//     This is the best font if you have the space as it is very readable and
//     gives 4 lines at 14 characters per line (with size = 1).
//     
//   - 11x16 font and the associated code occupies approx 3.5K uint8_ts
//     This is also very readable and gives 4 lines at 10 characters per line
//     (with size = 1).
//
//   Any or all together will be linked by calling the appropriate functions.
// 
//
//   Before calling ANY text function the starting position and optionally other
//   characteristics must be set by calling glcd_setxy()
//
//   void glcd_setxy(x, y, size, colour)
//       x and y: The upper left coordinate of the first character
//       size:    An integer that scales the size of the text (default is 1)
//       colour:  ON or OFF (default is ON)
//
//   If you are happy with the defaults you only need to specify x & y, for example:
//       glcd_setxy(0, 0);          // top left hand corner
//
//   All text functions update x and y automatically so that the invisible cursor is
//   ready for the next character.  The character \r will return the cursor to the
//   left margin and \n will cause the y position to step down a line.
//
//   Note that character wrapping is not supported, strings are truncated at the
//   edge of the display.
//
//   The data is stored in global variables and, as a shortcut, these can be accessed
//   directly.  The variables are:
//      int8 glcd_x, glcd_y         // Coordinates
//      int8 glcd_size              // Size
//      bool glcd_colour            // Colour
//
//   The writing functions are:
//
//   glcd_putc36(char)
//      * Write char in 3x6 font
//
//   glcd_text36(textptr)
//      * Write the null terminated text pointed to by textptr in 3x6 font
//
//   glcd_putc57(char)
//      * Write char in 5x7 font
//
//   glcd_text57(textptr)
//      * Write the null terminated text pointed to by textptr in 5x7 font
//
//   The glcd_putcXX(char) functions can be used in printf().  For example:
//      printf(glcd_char812, "Temperature is %d~", temperature);
//      * Note that the tild (~) character is replaced with a degrees C symbol
//        in the 8x12 font
// 
//
//**********************************************************************************
//    LCD DRIVER
//
//   The above routines are dependent on a graphics driver that exposes the following
//   function:
//
//   glcd_pixel(x,y,colour)
//      * Sets the pixel to the given colour.
//        - colour can be ON or OFF
//
//
//   Other functions that the driver should supply (but are not used by this library) are:
//
//   glcd_init()
//      * Initilise the display
//      * Must be called before any other function.
//
//   glcd_fillScreen(colour)
//      * Fills the entire LCD with the given colour.
//        - colour can be ON or OFF
//
//
//**********************************************************************************

 //   glcd_line(x1,y1,x2,y2,colour)
 //      * Draws a line from the first point to the second point
 //        with the given colour.
 //        - colour can be ON or OFF
 //
 //   glcd_rect(x1,y1,x2,y2,fill,colour)
 //      * Draws a rectangle with upper left point (x1,y1) and lower
 //        right point (x2,y2).
 //        - fill can be YES or NO
 //        - colour can be ON or OFF
 //
 //   glcd_bar(x1,y1,x2,y2,width,colour)
 //      * Draws a bar (wide line) from the first point to the
 //        second point.
 //        - width is the number of pixels wide
 //        - colour is ON or OFF
 //
 //   glcd_circle(x,y,radius,fill,colour)
 //      * Draws a circle with center at (x,y)
 //        - fill can be YES or NO
 //        - colour can be ON or OFF
 
 #include "SG12232A_Driver_1_0.h"
 
 void glcd_setxy(uint8_t x, uint8_t y,uint8_t sz, bool cl);
 void glcd_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool colour);
 void glcd_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill, bool colour);
 void glcd_bar(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t width, bool colour);
 void glcd_circle(uint8_t x, uint8_t y, uint8_t radius, bool fill, bool colour);
 void glcd_putc36(char c);
 void glcd_text36(char* textptr);
 void glcd_putc57(char c);
 void glcd_text57(char* textptr);