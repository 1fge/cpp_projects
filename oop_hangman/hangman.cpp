/****************************************
Simple hangman game utilzing OOP concepts
****************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;


class Hangman
{
    public:
        Hangman();
        Hangman(string filename, int lives);
        void initialize_game();
        void play_game();
    private:
        int lives_remaining;
        string file;
        string word;
        ifstream in;
        vector<string> wordlist;
        vector<char> letters_solved;
        vector<char> letters_remaining;
        bool is_solved = false;
        
        void atttempt_open_file();
        void create_word_list();
        string select_random_word();
        void initialize_letters_vector();
        void display_board_header();

        void display_solved_and_lives();
        void display_letters_remaining();
        void play_round();
        char prompt_user_letter();
        bool check_if_match(char letter);
        bool check_is_solved();
};

Hangman::Hangman()
// Default constructor uses the words.txt wordlist and sets the user's lives to 5
{
    file = "words.txt";
    lives_remaining = 5;
}

Hangman::Hangman(string filename, int lives)
// Allows user to instantiate Hangman class with their own file and lives
{
    file = filename;
    lives_remaining = lives;
}

void Hangman::initialize_game()
// Pick random word, display game header 
{
    word = select_random_word();
    initialize_letters_vector();
    display_board_header();
}

void Hangman::atttempt_open_file()
// Try to open wordlist file, exit on failure
{
    in.open(file);
    if (in.fail())
    {
        cout << "Could not open file '" << file << "', exiting.";
        exit(1);
    }
}

void Hangman::create_word_list()
// Read in wordlist file to vector until EOF 
{
    string tempstring;
    while(true)
    {
        if (!in.eof())
        {
            in >> tempstring;
            wordlist.push_back(tempstring);
        }
        else
            break;
    }
}

string Hangman::select_random_word()
// Randomly select a word out of wordlist vector
{
    atttempt_open_file();
    create_word_list();

    srand (time(NULL));
    int random_in_range = (rand() % wordlist.size() - 1) + 1;
    return wordlist[random_in_range];
}

void Hangman::initialize_letters_vector()
/* 
Create letters_remaining vector. 
letters_remaining contains the letters the user can select from each round
*/
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i=0; i < alphabet.length(); i++)
        letters_remaining.push_back(alphabet.at(i));
}

void Hangman::display_board_header()
{
    cout << endl << endl <<  "Solved Letters" << " " << setw(20) << "Lives Remaining" << setw(30) << "Letters Remaining" << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;
}

void Hangman::display_solved_and_lives()
// During each round, display the letters solved in the word and the user's remaining lives
{
    string word_placeholder = "";
    for (int i = 0; i < word.length(); i++)
    {
        if (!letters_solved.empty()) // if the user has solved at least 1 letter
        {
            if (count(letters_solved.begin(), letters_solved.end(), word.at(i))) // if current letter of the word is equal to the current letter_solved
            {
                word_placeholder +=  word.at(i); 
                word_placeholder += " ";
            }
            else
            {
                word_placeholder += "_ ";
            } 
        }
        else
            word_placeholder += "_ ";
    }
    cout << word_placeholder << " " << setw(10);
    for (int i = 0; i < lives_remaining; i++)
        cout << "X";
}

void Hangman::display_letters_remaining()
// For each letter in letters_remaining, display on board
{
    cout << " " << setw(15);
    for (int i=0; i < letters_remaining.size(); i++)
    {
        cout << letters_remaining[i];
        cout << " ";
    }
}

char Hangman::prompt_user_letter()
/*
Ask user for char until they supply one they haven't used already.
Then, remove that char from the letters_remaining vector
*/
{
    while (true)
    {
        char letter;
        cout << endl << "Enter a letter: ";
        cin >> letter;
        letter = tolower(letter);

        if (count(letters_remaining.begin(), letters_remaining.end(), letter))
        {
            letters_remaining.erase(remove(letters_remaining.begin(), letters_remaining.end(), letter), letters_remaining.end()); 
            return letter;
        }
        else
            cout << "You've already guessed that letter, try again.";
    }
}

bool Hangman::check_if_match(char letter)
{
    if (word.find(letter) != string::npos) // word.find(letter) equates to string::npos if letter not in word
        return true;
    return false;
}

bool Hangman::check_is_solved()
{
/*
For letter in word, check if that letter is in letters_solved.
Once all letters in word in letters_solved, return true
*/
    for (int i = 0; i < word.length(); i++)
    {
        if (!(count(letters_solved.begin(), letters_solved.end(), word.at(i))))
            return false;
    }
    return true;
}
void Hangman::play_round()
/* 
One round of hangman. Show letters solved of the word along with lives, ask for a letter
and check if it is in the word.
*/
{
    display_solved_and_lives();
    display_letters_remaining();
    char letter_for_round = prompt_user_letter();
    if (check_if_match(letter_for_round)) 
    {
        letters_solved.push_back(letter_for_round); // if letter in word, add letter to letters_solved vector
        if (check_is_solved()) // check if all letters solved
            is_solved = true;
    }
    else
        lives_remaining--; // if letter not in word, deduct a life
}

void Hangman::play_game()
// Play the game until the user wins or runs out of lives
{
    while (!is_solved && lives_remaining > 0)
    {
        play_round();
    }
    if (is_solved)
        cout << endl << "You won!" << endl;
    else
        cout << endl << "You've run out of lives." << endl;
    cout << "The word was '" << word << "'";
}

int main()
{
    Hangman hangman;
    hangman.initialize_game();
    hangman.play_game();
}