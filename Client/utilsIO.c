#include <stdio.h>

void getHandle(char* clientHandle, int bufferSize){
	printf("Input Handle: ");
    fgets(clientHandle, bufferSize, stdin);
}

void messagePrompt(char* message){
	int bufferSize = 501;

	printf("> ");
    fgets(message, bufferSize, stdin);
}
