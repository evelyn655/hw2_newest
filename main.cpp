#include "mbed.h"
#include "uLCD_4DGL.h"


AnalogOut  aout(PA_4);
AnalogIn Ain(A0); 

DigitalIn but_SEL(D6);
DigitalIn but_UP(D5);
DigitalIn but_DOWN(D3);

uLCD_4DGL uLCD(D1, D0, D2);

void print(int counter);

float ADCdata[2000];

int main(void)
{
    uLCD.background_color(WHITE);
    uLCD.cls();
    uLCD.textbackground_color(WHITE);
    int counter=3;
    uLCD.color(RED);
    uLCD.locate(1, 2);
    uLCD.printf("\n100Hz\n");
    uLCD.color(BLACK);
    uLCD.locate(1, 4);
    uLCD.printf("\n50Hz\n");
    uLCD.locate(1, 6);
    uLCD.printf("\n25Hz\n");
    uLCD.locate(1, 8);
    uLCD.printf("\n10Hz\n");

    while(1) {

        int t;
        int count=0;
        float i;

        while(1) {
            if (but_UP) {
                if(counter<3) counter++;
                else counter=3; 
                print(counter);
                ThisThread::sleep_for(50ms);
            } else if (but_DOWN) {
                if(counter>0) counter--;
                else counter=0;
                print(counter); 
                ThisThread::sleep_for(50ms);
            } else if (but_SEL) {
                if (counter==3) t=10;           // 100Hz
                else if (counter==2) t=20;      // 50Hz
                else if (counter==1) t=40;      // 25Hz
                else if (counter==0) t=100;     // 10Hz
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
            if (count>=2000) break;
        }

        for (int x=500; x<1500; x++) {
            printf("%f\r\n", ADCdata[x]);
        }

        ThisThread::sleep_for(10ms);
    }
}

void print(int counter) {
    //uLCD.cls();
    uLCD.color(BLACK);
    uLCD.locate(1, 2);
    uLCD.printf("\n100Hz\n");    
    uLCD.locate(1, 4);
    uLCD.printf("\n50Hz\n");
    uLCD.locate(1, 6);
    uLCD.printf("\n25Hz\n");
    uLCD.locate(1, 8);
    uLCD.printf("\n10Hz\n");

    if (counter==3) {
        uLCD.color(RED);
        uLCD.locate(1, 2);
        uLCD.printf("\n100Hz\n");
    } else if (counter==2) {
        uLCD.color(RED);
        uLCD.locate(1, 4);
        uLCD.printf("\n50Hz\n");
        
    } else if (counter==1) {
        uLCD.color(RED);
        uLCD.locate(1, 6);
        uLCD.printf("\n25Hz\n");
    } else if (counter==0) {
        uLCD.color(RED);
        uLCD.locate(1, 8);
        uLCD.printf("\n10Hz\n");
    }
}