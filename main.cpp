#include "mbed.h"
#include "uLCD_4DGL.h"


AnalogOut  aout(PA_4);      // D7
AnalogIn Ain(A0); 

InterruptIn but_SEL(D6);
InterruptIn but_UP(D5);
InterruptIn but_DOWN(D3);

uLCD_4DGL uLCD(D1, D0, D2);

void print(int counter);
void sampling();
void generating();
EventQueue sampling_queue(32 * EVENTS_EVENT_SIZE);
EventQueue generating_queue(32 * EVENTS_EVENT_SIZE);
Thread thread;

float ADCdata[2000];
int counter=3;
void UP();
void DOWN();
void SEL();

void UP()
{
    if(counter<3) counter++;
    else counter=3; 
    print(counter);
    //ThisThread::sleep_for(50ms);
}

void DOWN()
{
    if(counter>0) counter--;
    else counter=0;
    print(counter); 
    //ThisThread::sleep_for(50ms);
}

void SEL()
{
    if (counter==3) t=10;           // 100Hz
    else if (counter==2) t=20;      // 50Hz
    else if (counter==1) t=40;      // 25Hz
    else if (counter==0) t=100;     // 10Hz
    generating_queue.call(&generating);
    generating_queue.dispatch();
    sampling_queue.call(&sampling);
    thread.start(callback(&sampling_queue, &EventQueue::dispatch_forever));  
}

void generating()
{
    while(1)
    {

    }
}



int main(void)
{    
    //queue.call(&sampling);

    uLCD.background_color(WHITE);
    uLCD.cls();
    uLCD.textbackground_color(WHITE);
    uLCD.color(RED);
    uLCD.locate(1, 2);
    uLCD.printf("\n1\n");
    uLCD.color(BLACK);
    uLCD.locate(1, 4);
    uLCD.printf("\n1/2\n");
    uLCD.locate(1, 6);
    uLCD.printf("\n1/4\n");
    uLCD.locate(1, 8);
    uLCD.printf("\n1/8\n");
    //int counter=3;

    while(1) {

        int t;
        // int count=0;
        float i;

        //while(1) {

        but_UP.rise(&UP);
        but_DOWN.rise(&DOWN);
        but_SEL.rise(SEL);



        //     if (but_UP) {
        //         if(counter<3) counter++;
        //         else counter=3; 
        //         print(counter);
        //         ThisThread::sleep_for(50ms);
        //     } else if (but_DOWN) {
        //         if(counter>0) counter--;
        //         else counter=0;
        //         print(counter); 
        //         ThisThread::sleep_for(50ms);
        //     } else if (but_SEL) {
        //         if (counter==3) t=10;           // 100Hz
        //         else if (counter==2) t=20;      // 50Hz
        //         else if (counter==1) t=40;      // 25Hz
        //         else if (counter==0) t=100;     // 10Hz
        //         break;
        //     }
        // }

        // thread.start(callback(&sampling_queue, &EventQueue::dispatch_forever));       

        while (1) {
            // assuming VCC = 3.3v
            i=0;
            for (int x=0; x < (t*0.3);x++) {
                i += (1.0/(t*0.3));
                aout = i;
                // ADCdata[count]=Ain;             // comment out when not sampling
                // count++;
                ThisThread::sleep_for(1ms);
            }
            for (int x=0; x<(t*0.7); x++) {
                i -= (1.0/(t*0.7));
                aout = i;
                // ADCdata[count]=Ain;             // comment out when not sampling
                // count++;
                ThisThread::sleep_for(1ms);
            }
            // if (count>=2000) break;             // comment out when not sampling
        }

        // for (int x=500; x<1500; x++) {          // comment out when not sampling
        //     printf("%f\r\n", ADCdata[x]);       // comment out when not sampling
        // }                                       // comment out when not sampling

        ThisThread::sleep_for(10ms);            
    }
}

void sampling()
{
    while(1) {
        for (int i=0; i<2000; i++) {
            ADCdata[i] = Ain;
            ThisThread::sleep_for(1ms);
        }
        for (int i=500; i<1500; i++) {
            printf("%f\r\n", ADCdata[i]);
        }
        ThisThread::sleep_for(20s);
    }
}



void print(int counter) {
    //uLCD.cls();
    uLCD.color(BLACK);
    uLCD.locate(1, 2);
    uLCD.printf("\n1\n");    
    uLCD.locate(1, 4);
    uLCD.printf("\n1/2\n");
    uLCD.locate(1, 6);
    uLCD.printf("\n1/4\n");
    uLCD.locate(1, 8);
    uLCD.printf("\n1/8\n");

    if (counter==3) {
        uLCD.color(RED);
        uLCD.locate(1, 2);
        uLCD.printf("\n1\n");
    } else if (counter==2) {
        uLCD.color(RED);
        uLCD.locate(1, 4);
        uLCD.printf("\n1/2\n");
    } else if (counter==1) {
        uLCD.color(RED);
        uLCD.locate(1, 6);
        uLCD.printf("\n1/4\n");
    } else if (counter==0) {
        uLCD.color(RED);
        uLCD.locate(1, 8);
        uLCD.printf("\n1/8\n");
    }
}
