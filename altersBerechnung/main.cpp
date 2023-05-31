#include "mbed.h"

DigitalOut SerialDataInA(PA_9);
DigitalOut ShiftClock(PA_8);
DigitalOut LatchClock(PB_5);

DigitalOut led1(PA_5);
DigitalOut led2(PA_6);
DigitalOut led3(PA_7);
DigitalOut led4(PB_6);

Timeout timeout;
InterruptIn button1(PA_1);
InterruptIn button2(PA_4);
InterruptIn button3(PB_0);

unsigned int age = 1960;
unsigned int result = 0;
int currentYear = 2023;
bool resultReady = false;

enum statusTyp {l1, l2, l3, l4, l5, l6};
statusTyp status;

void isrTimeout();
void isrButton1();
void isrButton2();
void isrButton3();

void wait(int ms) {
    ThisThread::sleep_for(ms);
}

void shift(){
    ShiftClock = 0;
    ShiftClock = 1;
    ShiftClock = 0;
}
void clear(){
    SerialDataInA = 0;
    for(int i=0; i < 20; i++){ // 16
        ShiftClock = 1;
        ShiftClock = 0;
    }
}
void display(int index, int array[]){
    clear();
    for(int i=0; i < 8; i++){
        SerialDataInA = array[i]; 
        shift();
    }

    for(int i=0; i < 4; i++){
        shift();
    }
    if(index == 1){
         SerialDataInA = 0;
         shift();
         SerialDataInA = 0;
         shift();
         SerialDataInA = 0;
         shift();
         SerialDataInA = 1;
         shift();
    }
    if(index == 2){
         SerialDataInA = 0;
         shift();
         SerialDataInA = 0;
         shift();
         SerialDataInA = 1;
         shift();
         SerialDataInA = 0;
         shift();
    }
    if(index == 3){
         SerialDataInA = 0;
         shift();
         SerialDataInA = 1;
         shift();
         SerialDataInA = 0;
         shift();
         SerialDataInA = 0;
         shift();
    }
    if(index == 4){
         SerialDataInA = 1;
         shift();
         SerialDataInA = 0;
         shift();
         SerialDataInA = 0;
         shift();
         SerialDataInA = 0;
         shift();
    }
    LatchClock = 1;
    LatchClock = 0;
}
int sd_number_0[] = {1, 1, 0, 0, 0, 0, 0, 0};
int sd_number_1[] = {1, 1, 1, 1, 1, 0, 0, 1};
int sd_number_2[] = {1, 0, 1, 0, 0, 1, 0, 0};
int sd_number_3[] = {1, 0, 1, 1, 0, 0, 0, 0};
int sd_number_4[] = {1, 0, 0, 1, 1, 0, 0, 1};
int sd_number_5[] = {1, 0, 0, 1, 0, 0, 1, 0};
int sd_number_6[] = {1, 0, 0, 0, 0, 0, 1, 0};
int sd_number_7[] = {1, 1, 1, 1, 1, 0, 0, 0};
int sd_number_8[] = {1, 0, 0, 0, 0, 0, 0, 0};
int sd_number_9[] = {1, 0, 0, 1, 0, 0, 0, 0};

int sd_number_0_dot[] = {0, 1, 0, 0, 0, 0, 0, 0};
int sd_number_1_dot[] = {0, 1, 1, 1, 1, 0, 0, 1};
int sd_number_2_dot[] = {0, 0, 1, 0, 0, 1, 0, 0};
int sd_number_3_dot[] = {0, 0, 1, 1, 0, 0, 0, 0};
int sd_number_4_dot[] = {0, 0, 0, 1, 1, 0, 0, 1};
int sd_number_5_dot[] = {0, 0, 0, 1, 0, 0, 1, 0};
int sd_number_6_dot[] = {0, 0, 0, 0, 0, 0, 1, 0};
int sd_number_7_dot[] = {0, 1, 1, 1, 1, 0, 0, 0};
int sd_number_8_dot[] = {0, 0, 0, 0, 0, 0, 0, 0};
int sd_number_9_dot[] = {0, 0, 0, 1, 0, 0, 0, 0};


