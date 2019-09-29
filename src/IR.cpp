/*
IR.cpp - Library for setting pin modes, creating pin array, and querying IR sensors from set pins
Author: Alexander Hadik
Team: MicroMau5 - Tristan Paine, Kevin Jung, Alexander Hadik
*/

#include "../include/commons.h"
#include "mbed.h"
#include "../include/IR.h"

//*

unsigned long last_time = 0;
unsigned long now_time = 0;
unsigned long time_diff = 0;

    bool front_l_tx_fired_before ;  
    bool front_r_tx_fired_before ;
    bool diag_l_tx_fired_before  ;
    bool diag_r_tx_fired_before ;
    bool side_l_tx_fired_before ;
    bool side_r_tx_fired_before ;
    bool front_r_rx_read_before ;
    bool front_l_rx_read_before ;
    bool side_l_rx_read_before ;
    bool side_r_rx_read_before ;
    bool diag_r_rx_read_before ;
    bool diag_l_rx_read_before ;

  //Private function prototype
  

//constructor
//First front LTX diag LTX side 
IR::IR(int front_l_tx_Pin, int front_r_tx_Pin, int diag_l_tx_Pin, int diag_r_tx_Pin, int side_l_tx_Pin,int side_r_tx_Pin ,int front_l_rx_Pin, int front_r_rx_Pin, int side_l_rx_Pin, int side_r_rx_Pin, int diag_l_rx_Pin, int diag_r_rx_Pin)
{
  
    front_l_tx =front_l_tx_Pin ;  
    front_r_tx =front_r_tx_Pin ;  
     diag_l_tx = diag_l_tx_Pin ;  
     diag_r_tx = diag_r_tx_Pin ; 
     side_l_tx = side_l_tx_Pin ; 
     side_r_tx = side_r_tx_Pin ;   
    front_l_rx =front_l_rx_Pin ;  
    front_r_rx =front_r_rx_Pin ;  
     side_l_rx = side_l_rx_Pin ; 
     side_r_rx = side_r_rx_Pin ; 
     diag_l_rx = diag_l_rx_Pin ; 
     diag_r_rx = diag_r_rx_Pin ; 

    DigitalOut front_l_tx(PC_15);
    AnalogIn front_l_rx(PC_2);
    
    /*
    pinMode(front_l_tx, OUTPUT);
    pinMode(front_r_tx, OUTPUT);

    pinMode(diag_l_tx, OUTPUT);
    pinMode(diag_r_tx, OUTPUT);

    pinMode(side_l_tx, OUTPUT);
    pinMode(side_r_tx, OUTPUT);

    pinMode( front_r_rx, INPUT );
    pinMode( front_l_rx, INPUT );
    pinMode( side_l_rx, INPUT );
    pinMode( side_r_rx, INPUT );
    pinMode( diag_r_rx, INPUT );
    pinMode( diag_l_rx, INPUT );


/*
     int irArray[3][4]={
	  {front_l_tx,  front_r_tx,  front_l_rx,   front_r_rx},
	  {diag_l_tx,   diag_r_tx,   diag_l_rx,    diag_r_rx},
	  {side_l_tx,   side_r_tx ,  side_l_rx,    side_r_rx}
	};
//*/
}

/*
void IR::reset_params(void){

  now_time = micros();
  last_time = now_time;
  
  front_l_tx_fired_before = false ;  
  front_r_tx_fired_before = false ;
  diag_l_tx_fired_before  = false  ;
  diag_r_tx_fired_before  = false ;
  side_l_tx_fired_before  = false ;
  side_r_tx_fired_before  = false ;
  front_r_rx_read_before  = false ;
  front_l_rx_read_before  = false ;
  side_l_rx_read_before   = false;
  side_r_rx_read_before   = false;
  diag_r_rx_read_before   = false;
  diag_l_rx_read_before   = false;

}
*/

//ARRAY TO STORE LEFT SENSOR values
//int IR_readings[3][2];

void IR::powerUP_Tx(int ledPin){
    ledPin = 1;
    //digitalWrite(ledPin, HIGH);
}

void IR::powerDOWN_Tx(int ledPin){
    ledPin = 0;
}
float IR::get_Rx(int rx_pin_value){
  return rx_pin_value;
}


float front_left_IR    = 0;
float front_right_IR   = 0; 
float diag_left_IR     = 0;
float diag_right_IR    = 0;
float side_left_IR     = 0;
float side_right_IR    = 0;

void IR::map_IR(void){
  front_left_IR    = IR_readings[0][0];
  front_right_IR   = IR_readings[0][1]; 
  diag_left_IR     = IR_readings[1][0]; 
  diag_right_IR    = IR_readings[1][1]; 
  side_left_IR     = IR_readings[2][0]; 
  side_right_IR    = IR_readings[2][1]; 
}


void IR::fire_and_get(void){

  //at t=0
  powerUP_Tx(front_l_tx);
  wait_us(60);
  IR_readings[0][0] = get_Rx(front_l_rx);
  powerDOWN_Tx(front_l_tx); 
  wait_us(80);

  powerUP_Tx(front_r_tx);
  wait_us(60);
  IR_readings[0][1] = get_Rx(front_r_rx);
  powerDOWN_Tx(front_r_tx);
  wait_us(80);

  powerUP_Tx(diag_l_tx);
  wait_us(60);
  IR_readings[1][0] =  get_Rx(diag_l_rx);
  powerDOWN_Tx(diag_l_tx);    
  wait_us(80);

  powerUP_Tx(diag_r_tx);
  wait_us(60);
  IR_readings[1][1] =  get_Rx(diag_r_rx);
  powerDOWN_Tx(diag_r_tx);
  wait_us(80);

  powerUP_Tx(side_l_tx);
  wait_us(60);
  IR_readings[2][0] =  get_Rx(side_l_rx);
  powerDOWN_Tx(side_l_tx);    
  wait_us(80);

  powerUP_Tx(side_r_tx);
  wait_us(60);
  IR_readings[2][1] =  get_Rx(side_r_rx);
  powerDOWN_Tx(side_r_tx);    
  wait_us(80);

  map_IR();
}

