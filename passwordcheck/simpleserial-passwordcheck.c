/*  -*- tab-width: 4; c-basic-offset: 4; c-file-style: "linux"; indent-tabs-mode: nil; -*-
 */

#include "hal.h"
#include "simpleserial.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t random_buffer[32];
uint8_t password[8];


uint8_t set_random(uint8_t *x)
{
    memcpy(random_buffer, x, sizeof(random_buffer));
    return 0;
}

uint8_t set_password(uint8_t *x)
{
    memcpy(password, x, sizeof(password));
    simpleserial_put('r', sizeof(password), password);
    return 0;
}

uint8_t check_password_xor(uint8_t *attempt)
{
    uint8_t passbad = 0;

    trigger_high();
    for (uint8_t i = 0; i < sizeof(password); i++)
    {
        passbad |= password[i] ^ attempt[i];
    }
    trigger_low();

    simpleserial_put('r', 1, &passbad);

    return passbad;
}

uint8_t check_password_xor_randomstart(uint8_t *attempt)
{
    uint8_t passbad = 0;

    uint8_t j = random_buffer[0] % sizeof(password);

    trigger_high();
    for (uint8_t i = 0; i < sizeof(password); i++)
    {
        passbad |= password[j] ^ attempt[j];
        j = (j + 1) % sizeof(password);
    }
    trigger_low();

    simpleserial_put('r', 1, &passbad);

    return passbad;
}

uint8_t check_password_xor_randomstart_random_buffer(uint8_t *attempt)
{
    uint8_t passbad = 0;
    uint8_t buffer1[sizeof(random_buffer)], buffer2[sizeof(random_buffer)];

    // Copy random input
    memcpy(buffer1, random_buffer, sizeof(random_buffer));
    memcpy(buffer2, random_buffer, sizeof(random_buffer));
    // Copy password and attempt
    memcpy(buffer1, password, sizeof(password));
    memcpy(buffer2, attempt, sizeof(password));

    uint8_t j = random_buffer[0] % sizeof(random_buffer);

    trigger_high();
    for (uint8_t i = 0; i < sizeof(random_buffer); i++)
    {
        passbad |= buffer1[j] ^ buffer2[j];
        j = (j + 1) % sizeof(random_buffer);
    }
    trigger_low();

    simpleserial_put('r', 1, &passbad);

    return passbad;
}

int main(void)
{
    platform_init();
    init_uart();
    trigger_setup();

    simpleserial_init();
    simpleserial_addcmd('r', sizeof(random_buffer), set_random);
    simpleserial_addcmd('p', sizeof(password), set_password);
    simpleserial_addcmd('1', sizeof(password), check_password_xor);
    simpleserial_addcmd('2', sizeof(password), check_password_xor_randomstart);
    simpleserial_addcmd('3', sizeof(password), check_password_xor_randomstart_random_buffer);
    while(1)
        simpleserial_get();
}
