#include <Sparki.h> // include the sparki library
const String vers = "0.0.1";
const int servo_Left = -95;
const int servo_Center = -2;
const int servo_Right = 75;
//int edgeLimit = 500; // if edge detect is below this value, no surface underneath
int EDGE_LFT_LIMIT = -1;
int EDGE_RGT_LIMIT = -1;
int lightLeft   = -1;   // measure the left IR sensor
int lightCenter = -1; // measure the center IR sensor
int lightRight  = -1;  // measure the right IR sensor
int edgeLeft   = -1;   // measure the left edge IR sensor
int edgeRight  = -1;  // measure the right edge IR sensor
int cm = -1; // measures the distance with Sparki's eyes
int code = -1;

void get_env() {
  // top light sens
  lightLeft   = sparki.lightLeft();  
  lightCenter = sparki.lightCenter();
  lightRight  = sparki.lightRight(); 
  // bott edge sens
  edgeLeft   = sparki.edgeLeft();    
  edgeRight  = sparki.edgeRight();   
  
  cm = sparki.ping();  // get front dist w/ eyes

}

void init_feedback_sequence() {
  //get_env();


  for (int i = 0; i < 200; i=i+1)
  {
    sparki.beep(i*10); // plays a note proportional to the distance
    delay(5);  
    //sparki.sendIR(i);
  }
  
  sparki.servo(servo_Left); // servo to -90 pos (lft)
  delay(500); 

  sparki.servo(servo_Center); // servo to 0 pos (fwd)
  delay(500); 
  
  sparki.servo(servo_Right); // servo to 90 pos (rgt)
  delay(500);  

  sparki.servo(17); // servo to 0 pos (fwd)
  delay(500); 
  
  sparki.servo(-11); // servo to 90 pos (rgt)
  delay(300); 

  sparki.servo(servo_Center); // servo to 0 pos (fwd)
  delay(100); 

}

void decide_where_to_go() {
	//look right and measure
	sparki.servo(servo_Left);
	delay(2000);
	int left_cm = sparki.ping(); 
	// look left and measure
	sparki.servo(servo_Right);
	delay(2000);
	int right_cm = sparki.ping(); 
	// look forward
	sparki.servo(servo_Center);
	// compare right to left and go
	sparki.clearLCD();
	sparki.print("LEFT: ");
	sparki.println(left_cm);
	sparki.print("RGHT: ");
	sparki.println(right_cm);
	if (left_cm <= right_cm) {
		sparki.println("GOING RIGHT");
		sparki.updateLCD();
		sparki.moveRight(90);
		delay(1000);
		sparki.moveForward();
	} else {
		sparki.println("GOING LEFT");
		sparki.updateLCD();
		sparki.moveLeft(90);
		delay(1000);
		sparki.moveForward();
	}
}

void wall_detection_check() {
		// if far off
	cm = sparki.ping(); 
		// if <40cm green
	if (cm>50){
		sparki.RGB(RGB_OFF);
	} else if (cm>35) {
		sparki.RGB(RGB_GREEN);
		// if <35cm blue
	} else if (cm>15) {
		sparki.RGB(RGB_BLUE);
		// if <15cm red
	} else if (cm>6) {
		sparki.RGB(RGB_RED);
		// if <=6cm stop
	} else {
		sparki.moveStop();
		decide_where_to_go();
	}
	
	
	
}


void update_display() {
  get_env();
  sparki.clearLCD();
  
  sparki.print("LITE LFT: ");
  sparki.print(lightLeft);
  sparki.println(String("  " + vers));
  sparki.print("LITE CTR: ");
  sparki.println(lightCenter);
  sparki.print("LITE RGT: ");
  sparki.println(lightRight);
  
  sparki.print("EDGE LFT (");
  sparki.print(EDGE_LFT_LIMIT);
  sparki.print("): ");
  sparki.println(edgeLeft);
  sparki.print("EDGE RGT (");
  sparki.print(EDGE_RGT_LIMIT);
  sparki.print("): ");
  sparki.println(edgeRight);

  sparki.print("Ping: "); 
  sparki.print(cm);
  
  code = sparki.readIR();
  sparki.print("   IR: "); 
  sparki.println(code);

  sparki.print("VAL: "); 
  sparki.print(servo_Left);
  sparki.print(" "); 
  sparki.print(servo_Right);
  sparki.print(" ");
  sparki.print(servo_Center);

  sparki.updateLCD();

}


