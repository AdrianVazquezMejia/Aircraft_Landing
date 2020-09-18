#include<stdint.h>

void ce(long int p, long int q, long int t, long int *e, long int *d);
long int cd(long int x, long int  t);
void encrypt(long int *e,long int n, char *msg);
void decrypt(long int *en, long int *temp, long int n );
int prime(long int pr);
typedef short int pixel_t;
void encryptImage(pixel_t *image, int32_t  width, int32_t  height,long int *en, long int *temp, long int *e, long int n);
void decryptImage(pixel_t *image, int32_t  width, int32_t  height, long int *en, long int *temp, long int *d,  long int n);

