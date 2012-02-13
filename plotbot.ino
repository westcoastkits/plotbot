// WestCoastKits Plobot v0.5
//
// Control both Stepper motors at the same time with different speeds
// and accelerations. 
// Requires the AFMotor library (https://github.com/adafruit/Adafruit-Motor-Shield-library)
// And AccelStepper with AFMotor support (https://github.com/adafruit/AccelStepper)

#include <AccelStepper.h>
#include <AFMotor.h>

// two stepper motors one on each port
AF_Stepper motor1(200, 1);
AF_Stepper motor2(200, 2);



// Stepper motor speed in revolutions per minute
int stepperMotorSpeed = 60;

// number of steps per centimeter, calculated from radius of spool
// and the number of steps per radius
int StepUnit = 30;   

// Dimensions of the total drawing area in centimeters
int w= 241*StepUnit;
int h= 124*StepUnit;

// Coordinates of current (starting) point, bottom center of drawing area
int x1= w/2;
int y1= h;

// Length of strings from marker to bobbin
// These magical numbers are derived from the Pythagorean theorem
int a1= sqrt(pow(x1,2)+pow(y1,2));
int b1= sqrt(pow((w-x1),2)+pow(y1,2));




// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  motor1.onestep(FORWARD, SINGLE);
}
void backwardstep1() {  
  motor1.onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  motor2.onestep(FORWARD, SINGLE);
}
void backwardstep2() {  
  motor2.onestep(BACKWARD, SINGLE);
}

// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);

void setup()
{  
  
  Serial.begin(9600);

  Serial.println();
  Serial.println("SETUP");
  Serial.println();
  Serial.print("steps per centimeter: " );                       
  Serial.println(StepUnit);      
  Serial.print("width of drawing area in centimeters: " );                       
  Serial.println(w/StepUnit);      
  Serial.print("height of drawing area in centimeters: " );                       
  Serial.println(h/StepUnit);      
  Serial.print("width of drawing area in StepUnits: " );                       
  Serial.println(w);      
  Serial.print("height of drawing area in StepUnits: " );                       
  Serial.println(h);      
  Serial.print("X starting point: " );                       
  Serial.println(x1);      
  Serial.print("Y starting point: " );                       
  Serial.println(y1);      
  Serial.print("length of left string in StepUnits: " );                       
  Serial.println(a1);      
  Serial.print("length of right string in StepUnits: " );                       
  Serial.println(b1);      


/*  
    stepper1.setMaxSpeed(200.0);
    stepper1.setAcceleration(100.0);
    stepper1.moveTo(24);
    
    stepper2.setMaxSpeed(300.0);
    stepper2.setAcceleration(100.0);
    stepper2.moveTo(1000000);
*/
}


void moveTo(int x2, int y2) {

  Serial.println();  
  Serial.println("in moveTo routine...");
  Serial.println();  
  Serial.print("current position: " );                       
  Serial.print(x1);      
  Serial.print(", ");      
  Serial.println(y1);   
  Serial.print("moving to: ");      
  Serial.print(x2);   
  Serial.print(", ");      
  Serial.println(y2);   

  // a2 and b2 are the final lengths of the left and right strings
  int a2 = sqrt(pow(x2,2)+pow(y2,2));
  int b2 = sqrt(pow((w-x2),2)+pow(y2,2));

  Serial.println("line lengths..." );                       
  Serial.print("current left line length: " );                       
  Serial.println(a1);      
  Serial.print("left line moving to: ");      
  Serial.println(a2);   
  Serial.print("current right line length: ");      
  Serial.println(b1);   
  Serial.print("right line moving to: ");      
  Serial.println(b2);   

  int stepA;
  int stepB;
  int differenceA;
  int differenceB;
  
  if (a2>a1) { 
    stepA=1; 
    differenceA = a2-a1;
  }
  if (a1>a2) { 
    stepA=-1;
    differenceA = a1-a2;
  }
  if (a2==a1) {
    stepA=0; 
    differenceA = 0;    
  }
  if (b2>b1) { 
    stepB=1; 
    differenceB = b2-b1;
  }
  if (b1>b2) { 
    stepB=-1;
    differenceB = b1-b2;
  }
  if (b2==b1) {
    stepB=0; 
    differenceB = 0;
  }
  
  Serial.print("differenceA = ");      
  Serial.println(differenceA);   
  Serial.print("differenceB = ");      
  Serial.println(differenceB);   

  // Change the length of a1 and b1 until they are equal to the desired length

  while ((a1!=a2) || (b1!=b2)) {
    if (a1!=a2) { 
      a1 += stepA;
      StepperA.step(stepA);
    }
    if (b1!=b2) { 
      b1 += stepB;
      StepperB.step(-stepB);
    }
  }

  // return with x1 and x2 set to their new values
  x1 = x2;
  y1 = y2;
}




void loop()
{
  
  Serial.println();
  Serial.println("MAIN ROUTINE");
  Serial.println();
  
//  moveTo(729,1080);  
  
/*  
    // Change direction at the limits
    if (stepper1.distanceToGo() == 0)
	stepper1.moveTo(-stepper1.currentPosition());
    stepper1.run();
    stepper2.run();
*/

}
