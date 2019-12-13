#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

#define SERVERFIFO "/home/kurczak/serwerfifo"
#define CLIENTFIFO "/home/kurczak/klientfifo"

struct names{
  int ID;
  char *surname;
};

void nullingArray(char *array){
	for(int i = 0; i < sizeof(array); i++) array[i] = '\0';
};

int main(){
  struct names database[20];
  database[0].surname = "nazwisko0";
  database[1].surname = "nazwisko1";
  database[2].surname = "nazwisko2";
  database[3].surname = "nazwisko3";
  database[4].surname = "nazwisko4";
  database[5].surname = "nazwisko5";
  database[6].surname = "nazwisko6";
  database[7].surname = "nazwisko7";
  database[8].surname = "nazwisko8";
  database[9].surname = "nazwisko9";
  database[10].surname = "nazwisko10";
  database[11].surname = "nazwisko11";
  database[12].surname = "nazwisko12";
  database[13].surname = "nazwisko13";
  database[14].surname = "nazwisko14";
  database[15].surname = "nazwisko15";
  database[16].surname = "nazwisko16";
  database[17].surname = "nazwisko17";
  database[18].surname = "nazwisko18";
  database[19].surname = "nazwisko19";
  FILE *fs;
  int client_fifo = 0;
  int chosen_index = 0;
  char buffer[80] = "";
  char index[2] = "";
  char answer[20] = "";

  while(1){
  //   //Resetowanie zmiennych.
    chosen_index = 0;
    nullingArray(buffer);
	  nullingArray(index);

    //Otwarcie fifo serwera.
    fs = fopen(SERVERFIFO, "r");
    fgets(buffer, 80, fs);
    fclose(fs);

    //Pobranie indeksu z zapytania.
    //Case - dwucyfrowy index.
    if(isdigit(buffer[3])) {
      index[0] = buffer[2];
      index[1] = buffer[3];
    }
    //Jednocyfrowy index.
    else{
      index[0] = buffer[2];
      index[1] = '\0';
    }
    //Zapis indexu.
    sscanf(index, "%d", &chosen_index);

    //Wybor odpowiedzi w zaleznosci od znalezionej liczby.
    //Case - brak rekordu.
    if(chosen_index < 0 || chosen_index > 19){
      strcpy(answer, "Nie ma takiego rekordu w bazie!");
    }
    //Case - znaleziono rekord.
    else {
     sscanf(database[chosen_index].surname, "%s", answer);
    }
    //Wyslanie odpowiedzi do fifo klienta.
    // sleep(2);
    client_fifo = open(CLIENTFIFO, O_WRONLY);
    write(client_fifo, answer, strlen(answer)+1);
    close(client_fifo);
  }
  return 0;
}
