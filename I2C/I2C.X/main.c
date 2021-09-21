/*
 * File:   main.c
 * Author: gustavo
 *
 * Created on 17 de Setembro de 2021, 19:10
 * 
 * -------------------------------------------------
 *          MAPA DE ENTRADAS E SAIDAS
 * -------------------------------------------------
 *  Pinos      |nº     | Conexão
 * ------------|-------|-------------------------------
 * RC3/SCL     |18     | SCL
 * RC4/SDA     |23     | SDA
 * -------------------------------------------------
 * -------------------------------------------------
 * 
 */

#include "config.h"
#include <xc.h>
#include "i2c.h"
#include "delay.h"

int main()
{
    I2C.init(100); //Initialize I2C Master with 100KHz clock
   
    while(1)
    {
        I2C.start();
        
        I2C.write(0xC0); 
        I2C.write(0x0F); 
        I2C.write(0xFF);
        
        I2C.stop();
        
        __delay_ms(1000);
    }
}
