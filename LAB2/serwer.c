#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


int isClientDone() {
    int a = 0;
     while(a==0){
        if( access( "done", F_OK ) != -1 ) {
            a= 1;
        }
         return a;
    }
}

int main(int argc, char *argv[]) {

    char reply[256]="";
    char msg[256]="";
    int answer_file = open("wyniki.txt", O_RDWR | O_APPEND);

    while(1) {

        if(isClientDone()){

            remove("done");
            FILE *data_file  = fopen("dane.txt", "r");
            //odczytanie wiadomosci
            while (fgets(msg, 256, data_file) != NULL){
                    printf("%s", msg);}
                    fclose(data_file);
                    printf("\n");

            printf("odpowiedź:\n");

char ch;
            do{
                    gets(reply);
                   ch =  getchar();
              }while(ch != '\x1b' && ch !='\n');


            FILE *clear_data  = fopen("wyniki.txt", "w");
            fclose(clear_data);
                    int answer_file = open("wyniki.txt", O_RDWR | O_APPEND);
                    write(answer_file,reply, 256);
                    close(answer_file);
            //serwer done
                    FILE *done = fopen( "done", "w");
                    fprintf(done, "done");
                    fclose(done);
            //cleanup

            sleep(5);
                    remove("lockfile");


        }


    }}
