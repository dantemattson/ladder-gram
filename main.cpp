#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <set>
#include <unordered_map>
#include <stack>
#include <chrono>

using namespace std;

// optimised averages
char averages[] = { 'e', 's', 'i', 'a', 'r', 'n', 't', 'o', 'l', 'c', 'd', 'u', 'g', 'p', 'm', 'h', 'b', 'y', 'f', 'v', 'k', 'w', 'z', 'x', 'j', 'q' };

// Function to get all the shortest possible
// sequences starting from 'start' to 'target'
void findLadders(unordered_map<string, int> dictionarymap, string beginWord, string endWord)
{
	// queue of search states
	queue<stack<string> > ladderqueue;
	// current search
	stack<string> wordladder;
	//set<string> testword;

	// initial conditions
	stack<string> ladderstack({ beginWord });
	ladderqueue.push(ladderstack);

	while (!(ladderqueue.empty())) {

		stack<string> ladder = ladderqueue.front();
		ladderqueue.pop();
		string word = ladder.top();

		if (word == endWord) {

			while (!ladder.empty()) {
				cout << ladder.top() << " ";
				ladder.pop();
			}
			cout << "\n";
			return;

		}
		else {
			// valid english neighbor word on top of the stack:
			for (int i = 0; i < word.size(); i++) {
				// Consider setting so it only uses top 25 most common letters?
				for (int j = 0; j < 26; j++) {
					string test = word.substr(0, i) + averages[j] + word.substr(i + 1);

					// if that word is an english word
					if (dictionarymap.find(test) != dictionarymap.end()) {
						// create a copy of the current ladder stack with the new word on top
						stack<string> copy(ladder);

						ladder.push(test);

						// add the copy stack to the end of the queue so it is searched later
						ladderqueue.push(ladder);
						ladder = copy;
						// don't traverse this word again
						dictionarymap.erase(test);
					}
				}
			}
		}

	}

	cout << "Couldn't find a path...\n";
	return;
}

int main()
{
	string firstWord, secondWord;

	cout << "Enter first word\n";

	cin >> firstWord;

	cout << "Enter second word\n";

	cin >> secondWord;

	if (firstWord.size() != secondWord.size()) {
		cout << "Words must be the same length\n";
		return -1;
	}

	int n = firstWord.size();
	// use map
	unordered_map<string, int> wl;

	ifstream ifs("dictionary.txt");

	if (ifs.bad()) {
		cout << "The dictionary couldn't be opened\n";
		return -1;
	}

	string line;

	while (getline(ifs, line)) {
		if (line.size() == n) {
			// cout << line << "\n";
			wl[line] = 0;
		}

	}

	cout << "Loaded " << wl.size() << " words\n";

	if (wl.find(firstWord) == wl.end()) {
		cout << firstWord << " is not in the dictionary\n";
		return -1;
	}
	if (wl.find(secondWord) == wl.end()) {
		cout << firstWord << " is not in the dictionary\n";
		return -1;
	}

	
	cout << "Going from " << firstWord << " to " << secondWord << ":\n";

	// -----------------------------------------------
	auto start = chrono::high_resolution_clock::now();
	// -----------------------------------------------

	findLadders(wl, secondWord, firstWord);

	// -----------------------------------------------
	cout << "\n_____________\n\nfunction took " << (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start)).count() << "ms\n";
	// -----------------------------------------------
}