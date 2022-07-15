#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Few arguments");
        return 1;
    } 
    else if (argc > 3) {
        printf("Too many arguments");
        return 2;
    }
    else if (argc == 3) {
        FILE *myfile;
        myfile = fopen(argv[argc - 1],"r");
        int symbol;
        int lastSymbol;
        if  ((strcmp(argv[1], "-w") == 0) || (strcmp(argv[1], "--word") == 0))    {
            long wordCounter = 0;
            while( fscanf( myfile, "%*s" ) != EOF ) {   
                wordCounter++;
                }
                printf("%s %d\n", "Words in file:", wordCounter);
            }
            else if ((strcmp(argv[1], "-l") == 0) || (strcmp(argv[1], "--lines") == 0))   {
                long linesCounter = 0;
                while ((symbol = fgetc(myfile)) != EOF) {
                    lastSymbol = symbol;
                    if (symbol == '\n') {
                        ++linesCounter;
                    }
                }
                if ((lastSymbol != '\n') && (lastSymbol != EOF))    {
                    ++linesCounter;
                }
                printf( "%s %d\n", "Lines in file:", linesCounter);
            }
            else if ((strcmp(argv[1], "-c") == 0) || (strcmp(argv[1], "--bytes") == 0))   {
                long byteCounter = 0;
                while ((symbol = fgetc(myfile)) != EOF )    {
                    ++byteCounter;
                    if (symbol == '\n') {
                        ++byteCounter;
                    }
                }
                printf("%s %d\n", "Byte in file:", byteCounter );
            }
            else   {
                printf("Wrong command");
                return 3;
            }
        }

    return 0;
}
