#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define SERVERFIFO "/home/kurczak/serwerfifo"
#define CLIENTFIFO "/home/kurczak/klientfifo"

int main(int argc, char *argv[]){
//Deklaracje zmiennych.
  FILE *client_fifo;
  char *home = getenv("HOME");
  char msg[200] = "";
  char information[120] = "";
  char buffer[80] = "";
  int index = 0;
  int server_fifo = open(SERVERFIFO, O_WRONLY);

// Konkatenacja szukanego indexu oraz sciezki fifo.
  strcat(information, argv[1]);
  strcat(information, home);
  do{
    index = index + 1;
  } while(information[index] != '\0');

//Przypisanie indexu i sciezki do wiadomosci.
  sprintf(msg, "%d%s", index, information);


//Wyslanie wiadomosci do fifo.
  write(server_fifo, msg, strlen(msg)+1);
  close(server_fifo);

//odczytanie zawartosci kolejki.
  client_fifo = fopen(CLIENTFIFO, "r");
  fgets(buffer, 80, client_fifo);
  printf("\n%s\n", buffer);
  fclose(client_fifo);

  return(0);
}