void display4(int seg1, int seg2, int seg3, int seg4, int timer){
    for (int i = 0; i<timer/4; i++) {
        if (seg1 == 1) {
            display(1, sd_number_1); 
        } else if (seg1 == 2) {
            display(1, sd_number_2); 
        } else if (seg1 == 3) {
            display(1, sd_number_3); 
        } else if (seg1 == 4) {
            display(1, sd_number_4); 
        } else if (seg1 == 5) {
            display(1, sd_number_5); 
        } else if (seg1 == 6) {
            display(1, sd_number_6); 
        } else if (seg1 == 7) {
            display(1, sd_number_7); 
        } else if (seg1 == 8) {
            display(1, sd_number_8); 
        } else if (seg1 == 9) {
            display(1, sd_number_9); 
        } else if (seg1 == 0) {
            display(1, sd_number_0); 
        }
        ThisThread::sleep_for(1ms);


        if (seg2 == 1) {
            display(2, sd_number_1); 
        } else if (seg2 == 2) {
            display(2, sd_number_2); 
        } else if (seg2 == 3) {
            display(2, sd_number_3); 
        } else if (seg2 == 4) {
            display(2, sd_number_4); 
        } else if (seg2 == 5) {
            display(2, sd_number_5); 
        } else if (seg2 == 6) {
            display(2, sd_number_6); 
        } else if (seg2 == 7) {
            display(2, sd_number_7); 
        } else if (seg2 == 8) {
            display(2, sd_number_8); 
        } else if (seg2 == 9) {
            display(2, sd_number_9); 
        } else if (seg2 == 0) {
            display(2, sd_number_0); 
        }

        ThisThread::sleep_for(1ms);

        if (seg3 == 1) {
            display(3, sd_number_1); 
        } else if (seg3 == 2) {
            display(3, sd_number_2); 
        } else if (seg3 == 3) {
            display(3, sd_number_3); 
        } else if (seg3 == 4) {
            display(3, sd_number_4); 
        } else if (seg3 == 5) {
            display(3, sd_number_5); 
        } else if (seg3 == 6) {
            display(3, sd_number_6); 
        } else if (seg3 == 7) {
            display(3, sd_number_7); 
        } else if (seg3 == 8) {
            display(3, sd_number_8); 
        } else if (seg3 == 9) {
            display(3, sd_number_9); 
        } else if (seg3 == 0) {
            display(3, sd_number_0); 
        }
        ThisThread::sleep_for(1ms);

        if (seg4 == 1) {
            display(4, sd_number_1); 
        } else if (seg4 == 2) {
            display(4, sd_number_2); 
        } else if (seg4 == 3) {
            display(4, sd_number_3); 
        } else if (seg4 == 4) {
            display(4, sd_number_4); 
        } else if (seg4 == 5) {
            display(4, sd_number_5); 
        } else if (seg4 == 6) {
            display(4, sd_number_6); 
        } else if (seg4 == 7) {
            display(4, sd_number_7); 
        } else if (seg4 == 8) {
            display(4, sd_number_8); 
        } else if (seg4 == 9) {
            display(4, sd_number_9); 
        } else if (seg4 == 0) {
            display(4, sd_number_0); 
        }
        ThisThread::sleep_for(1ms);
    }
}

void laufLicht(int duration){
    for (int i = 0; i<duration; i++) {
        if (status == l1){
        led1 = 0;
        led2 = 1;
        led3 = 1;
        led4 = 1;
        status = l2;
    } else if (status == l2){
        led1 = 1;
        led2 = 0;
        led3 = 1;
        led4 = 1;
        status = l3;
    } else if (status == l3){
        led1 = 1;
        led2 = 1;
        led3 = 0;
        led4 = 1;
        status = l4;
    } else if (status == l4){
        led1 = 1;
        led2 = 1;
        led3 = 1;
        led4 = 0;
        status = l5;
    } else if (status == l5){
        led1 = 1;
        led2 = 1;
        led3 = 0;
        led4 = 1;
        status = l6;
    } else if (status == l6){
        led1 = 1;
        led2 = 0;
        led3 = 1;
        led4 = 1;
        status = l1;
    }
    ThisThread::sleep_for(100ms);
    }
}

void isrButton1(){
    age++;
}

void isrButton2(){
    age--;
}

void isrButton3(){
    result = currentYear - age;
    resultReady = true;
}

int main() {  
    led1 = 1;
    led2 = 1;
    led3 = 1;
    led4 = 1;
    button1.fall( &isrButton1 );
    button2.fall( &isrButton2 );
    button3.fall( &isrButton3 );



    while (true) {
        led1 = 1;
        led2 = 1;
        led3 = 1;
        led4 = 1;
        int digit1 = (age / 1000) % 10;
        int digit2 = (age / 100) % 10;
        int digit3 = (age / 10) % 10;
        int digit4 = age % 10;
        // Anzeigen der Stunden und Minuten
        display4(digit1, digit2, digit3, digit4, 1000);
        if (resultReady == true) {
            digit1 = (result / 1000) % 10;
            digit2 = (result / 100) % 10;
            digit3 = (result / 10) % 10;
            digit4 = result % 10;
            if (digit1 == 0) {
                digit1 = -1;
            }
            if (digit2 == 0) {
                digit2 = -1;
            }
            if (digit3 == 0) {
                digit3 = -1;
            }

            laufLicht(30);
            led1 = 0;
            led2 = 0;
            led3 = 0;
            led4 = 0;
            display4(digit1, digit2, digit3, digit4, 8000);
            resultReady = false;
        }
    }
}