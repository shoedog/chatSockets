#ifndef UTILS_IO_H
#define UTILS_IO_H

/******************************************************************************
*   Function: getHandle
*
*   Description: Prompt for and set user handle from input
*
*   Entry: *clientHandle: char array to set
*          bufferSize: size of handle
*
*   Exit: clientHandle set from user input
*
*   Purpose: get client handle for chat
*
******************************************************************************/
void getHandle(char *clientHandle, int bufferSize);

/******************************************************************************
*  Function: messagePrompt
*
*   Description: Prompt for and set message from input
*
*   Entry: *message: char * to hold message
*
*   Exit: message set from user input
*
*   Purpose: get client message for chat
*
******************************************************************************/
void messagePrompt(char *message);

#endif
