//Duy Pham 1002035014

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_the_bingo(int array[5][5]);

void print_the_bingo(int array[5][5]);

int pick_number(int array[75]);

int number_check(int array[5][5], int number);

int row_check(int array[5][5]);

int column_check(int array[5][5]);

int diagonal_check(int array[5][5]);

int main(void)
{
    //set up random 
    srand(time(0));

    //array set up
    int bingo[5][5] = {};
    int duplicate[75] = {};

    //fill and print the bingo
    fill_the_bingo(bingo);
    print_the_bingo(bingo);

    //Bingo requirement
    int row = 0;
    int column = 0;
    int diagonal = 0;

    //play Bingo!!
    while(row == 0 && column == 0 && diagonal == 0)
    {
        //pick and print a random number
        int number = pick_number(duplicate);
        if(number <= 15)
        {
            printf("\nThe next number is B%d\n", number);
        }
        else if(number <= 30)
        {
            printf("\nThe next number is I%d\n", number);
        }
        else if(number <= 45)
        {
            printf("\nThe next number is N%d\n", number);
        }
        else if(number <= 60)
        {
            printf("\nThe next number is G%d\n", number);
        }
        else
        {
            printf("\nThe next number is O%d\n", number);
        }

        //ask player
        char answer;
        printf("\nDo you have it? (Y/N)");
        scanf(" %c", &answer);

        //check if answer is valid
        if(answer == 89 || answer == 121)
        {
            //check if number exist
            int check = number_check(bingo, number);

            //if doesn't exist
            if(check == 0)
            {
                printf("\nThat value is not on your BINGO card - are you trying to cheat??\n");

                //play again
                print_the_bingo(bingo);
            }
            else
            {
                //play again
                print_the_bingo(bingo);

                //bingo check
                row = row_check(bingo);
                column = column_check(bingo);
                diagonal = diagonal_check(bingo);

                //print congrat
                if(row == 1 && column == 0 && diagonal == 0)
                {
                    printf("\nYou filled out a row - BINGO!!!\n");
                }
                else if(row == 0 && column == 1 && diagonal == 0)
                {
                    printf("\nYou filled out a column - BINGO!!!\n");
                }
                else if(row == 0 && column == 0 && diagonal == 1)
                {
                    printf("\nYou filled out a diagonal - BINGO!!!\n");
                }
                else if(row == 1 && column == 1 && diagonal == 0)
                {
                    printf("\nYou filled out a row and a column - BINGO!!!\n");
                }
                else if(row == 1 && column == 0 && diagonal == 1)
                {
                    printf("\nYou filled out a row and a diagonal - BINGO!!!\n");
                }
                else if(row == 0 && column == 1 && diagonal == 1)
                {
                    printf("\nYou filled out a column and a diagonal - BINGO!!!\n");
                }
                else if(row == 1 && column == 1 && diagonal == 1)
                {
                    printf("\nYou filled out a row, a column, and a diagonal - BINGO!!!\n");
                }
            }
        }
        else
        {
            //play again
            print_the_bingo(bingo);
        }
    }

    return 0;
}

void fill_the_bingo(int array[5][5])
{
    //basic set up
    int unique[75];
    int counter = 0;

    //fill the array
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {   

            //get random number in range
            int number = rand() % 15 + (15 * i) + 1;

            //condition for special case at the middle
            if(i == 2 && j == 2)
            {
                array[2][2] = 0;
            }
            else
            {
                int inner_counter = 0;

                //check if number is duplicate or not
                while(inner_counter < counter)
                {
                    if(unique[inner_counter] == number)
                    {
                        number = rand() % 15 + (15 * i) + 1;
                        inner_counter = 0;
                    }
                    else
                    {
                        inner_counter ++;
                    }
                }

                //add number to unique set
                unique[counter] = number;
                counter ++;

                //add number to the bingo set
                array[j][i] = number;
            }
        }
    }
}

void print_the_bingo(int array[5][5])
{
    //print BINGO title
    printf("\n%5c%8c%8c%8c%8c\n", 'B', 'I', 'N', 'G', 'O');
    printf("-----------------------------------------\n");

    //print BINGO value
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(array[i][j] == 0)
            {
                printf("|%4c\t", 'X');
            }
            else
            {
                printf("|%4d\t", array[i][j]);
            }
        }
        printf("|\n-----------------------------------------\n");
    }
}

int pick_number(int array[75])
{
    int dup_check = 0;

    //pick a random number
    int number = rand() % 75 + 1;

    //check if duplicate
    while(array[dup_check] != 0)
    {
        if(array[dup_check] == number)
        {
            number = rand() % 75 + 1;
            dup_check = 0;
        }
        else
        {
            dup_check ++;    
        }
    }

    //add to duplicate array
    array[dup_check] = number;

    return number;
}

int number_check(int array[5][5], int number)
{
    int boolen = 0;
    
    //loop through array to check for number
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if (array[j][i] == number)
            {
                array[j][i] = 0;
                boolen++;
            }
        }
    }

    return boolen;
}

int row_check(int array[5][5])
{
    int boolean = 0;

    for(int i = 0; i < 5; i++)
    {
        int counter = 0;
        for(int j = 0; j < 5; j++)
        {
            if(array[i][j] == 0)
            {
                counter++;
            }
            if(counter == 5)
            {
                boolean++;
            }
        }
    }

    if(boolean > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int column_check(int array[5][5])
{
    int boolean = 0;

    for(int i = 0; i < 5; i++)
    {
        int counter = 0;
        for(int j = 0; j < 5; j++)
        {
            if(array[j][i] == 0)
            {
                counter++;
            }
            if(counter == 5)
            {
                boolean++;
            }
        }
    }

    if(boolean > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int diagonal_check(int array[5][5])
{
    int counter1 = 0;
    int counter2 = 0;

    for(int i = 0; i < 5; i++)
    {
        if(array[i][i] == 0)
        {
            counter1++;
        }
        if(array[i][4-i] == 0)
        {
            counter2++;
        }
    }

    if(counter1 == 5 || counter2 == 5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}