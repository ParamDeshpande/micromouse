
#include "../include/Utils.h"

/*/Experimental  !!
void wait_for_G_press(void){

    Serial.begin(115200);
    while(true) { // remain here until told to break
  if(Serial.available() > 0) // did something come in?
    if(Serial.read() == 'Q') // is that something the char G?
      break;
  }
}
*/