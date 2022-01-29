#include "monkeys.h"
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

// CharDistribution functions

CharDistribution::CharDistribution()
{
	this->prefix = "";
	this->distSize = 0;
}

CharDistribution::CharDistribution(string prefix) // overloaded constructor
{
	//initialize distribution
	this->prefix = prefix;
	this->distSize = 0;
}

CharDistribution::CharDistribution(string prefix, char c) // overloarded constructor
{
	//initialize distribution
	this->prefix = prefix;
	this->distSize = 0;
	occurs(c);
}

void CharDistribution::occurs(char x)
{
	//update distribution
	int asciiVal = int(x); //convert to ascii value

	if (asciiVal >= 97 && asciiVal <= 122) // if lowercase letter
	{
		charDist.at(asciiVal - 97) = charDist.at(asciiVal - 97) + 1; //hash to proper index
		distSize++;
	}
	else if (asciiVal == 32) // if whitespace
	{
		charDist.at(26)++; //hash to end of distribution
		distSize++;
	}
}

char CharDistribution::getRandomChar() //outputs a random character based on frequency
{
	int random = rand() % distSize + 1; // uses hash function
	int sum = 0;

	for (int c = 0; c < 27; c++)
	{
		sum += charDist.at(c);
		if (sum >= random)
		{
			if (c == 26)
				return char(32); // whitespace
			else
				return char(c + 97);
		}
	}

}

int CharDistribution::getSize()
{
	return distSize;
}

vector<int> CharDistribution::getDistribution()
{
	return charDist;
}

void CharDistribution::displayDistribution()
{
	for (int i = 0; i < charDist.size(); i++)
	{
		cout << charDist.at(i) << ", ";
	}
}

string CharDistribution::getPrefix()
{
	return prefix;
}

// more functions!

string openFile(string filePath)
{
	ifstream text(filePath);
	string contents = "";
	text >> std::noskipws;
	for (char c; text >> c; )
	{
		// handles new lines and whitespaces
		if (c == '\r')
			c = char(32);
		else if (c == '\n')
			continue;

		contents += c;
	}
	return contents;
}

int getFileLength(string filePath)
{
	ifstream text(filePath);
	int fileSize = 0;

	if (text.is_open())
	{
		text.seekg(0, text.end);
		fileSize = text.tellg(); //get input size of file
		text.seekg(0, text.beg);
	}
	else
	{
		cout << "File couldn't be opened" << endl;
	}
	return fileSize;
}

void fillTable(HashTable& hashT, string text, int window=1)
{

	for (int pos = 0; pos < text.size() - window; pos++)
	{
		string prefix = text.substr(pos, window);
		char c = text[pos + window];

		if (hashT.search(prefix) != nullptr)
		{
			(*hashT.search(prefix))->occurs(c);
		}
		else
		{
			CharDistribution* characterDist = new CharDistribution(prefix, c);
			hashT.insert(prefix, characterDist);
		}
	}
}


string outputText(HashTable& hashT, string text, int window=1, int outputSize=10000)
{
	string initWChars = text.substr(0, window);
	string result = initWChars;

	string initPrefix = initWChars;
	for (int index = 1; index < outputSize - window; index++)
	{

		if (hashT.search(initPrefix) == nullptr)
			return result;
		result += (*hashT.search(initPrefix))->getRandomChar();
		initPrefix = result.substr(index, window);
	}
	return result;
}

#include <chrono>

int main()
{
	int windowSize = 3;
	int outputSize = 20000;
	string textData = openFile("merchant.txt");

	ofstream outputFile;
	outputFile.open("monkeyTyping.txt");

	string response;
	cout << "Select Hash Table Implementation - Type \"1\" for Separate Chaining, \"2\" for Linear Probing, or \"3\" for Double Hashing: ";
	cin >> response;

	if (response == "1")
	{
		cout << "Separate Chaining Hash Table: " << endl << endl;
		ChainHT chainHashT(textData.size());
		chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
		fillTable(chainHashT, textData, windowSize);
		chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
		cout << outputText(chainHashT, textData, windowSize, outputSize) << endl << endl << endl;
		cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl << endl << endl; //take delta time in microseconds
		outputFile << outputText(chainHashT, textData, windowSize, outputSize);
	}

	if (response == "2")
	{
		cout << "Linear Hash Table: " << endl << endl;
		LinearHT linearHashT(textData.size());
		chrono::high_resolution_clock::time_point start2 = chrono::high_resolution_clock::now();
		fillTable(linearHashT, textData, windowSize);
		chrono::high_resolution_clock::time_point end2 = chrono::high_resolution_clock::now(); //end clock
		cout << outputText(linearHashT, textData, windowSize, outputSize) << endl << endl << endl;
		cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end2-start2).count() << " µs" <<  endl << endl << endl; //take delta time in microseconds
		outputFile << outputText(linearHashT, textData, windowSize, outputSize);
	}

	if (response == "3")
	{
		cout << "Double Hashing Hash Table: " << endl << endl;
		DoubleHT doubleHashT(textData.size());
		chrono::high_resolution_clock::time_point start3 = chrono::high_resolution_clock::now();
		fillTable(doubleHashT, textData, windowSize);
		chrono::high_resolution_clock::time_point end3 = chrono::high_resolution_clock::now(); //end clock
		cout << outputText(doubleHashT, textData, windowSize, outputSize) << endl << endl << endl;
		cout << "Elapsed: " << chrono::duration_cast<chrono::microseconds>(end3-start3).count() << " µs" <<  endl << endl << endl; //take delta time in microseconds
		outputFile << outputText(doubleHashT, textData, windowSize, outputSize);
	}


	return 0;

}
