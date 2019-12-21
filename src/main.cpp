/* xej-Nucleo-F401RE-and-HC05-Bluetooth.cpp
  Test Nucleo-F401RE with HC05 Bluetooth adapter
  
  Wanted to use it for upload of telemetry
  type a command and bt port and it will be echoed back
  
  pin-HC05  Pin-MBed
   TX   --- PA_12
   RX   --- PA_11
   +5V  --- +5 on CN6
               Also worked on 3.3V on CN6
   GND  --- GND on CN6
   STATE--- NC - not connected
   EN   --- NC - not connected
  
   If you cycle power on mbed you may need to close 
   and re-open the port connection which
   is pretty easy when using RealTerm.
  
   tested with Honbay® Wireless Bluetooth Host Serial Transceiver Module   
   Draws about 30mA when starting then drops back
   to 10mA when idle with a jump to about 20 mA 
   when transmitting.
   
   ***
  * By Joseph Ellsworth CTO of A2WH
  * Take a look at A2WH.com Producing Water from Air using Solar Energy
  * March-2016 License: https://developer.mbed.org/handbook/MIT-Licence 
  * Please contact us http://a2wh.com for help with custom design projects.
  ***
  
*/
#include "mbed.h"
#include "commons.h"
#include "multi-serial-command-listener.h"
#include "IR.h"
#include "imu.h"
#include "encoder.h"
#include "motor_commons.h"
#include "actuator.h"
#include "buzzer.h"
#include "../include/sen_fusion.h"
#define DEBUG_VIA_PRINTF 


  //  myled= !myled;
char myCommand[SCMD_MAX_CMD_LEN+1];

int char_int =0;
void char_to_int(void){
  char_int = myCommand[0] - '0';
}
Serial bt(PA_11, PA_12);  // This one works
Serial pc(USBTX, USBRX);     // WORKS AFTER CHANGING SOLDER BRIDGES

#define DEBUG

#ifdef DEBUG
Timer t_global ;
// PRIVATE VARS

static double now = 0;
static double last_time = 0;
#endif // DEBUG

double delT ;  


//FUNCTION PROTOTYPES
void commandCallback(char *, void *); 

int main(void) {
  ///*MAIN SETUP BEGINS HERE***********
  pc.baud(9600);
  bt.baud(9600);

  /////*MAIN SETUP ENDS HERE*
  #ifdef DEBUG
  #endif // DEBUG     

  while(1) { 
    ///*LOOP CODE BEGINS HERE*
      t_global.start();
      last_time = t_global.read_ms();
      
    //#ifdef DEBUG
    main_controller(0,0);
    //#endif // DEBUG
    
    now = t_global.read_us();
    t_global.stop();
    delT = now - last_time;

    ///*LOOP CODE ENDS HERE*
  }
  return 0;
} 

/*
 //IR_module.fire_and_get();
    //IR_module.display_IR();
    
   // bt.printf(" | f_l %3.3f%% | ",front_left_IR );
    //buzzer_off();   
  

     r_forward(00);
     l_forward(00);



     //buzzer_on();
           //desired_vel = 10.1;
    //main_controller(desired_vel,0);
    
     //ledtest = 1;
     //disp_enc();
    //printf("The time elapsed is %f \n", t_global.read());
    //read_encoder();
    //refresh_imu();
    //wait(0.5); 
    //pc.printf("right count =\n\r");  
    //buzzer_off();
    //  desired_vel = 5; // 5 m per sec
    //  const_Speed();
    //bt.printf("percentage: %3.3f%% ", rxtest.read()*100.0f);
    //bt.printf("normalized: 0x%04X \r\n", rxtest.read_u16());
    //bt.printf("analog val =  \r \n");
    //rightMotor.backward(100);
    //leftMotor.backward(100);

    //Lenable = 1;
    //Linput1 = 1;
    //Linput2 = 0;

    //r_forward(20);
    //l_backward(20);
 

    //main_controller(10,0);
      //bt.printf("PA_11/PA_12 %d seconds\r\n", i);
      //*bt.printf("front_left_IR value %d \r\n", front_left_IR);
     // myled = !myled;



struct SCMD *cmdProc = scMake(&bt, commandCallback, NULL)  ;
  //pc.printf("Test HC05 Bluetooth Connection !\r\n");
  



  if (myCommand[0] != 0) {     
          pc.printf("Command Recieved =%s\r\n", myCommand);
          bt.printf("\r\nCommand Recieved =%s\r\n", myCommand);
          if (strcmp(myCommand,"clear") == 0) {
            i = 0;
          }
          myCommand[0] = 0; // clear until we recieve the next command
      }        
    

*/
 

//UTILITY FUNCTION
void commandCallback(char *cmdIn, void *extraContext) {
  strcpy(myCommand, cmdIn);
  // all our commands will be recieved async in commandCallback
  // we don't want to do time consuming things since it could
  // block the reader and allow the uart to overflow so we simply 
  // copy it out in the callback and then process it latter. 
  
  // See data_log one of dependants of this library for example 
  // of using *extraContext
}
//*/