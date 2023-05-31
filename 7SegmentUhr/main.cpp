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

unsigned int counter = 0;  
unsigned int seconds = 0;
unsigned int hours = 0;
unsigned int minutes = 0;

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

        if (i < 100) {
        
        if (seg2 == 1) {
            display(2, sd_number_1_dot); 
        } else if (seg2 == 2) {
            display(2, sd_number_2_dot); 
        } else if (seg2 == 3) {
            display(2, sd_number_3_dot); 
        } else if (seg2 == 4) {
            display(2, sd_number_4_dot); 
        } else if (seg2 == 5) {
            display(2, sd_number_5_dot); 
        } else if (seg2 == 6) {
            display(2, sd_number_6_dot); 
        } else if (seg2 == 7) {
            display(2, sd_number_7_dot); 
        } else if (seg2 == 8) {
            display(2, sd_number_8_dot); 
        } else if (seg2 == 9) {
            display(2, sd_number_9_dot); 
        } else if (seg2 == 0) {
            display(2, sd_number_0_dot); 
        }
        } else {

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

void isrButton1(){
    seconds = seconds + 60;
}

void isrButton2(){
    hours++;
}

void isrButton3(){
    if (hours == 0) {
        hours = 23;
    } else {
        hours--;
    }
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
        int minutesDisplay = minutes % 60;
        int hoursDisplay = hours % 24;
        //int seconds = counter % 60;

        // Anzeigen der Stunden und Minuten
        display4(hoursDisplay / 10, hoursDisplay % 10, minutesDisplay / 10, minutesDisplay % 10, 1000);
        printf("Minuten: %d, Stunden: %d\n", minutesDisplay, hoursDisplay);                

        //Sekundenanzeige
        if (seconds < 15) {
            led1 = 1;
            led2 = 1;
            led3 = 1;
            led4 = 1;
        } else if (seconds < 30) {
            led1 = 0;
        } else if (seconds < 45) {
            led2 = 0;
        } else if (seconds < 58) {
            led3 = 0;
        } else if (seconds == 59) {
            led4 = 0;
        }

        // Hochzählen des Zählers für Sekunden
        seconds++;
        

        // Hochzählen des Zählers für Stunden, wenn 60 Minuten erreicht sind
        if (seconds >= 60) {
            minutes++;
            seconds = 0;
        }

        // Hochzählen des Zählers für die Stunden, wenn 60 Min erreicht sind
        if (minutes >= 60) {
            hours++;
            minutes = 0;
        }

        // Zurücksetzen des Zählers für Stunden und Minuten, wenn 24 Stunden erreicht sind
        if (hours >= 24) {
            seconds = 0;
            hours = 0;
            minutes = 0;
        }
    }
}