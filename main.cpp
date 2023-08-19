/*
part of the MTU COMP71004 module
author: Krishna Panduru

the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.

++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
#include "mbed.h"


DigitalOut myled(LED1);
UnbufferedSerial  pc(USBTX, USBRX);  //using unbufferedserial as per mbed OS6
UnbufferedSerial  dev(PB_6, PB_7);  // looked up pins in data sheet, these ones worked

void dev_recv(){
    char c;
    while(dev.readable()){
        dev.read(&c, 1);
        pc.write(&c, 1);   //putc and getc gave error so took this from example program on github
    }    
}

void pc_recv(){
    char c;
    while(pc.readable()){
        pc.read(&c, 1);
        dev.write(&c, 1);
    }    
}

int main() {
    pc.baud(9600);
    dev.baud(9600);   //device1 does not exist
    pc.attach(&pc_recv);
    dev.attach(&dev_recv);
    pc.write("\rHello!!\r\n",10);//  printf would't work so used write
    
    while(1) {
        myled = 1;
        wait_us(1000000); //changed to micro seconds
        myled = 0;
        wait_us(1000000);
    }
}   // no run time error showed up
