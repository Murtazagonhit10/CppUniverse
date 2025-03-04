#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Do not get scared of \033 things
//\033[1;3 prints Bold+Italic words
//\033[1 prints Bold words
//\033[3 prints Italic words
//\033[0 resets the formatting

//Gives a Warm Welcome
void welcome()
{
    cout << "\n\n\033[1;3mWELCOME TO THE THE LUCKY GUESS ARENA\n\n\033[0m";
    cout << "The \033[1mRules\033[0m of the Game are simple: \n";
    cout << "You will be given with a choice of Difficulty level corresponding to the number of chances you get.\n"
            "If you \033[1mCorrectly\033[0m Guess the number before the number of chances end, you \033[1;3mWIN!!\033[0m, else you \033[1mlose...\033[0m :(\n\n";
}
//Asks the user to Select the Difficulty level
void selectLevel(int &choice) 
{
    cout << "\nThe \033[1mRange\033[0m in which You will have to Guess is \033[1;3m1-100\n\n\033[0m";

    do
    {
        cout << "\nPlease select the difficulty level: \n"
                "1. \033[1mEasy   (10 chances)\n\033[0m"
                "2. \033[1mMedium (5 chances)\n\033[0m"
                "3. \033[1mHard   (3 chances)\n\033[0m";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 3)
            cout << "Please Enter a Valid Number..\n";
    } while (choice < 1 || choice > 3);
}
//Generates a random Number within a given range, in this case the range is 1-100
int generateRandom()
{
    srand(time(0));
    int min = 1, max = 100;

    return (min + (rand() % (max - min + 1)));
}

//User plays the game when this function is called
void playGame(int &chances,int &highscore,bool& win)
{
    cout << "\n\nGreat! You have selected the " << (chances==10?"Easy": chances==5?"Medium": "Hard") << " Difficulty Level.\n"
            "\033[1;3mLET'S START THE GAME!\n\n\033[0m";

    int comp_choice = generateRandom(); //random number generated
    time_t start_time, end_time; //time checks to calculate how much time player took to guess the number
    time(&start_time);//starting check
    for (int i = 1; i <= chances; i++)
    {
        int guess;
        do
        {
            cout << "Enter Your Guess: ";
            cin >> guess;
            if (guess < 1 || guess > 100)
            {
                cout << "The Range is \033[1m1-100!!!\n\033[0m";
            }
        } while (guess < 1 || guess > 100);

        if (guess == comp_choice) //User guesses correctly
        {
            time(&end_time);//ending check
            double time_taken = difftime(end_time, start_time);
            cout << "\n\033[1;3mCongratulations You've Won the Game!!!\n\033[0m"
                 << "You Guessed the Number Correctly in \033[1;3m" << i << " " << ((i == 1) ? "Attempt\n\n" : "Attempts\n")<<"\033[0m";
            if (i < highscore)
                highscore = i;
            cout << "\n\033[1;3mBest Score in\033[0m " << (chances==10?"Easy": chances==5?"Medium": "Hard") << " Difficulty: \033[1;3m" << highscore << ((highscore == 1) ? " Attempt\n\n" : " Attempts\n")<<"\033[0m";
            cout << "Total Time Taken: \033[1;3m" << time_taken << " seconds. \n\n\033[0m";
            win = true;
            break;
        }
        else if (guess > comp_choice)//incorrect guess so a hint provided
        {
            cout << "\nIncorrect! The number is Less than " << guess << endl
                 << "You've got \033[1;3m" << chances - i << "\033[0m Guesses Remaining!!\n\n";
        }
        else //incorrect guess so a hint provided
        {
            cout << "\nIncorrect! The number is Greater than " << guess << endl
                 << "You've got \033[1;3m" << chances - i << "\033[0m Guesses Remaining!!\n\n";
        }
    }

    if (!win) //Couldn't Guess in the Guess limit
    {
        cout << "\nYou Lost... but \033[1mHey, at least you had FUN!!\n\033[0m";
        cout << "The Correct Number was \033[1m" << comp_choice << "\n\033[0m";
    }
}

char anotherGame() //Asks user if he wants to play again.
{
    char another;
    cout << "Wanna Give it Another Shot??\n";
    do
    {
        cout << "Press \033[1mY\033[0m to play Again or \033[1mX\033[0m to quit: ";
        cin >> another;
        if (another != 'x' && another != 'X' && another != 'y' && another != 'Y')
            cout << "\nEnter Valid Character...\n";
    } while (another != 'x' && another != 'X' && another != 'y' && another != 'Y');

    return another;
}

int main()
{
    welcome();

    int choice = 0;
    bool win = false;
again: //Label to control return to this point if user wants to play again

    selectLevel(choice);

    if (choice == 1)
    {
        int chances=10;
        int highscore=10;
        playGame(chances,highscore,win);
    }
    else if (choice == 2)
    {
        int chances=5;
        int highscore=5;
        playGame(chances,highscore,win);
    }
    else
    {
        int chances=3;
        int highscore=3;
        playGame(chances,highscore,win);
    }

    char another=anotherGame();
    if (another == 'y' || another == 'Y')
        goto again;
    else
        cout << "\n\033[1;3mHave a Nice Day!!\n\n\033[0m";
    return 0;
}
