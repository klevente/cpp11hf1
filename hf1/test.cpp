#include <iostream>
#include "mystring.h"

int main() {
	MyString s = "bla";
	MyString s2 = "bla";
	MyString s3 = s + s2;
	MyString s4 = s3 + 'x';

	std::cout << s << " " << s2 << " " << s3 << " " << s4 <<"\n";

	MyString s5 = s4;
	MyString s6 = s5;
	s4 += s;
	std::cout << s4 << "\n";

	char c = s4[1];
	std::cout << c << "\n";

	s4[1] = 'x';
	std::cout << s4 << "\n";

	MyString s7;
	std::cin >> s7;

	std::cout << s7 << "\n";

	MyString s8;
	std::cout << s8 << "\n";

	std::cin.get();

	return 0;
}