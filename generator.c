#include "generator.h"

int main( int argc, char ** argv)
{
	generate_totp();
	return 0;
}

bool generate_totp() {
	uint32_t bin_code, totp;
	uint8_t * key, *result;
  time_t current_time;
  current_time = time(NULL) / PERIOD;
  unsigned char secret[] = SECRET;
  unsigned char *data = target_data(current_time);
	result = hmac_sha512(secret, sizeof(secret), data, 8);
  free(data);
	bin_code = dynamic_truncation( result, RESULT_LEN);
  int sss = pow(10, DIGITS);
	totp = bin_code % sss;
	printf("One-time Password: %d\n", totp);
	return true;
}

unsigned char * target_data(time_t current_time) {
  char shex[9];
  unsigned char *str = (unsigned char *) malloc(sizeof(char) * 8);
  sprintf(shex, "%lx", current_time);
  if (shex[7] == 0) {
    memcpy(str, "00000000", sizeof(char) * 8);
    memcpy(str + 1, shex, sizeof(char) * 7);
  } else {
    memcpy(str, shex, sizeof(char) * 8);
  }
  return str;
}

uint32_t dynamic_truncation(const uint8_t *input, int length)
{
	uint32_t bin_code;
	uint8_t offset;
	offset = input[length - 1] & 0x3F;
	offset = offset % MAX_OFFSET;  
	bin_code = (input[offset] & 0x7f) << 24
		| (input[offset+1] & 0xff) << 16
		| (input[offset+2] & 0xff) << 8
		| (input[offset+3] & 0xff) ;

	return bin_code;
}