/*

  void IR::display_IR(void){

  Serial.print("  front left  ");
  Serial.print(analogRead(A0));


  Serial.print("  front right  ");
  Serial.print(IR_readings[0][1]);
  

  Serial.print("  diag left ");
  Serial.print(IR_readings[1][0]);


  Serial.print("  diag right  ");
  Serial.print(IR_readings[1][1]);
  

  Serial.print("  side left ");
  Serial.print(IR_readings[2][0]);


  Serial.print("  side right  ");
  Serial.print(IR_readings[2][1]);
  
  Serial.println("");
//*
  }
*/
IR IR_module( front_l_tx_Pin_No,  front_r_tx_Pin_No,  diag_l_tx_Pin_No,  diag_r_tx_Pin_No,  side_l_tx_Pin_No, side_r_tx_Pin_No , front_l_rx_Pin_No,  front_r_rx_Pin_No,  side_l_rx_Pin_No, side_r_rx_Pin_No,  diag_l_rx_Pin_No,  diag_r_rx_Pin_No);





/*

  now_time = micros();
    

      Serial.print(" time ");
      Serial.print(now_time);

      Serial.print("  last time ");
      Serial.print(last_time);

      
  time_diff = (now_time - last_time);

      Serial.print("  time diff ");
      Serial.print(time_diff);



      Serial.println(" ");

  //firing front sensors
  
  //Fire left at t = 0. //  5 US buffer
  if(time_diff > 5 AND time_diff < 60){
    if(front_l_tx_fired_before == false){
      
      Serial.print("  Fired LTX at ");
      Serial.print(time_diff);
      
      powerUP_Tx(front_l_tx);
      front_l_tx_fired_before =true;
    }
    
  }
  
  //Measure / get rx op
  else if(time_diff > 60 AND time_diff < 140){
    if(front_l_rx_read_before == false){
      
      Serial.print("  Read LRX at ");
      Serial.print(time_diff);
      
      
      IR_readings[0][0] = get_Rx(front_l_rx);
      front_l_rx_read_before = true;
      powerDOWN_Tx(front_l_tx);    
    }
  }
  
  //80US delay

  //Firing right sensors
  else if(time_diff > 140 AND time_diff < 200){
    if(front_r_tx_fired_before == false){
      powerUP_Tx(front_r_tx);
      front_r_tx_fired_before =true;
    }
  }
  else if(time_diff > 200 AND time_diff < 280){
  if(front_r_rx_read_before == false){
      IR_readings[0][1] = get_Rx(front_r_rx);
      front_r_rx_read_before = true;
      powerDOWN_Tx(front_r_tx);
    }
  }


  //Firing diagonals Left 

  else if(time_diff > 280 AND time_diff < 340){
    if(diag_l_tx_fired_before == false){    
      powerUP_Tx(diag_l_tx);
      diag_l_tx_fired_before = true;
    }
  }

  else if(time_diff > 340 AND time_diff < 420){
  if(diag_l_rx_read_before == false){
      IR_readings[1][0] =  get_Rx(diag_l_rx);
      diag_l_rx_read_before = true;
      powerDOWN_Tx(diag_l_tx);    
    }
  }
  
  //Firing diag right

  else if(time_diff > 420 AND time_diff < 480){
        if(diag_r_tx_fired_before == false){
        powerUP_Tx(diag_r_tx);
        diag_r_tx_fired_before = true;
        }
  }

  else if(time_diff > 480 AND time_diff < 560){
    if(diag_r_rx_read_before == false){
      IR_readings[1][1] =  get_Rx(diag_r_rx);
      diag_r_rx_read_before = true;
        powerDOWN_Tx(diag_r_tx);

    }
  }

  
  //Side sensors

  //Firing diagonals Left 

  else if(time_diff > 560 AND time_diff < 620){
     if(side_l_tx_fired_before == false){    
        powerUP_Tx(side_l_tx);
        side_l_tx_fired_before = true; 
     }
  }
  else if(time_diff > 620 AND time_diff < 700){
    if(side_l_rx_read_before == false){
    IR_readings[2][0] =  get_Rx(side_l_rx);
    side_l_rx_read_before = true;
    powerDOWN_Tx(side_l_tx);    
    }
  }
  
  //Firing side right

  else if(time_diff > 700 AND time_diff < 760){
    if(side_r_tx_fired_before == false){
      powerUP_Tx(side_r_tx);
      side_r_tx_fired_before = true;
    }

  }
  else if(time_diff > 760){
    IR_readings[2][1] =  get_Rx(side_r_rx);
      powerDOWN_Tx(side_r_tx);    
    //reset_params();
  }//*/
  



//Create an obj for IR ARRAY

//change this to get the sensor value
  //int sensorReading = readSensor(4, side_l_rx);
  //Serial.println(sensorReading);
  //
 //pinMode(4, OUTPUT );
 //digitalWrite(4, HIGH);
  //*/