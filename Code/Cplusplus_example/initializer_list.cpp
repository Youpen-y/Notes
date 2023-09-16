#include <iostream>

void print(std::initializer_list<int> vals);

int main()
{
    print({1,2,3,6,5});
    return 0;
}

void print(std::initializer_list<int> vals)
{
    for(auto p = vals.begin(); p != vals.end(); ++p)
    {
	std::cout << *p << "\n";
    }
}

