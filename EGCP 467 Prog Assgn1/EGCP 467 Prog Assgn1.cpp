// EGCP 467 Prog Assgn1.cpp 
// Winston Do

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cstdlib> //used for the random number generator for testing keys


std::string EncryptCaesar(std::string, int);
std::string DecryptCaesar(std::string, int);
void StatAttack(std::string, float);

//helper functions
int clamp(int, int);
char int2char(int);
int char2int(char);
int countTotalChar(std::string);
std::map<char, float> createFrequencyMap(std::string);
float calcPhi(std::string, int);


//unigrams implemented in a map
const std::map<char, float> unigram = { 
	{'A',0.080}, {'B',0.015}, {'C',0.030}, {'D',0.040}, {'E',0.130},
	{'F',0.020}, {'G',0.015}, {'H',0.060}, {'I',0.065}, {'J',0.005},
	{'K',0.005}, {'L',0.035}, {'M',0.030}, {'N',0.070}, {'O',0.080},
	{'P',0.020}, {'Q',0.002}, {'R',0.065}, {'S',0.060}, {'T',0.090},
	{'U',0.030}, {'V',0.010}, {'W',0.015}, {'X',0.005}, {'Y',0.020},
	{'Z',0.002} };


int main()
{
	int a = 0;
	while (a >= 0)
	{	
		std::string msg = "INVADING GAUL SOON";
		int key = rand() % 26+1;
		std::string cipher = EncryptCaesar(msg,key);
		std::cout << "msg is: (" << msg << ")\n";
		std::cout << "cipher is: [" << cipher <<"] with key: " << key <<"\n";
		//std::cout << "Enter correlation threshold :";
		float thres = 0.05;
		//std::cin >> thres;
		StatAttack(cipher, thres);
		std::cout << "\nTo continue testing new keys enter a positive number:";
		std::cin >> a;
		std::cout << "\n\n";
		
	}
}

void StatAttack(std::string cipher, float threshold)
{
	std::map<char, float> freqmap = createFrequencyMap(cipher);
	//freqmap = createFrequencyMap(msg);
	for (auto i = 0; i < 26; i++)
	{
		if (calcPhi(cipher, i) > threshold)
		{
			std::cout << i << ", " << calcPhi(cipher, i) << ", " << DecryptCaesar(cipher,i) <<  "\n";
		}
	}
}

std::string DecryptCaesar(std::string c, int key)
{
	std::string msg;
	for (unsigned i = 0; i < c.size(); i++)
	{
		if (c[i] != ' ') {
			msg.push_back(int2char(char2int(c[i]) - key));
		}
		else {
			msg.push_back(' ');
		}

	}
	return msg;
}

std::string EncryptCaesar(std::string msg, int key)//only takes in capital letters, no error checking
{
	std::string cipher;
	for (unsigned i = 0; i < msg.size(); i++)
	{
		if (msg[i] != ' ') {
			cipher.push_back(int2char(char2int(msg[i]) + key));
		}
		else {
			cipher.push_back(' ');
		}
	}
	return cipher;
}

float calcPhi(std::string c, int key)
{
	float phi = 0.0;
	std::map<char, float> freqmap = createFrequencyMap(c);
	for (auto const& it : freqmap)
	{
		//std::cout << it.second << " x " << "p(" << char2int(it.first) - key <<")" << " -> " << unigram.at(int2char(char2int(it.first) - key)) << "\n";
		phi += it.second * unigram.at(int2char(char2int(it.first) - key));
	}
	return phi;

}

//gives the frequency of the characters in the cipher string. super slow O(n^2)
std::map<char, float> createFrequencyMap(std::string s)
{
	float total = static_cast<float>(countTotalChar(s));
	std::map<char, float> freqmap;
	for (auto i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ') {
			float count = std::count(s.begin(), s.end(), s[i]);
			freqmap.try_emplace(s[i], count / total);
		}
	}
	return freqmap;
}




int countTotalChar(std::string m)
{
	int count = 0.0;
	for (unsigned i = 0; i < m.size(); i++)
	{
		if (m[i] != ' ') {
			count++;
		}
	}
	return count;
}



int char2int(char c)
{
	return clamp(static_cast<int>(c)-65,25);
}

char int2char(int n)
{
	return static_cast<char>(clamp(n,25)+65);
}

int clamp(int a, int max) //keeps values between 0 and max, handling overflow
{
	if (a > 0)
	{
		while (a > max)
		{
			a -= (max + 1);
		}
		return a;
	}
	if (a <= 0)
	{
		while (a < 0)
		{
			a += (max + 1);
		}
		return a;
	}
}
