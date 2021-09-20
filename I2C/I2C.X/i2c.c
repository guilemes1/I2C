/*
 * File:   i2c.c
 * Author: guilherme
 *
 * Created on 20 de Setembro de 2021, 19:13
 */

#include "delay.h"
#include <xc.h>
#define SCL PORTCbits.RC3
#define SDA PORTCbits.RC4

void I2C_init(const unsigned long freq_K)
{
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    
    SSPCON  = 0b00101000;
    SSPCON2 = 0b00000000;
    
    //SSPADD = _XTAL_FREQ / 4;
    SSPADD  = (_XTAL_FREQ / (4*freq_K*100)) - 1;   //CONFIGURA A VELOCIDADE DE CLOCK
    SSPSTAT = 0b00000000;                          //STATUS DO BARRAMENTO I2C
    
}

void I2C_Hold (void) //MANTER A EXECUÇÃO DO DISPOSITIVO ATÉ A OPERAÇÃO I2C SER CONCLUIDA
{
    while(   (SSPCON2 & 0b00011111)    ||    (SSPSTAT & 0b00000100)   ) ; //check the this on registers to make sure the IIC is not in progress
}

void I2C_start()
{
  I2C_Hold();  //Hold the program is I2C is busy 
  SEN = 1;     //INICIA A COMUNIÇÃO I2C --> SDA PASSA PARA "0"
}

void I2C_stop()
{
  I2C_Hold(); //Hold the program is I2C is busy 
  PEN = 1;    //ENCERRA A COMUNICAÇÃO
}

void I2C_write(unsigned data)
{
  I2C_Hold();            //Hold the program is I2C is busy
  SSPBUF = data;         //pg82/234
}

unsigned short I2C_read(unsigned short a)
{
  unsigned short temp;
  I2C_Hold();
  RCEN = 1;
  I2C_Hold();
  temp = SSPBUF;      //Read data from SSPBUF
  I2C_Hold();
  ACKDT = (a)?0:1;    //Acknowledge bit
  ACKEN = 1;          //Acknowledge sequence
  return temp;
}


/*void carrega_dados (char dado)
{
    char i = 7;
    
    for(int j = 0; j <= 7; j++)
    {
        char d; 
        
        d = dado >> i;
        
        SCL = 0;
        __delay_us(5);
        SDA = d;
        SCL = 0;
        __delay_us(5);
        SCL = 1;
        __delay_us(5);
        i--;
    }    
}*/



