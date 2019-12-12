/*  -*- tab-width: 4; c-basic-offset: 4; c-file-style: "linux"; indent-tabs-mode: nil; -*-
 */

#include "hal.h"
#include "simpleserial.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <mbedtls/sha1.h>

#define LENGTH_OF_PASSWORD 8
#define SHA1_DIGEST_SIZE 20

uint8_t password_hash[SHA1_DIGEST_SIZE];


uint8_t set_password(uint8_t *x)
{
    mbedtls_sha1(x, LENGTH_OF_PASSWORD, password_hash);
    simpleserial_put('r', SHA1_DIGEST_SIZE, password_hash);
    return 0;
}

uint8_t check_password_hash(uint8_t *attempt)
{
    uint8_t passbad = 0;

    uint8_t attempt_hash[SHA1_DIGEST_SIZE];
    mbedtls_sha1(attempt, LENGTH_OF_PASSWORD, attempt_hash);

    trigger_high();
    for (uint8_t i = 0; i < SHA1_DIGEST_SIZE; i++)
    {
        if (password_hash[i] != attempt_hash[i])
        {
            passbad = 1;
            break;
        }
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
    simpleserial_addcmd('p', LENGTH_OF_PASSWORD, set_password);
    simpleserial_addcmd('4', LENGTH_OF_PASSWORD, check_password_hash);
    while(1)
        simpleserial_get();
}
