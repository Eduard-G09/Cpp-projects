#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>

void LogTitle (std::string message, bool printTop = true, bool printBottom = true)
{
	if (printTop)
	{
		std::cout << "+---------------------------------+" << std::endl;
		std::cout << "|";
	}
	else
		std::cout << "|";

	bool beforeMsg = true;
	for (int i = message.length(); i < 33; i++)
	{
		if (beforeMsg)
			message = " " + message;
		else
			message = message + " ";
		beforeMsg = !beforeMsg;
	}
	std::cout << message.c_str();

	if (printBottom)
	{
		std::cout << "|" << std::endl;
		std::cout << "+---------------------------------+" << std::endl;
	}
	else
		std::cout << "|" << std::endl;
}

void Hangman(int level)
{
	if (level >= 1)
		LogTitle("|", false, false);
	else
		LogTitle("", false, false);

	if (level >= 2)
		LogTitle("|", false, false);
	else
		LogTitle("", false, false);

	if (level >= 3)
		LogTitle("O", false, false);
	else
		LogTitle("", false, false);

	if (level == 4)
		LogTitle("|", false, false);

	if (level == 5)
		LogTitle("/| ", false, false);

	if (level >= 6)
		LogTitle("/|\\", false, false);
	else
		LogTitle("", false, false);

	if (level == 7)
		LogTitle("/  ", false, false);

	if (level >= 8)
		LogTitle("/ \\", false, false);
	else
		LogTitle("", false, false);
}
	
void Letters(std::string LetterRow, char from, char to)
{
	std::string string;
	for (char i = from; i <= to; i++)
	{
		if (LetterRow.find(i) == std::string::npos)
		{
			string += i;
			string += " ";
		}
		else
			string += "  ";
	}
	LogTitle(string, false, false);
}

void LeftLetters (std::string left)
{
	LogTitle("Remaining Letters");
	Letters(left, 'A', 'M');
	Letters(left, 'N', 'Z');
}

bool ChecLetters(std::string word, std::string guessed)
{
	std::string s;
	bool letter = true;
	for (int i=0; i < word.length(); i++)
	{
		if (guessed.find(word[i]) == std::string::npos)
		{
			letter = false;
			s += "_ ";
		}
		else
		{
			s += word[i];
			s += " ";
		}
	}
	LogTitle(s, false);
	return letter;
}

std::string readWords(std::string filename)
{
	std::string word;
	std::vector<std::string> a;
	std::ifstream file(filename);
	if (file.is_open()) 
	{
		while (file >> word) 
		{
			a.push_back(word);
		}
		int randomLine = rand() % a.size();
		word = a.at(randomLine);

		file.close();
	}
	else 
	{
		std::cerr << "Unable to open file " << filename << std::endl;
	}
	return word;
}

int Tries(std::string word, std::string guessed)
{
	int error = 0;
	for (int i = 0; i < guessed.length(); i++)
	{
		if (word.find(guessed[i]) == std::string::npos)
		{
			error++;
		}
	}
	return error;
}

int main()
{
	srand(time(0));
	std::string wordGuess;
	std::string wordToGuess = readWords("words.txt");

	bool win = false;
	int tries = 0;
	do
	{
		system("cls");
		LogTitle("HANGMAN GAME");
		Hangman(tries);
		LeftLetters(wordGuess);
		LogTitle("Guess the word");
		win = ChecLetters(wordToGuess, wordGuess);

		if (win)
			break;
			
		char b;
		std::cout << "Guess a letter > "; std::cin >> b;
		if (wordGuess.find(b) == std::string::npos)
		{
			wordGuess += b;
		}
		tries = Tries(wordToGuess, wordGuess);

	} while (tries <= 8);

	if (win)
		LogTitle("YOU WON");
	else
	{
		LogTitle("GAME OVER");
		std::cout << "The word was : " << wordToGuess << std::endl;
	}


	system("pause");
	return 0;
}

/*
+---------------------------------+
|             HANG MAN            |
+---------------------------------+
|               |                 |
|               |                 |
|               O                 |
|              /|\                |
|               |                 |
|              / \                |
|         +----------+            |
|         |          |            |
+---------------------------------+
|        Available letters        |
+---------------------------------+
|     A B C D E F G H I J K L M   |
|     N O P Q R S T U V W X Y Z   |
+---------------------------------+
|         Guess the word          |
+---------------------------------+
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |
+---------------------------------+
>
*/