void get_IR() {
  code = sparki.readIR();
  switch(code){
   
  // Movement buttons
  case 70: sparki.moveForward(); break;
  case 21: sparki.moveBackward(); break;
  case 67: 
  case 71: sparki.moveRight(); break;
  case 69:
  case 68: sparki.moveLeft(); break;
  case 64: sparki.moveStop(); 
           sparki.gripperStop();
           break;
  
  // Gripper Buttons
  case 9:  sparki.gripperOpen(); break;
  case 7:  sparki.gripperClose(); break;
  
  // buzzer
  case 13:  sparki.beep(); break;
  
  // Servo Buttons
  case 12:  sparki.servo(servo_Left); break;
  case 24:  sparki.servo(servo_Center); break;
  case 94:  sparki.servo(servo_Right); break;
  
  // RGB LED
  case 90:  sparki.RGB(RGB_OFF); break;
  case 66:  sparki.RGB(RGB_RED); break;
  case 82:  sparki.RGB(RGB_GREEN); break;
  case 74:  sparki.RGB(RGB_BLUE); break;
  
  default:
    break;
  }
}

void edge_avoidance() {
  get_env();
  if ( (edgeLeft < EDGE_LFT_LIMIT) && (edgeRight > EDGE_RGT_LIMIT) ) // if no surface under left sensor
  {
    sparki.moveBackward(5);
    sparki.moveRight(35); // turn right
  }

  if ( (edgeLeft > EDGE_LFT_LIMIT) && (edgeRight < EDGE_RGT_LIMIT) ) // if no surface under right sensor
  {
    sparki.moveBackward(5);
    sparki.moveLeft(35); // turn left
  }

  if ( (edgeLeft < EDGE_LFT_LIMIT) && (edgeRight < EDGE_RGT_LIMIT) ) // if no surface under either sensor
  {
    sparki.moveBackward(5); // straight back
    sparki.moveLeft(180); // turn around
  }

}


void setup() 
{
  EDGE_LFT_LIMIT = sparki.edgeLeft()-100;
  EDGE_RGT_LIMIT = sparki.edgeRight()-100;
  // delay(3000);
  init_feedback_sequence();
  
}

void loop() {

  // if ( get_IR() == false ) {    
  //   edge_avoidance();
  // }
//  get_IR();
  update_display();
  edge_avoidance();
  wall_detection_check();
  code = sparki.readIR();
  switch(code){
   
  // Movement buttons
  case 70: sparki.moveForward(); break;
  case 21: sparki.moveBackward(); break;
  case 67: 
  case 71: sparki.moveRight(); break;
  case 69:
  case 68: sparki.moveLeft(); break;
  case 64: sparki.moveStop(); 
           sparki.gripperStop();
           break;
  
  // Gripper Buttons
  case 9:  sparki.gripperOpen(); break;
  case 7:  sparki.gripperClose(); break;
  
  // buzzer
  case 13:  sparki.beep(); break;
  
  // Servo Buttons
  case 12:  sparki.servo(servo_Left); break;
  case 24:  sparki.servo(servo_Center); break;
  case 94:  sparki.servo(servo_Right); break;
  
  // RGB LED
  case 90:  sparki.RGB(RGB_OFF); break;
  case 66:  sparki.RGB(RGB_RED); break;
  case 82:  sparki.RGB(RGB_GREEN); break;
  case 74:  sparki.RGB(RGB_BLUE); break;
  
  default:
    break;
  }
  //delay(100); // wait 0.1 seconds
}