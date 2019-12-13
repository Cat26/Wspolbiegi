#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

#define DICTSIZE 20
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

dictionary dictPolEng[DICTSIZE] = {
   {"klawiatura", "keyboard"},
   {"kot", "cat"},
   {"pies", "dog"},
   {"pomarancza", "orange"},
   {"ekran", "screen"},
   {"lampa", "lamp"},
   {"mleko", "milk"},
   {"ciastko", "cookie"},
   {"stol", "table"},
   {"samolot", "plane"},
   {"dom", "house"},
   {"samochod", "car"},
   {"gra", "game"},
   {"grac", "play"},
   {"chwila", "while"},
   {"drzewo", "tree"},
   {"telefon", "telephone"},
   {"glowa", "head"},
   {"mysz", "mouse"},
   {"slon", "elephant"}
};

char *translate(char* word){
   int i;
   for ( i = 0; i < DICTSIZE; i++) {
      if(!strcmp(word, dictPolEng[i].polish))
         return dictPolEng[i].english; }
   return "Not in the dicionary";
}
int IN, OUT;
int main(int argc, char *argv[]) {

   message msg;
   //create new segment
   IN = msgget(keyin, 0777 | IPC_CREAT);
   OUT = msgget(keyout, 0777 | IPC_CREAT);

   while(1){
      msgrcv(IN, &msg, sizeof(char)*110, 0, 0);
      printf("\"%s\", ", msg.my_word);
      strcpy(msg.my_word, translate(msg.my_word));
      printf("Sending translation to %5ld: \"%s\".\n", msg.pID, msg.my_word);
      msgsnd(OUT, &msg, sizeof(char)*110, 0);
   }
   return 0;
}
