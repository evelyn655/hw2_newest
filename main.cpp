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

float ADCdata[1100];


int main(void)
{
while(1){

    int t=10;
    int count=0;
    float i;

    while(1) {
        if(!test) {
            //printf("test is pressed\r\n");
        }
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
      // change the voltage on the digital output pin by 0.1 * VCC
      //  and print what the measured voltage should be (assuming VCC = 3.3v)
      //for (float i = 0.0f; i < 1.0f; ) {
            i=0;
            for (int x=0; x < (t*0.3);x++) {
                i += (1.0/(t*0.3));
                aout = i;
                ADCdata[count]=Ain;
                count++;
                //printf("%d\r\n", count);
                ThisThread::sleep_for(1ms);
            }
            for (int x=0; x<(t*0.7); x++) {
                i -= (1.0/(t*0.7));
                aout = i;
                ADCdata[count]=Ain;
                //printf("%f\r\n", ADCdata[j]);
                //printf("%d\r\n", count);
                count++;
                ThisThread::sleep_for(1ms);
            }    
            if (count>=1100) {
                break;
            }
            
            
            //aout = i;
            //printf("aout = %f volts\n", aout.read() * 3.3f);
            // turn on the led if the voltage is greater than 0.5f * VCC
            //dout = (aout > 0.5f) ? 1 : 0;
            //ThisThread::sleep_for(1s);
      //}
   }

    for (int x=100; x<1100; x++) {
        printf("%f\r\n", ADCdata[x]);
        
    }
    ThisThread::sleep_for(10ms);
    //count = 0;
            
}




}