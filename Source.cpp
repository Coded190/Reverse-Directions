//Reverse Directions

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_KEYWORD = 8;

string dataBase_Compass(string); //Checks for one of the 8 Keywords in the line of data
string formatLine(string, int);

//first instruction is doubled at the end, last two instructions are placed in the beginning

struct wordList
{
	string word;
	wordList* next;
};
typedef wordList* wordPtr;
wordPtr head = nullptr;

struct Node
{
	string line;
	Node* next;
	Node* prev;
};

typedef Node* linePtr;
linePtr front = nullptr;
linePtr rear = nullptr;
int q_Size = 0;

int main()
{
	ifstream inputFile;
	inputFile.open("test_File");
	string input;

	if (inputFile)
	{
		front = new Node;
		front->prev = front->next = nullptr;
		linePtr tPtr = nullptr;
		int index = 0;
		int j = 1;

		while (getline(inputFile, input))	//reads in a line and returns boolean
		{

			if (isdigit(input[0]))
			{
				front->line = "Directions " + j;
				front->line = front->line + ":";
				rear->next = new Node;
				rear = rear->next;
			}
			else
			{
				//places line into a queue
				if (index == 0)
				{
					index++;

					rear->line = input;
				}
				else
				{
					index++;

					tPtr = new Node;
					tPtr->prev = tPtr->next = nullptr;
					tPtr->line = input;

					if (rear == nullptr)
					{
						rear = front = tPtr;
					}
					else
					{
						rear->next = tPtr;
						tPtr->prev = rear;
						rear = tPtr;
					}
				}
			}
		}

		//step through the queue's contents forwards and change each key word
		linePtr keyPtr = front;

		while (keyPtr)
		{
			keyPtr->line = formatLine(keyPtr->line, index);
			keyPtr = keyPtr->next;
		}

		linePtr q_ptr = rear;

		//display the directions in reverse order of read in strings
		while (q_ptr)
		{
			cout << q_ptr->line << endl;
			q_ptr = q_ptr->prev;
		}


		//DONE :)


		inputFile.close();

	}
	else
	{
		cout << "Error: File not found.\n";
	}

	return 0;
}


//-------------------------------------------------------------
// Formats the inputted line from the user and changes the 
// order of directions.
// 
// @param - string, index
// @return - string
//-------------------------------------------------------------

string formatLine(string line, int index)
{
	//formats the line into the correct output
	//use dataBase_Compass function to change the keyword

	wordPtr ptr = head;

	bool newNode = false;
	string str;
	int prevSpace = 0;

	//search through the string to find each word
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == ' ') //send str to the node's word
		{
			ptr->word = str;
			newNode = true;
		}

		str += line[i];

		if (i == line.length() - 1) //send string to the node's word
		{
			ptr->word = str;
			newNode = true;
		}

		if (newNode && i != line.length() - 1)
		{
			ptr->next = new wordList;
			ptr = ptr->next;
			newNode = false;
		}
	}

	//check each word in the LL for a matching keyword
	ptr = head;
	while (ptr)
	{
		ptr->word = dataBase_Compass(ptr->word);	//changes if a keyword matches

		ptr = ptr->next;
	}

	//place the new line back into a string

	ptr = head;
	str = "";

	while (ptr)
	{
		str += ptr->word;

		if (!ptr->next)
		{
			break;
		}
		else
		{
			str += " ";
		}
	}

	return str;
}


//-------------------------------------------------------------
// This function checks for the keywords and swaps the 
// directions.
// 
// @param - string
// @return - string
//-------------------------------------------------------------

string dataBase_Compass(string str)
{
	string arr[8] = { "north", "south", "east", "west", "left", "right", "Continue", "Arrive"};
	int index = 0;
	bool flag = false;

	while (index < MAX_KEYWORD)
	{
		if (str == arr[index])
		{
			flag = true;
			break;
		}
		index++;
	}

	if (flag)
	{
		if (index % 2 == 0)
		{
			str = arr[index + 1];
		}
		else
		{
			str = arr[index - 1];
		}
	}
	
	return str;
}