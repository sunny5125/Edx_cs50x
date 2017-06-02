#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
int main(void)
{
    string inputName = GetString();
    char initial_character[10];
    int i = 0, j = 0;

    for (i=0; inputName[i]!='\0'; i++){
        if (i == 0)                             
            initial_character[j++]=toupper(inputName[i]);
        if (inputName[i-1] == ' ')                   
            initial_character[j++]=toupper(inputName[i]);
    }

    for(i=0; i<j; i++){
        printf("%c",initial_character[i]);
    }                         
    printf("\n");
    return 0;
}