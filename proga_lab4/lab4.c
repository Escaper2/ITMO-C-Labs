#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct structOfFrame              
{
    char idOfFrame[4];
    char sizeOfFrame[4];
    char frameFlags[2];
    char unicode;
};
int tagRead(FILE* file, char *id, char *version, char *f, char *len) {
    fread(id,1,3,file);
    fread(version,1,2,file);
    fread(f,1,1,file);
    fread(len,1,4,file);
}
int toInteger(char len[4], int bit) {
    return (int)len[0] << (3 * bit) | (int)len[1] << (2*bit) | (int)len[2]<<bit | (int)len[3];      
}
int tagCheck(FILE* file) {
    char id[3]; char version[2]; char flags;  char f[1]; unsigned int size; char len[5];
    if (file == NULL) {        
        printf("Problem with a input file");
        return 1;
    }
    printf("\nPlease, wait\n\n");
    tagRead(file,id,version,f,len);             
    if (memcmp(id,"ID3",3) != 0) {     
        printf("Not ID3 tag\n");
        return 2;
    }
    if (version[0] > 3) {
        printf("Wrong ID3v2 version");    
        return 3;
    }
    size = toInteger(len,7);
    return size;
}
int get(char status, unsigned char *temp, char unicode, char* idOfFrame) {
    printf(" %s: ",idOfFrame);
    if (unicode) {
         wprintf(L"%ls",temp+2);
        }
    else {
    printf("%s  \n", temp);
    }
}

int show(char *filename, unsigned char* getStatus) {
    int i; FILE* file; unsigned int frameSize; unsigned int size; int c = 0;
    struct structOfFrame frame; unsigned char value; int sizeOfNew; 
    file = fopen(filename,"rb");
    size = tagCheck(file);
    printf("Size of Tag %d\n", size);
    if (getStatus == NULL) {
        printf("\nFrames in file:\n");
    }
    else {
        printf("\nProp name of your tag");
    }
    while(ftell(file)<=size) {
        int a = ftell(file);
        if ((fread(&frame,1,11,file) != 11) || frame.idOfFrame[0] == 0) {
            break;
        }
        if (getStatus == NULL) {
            printf("%s: ",frame.idOfFrame);
        }
        frameSize = toInteger(frame.sizeOfFrame,8);
        unsigned char *tempArr = malloc(frameSize);
        memset(tempArr,0,frameSize);
        fread(tempArr,1,frameSize-1,file);
        if (getStatus != NULL) {
            if (strcmp(getStatus,frame.idOfFrame)==0) {
                get(*getStatus,tempArr,frame.unicode,frame.idOfFrame);
                c++;
            }
        }
        else if (getStatus == NULL) {
            if (frame.unicode) {
                wprintf(L"%ls\n",tempArr+2);
            }
            else {
            printf("%s \n", tempArr);
            printf("-------------------------- \n");
            }
        }
    }
    if (getStatus != NULL && c == 0) {
        printf(": this frame is not in the tag");
    }
}
int tagWrite(FILE* file, FILE* out, unsigned char* newHead) {
    char id[3]; char version[2]; char flags;  char f[1]; unsigned int size; char len[5];
    fread(id,1,3,file);
    fread(version,1,2,file);
    fread(f,1,1,file);
    fread(len,1,4,file);
    memcpy(len,newHead,4);
    fwrite(id,1,3,out);
    fwrite(version,1,2,out);
    fwrite(f,1,1,out);
    fwrite(len,1,4,out);
}

