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
    size_t dicsize = sizeof(alphabet);
    fputs("This is collision free property experiment.\n", stderr);
    char *str = malloc(sizeof(char)*inputsize);
    char *str2 = malloc(sizeof(char)*inputsize);
    int count = 0;
    while (1) {
        count++;
	int i;
	for (i = 0; i < inputsize; i++){
	    int tmp = rand() / (RAND_MAX / (dicsize - 1)); //index from 0 to dicsize -1
	    str[i] = alphabet[tmp];
	}
	for (i = 0; i < inputsize; i++){
            int tmp = rand() / (RAND_MAX / (dicsize - 1)); 
            str2[i] = alphabet[tmp];
        }
	unsigned char *hash1 = hash(str, dicsize);
	unsigned char *hash2 = hash(str2, dicsize);
	if (strncmp(hash1, hash2, 3) == 0){
	    fputs("A collision (24 bit) occurs...\n", stderr);
	    printf("Message 1 is %s\n", str);
	    fputs("Its hash output is\n", stderr);
	    for(i = 0; i < 32; i++){   
                fprintf(stderr, "%02X", hash1[i]);
            }
	    printf("Message 2 is %s\n", str2);
	    fputs("Its hash output is\n", stderr);
	    for(i = 0; i < 32; i++){   
		fprintf(stderr, "%02X", hash2[i]);
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
