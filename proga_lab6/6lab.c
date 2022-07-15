#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <io.h> 
struct structOfArchive {
    char sizeOfName[4];
    char sizeOfFile[4];
};
int toBytes(int lenOfName, char *archive) {
    archive[3] = lenOfName & 127;
    archive[2] = (lenOfName >> 8) & 127;
    archive[1] = (lenOfName >> 16) & 127;
    archive[0] = (lenOfName >> 24) & 127; 
}
int toInteger(char len[4], int bit) {
    return (int)len[0] << (3 * bit) | (int)len[1] << (2*bit) | (int)len[2]<<bit | (int)len[3];      
}
int writeToFile(FILE *file, char* sizeOfName, char* sizeOFile, char* todo, int lenOfName) {
    fwrite(sizeOfName,1,4,file);
    fwrite(sizeOFile,1,4,file);
    fwrite(todo,1,lenOfName,file);
}
int create(FILE *file, char *todo) {
    FILE *readFile; int lenOfFile; struct structOfArchive archive; int lenOfName;
    readFile = fopen(todo, "rb");
    lenOfFile = filelength(fileno(readFile));
    lenOfName = strlen(todo);
    toBytes(lenOfName,archive.sizeOfName);
    toBytes(lenOfFile,archive.sizeOfFile);
    writeToFile(file,archive.sizeOfName,archive.sizeOfFile,todo,lenOfName);
    int i;
    while((i = fgetc(readFile)) != EOF) {
        fputc(i,file);
    }
}
int extract(FILE *file) {
    uint64_t lenOfArchive; struct structOfArchive archive; int nameSize; int insideOfFileSize; FILE *out;
    lenOfArchive = filelength(fileno(file));
    while(ftell(file)<lenOfArchive) {
        fread(archive.sizeOfName,sizeof(char),4,file);
        nameSize = toInteger(archive.sizeOfName,8);
        fread(archive.sizeOfFile,sizeof(char),4,file);
        insideOfFileSize = toInteger(archive.sizeOfFile,8);
        nameSize++;
        unsigned char *tempArr = malloc(nameSize);
        memset(tempArr,0,nameSize);
        fread(tempArr,1,nameSize-1,file);
        out = fopen(tempArr, "wb");
        int i=0;
        for(i;i<insideOfFileSize;i++) {
            fputc(fgetc(file),out);
        }
    }
}
int list(FILE *file) {
    uint64_t lenOfArchive; struct structOfArchive archive; int nameSize; int insideOfFileSize;
    lenOfArchive = filelength(fileno(file));
    while(ftell(file)<lenOfArchive) {
        fread(archive.sizeOfName,1,4,file);
        nameSize = toInteger(archive.sizeOfName,8);
        fread(archive.sizeOfFile,sizeof(char),4,file);
        insideOfFileSize = toInteger(archive.sizeOfFile,8);
        unsigned char *tempArr = malloc(nameSize);
        memset(tempArr,0,nameSize);
        fread(tempArr,1,nameSize,file);
        printf("%s\n",tempArr);
        unsigned char *tempArr2 = malloc(insideOfFileSize);
        memset(tempArr2,0,insideOfFileSize);
        fread(tempArr2,1,insideOfFileSize,file);
    }
}
 int main(int argc,char *argv[]) {
    FILE *file;
    unsigned char *archivename;
        if (argc < 3) { 
        printf("Few arguments");
        return 5;
    }
    for(int i=1; i < argc-1; i++) {
        if (strstr(argv[i],"--file")) {
            archivename = argv[i+1];
            i+=2;
        }
        if (strstr(argv[i],"--create")) {
            while (i<argc-1) {
                i++;
                file = fopen(archivename,"ab");
                create(file,argv[i]);
                fclose(file);
            }
        }
        if (strstr(argv[i],"--list")) {
            file = fopen(archivename,"rb");
            list(file);
            fclose(file);
        }
        if (strstr(argv[i],"--extract")) {
            file = fopen(archivename,"rb");
            extract(file);
            fclose(file);
        }
    } 
    return 0;
}