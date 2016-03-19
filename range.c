#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
 
//#define TRUE 1
 
#define TRIG 8
#define ECHO 9

void setup() {
        wiringPiSetup();
        pinMode(TRIG, OUTPUT);
        pinMode(ECHO, INPUT);
 
        //TRIG pin must start LOW
        digitalWrite(TRIG, LOW);
        delay(30);
}
 
int getCM() {
        //Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG, LOW);
 
        //Wait for echo start
        while(digitalRead(ECHO) == LOW);
 
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO) == HIGH);
        long travelTime = micros() - startTime;
 
        //Get distance in cm
        int distance = travelTime / 58;
 
        return distance;
}
 
int main(void) {
	int a;
        setup();
	for( a=0; a<200; a = a + 1 ){
		int dist = getCM(); 
        	printf("Distance: %dcm\n", dist);
		if( dist < 100 ){
			printf("THE DOOR IS OPEN!!\a\n");	
		}
		delay(500);
 	}
        return 0;
}
