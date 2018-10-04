#pragma once
#include <iostream>

class MyString {
public:

	MyString(const char* rhs = "");
	MyString(const MyString& rhs);
	MyString& operator=(const MyString& rhs);

	MyString(MyString&& rhs);
	MyString& operator=(MyString&& rhs);

	~MyString();

	MyString operator+(const MyString& rhs) const;
	MyString& operator+=(const MyString& rhs);

	size_t length() const;

	char& operator[](size_t i);
	const char& operator[](size_t i) const;

private:
	class StringValue {
	public:
		StringValue(const char* rhs = "");
		
		
	private:
		const char* val;
		unsigned int cnt = 1;

		void incrementRefCount(); //cnt++;

		void decrementRefCount();
			/*cnt--;
			if (cnt == 0) {
				delete[] val;
			}*/
	};

};

std::ostream& operator<<(std::ostream& os, const MyString& str);

std::istream& operator>>(std::istream& is, const MyString& str);