#pragma once
#include <iostream>
#include <map>

class MyString {
private:
	class CharProxy;
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

	MyString::CharProxy operator[](size_t i);
	const char& operator[](size_t i) const;

	const char* c_str() const;

private:
	class StringValue {
	public:
		StringValue(const char* rhs = "");
		~StringValue();

		char* getData();

		unsigned int getRefCount() const;
		
		void increment_ref_count();
		void decrement_ref_count();

	private:
		char* data;
		unsigned int cnt = 1;
	};

	void remove_str_val();

	StringValue* strval;

	class CharProxy {
	public:
		CharProxy(MyString& str, size_t idx);

		CharProxy& operator=(char c);

		operator char() const;

	private:
		MyString& str;
		const size_t idx;
	};
	static std::map<const char*, StringValue*> string_storage;
	//static char X;
};

std::ostream& operator<<(std::ostream& os, const MyString& str);

std::istream& operator>>(std::istream& is, MyString& str);