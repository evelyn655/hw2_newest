/*#include "mbed.h"

// Initialize a pins to perform analog and digital output functions
// Adjust analog output pin name to your board spec.
AnalogOut  aout(PA_4);
DigitalOut dout(LED1);
AnalogIn Ain(A0); 

DigitalIn but_SEL(D6);
DigitalIn test(USER_BUTTON);
DigitalIn but_UP(D5);
DigitalIn but_DOWN(D4);

float ADCdata[300];


int main(void)
{
    while(1) {
        int t;
        int count=0;
        float i;
        t=25;

        while(1) {
            if (but_UP){
                //printf("UP is pressed\n");
            }
            if (but_DOWN){
                //printf("UP is pressed\n");
            }
            if (but_SEL){
                //printf("SEL is pressed\n");
                
                break;
            }       
        }

        while (1) {
            //assuming VCC = 3.3v
            i=0;
            for (int x=0; x < (t*0.3);x++) {
                i += (1.0/(t*0.3));
                aout = i;
                ADCdata[count]=Ain;
                count++;
                //printf("%d\r\n", count);
                ThisThread::sleep_for(4ms);
            }
            for (int x=0; x<(t*0.7); x++) {
                i -= (1.0/(t*0.7));
                aout = i;
                ADCdata[count]=Ain;
                //printf("%f\r\n", ADCdata[j]);
                count++;
                ThisThread::sleep_for(4ms);
            }       
            if (count>=300) {
                break;
            }
        }

        for (int x=50; x<300; x++) {
            printf("%f\r\n", ADCdata[x]);
        
        }
        ThisThread::sleep_for(10ms);
    }
}
*/



#include "mbed.h"

// Initialize a pins to perform analog and digital output functions
// Adjust analog output pin name to your board spec.
AnalogOut  aout(PA_4);
DigitalOut dout(LED1);
AnalogIn Ain(A0); 

DigitalIn but_SEL(D6);
DigitalIn test(USER_BUTTON);
DigitalIn but_UP(D5);
DigitalIn but_DOWN(D4);

float ADCdata[350];


int main(void)
{
while(1){

    int t;
    int count=0;
    float i;

    while(1) {
        if (but_UP){
            //printf("UP is pressed\n");
        }
         if (but_DOWN){
            //printf("UP is pressed\n");
        }
         if (but_SEL){
            //printf("SEL is pressed\n");
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
                ThisThread::sleep_for(4ms);
            }
            for (int x=0; x<(t*0.7); x++) {
                i -= (1.0/(t*0.7));
                aout = i;
                ADCdata[count]=Ain;
                count++;
                ThisThread::sleep_for(4ms);
            }    
            if (count>=350) {
                break;
            }
            
            
   }

    for (int x=100; x<350; x++) {
        printf("%f\r\n", ADCdata[x]);
        
    }
    ThisThread::sleep_for(10ms);
            
}




}