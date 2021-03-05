#include <iostream>
#include <string>

int main()
{
	int size = 0;

	std::cout << "Count of words: ";
	std::cin >> size;

	std::string* words = new std::string[size];

	for (int i = 0; i < size; i++)
	{
		std::cout << "Insert " << i + 1 << " word\n> ";
		std::cin >> words[i];
	}

	for (int i = 0; i < size; i++)
	{
		int cutStart = words[i].size() / 2;
		
		if (words[i].size() % 2 == 0)
		{
			words[i].replace(cutStart - 1, 2, "");
		}
		else
		{
			words[i].replace(cutStart, 1, "");
		}
	}

	std::cout << "\n";
	for (int i = 0; i < size; i++)
	{
		std::cout << words[i] << "\n";
	}

	delete[] words;
}
