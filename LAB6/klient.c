#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

#define keyin 10
#define keyout 9

typedef struct {
   char polish[100];
   char english[100];
} dictionary;

typedef struct {
   long pID;
   char my_word[100];
} message;

int main(int argc, char *argv[]) {
  message msg;
  int IN, OUT;

  IN=msgget(keyin, 0777);
  OUT=msgget(keyout, 0777);

  strcpy(msg.my_word, argv[1]);
  msg.pID=getpid();
  //send message to message quque
  msgsnd(IN, &msg, sizeof(char)*110, 0);
  printf("POL: \"%s\" - ", argv[1]);
  //receive message from message queue
  msgrcv(OUT, &msg, sizeof(char)*110, getpid(), 0);
  printf("ENG: \"%s\".\n", msg.my_word);

  return 0;
}
