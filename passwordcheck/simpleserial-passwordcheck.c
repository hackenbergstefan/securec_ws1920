/*  -*- tab-width: 4; c-basic-offset: 4; c-file-style: "linux"; indent-tabs-mode: nil; -*-
 */

#include "hal.h"
#include "simpleserial.h"
#include <stdint.h>
#include <stdlib.h>

#define PASSWORD_MAX_LENGTH 2

uint8_t check_password(uint8_t* x)
{
    uint8_t *correct_passwd = x,
        *attepmt = x + PASSWORD_MAX_LENGTH;
    uint8_t passbad = 0;

    trigger_high();
    for (uint8_t i = 0; i < PASSWORD_MAX_LENGTH; i++)
    {
        passbad |= correct_passwd[i] ^ attepmt[i];
    }
    trigger_low();
    return passbad;
}

int main(void)
{
    platform_init();
    init_uart();
    trigger_setup();

    simpleserial_init();
    simpleserial_addcmd('p', 2 * PASSWORD_MAX_LENGTH, check_password);
    while(1)
        simpleserial_get();
}
