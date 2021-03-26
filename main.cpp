#include "mbed.h"

// Initialize a pins to perform analog and digital output functions
// Adjust analog output pin name to your board spec.
AnalogOut  aout(PA_4);
AnalogIn Ain(A0); 

DigitalIn but_SEL(D6);
DigitalIn test(USER_BUTTON);
DigitalIn but_UP(D5);
DigitalIn but_DOWN(D4);

float ADCdata[2000];


int main(void)
{
    while(1){

        int t;
        int count=0;
        float i;

        while(1) {
            int counter=0;
            if (but_UP){
            
            }
            if (but_DOWN){
                
            }
            if (but_SEL){
                t=10;
                break;
            }
        
        }


        while (1) {
      
            // assuming VCC = 3.3v
            i=0;
            for (int x=0; x < (t*0.3);x++) {
                i += (1.0/(t*0.3));
                aout = i;
                ADCdata[count]=Ain;
                count++;
                ThisThread::sleep_for(1ms);
            }
            for (int x=0; x<(t*0.7); x++) {
                i -= (1.0/(t*0.7));
                aout = i;
                ADCdata[count]=Ain;
                count++;
                ThisThread::sleep_for(1ms);
            }
                
            if (count>=2000) {
                break;
            }
            
        }

        for (int x=500; x<1500; x++) {
            printf("%f\r\n", ADCdata[x]);
        
        }
        ThisThread::sleep_for(10ms);

    }
}