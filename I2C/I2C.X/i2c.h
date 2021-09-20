#ifndef I2C_H
#define I2C_H

void I2C_init(const unsigned long freq_K);
void I2C_Hold (void);
void I2C_start(void);
void I2C_stop(void);
void I2C_write(unsigned data);
unsigned short I2C_read(unsigned short a);

struct
{
    void (* init)(const unsigned long freq_K);
    void (* hold)(void);
    void (* start)(void);
    void (* stop)(void);
    void (* write)(unsigned data);
    unsigned short (* read)(unsigned short a);
} I2C = { I2C_init, I2C_Hold, I2C_start, I2C_stop, I2C_write, I2C_read };


#endif