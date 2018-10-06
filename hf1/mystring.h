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

	MyString operator+(char rhs) const;
	MyString& operator+=(char rhs);

	size_t length() const;

	char& operator[](size_t i);
	const char& operator[](size_t i) const;

	const char* c_str() const;

private:
	class StringValue {
	public:
		StringValue(const char* rhs = "");
		~StringValue();

		char* getData();

		unsigned int getRefCount() const;
		
		void incrementRefCount();
		void decrementRefCount();

	private:
		char* data;
		unsigned int cnt = 1;
	};

	void remove_str_val();

	StringValue* strval;

};

std::ostream& operator<<(std::ostream& os, const MyString& str);

std::istream& operator>>(std::istream& is, MyString& str);