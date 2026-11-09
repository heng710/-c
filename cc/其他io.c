#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main(int argc,char *argv[]){
    DIR *dir=opendir(argv[1]);
    if(dir==NULL){
        perror("opendir fail");
        return -1;
    }
    char bmp[20][1024]={"1.bmp","2.bmp","3.bmp"};
    int i=0;
    while(1){
        struct dirent *ent=readdir(dir);
        if(ent==NULL){
            break;
        }
        if(ent->d_name[i]!='.'&&ent->d_type==DT_REG){
           char path[1024];
           sprintf(path,"%s/%s",argv[1],ent->d_name);
           strcpy(bmp[i],path);
           i++;
        }
    }
    for(int j=0;j<i;j++){
        printf("%s\n",bmp[j]);
    }
    closedir(dir);
    return 0;
}

