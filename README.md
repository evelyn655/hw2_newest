# Homework 2 Digital, Analog I/O and 

## How to set up my program
### 1. Waveform generating:
```
while (1) {
            // assuming VCC = 3.3v
            i=0;
            for (int x=0; x < (t*0.3);x++) {    // 三角波的上升部分
                i += (1.0/(t*0.3));             // t*0.3 上到頂端，因此一次上升的高度為 1.0/(t*0.3)
                aout = i;                       // output the signal (DAC)
                ThisThread::sleep_for(1ms);     
            }
            for (int x=0; x<(t*0.7); x++) {    // 三角波的下降部分
                i -= (1.0/(t*0.7));
                aout = i;
                ThisThread::sleep_for(1ms);
            }
 ```
 1. variable t: 將一周期的波切成t格來完成。
 2. S=3 for my student ID,  所以 t 格前 30% 是三角波上升的部分，後 70% 則是三角波往下的部分。
 3. 一個波的週期為 t 乘上 sleep for 的時間 1ms，頻率則為週期之倒數。
 ![image](https://drive.google.com/drive/u/2/folders/1mYAm3xzJ0zZAh_EW9i4S6wNL--XxZ-g_,13800590306375)
 ###
 
