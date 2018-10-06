#include <iostream>
#include "mystring.h";

int main() {
	MyString s = "bla";
	MyString s2 = "ble";
	MyString s3 = s + s2;
	MyString s4 = s3 + 'x';

	std::cout << s << " " << s2 << " " << s3 << " " << s4 <<"\n";

	MyString s5 = s4;
	MyString s6 = s5;
	s4 += s;
	std::cout << s4 << "\n";

	auto c = s4[1];

	

	MyString s7;
	std::cin >> s7;

	std::cout << s7;

	std::cin.get();

	return 0;
}