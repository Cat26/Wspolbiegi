#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
void lockfileCheck() {
    while (open("lockfile", O_CREAT | O_EXCL, 0) == -1) {
        printf("Serwer zajety, prosze czekac\n");
        sleep(3);
    }
}
int isServerDone() {
    int a = 0;
    while(a==0){
        if( access("done", F_OK ) != -1 ) {
            a= 1;
        }
        return a;
    }
}

int main(int argc, char *argv[]) {
    lockfileCheck();
    FILE *clear_data  = fopen("dane.txt", "w");
    fclose(clear_data);


    char msg[256]="";
    char reply[256]="";



//pobranie wiadomosci
    FILE *konto  = fopen("dane.txt", "w");
    fprintf(konto, "%s", argv[1]);
    fprintf(konto, "\n");
    fclose(konto);

    printf("Wpisz wiadomość:\n");

    scanf("%[^/\x1b]s", msg);
    int data_file = open("dane.txt", O_RDWR | O_APPEND);


    write(data_file,msg, 256);
    close(data_file);
    FILE *done = fopen( "done", "w");
    fprintf(done, "done");
    fclose(done);
    sleep(10);
//


    while(1){
     int b = isServerDone();
    if (b==1){
        break;
    }}

//    sleep(3);
        remove("done");
//                printf("jestesmy\n");
                FILE *result_file  = fopen("wyniki.txt", "r");
                while (fgets(reply, 256, result_file) != NULL){
                    printf("%s", reply);}
    printf("\n");
    fclose(result_file);
//    remove("wyniki.txt");

    }
