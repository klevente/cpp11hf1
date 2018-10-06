#include <iostream>
#include "mystring.h";

int main() {
	MyString s = "bla";
	MyString s2 = "ble";
	s2 = s;

	std::cout << s << " " << s2;

	std::cin.get();
	return 0;
}