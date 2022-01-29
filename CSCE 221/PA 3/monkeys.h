#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

class CharDistribution // covers character distribution implementation
{
    private:
      int distSize;
    	string prefix;
    	vector<int> charDist {vector <int> (27,0)}; //initialize vector to store char frequency

    public:
        // constructors
        CharDistribution(); // default
        CharDistribution(string prefix); // overloaded
        CharDistribution(string prefix, char c); // overloaded

        // getters
        int getSize();
        vector<int> getDistribution();
        string getPrefix();

        // update hash table
        void occurs(char x);

        // used to generate output text
        char getRandomChar();

        // used in testing to display distribution
        void displayDistribution();
};

class HashTable // abstraction of hash table used to define separate types of tables
{

protected:
	int tableSize;

public:

	int getTableSize()
	{
		return tableSize;
	}

	int hash(string key)
	{
		int hashVal = 0;
		for (char c : key)
    {
      hashVal %= tableSize;
      hashVal = 37 * hashVal + int(c); // follows given hash function
    }

		return hashVal % tableSize;
	}

  virtual CharDistribution** search(string key) = 0;

	virtual void insert(string key, CharDistribution*& characterDist) = 0;

};

class ChainHT : public HashTable // hash table using separate chaining method
{
private:

	struct TableNode
  {

		CharDistribution* characterDist;
    TableNode* next;

		TableNode(CharDistribution* characterDist)
		{
			this->characterDist = characterDist;
			next = nullptr;
		}

		CharDistribution** getDistribution()
		{
			return &characterDist;
		}
	};

	vector<TableNode*> hashtable;

public:

  // constructors
	ChainHT() // default
	{
		this->tableSize = 0;
		this->hashtable = vector<TableNode*>(tableSize, nullptr);
	}

	ChainHT(int tableSize) // overloaded
	{
		this->tableSize = tableSize;
		this->hashtable = vector<TableNode*>(tableSize, nullptr);
	}

  // searchand insert functions

	void insert(string key, CharDistribution*& characterDist)
	{
		int index = hash(key);
		TableNode* node = hashtable.at(index);
		hashtable.at(index) = new TableNode(characterDist);
		hashtable.at(index)->next = node;
	}

	CharDistribution** search(string key)
	{
		int index = hash(key);
		TableNode* node = hashtable.at(index);

		if (node == nullptr)
		{
			return nullptr;
		}
		else
		{
			while (node != nullptr)
			{
				CharDistribution* characterDist = *node->getDistribution();
				if (characterDist->getPrefix() == key)
				{
					return node->getDistribution();
				}
				else
				{
					node = node->next;
				}
			}
			return nullptr;
		}
	}

};

class LinearHT : public HashTable // hash table using linear probing method
{
private:

	vector<CharDistribution*> hashtable;

public:

  // constructors
	LinearHT() // default
	{
		this->tableSize = 0;
		this->hashtable = vector<CharDistribution*>(tableSize, nullptr);
	}

	LinearHT(int tableSize) // overloaded
	{
		this->tableSize = tableSize;
		this->hashtable = vector<CharDistribution*>(tableSize, nullptr);
	}

  // search and insert functions

	void insert(string key, CharDistribution*& characterDist)
	{
		int index = hash(key);
		bool inserting = true;
		while (inserting) {
			if (hashtable.at(index) == nullptr)
			{
				hashtable.at(index) = characterDist;
				return;
			}
			++index %= tableSize; //increment index and reset to zero if reached table size
		}
	}

	CharDistribution** search(string key)
	{
		int index = hash(key);
		bool inserting = true;
		while (inserting) //search until nullptr or key is found
		{
			CharDistribution* characterDist = hashtable.at(index);
			if (characterDist == nullptr)
			{
				return nullptr; //not in the table
			}
			else if (characterDist->getPrefix() == key)
			{
				return &hashtable.at(index);
			}
			++index %= tableSize;
		}
	}

	vector<CharDistribution*> getTable()
	{
		return hashtable;
	}

};

class DoubleHT : public HashTable // hash table using double hashing method
{

private:

	vector<CharDistribution*> hashtable;

public:

  // constructors
	DoubleHT() // default
	{
		this->tableSize = 0;
		this->hashtable = vector<CharDistribution*>(tableSize, nullptr);
	}

	DoubleHT(int tableSize) // overloaded
	{
		this->tableSize = tableSize;
		this->hashtable = vector<CharDistribution*>(tableSize, nullptr);
	}

	int hashPrime(string key) // enables only hashing to prime values
	{
		const int R = 7;
		int hashVal = 0;
		for (char c : key)
			hashVal += R - (c % R);

		return hashVal % tableSize;
	}

  // search and insert functions

	void insert(string key, CharDistribution*& characterDist)
	{
		int hashed = hash(key);
		int hashedPrime = hashPrime(key);
		int offset = 0;
		int index = hashed;
		bool inserting = true;
		while (inserting)
    {
			if (hashtable.at(index) == nullptr)
			{
				hashtable.at(index) = characterDist;
				return;
			}
			index = hashed + (++offset * hashedPrime);
			index %= tableSize;
		}
	}

	CharDistribution** search(string key)
	{
		int hashed = hash(key);
		int hashedPrime = hashPrime(key);
		int offset = 0;
		int index = hashed;
		bool inserting = true;
		while (inserting)
		{
			CharDistribution* characterDist = hashtable.at(index);
			if (characterDist == nullptr)
			{
				return nullptr;
			}
			else if (characterDist->getPrefix() == key)
			{
				return &hashtable.at(index);
			}
			index = hashed + (++offset * hashedPrime);
			index %= tableSize;
		}
	}
};
