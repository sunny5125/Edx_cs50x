#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
	float moneyHave;
    int moneyHaveInt;
    int coins = 0;

    do
    {
        printf("How much change is owed? ");
        moneyHave = GetFloat();
    } while (moneyHave <= 0);
    
    moneyHaveInt = round(moneyHave * 100);
    
    while (moneyHaveInt > 0)
    {
        if (moneyHaveInt - 25 >= 0)
        {
            moneyHaveInt -= 25;
            coins++;
        }
        else if (moneyHaveInt - 10 >= 0)
        {
            moneyHaveInt -= 10;
            coins++;
        }
        else if (moneyHaveInt - 5 >= 0)
        {
            moneyHaveInt -= 5;
            coins++;
        }
        else
        {
            moneyHaveInt -= 1;
            coins++;
        }
    }
    
    printf("%d\n", coins);
    
    
	return 0;
}
