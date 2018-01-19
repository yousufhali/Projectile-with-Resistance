
/*

In this program, I am trying to calculate the velocity that a ball needs to be released to hit a point despite the presence of air-resistance.
Process Overview: Discrete-time simulation

Variable Definitions:

h= height above the ground that the ball is released from
d = horizontal distance to the target
step= discrete simulation incrementing constant
m = mass of the ball
w = width of the trench or building where the target is at
theta= angle in degrees
t= height above the ground of the target



*/
#include <stdlib.h>
#include <limits>
#include <math.h>


//Function declarations
							 
bool hitTargetGivenAngle (const float h, const float m, const float theta, 
              const float d, const float step, const float k,
              const float t, const float b, const float w, float& v);

float calculateVelocityx(float vx, float k,float step, float m, float &positionx, float &acceleration, float vowel);
float calculateVelocityy(float vy, float k,float step, float m, float &positiony, float &acceleration);

//


//Helper functions
float calculateVelocityx(float vx, float k, float step,float m, float &positionx, float &acceleration, float vowel){
    float x=positionx;
    acceleration=-1*(vx*vowel*k)/m;
    float velocity= vx+(acceleration*step);
    positionx=positionx+(vx*step);
    velocity=vx+acceleration*step;
    return velocity;



}

float calculateVelocityy(float vy, float k, float step, float m,  float &positiony, float &acceleration, float vowel){
    float y=positiony;
    float velocity=0;
    acceleration=-9.8-(k*vy*vowel)/m;
    positiony=positiony+(vy*step) ;
    velocity=vy+acceleration*step;
    
    return velocity;



}
//


// Perform a discrete time simulation
bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float step, const float k,
              const float t, const float b, const float w, float& v) {
  

                if ( m<0 || w<0 || b<0|| k<0 ||d<0 || theta>180 || step<=0  || h<0 || theta==90 )
                return false;
                

                float step2=step;
                
                    
                
                
                float acceleration=0;
                float theta1=theta*(M_PI/180);
                float vi=sqrt(((-4.9*d*d)/(t-h-d*tan(theta1)))/(cos(theta1)*cos(theta1)));
                float time=d/(vi*cos(theta1));
                time*=2;
                
                float currentVelocity=vi*2;
                float currentVelocityx=0;
                
                float currentVelocityy=0;
                float timer=0;
                float positionx=0;
                float positiony=h;
                float thetai=theta1;
                float tempvx=0;
                float tempvy=0;
                bool hit=false;
                float vowel=currentVelocity;
                int i =0;
                
                while (currentVelocity>=vi && i<100000 ){
                    thetai=theta1;
                    timer=0;
                    positionx=0;
                    positiony=h;
                    currentVelocityx=currentVelocity*cos(theta1);
                    currentVelocityy=currentVelocity*sin(theta1);
                    vowel=currentVelocity;
                    hit=false;
                    while (timer<=time){
                        
                        //CALCULATE VELOCITY USING ACCELERATION; HENCE, THE POSITION
                        currentVelocityx=calculateVelocityx(currentVelocityx,k,step,m,positionx,acceleration,vowel);
                        currentVelocityy=calculateVelocityy(currentVelocityy,k,step,m,positiony, acceleration,vowel);
                        vowel=sqrt(pow(currentVelocityx,2)+pow(currentVelocityy,2));
                        if (positionx<b && positiony<0 ){
                           hit=true;
                        }
                        if ((fabs((fabs(positiony)-t))<=0.1) && fabs((fabs(positionx)-fabs(d)))<=0.1 ){
                            
                            v=currentVelocity;
                            if (hit==false){
                            return true;
                            }
                        }
                        timer+=(step);
                        
                    }
                    i++;
                    currentVelocity-=0.01;
                }
                hit=false;
                currentVelocity=vi*2;
                while (currentVelocity>=vi){
                    thetai=theta1;
                    hit=false;
                    timer=0;
                    positionx=0;
                    positiony=h;
                    currentVelocityx=currentVelocity*cos(theta1);
                    currentVelocityy=currentVelocity*sin(theta1);
                    vowel=currentVelocity;
                    while (timer<=time){
                        
                        //CALCULATE VELOCITY USING ACCELERATION; HENCE, THE POSITION
                        currentVelocityx=calculateVelocityx(currentVelocityx,k,step,m,positionx,acceleration,vowel);
                        currentVelocityy=calculateVelocityy(currentVelocityy,k,step,m,positiony, acceleration,vowel);
                        vowel=sqrt(pow(currentVelocityx,2)+pow(currentVelocityy,2));
                        if (positionx<b && positiony<0 ){
                            hit=true;
                        }
                        if ((fabs((positiony-t))<=0.1) && fabs((fabs(positionx)-fabs(d)))<=0.1){
                            
                            v=currentVelocity;
                            if (hit==false){
                            return true;
                            }
                        }
                        timer+=(step);
                        
                    }
                    currentVelocity-=0.01;
                }
                v=currentVelocity;


                return false;

}
		
//TESTING
int main() {
	
  //TESTING VALUES
  float h = 50;
  float d = 60;
  float b = 40;
  float t = -30;
  float w = 30;
  float m = 0.5;//Mass of ball
  float step = 0.001;
  float k = 0.003; //Resistance constant
  float theta = 53.61; // Make sure the angle is in degrees;
  float v = 25;	

  cout << endl << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;

  if (hitTargetGivenAngle (h, m, theta, d, step, k, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity" << endl << endl;
  }
    
  return 0;
}

