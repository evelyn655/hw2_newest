#include "mbed.h"
#include "uLCD_4DGL.h"

// Initialize a pins to perform analog and digital output functions
// Adjust analog output pin name to your board spec.
AnalogOut  aout(PA_4);
AnalogIn Ain(A0); 

DigitalIn but_SEL(D6);
//DigitalIn test(USER_BUTTON);
DigitalIn but_UP(D5);
DigitalIn but_DOWN(D3);

uLCD_4DGL uLCD(D1, D0, D2);

float ADCdata[2000];
void print(int counter);

int main(void)
{
    uLCD.background_color(WHITE);
    uLCD.cls();
    int counter=3;
    uLCD.color(BLACK);
    uLCD.textbackground_color(GREEN);
    uLCD.locate(1, 2);
    uLCD.printf("\n100Hz\n");

                
    while(1){

        int t;
        int count=0;
        float i;

        
        
        while(1) {
            if (but_UP){
                if(counter<3) counter++;
                else counter=3; 
                print(counter);
                ThisThread::sleep_for(50ms);
            
            }
            else if (but_DOWN){
                if(counter>0) counter--;
                else counter=0;
                print(counter); 
                ThisThread::sleep_for(50ms);
            }
            else if (but_SEL){
                if (counter==3) t=10;
                else if (counter==2) t=20;
                else if (counter==1) t=40;
                else if (counter==0) t=100;
                break;
            }
        
        }


        while (1) {
      
            // assuming VCC = 3.3v
            i=0;
            for (int x=0; x < (t*0.3);x++) {
                i += (1.0/(t*0.3));
                aout = i;
                //ADCdata[count]=Ain;
                count++;
                ThisThread::sleep_for(1ms);
            }
            for (int x=0; x<(t*0.7); x++) {
                i -= (1.0/(t*0.7));
                aout = i;
                //ADCdata[count]=Ain;
                count++;
                ThisThread::sleep_for(1ms);
            }
/*                
            if (count>=2000) {
                break;
            }
*/            
        }
/*
        for (int x=500; x<1500; x++) {
            printf("%f\r\n", ADCdata[x]);
        
        }
        ThisThread::sleep_for(10ms);
*/
    }
}

void print(int counter){
    uLCD.cls();
    uLCD.color(BLACK);
    uLCD.textbackground_color(GREEN);
    uLCD.locate(1, 2);
    if (counter==3) uLCD.printf("\n100Hz\n");
    else if (counter==2) uLCD.printf("\n50Hz\n");
    else if (counter==1) uLCD.printf("\n25Hz\n");
    else if (counter==0) uLCD.printf("\n10Hz\n");
}