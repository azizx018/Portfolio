#include <iostream>
#include <fstream>
#include <string>
#include<map>
using namespace std;



//function to count the number of times the user entered word appears in the file
void userEnteredWordCount(istream& in, string word, string enteredWord, int& count) {

	while (!in.eof()) {
		in >> word;
		if (!in.fail()) {
			if (word == enteredWord) {
				++count;
			}
		}
	}
	cout << enteredWord << " appears in the file " << count << " times" << endl;
}


//sets up a map to count each word in the file and increment the count
//of each wordd
void countWords(istream& in, map<string, int>& words) {
	string text;
	while (in >> text) {
		++words[text];
	}
}
//writes to data file for backup
void writeToFile(istream& in, ofstream& out, map<string, int>& words) {
	while (!in.eof()) {
		string text;
		in >> text;
		if (!in.fail()) {
			++words[text];
		}

	}
	for (auto inventory : words) {
		out << inventory.first << " " << inventory.second << endl;
	}

}
//makes histogram of the frequency of each word
void histoCount(istream& in, map<string, string>& items) {
	string text;
	string star = "*";
	while (in >> text) {
		//if the word is not in the map, add it to the map and add a star
		if (items.count(text) == 0) {
			items[text] = star;
		}
		else {
			//if in the map increment the star
			items[text] += star;
		}

	}
}

//displays the main menu to the user
int displayMainMenu() {
	int choice;
	cout << "Please chose an option below:" << endl;
	cout << "1.Look up items by word." << endl;
	cout << "2.Print a list of items and their frequency." << endl;
	cout << "3. Print frequency information in a histogram" << endl;
	cout << "4. Exit" << endl;
	cin >> choice;
	return choice;
}


int main() {
	ifstream in; // input file stream
	ofstream out; // output file stream
	string backupFile = "frequency.dat.txt";
	string userWord;
	int wordFrequency = 0;
	string currentWord;
	int choice = displayMainMenu();
	bool choiceIsValid = false;
	map<string, int> wordMap; //sets up a map to store the words and their frequency
	map<string, string> wordHisto; //sets up a map to store the words and their frequency in a histogram

	//open the file to write
	out.open(backupFile);

	//error message if write file can't be opened
	if (!out.is_open()) {
		cout << "Having trouble opening your file." << endl;
		return 1;
	}
	//writes to the backup file
	writeToFile(in, out, wordMap);
	out.close();

	while (!choiceIsValid)
	{
		if (choice >= 1 && choice <= 4) {
			choiceIsValid = true;
		}
		else {
			cout << "Please enter a valid choice 1-4" << endl;
			cin >> choice;

		}

	}

	// open the file to read
	in.open("items.txt");

	//error message if read file can't be opened
	if (!in.is_open()) {
		cout << "Having trouble opening your file." << endl;
		return 1;
	}

	//takes user input and does the appropriate action
	void handleMenuChoice(); {
		switch (choice) {
		case 1:
			cout << "Please enter an item: " << endl;
			cin >> userWord;
			//captializes the first letter of the user entered word
			userWord[0] = toupper(userWord[0]);
			//removes spaces from the user entered word
			userWord = userWord.substr(0, userWord.length());
			userEnteredWordCount(in, currentWord, userWord, wordFrequency);
			break;
		case 2:
			countWords(in, wordMap);
			//prints the word and its frequency
			for (auto inventory : wordMap) {
				cout << inventory.first << " " << inventory.second << endl;

			}
			break;
		case 3:
			histoCount(in, wordHisto);
			for (auto inventory : wordHisto) {
				cout << inventory.first << " " << inventory.second << endl;
			}
			break;
		case 4:
			cout << "Goodbye" << endl;
			break;
		default:
			cout << "choice not valid" << endl;
			break;
		}
	}

	// close the file
	in.close();


	return 0;
}