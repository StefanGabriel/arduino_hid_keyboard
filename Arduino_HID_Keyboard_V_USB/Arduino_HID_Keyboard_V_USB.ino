/* Anca Stefan Gabriel
 * SMP 2020
 */  

//import the libraries used
#include <Keypad.h>
#include "UsbKeyboard.h"
#include <util/delay.h>

//the next 2D array will contain the
//characters that we have on our 4x4
//keypad
char keys[4][4] = 
  {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };

//we need to declare all the pins used
//the first 4 pins are for the rows and the
//next 4 for the columns. The way these works
//(we have 16 characters/buttons and only 8 pins) is that
//for each button we will have two indicators: Row and Column.
//When a button is pressed we will identify which row and which
//column corresponds to that button (when a button is pressed,
//the Row and Column will be shorted). For example, button "1" is
//identified by R1 and C1 and when we press that button we can see
//that if we measure the resistance between R1 and C1 we will
//obtain a value close to 0.
byte row_pins[] = {6, 7, 8, 9};
byte column_pins[] = {10, 11, 12, 13};
Keypad keypad = Keypad(makeKeymap(keys), row_pins, column_pins, 4, 4);

//declare the pins used by the
//buttons. We will use the analog
//pins as digital pins
#define ptsc A0 
#define details A1 
#define pass A2
#define copy_button A3
#define paste_button A4
#define cut_button A5

void setup() { 
  //set the pins used by the buttons as
  //INPUT. We use hardware pullup resistors
  //but the Atmega chip has pullup resistors (20KOhms)
  //that we can access by declaring the inputs
  //as INPUT_PULLUP
  pinMode(ptsc, INPUT);
  pinMode(details, INPUT);
  pinMode(pass, INPUT);
  pinMode(copy_button, INPUT);
  pinMode(paste_button, INPUT);
  pinMode(cut_button, INPUT);
  
  //deactivate Timer 0 overflow interrupt
  //Timer 0 interferes with the
  //delays and any other time
  //related tasks used by the 
  //UsbKeyboard library  
  TIMSK0&=!(1<<TOIE0);
}

//because Timer 0 is disabled, we will a library
//that will give us delays, for example <util/delay.h>,
//which contains special functions for busy-wait delay loops
void loop() {   
  UsbKeyboard.update();
  
  //when a button is pressed we will use a defined
  //scenario: copy (CTRL+C), cut(CTRL+V) etc.
  //you can send a phrase, a number, 
  //read a temperature from a sensor and
  //send it in Celsius or Fahrenheit, etc.
  if (digitalRead(ptsc) == 0) {         
    UsbKeyboard.sendKeyStroke(0x46);     
    _delay_ms(200);   
  }
  
  if (digitalRead(pass) == 0) {         
    UsbKeyboard.sendKeyStroke(KEY_S, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_T);
    UsbKeyboard.sendKeyStroke(KEY_R);
    UsbKeyboard.sendKeyStroke(KEY_O);
    UsbKeyboard.sendKeyStroke(KEY_N);
    UsbKeyboard.sendKeyStroke(KEY_G);
    UsbKeyboard.sendKeyStroke(0x2d);
    UsbKeyboard.sendKeyStroke(KEY_P, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_A);
    UsbKeyboard.sendKeyStroke(KEY_S);
    UsbKeyboard.sendKeyStroke(KEY_S);
    UsbKeyboard.sendKeyStroke(KEY_W);
    UsbKeyboard.sendKeyStroke(KEY_O);
    UsbKeyboard.sendKeyStroke(KEY_R);
    UsbKeyboard.sendKeyStroke(KEY_D);
    _delay_ms(200);   
  }
  
  if (digitalRead(details) == 0) {         
    UsbKeyboard.sendKeyStroke(KEY_A, MOD_SHIFT_LEFT);     
    UsbKeyboard.sendKeyStroke(KEY_N, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_C, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_A, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_SPACE); 
    UsbKeyboard.sendKeyStroke(KEY_S, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_T, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_E, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_F, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_A, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_N, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_SPACE); 
    UsbKeyboard.sendKeyStroke(KEY_S, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_M, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_P, MOD_SHIFT_LEFT); 
    UsbKeyboard.sendKeyStroke(KEY_2); 
    UsbKeyboard.sendKeyStroke(KEY_0); 
    UsbKeyboard.sendKeyStroke(KEY_2); 
    UsbKeyboard.sendKeyStroke(KEY_0); 
    _delay_ms(200);   
  }
  
  if (digitalRead(copy_button) == 0) {     
    UsbKeyboard.sendKeyStroke(KEY_C, MOD_CONTROL_LEFT);        
    _delay_ms(200);   
  }
  
  if (digitalRead(cut_button) == 0) {     
    UsbKeyboard.sendKeyStroke(KEY_X, MOD_CONTROL_LEFT);        
    _delay_ms(200);   
  }
  if (digitalRead(paste_button) == 0) {     
    UsbKeyboard.sendKeyStroke(KEY_V, MOD_CONTROL_LEFT);  
        
    _delay_ms(200);   
  }
  
  //get the key pressed and send the code to USB
  char key = keypad.getKey();
  if(key){
    byte value = decode_keypad_entry(key);
    if((value == 0x20 || value == 0x25) && (key == '*' || key == '#')){
      UsbKeyboard.sendKeyStroke(value, MOD_SHIFT_LEFT);
    }
    else {
      UsbKeyboard.sendKeyStroke(value);
    }
    _delay_ms(200);
  }
}

//to have less code in our loop() we will use a 
//function that will have one paramether (the key pressed)
//and will return the value (as a byte) of the corresponding
//HID code for USB
byte decode_keypad_entry(char key){
  if(key == '1'){ 
    return KEY_1;
  }
    
  if(key == '2')
    return KEY_2;
    
  if(key == '3')
    return KEY_3;
    
  if(key == '4')
    return KEY_4;
    
  if(key == '5')
    return KEY_5;
    
  if(key == '6')
    return KEY_6;
    
  if(key == '7')
    return KEY_7;
    
  if(key == '8')
    return KEY_8;
    
  if(key == '9')
    return KEY_9;
    
  if(key == '0')
    return KEY_0;
  
  if(key == 'A')
    return KEY_A;
  
  if(key == 'B')
    return KEY_B;
  
  if(key == 'C')
    return KEY_C;
    
  if(key == 'D')
    return KEY_D;
    
  if(key == '*')
    return 0x25;
    
  if(key == '#')
    return 0x20;
}
