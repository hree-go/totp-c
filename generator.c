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
  current_time = time(NULL);
  char hex[8];
  printf("ooooooooooooooo");
  sprintf(hex, "%x", current_time / 60);
  printf("--------------------%s\n", hex);
  printf("--------------------%d\n", sizeof(hex));
	result = hmac_sha512( "hello", 5,  hex, 7 /* 8 */);
	printf("\n\n\tresult: %s\n\n", result);
	printf("\n\n\tresult: %d\n\n", result);
	bin_code = dynamic_truncation( result, RESULT_LEN);
  printf("\dbin_code:%d\n", bin_code);
  int sss = pow(10, DIGITS);
  printf("\ddd: %d\n", DIGITS);
  printf("\nsss: %d\n", sss);
	totp = bin_code % sss;
	printf("\n\n\tOne-time Password: %u\n\n", totp);
	return true;
}


uint32_t dynamic_truncation(const uint8_t *input, int length)
{
	uint32_t bin_code;
	uint8_t offset;

	offset = input[length - 1] & 0x3F;
	offset = offset % MAX_OFFSET;  

  printf("\ntest:%d\n", input[offset]);
  printf("\ntest:%d\n", input[offset + 1]);
  printf("\ntest:%d\n", input[offset + 2]);
  printf("\ntest:%d\n", input[offset + 3]);


	bin_code = (input[offset] & 0x7f) << 24
		| (input[offset+1] & 0xff) << 16
		| (input[offset+2] & 0xff) << 8
		| (input[offset+3] & 0xff) ;

	return bin_code;
}
