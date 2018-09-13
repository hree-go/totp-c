#include "hmac.h"
#include <inttypes.h>
#include <math.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#ifdef DEBUG
#define PRINTD( format, ... ) fprintf(stderr,format, __VA_ARGS__ );
#else
#define PRINTD( format, ... )
#endif

#define DIGITS 6
#define PERIOD 60
#define MAX_OFFSET (length - 5)
#define SECRET "your_secret"

bool generate_totp(void);

uint32_t dynamic_truncation(const uint8_t *input, int length);

unsigned char* target_data(time_t current_time);
