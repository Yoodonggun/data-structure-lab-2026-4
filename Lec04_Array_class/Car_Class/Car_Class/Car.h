#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <cstdio>
#include <cstring> 

class car {
protected:
    int speed;
    char name[40];

public:
    int gear;

    car() : speed(0), gear(1) { 
        strcpy(name, "Unknown");
    }
    ~car() {}
    car(int s, const char* n, int g) : speed(s), gear(g) {
        strcpy(name, n);
    }
    void changeGear(int g = 4) {
        gear = g;
    }
    void speedUp() {
        speed += 5;
    }
    void display() {
        printf("[%s] : gear=%d speed=%dkmph\n", name, gear, speed);
    }
    void whereAmI() {
        printf("address = %p\n", (void*)this);
    }
};