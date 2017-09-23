#ifndef ITOA_H
#define ITOA_H


/*
* dado un valor y una base devuelve la conversión del valor a dicha base como
* cadena de caracteres
*/
char* itoa(int val, int base){

	static char buf[32] = {0};

	int i = 30;

	for(; val && i ; --i, val /= base)

		buf[i] = "0123456789abcdef"[val % base];
	printf("%s \n", buf);
	return &buf[i+1];

}

#endif
