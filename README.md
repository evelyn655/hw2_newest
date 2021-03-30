# Homework 2 Digital, Analog I/O and LCD

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

下圖為經過RC filter前的三角波。
![](https://i.imgur.com/OvIcvH4.png)

### 2. RC filter
R = 30 kΩ
C = 0.22 µF
截止頻率約為 24 Hz

經過RC filter之後的三角波型。(10Hz)
![](https://i.imgur.com/0Ih3lm0.png)


 
 ### 3. Sampling
 將經過 RC filter 的訊號連接至 AnalogIn 進行取樣。
 ```
 while (1) {
            // assuming VCC = 3.3v
            i=0;
            for (int x=0; x < (t*0.3);x++) {
                i += (1.0/(t*0.3));
                aout = i;
                ADCdata[count]=Ain;             // comment out when not sampling
                count++;
                ThisThread::sleep_for(1ms);
            }
            for (int x=0; x<(t*0.7); x++) {
                i -= (1.0/(t*0.7));
                aout = i;
                ADCdata[count]=Ain;             // comment out when not sampling
                count++;
                ThisThread::sleep_for(1ms);
            }
            if (count>=2000) break;             // comment out when not sampling     
        }
```
在產生三角波型的for迴圈裡，加入```ADCdata[count]=Ain;```，對從 AnalogIn 接收進來的訊號以1ms為週期進行取樣，並將取樣到的值存入陣列ADCdata中。

我的設定是取樣2000個點，所以在陣列存入2000個值後即可跳出迴圈。(```if (count>=2000) break;```)。


### 4. Analysis
```
for (int x=500; x<1500; x++) {          
    printf("%f\r\n", ADCdata[x]);       
}
```
取樣2000筆資料後，為了排除剛 reset 過後可能還未穩定的波型取樣數值，因此我只 print 出中間1000筆資料，並由 Python program 畫出 FFT 圖。

因為 printf 的執行速度很慢，若將 printf 放在產生波的 for 迴圈中，會使得用 DAC 產生的波之周期被拉長。
因此我先儲存了足夠的資料數量後，才一次 print 出來。

### 5. Button Inputs and Frequency Selecting
共有四種可以選擇的頻率，因此使用一個可以數0-3的counter。
每個數字會對應一個頻率選擇(t的賦值)，並在 uLCD 上印出目前所選擇到的頻率(print函示)。
```
while(1) {
            if (but_UP) {
                if(counter<3) counter++;
                else counter=3; 
                print(counter);
                ThisThread::sleep_for(50ms);    // sleep for 時間太短會導致 button 過於靈敏。
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
                break;                          // 按下確認 button 後，跳出選擇迴圈，進入產生波的 while 迴圈。
            }
        }
```

### 6. uLCD Display
main 裡的初始設定：
```
uLCD.background_color(WHITE);        // 將背景設定成白色
uLCD.cls();
uLCD.textbackground_color(WHITE);
int counter=3;
uLCD.color(RED);                     // 目前選擇到的頻率用紅色字體 highlight
uLCD.locate(1, 2);
uLCD.printf("\n100Hz\n");            // 預設為 100Hz 的波
uLCD.color(BLACK);                   // 其他頻率則以黑色字體依序 print 在 uLCD 顯示器上
uLCD.locate(1, 4);
uLCD.printf("\n50Hz\n");
uLCD.locate(1, 6);
uLCD.printf("\n25Hz\n");
uLCD.locate(1, 8);
uLCD.printf("\n10Hz\n");
```

print 函式：
每按一次 button，就會執行一次 print ，印出目前的選擇。
```
void print(int counter) {
    uLCD.color(BLACK);
    uLCD.locate(1, 2);
    uLCD.printf("\n100Hz\n");    
    uLCD.locate(1, 4);
    uLCD.printf("\n50Hz\n");
    uLCD.locate(1, 6);
    uLCD.printf("\n25Hz\n");
    uLCD.locate(1, 8);
    uLCD.printf("\n10Hz\n");

    if (counter==3) {                // counter 數到 3，對應的頻率為 100Hz ，以紅色字體 highlight
        uLCD.color(RED);
        uLCD.locate(1, 2);
        uLCD.printf("\n100Hz\n");
    } else if (counter==2) {        // 以下同理，依照 counter 算到的數字，highlight 對應的頻率
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
```





## Results (Sampling Frequency=1000Hz)
### 1. 10Hz
picoscope:
![](https://i.imgur.com/seohYze.png)

FFT:
![](https://i.imgur.com/m62wiTX.png)

picoscope是直接量經過 RC filter 完之後的 analog 訊號，所以波的振幅大小介於0-3之間。
而 FFT 圖則是用 ADC sample 過後重建的訊號樣子，所以縱座標的值介於 0-1。

可以由圖中一秒出現10個波峰驗證其頻率(10Hz)。
並且 frequency response 在頻率為10時有高峰值。


### 2. 25Hz (cut-off frequency)
picoscope:
![](https://i.imgur.com/FgNW0br.png)

FFT:
![](https://i.imgur.com/jXopmbY.png)

可以由圖中出現的波峰數驗證該訊號之頻率(25Hz)。
因為已經達到 RC filter 的截止頻率，可以明顯看到訊號之震幅減弱。

### 3. 50Hz
picoscope:
![](https://i.imgur.com/ULAJtGH.png)

FFT:
![](https://i.imgur.com/2CcoxUu.png)

每秒 50 個波峰。
訊號之震幅更小。

### 4. 100Hz
picoscope:
![](https://i.imgur.com/wY2XoGB.png)

FFT:
![](https://i.imgur.com/c912R14.png)
