#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

static unsigned char * hash(const char *text, size_t dsize){
    unsigned char *resultT = malloc(sizeof(char)*32);
    EVP_Digest(text, dsize, resultT, NULL, EVP_sha256(), NULL);
    return resultT;
} 

const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,./<>?;':-_!@#$&*";

int main(){
    srand(time(NULL));
    clock_t tic = clock();
    int inputsize = 19;
    unsigned char *origin = hash("hellobravenewworld!", inputsize);
    size_t dicsize = sizeof(alphabet);
    fputs("This is one way property experiment.\n", stderr);
    char *str = malloc(sizeof(char)*inputsize);
    int count = 0;
    while (1) {
        count++;
	int i;
	for (i = 0; i < inputsize; i++){
	    int tmp = rand() / (RAND_MAX / (dicsize - 1)); //index from 0 to dicsize -1
	    str[i] = alphabet[tmp];
	}
	unsigned char *tocomp = hash(str, dicsize);
	if (strncmp(tocomp, origin, 3) == 0){
	    fputs("SHA256 output of string 'hellobravenewworld!':\n", stderr);
	    for(i = 0; i < 32; i++){   
                fprintf(stderr, "%02X", origin[i]);
            }
	    fputs("\nA hash match (24 bit) occurs!\n", stderr);
	    printf("%s\n", str);
	    fputs("Its hash output is\n", stderr);
	    for(i = 0; i < 32; i++){   
		fprintf(stderr, "%02X", tocomp[i]);
	    }
	    fputs("\n", stderr);
	    break;
	}
    }    
    clock_t toc = clock();
    printf("Number of Iterations is %d\n", count);
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return 0;
}
