#include <vector>
#include <string>
#include <iostream>

int main()
{
	std::string word = "Hello";
	std::string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::cout << word << std::endl;
	for(int i=0; i<word.size()-1; i++)
	{
		for (int j=i+1; j<word.size(); j++)
		{
			std::string temp = word;
			std::swap(temp[i],temp[j]);

			std::cout << temp << std::endl;

		}
	}
	return 0;
}