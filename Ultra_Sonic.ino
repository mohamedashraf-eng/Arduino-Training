 /***************************************************************/
  /*
    *           ** UltraSonic Sensor Manipulating ** 
              
    * Author:    Mohamed Ashraf (Wx)
    * Project:   Controlling ultrasonic sensor with potentiometer. 
    * Data:      7/21/2021 
    
    * 
  */
/***************************************************************/
//========================================== CODE START ============================================================>
  
/*****************************************************************/ 
  #define ENABLE true // that will disable the program (STATIC)   <- Enable the code
/****************************************************************/ 


  #if (ENABLE == true)  //  ENABLED = TRUE - Program working
  
  /* HIGH LEVEL CODING SECTION START: */
  
  #pragma pack(1)   // Disable compiler padding.
  typedef struct {  
    
        uint8_t     /* <size:0:13:pins- size:4:inf:bits > */
        
         Trigger_pin : 4,      // Trigger pin assign for multiple ultrasonic sensors . (4 bits size) 0000
         Echo_pin    : 4;     // Echo pin assign for multiple ultrasonic sensosrs.     (4 bits size) 0000
                
       float    /* Maximum disance can "HC-SR04" handle is (1.5 to 2)meter (-+5%) error */
       
         Duration    ,   // Duration calculation for multiple ultrasonic sensors. (10 bits size) 00|00 0000 0000
         Distance    ;   // Distance calculation for multiple ultrasonic sensors. (10 bits size) 00|00 0000 0000
       
    }UltraSonic; // #end struct_Ultrasonic
    
                          /* Pin assign to ultrasonic_1 field. */
    UltraSonic ultrasonic_1 = {
                              .Trigger_pin = 3,   // Assigning 3 to trigger pin.
                              .Echo_pin    = 4  //  Assigning 4 to echo pin.
                              }; //#end assign for ultrasonic_1
                              
    UltraSonic *UltraSonic_1_ptr = (&ultrasonic_1);        // To access it by reference.
          
  /* HIGH LEVEL CODING SECTION END: */
//============================================================================================================>
  /* DEFINES SECTION START: */

   #define Sound_Speed (0.03430)

   #define Potentiometer_pin (A1)
      
   #define GREEN_LED 5U
   #define RED_LED   6U
   
  /* DEFINES SECTION END: */
//============================================================================================================>
  /* VRIABLE DEFINETION START: */
  
  uint16_t PotValue;
  
  unsigned long TIME = 0U;
  unsigned long SYSTEM_TIME = 0U;
  
  /* VRIABLE DEFINETION END: */
//============================================================================================================>
  void setup() 
  { 
    Serial.begin(57600); // start UART communication to view serial monitor.
/* --------------- --------------- --------------- --------------- --------------- --------------- --------------- */     
 /* Ultra Sonic sensor 1 -- Initlization Section start: */
 
    pinMode(ultrasonic_1.Trigger_pin,OUTPUT);
    digitalWrite(ultrasonic_1.Trigger_pin,LOW);
    pinMode(ultrasonic_1.Echo_pin,INPUT);
    digitalWrite(ultrasonic_1.Echo_pin,LOW);
    
 /* Ultra Sonic sensor 1 -- Initlization Section end: */
/* --------------- --------------- --------------- --------------- --------------- --------------- --------------- */  
    pinMode(Potentiometer_pin,INPUT);

    pinMode(GREEN_LED,OUTPUT); digitalWrite(GREEN_LED,LOW);
    pinMode(RED_LED,OUTPUT);   digitalWrite(RED_LED,LOW);


    TIME = millis(); SYSTEM_TIME = millis();
  }// #END VOID SETUP
  
  void loop() 
  {
     #define SysDelay 100U  // Delay to stablize the system reading.
      
     if((millis() - SYSTEM_TIME) > SysDelay){
      
     
    /* Ultra Sonic sensor 1 -- Initlization Section start: */
    
    digitalWrite(ultrasonic_1.Trigger_pin,LOW);
    delayMicroseconds(2u);
    digitalWrite(ultrasonic_1.Trigger_pin,HIGH);
    delayMicroseconds(10u);
    digitalWrite(ultrasonic_1.Trigger_pin,LOW);

    (UltraSonic_1_ptr->Duration) = pulseIn(ultrasonic_1.Echo_pin,HIGH);
   
    (UltraSonic_1_ptr->Distance) = ( ((UltraSonic_1_ptr->Duration) * Sound_Speed ) /2U) + 0.31;
    
    /* For validity test only -- Takes more space to init urat communication*/ // Comment while in action.
    //Serial.print("Distance: "); Serial.print(ultrasonic_1.Distance); Serial.println(" Cm");


  /* Ultra Sonic sensor 1 -- Initlization Section end: */
  
/* --------------- --------------- --------------- --------------- --------------- --------------- --------------- */   
 /* Potentiometer -- value handle Section start: */
    #define MinValue 30U     
    #define MaxValue 200U
    
    PotValue = map(analogRead(Potentiometer_pin),0U,1023U,MinValue,MaxValue);    // Min value - Max value can be changed.
    
    /* For validity test only -- Takes more space to init urat communication*/ // Comment while in action.
    //Serial.print("PotValue: ");Serial.println(PotValue);  
 /* Potentiometer -- value handle Section end: */   
/* --------------- --------------- --------------- --------------- --------------- --------------- --------------- */ 
 /* Actions Section start: */
 
      /* If the distance value between 0 - (30-200) */
    
    if( ((UltraSonic_1_ptr->Distance) > 0U) && ( (UltraSonic_1_ptr->Distance) < PotValue) ) 
    {
      digitalWrite(GREEN_LED,HIGH);
      digitalWrite(RED_LED,LOW);
    } // #END IF

      /* If the distance value between (30-200) - 200 */
    else if( ( (UltraSonic_1_ptr->Distance) > PotValue ) && ( (UltraSonic_1_ptr->Distance) < 200U) ) 
     { 
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(RED_LED,HIGH);
     } // #END ELSE IF
     
    else 
    {
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(RED_LED,LOW);
    } // #END ELSE
  
    #define event_based_delay 250U // Not > 250 -

    #if (event_based_delay <= 250U)
    
    if((millis() - TIME) >= event_based_delay){
      
    /* For validity test only -- Takes more space to init urat communication*/ // Comment while in action.
    
    Serial.print("Green Range now is from 0 to "); Serial.println(PotValue);
    Serial.print("Red Range now is from "); Serial.print(PotValue); Serial.println(" to 200.");
    Serial.println(" ");

    TIME = millis();   // Reset the delay.
    
    } // #END IF - MILLIS
    
    #endif
    SYSTEM_TIME = millis();
  } // #END IF - MILLIS()
 /* Actions Section end: */
/* --------------- --------------- ERROR HANDLING SECTION START: --------------- --------------- --------------- */ 
/* --------------- --------------- ERROR HANDLING SECTION END: --------------- --------------- --------------- */ 

  //delay(500); // Reading purpose // Comment.
  } // #END VOID LOOP
//================================ FUNCTIONS ====================================================================>

//========================================== CODE END ============================================================>
#else (exit(0))
#endif
