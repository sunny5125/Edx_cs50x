#include <cs50.h>
#include <stdio.h>

int GetPositiveInt(void) {
    int n;
    do
    {
        printf("Enter amount of time spend in the shower: ");
        n = GetInt();
    } 
    while(n < 1);
    return n;
}

int main(void) {
    
    int timeInShower = GetPositiveInt();
    int x = (timeInShower * 1.5) * 128;
    int y = x /16;
    timeInShower = y;
    printf("Number of bottles used : %i\n", timeInShower);
}

