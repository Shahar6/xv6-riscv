#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    
    char cont = '1';
    int checkers_num = 3;
    if(argc > 1){
        checkers_num = atoi(argv[1]);
    }

    while(cont == '1'){
        int primes_found = 0;
        int channel_check = channel_create();
        int channel_print = channel_create();

        if(channel_check == -1 || channel_print == -1){
            printf("Couldn't create channels\n");
            channel_destroy(channel_check);
            channel_destroy(channel_print);
            return -1;
        }

        for(int i=0; i < checkers_num; i++){
            int id = fork();
            if (id == 0) {
                for(;;){
                    int num;
                    int code = channel_take(channel_check, &num);
                    if(code != 0)
                        exit(0);
                    int a = 2;
                    while(a < num/2){
                        if(num % a == 0)
                            break;
                        a = a + 1;
                    }
                    if(a >= num/2)
                        code = channel_put(channel_print, num);
                    if(code != 0){
                        printf("Checker %d finished\n", getpid());
                        channel_destroy(channel_check);
                        exit(0);
                    }
                }
            }
        }

        int id = fork();
        if(id == 0){
            for(;;){
                int num;
                int code = channel_take(channel_print, &num);
                if(code != 0)
                    exit(0);
                printf("Found prime number %d found(%d/100)\n", num, primes_found + 1);
                primes_found = primes_found + 1;
                if(primes_found == 100){
                    printf("Printer %d finished\n", getpid());
                    channel_destroy(channel_print);
                    exit(0);
                }
            }
        }
        else{
            int num = 2;
            for(;;){
                int code = channel_put(channel_check, num);
                if(code != 0){
                    printf("Generator %d finished\n", getpid());
                    break;
                }
                num = num + 1;
            }
            int* pid = 0;
            for(int i=0; i<1 + checkers_num; i++){
                int code = wait(pid);
                if(code == -1){
                    break;
                }
            }
            printf("Program finished.\nEnter 'y' to start again.\n");
            char buf[100];
            gets(buf, 100);
            if(buf[0] != 'y'){
                cont = '0';
            }
        }
    }
    return 0;
}