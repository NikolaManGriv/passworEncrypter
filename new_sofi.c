#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int T = 126;
int P = 33;



void help(){
	printf(
			"\t\t*********************\n"
			"\t\t* usage:            *\n"
			"\t\t* sofi -e <mssg>    *\n"
			"\t\t* Encrypts message  *\n"
			"\t\t* sofi -d <mssg>    *\n"
			"\t\t* Decrypts message  *\n"
			"\t\t*********************\n"
	      );
}


int fun(int x, int M){
    int m = x+M;
    return m > T ? (m % T) + P-1 : m;
}

int desFun(int x, int M){
    int n = x-M;
    return x <=	P+M-1 ? T +x -M -P+1 : n;
}

int* get_rand_room(char* mssg, unsigned int size){
    return !mssg ? NULL : malloc(sizeof(int)* size);
}

void fill_rand_room(int* r, unsigned int size){
    FILE* f = fopen("/dev/urandom", "rb");
    if (!f){ printf("something went wrong with internal encryption logic\n"); return ; }
    fread(r, sizeof(int), size, f);
    fclose(f);
    for (unsigned int i =0; i< size; i++){
	r[i] = r[i] < 0 ? (-r[i]) % (T-P+1): r[i]% (T-P+1);
 	r[i] = r[i] < P ? P : r[i];
	assert(P <= r[i] && r[i] <= T);
    }
}

void encrypt(char* mssg, int* random_m, unsigned int size ){
    printf("Encrypting...\n");
    for (unsigned int i=0; i< size; i++){
	printf("%c%c", fun((int)mssg[i], random_m[i]), fun(random_m[i], P));
    }
    printf("\n");
    printf("come back later :D\n");
    fflush(stdout);
    free(random_m);
}

void decrypt(char* mssg, unsigned int size){
    printf("Decrypting...\n");
    for (unsigned int i =0; i< size-1; i+=2){
	mssg[i+1] = desFun(mssg[i+1], P);
	printf("%c", desFun(mssg[i], mssg[i+1]));
    }
    printf("\nThanks, come back later :D\n");
    fflush(stdout);
}



int main(int argc, char** argv ){

    if (argc < 3 || !((strcmp(argv[1], "-d")==0) ^ (strcmp(argv[1], "-e")==0))){
	help();
	return 0;
    }
    
    unsigned int size = strlen(argv[2]); 
    if (strcmp(argv[1], "-e")==0){
	int* ran_m = get_rand_room(argv[2], size);    

	if(!ran_m){printf("invalid message to work with\n");  return 0;}
	fill_rand_room(ran_m, size); 
	encrypt(argv[2], ran_m, size);
    }
    //case -d
    else{
	decrypt(argv[2], size);
    }
    return 0;
}
/*
//tests
int main(void){

    int* ran_m = get_rand_room("hola", 1);    
    for(int i =P; i<T+1; i++){
	fill_rand_room(ran_m, 1); 
	int val = desFun (fun(i, *ran_m), *ran_m); 
	//if (P> val || val > T){printf("Error :(\n");return 0; }
	if(val != i){printf("Error :(\n");return 0; }
    }
    printf("SUCCESS :D\n");
    free(ran_m);
    return 0;
}
*/