int set(char* filename, unsigned char* getStatus, char* newValue) {
    FILE* file; FILE* out; struct structOfFrame frame;
    unsigned int size; unsigned int frameSize; int sizeOfNew = strlen(newValue)+1;
    unsigned char newFrameSize[4]; int difHeadSize; int NewHeadSize; unsigned char newHead[4]; int flag = 0;
    int strcmpFlag=0;   unsigned char newFlag[2]; 
    if (getStatus == NULL) {
        printf("No proper name");
        return 4;
    }
    file = fopen(filename,"rb");
    out = fopen("out.txt","wb");
    size = tagCheck(file);
    fseek(out,10,SEEK_SET);

    if (out == NULL) {
        printf("Output error");
        return 1;
    }
    while(ftell(out)<=size) {
        fread(&frame,1,11,file);

        if (frame.idOfFrame[0] == 0) {
            if (strcmpFlag == 0) {
            memcpy(frame.idOfFrame, getStatus,4);
            newFrameSize[3] = sizeOfNew & 127;
            newFrameSize[2] = (sizeOfNew >> 8) & 127;
            newFrameSize[1] = (sizeOfNew >> 16) & 127;
            newFrameSize[0] = (sizeOfNew >> 24) & 127;
            memcpy(frame.sizeOfFrame,newFrameSize,4);
            newFlag[1] = flag & 127;
            newFlag[0] = (flag >> 8) & 127;
            memcpy(frame.frameFlags,newFlag,2);
            fwrite(&frame,1,11,out);
            fwrite(newValue,1,sizeOfNew-1,out);
            NewHeadSize = (size+sizeOfNew);
            size = NewHeadSize;
            }
            break;
        }
        if (strcmp(getStatus,frame.idOfFrame)==0) {
            frameSize = toInteger(frame.sizeOfFrame,8);
            NewHeadSize = ((size-frameSize-1) + sizeOfNew)+1;              
            size = NewHeadSize;
            newFrameSize[3] = sizeOfNew & 127;
            newFrameSize[2] = (sizeOfNew >> 8) & 127;
            newFrameSize[1] = (sizeOfNew >> 16) & 127;
            newFrameSize[0] = (sizeOfNew >> 24) & 127;
            memcpy(frame.sizeOfFrame,newFrameSize,4);
            fwrite(&frame,1,11,out);
            fwrite(newValue,1,sizeOfNew-1,out);
            unsigned char *tempArr = malloc(frameSize-1);
            memset(tempArr,0,frameSize);
            fread(tempArr,1,frameSize-1,file);
            strcmpFlag = 1;
            continue;
        }
        fwrite(&frame,1,11,out);
        frameSize = toInteger(frame.sizeOfFrame,8);
        unsigned char *tempArr = malloc(frameSize);
        memset(tempArr,0,frameSize);
        fread(tempArr,1,frameSize-1,file);  
        fwrite(tempArr,1,frameSize-1,out);
    }
    while(!feof(file)) {
        fputc(fgetc(file),out);
    }
    
    newHead[3] = NewHeadSize & 127;
    newHead[2] = (NewHeadSize >> 7) & 127;
    newHead[1] = (NewHeadSize >> 14 ) & 127;
    newHead[0] = (NewHeadSize >> 21) & 127;
    fseek(out,0,SEEK_SET);
    fseek(file,0,SEEK_SET);
    tagWrite(file,out,newHead);
    fclose(file);
    fclose(out);
    char outname[] = "out.txt";
    int a = remove(filename);                                                   
    int b = rename(outname,filename);                                                   
    printf("%d status of rename\n",b);                                          
    printf("%d status of remove\n",a);                                                      
    if (a == 0 && b == 0){                                                                              
    printf("Succesful setted %s at the %s frame\n",newValue,getStatus);                 
    }                                                                             
    else {                                                                              
        printf("Problem with set\n");                                                                   
        exit(5);
    }
}

int main(int argc, char *argv[]) {
    unsigned char *filename;
    unsigned char *getStatus;
    unsigned char *newValue; 
    if (argc < 3) {
        printf("Few arguments");
        return 5;
    }
    if (argc > 4) {
        printf("Too many arguments");
        return 5;
    }
    if (strstr(argv[1],"--filepath")) {
        unsigned char *supArr = strtok(argv[1],"=");
        supArr = strtok(NULL,"=");
        filename = malloc(strlen(supArr)+1);
        strcpy(filename,supArr);

    } 
    if (!strcmp(argv[2],"--show")) {
        getStatus = NULL;
        show(filename,getStatus);
    }
    if (strstr(argv[2],"--get")) {
        unsigned char *supArr = strtok(argv[2],"=");
        supArr = strtok(NULL, "=");
        getStatus = malloc(strlen(supArr)+1);
        strcpy(getStatus,supArr);
        show(filename,getStatus);
    }
    if (strstr(argv[2],"--set")) {
        unsigned char *supArr = strtok(argv[2],"="); 
        unsigned char *getStatus = strtok(NULL, "="); 
        unsigned char *secSupArr = strtok(argv[3],"=");  
        unsigned char *newValue = strtok(NULL,"=");  
        set(filename,getStatus,newValue);  
    }
    return 0;
}
