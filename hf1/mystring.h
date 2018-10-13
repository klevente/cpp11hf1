#pragma once
#include <iostream>
#include <set>

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

		char* get_data();

		unsigned int get_ref_count() const;
		
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
		CharProxy& operator=(const CharProxy& cp);

		operator char() const;

	private:
		MyString& str;
		const size_t idx;

		void create_new_val();
	};
	static std::set<StringValue*> string_storage;
};

std::ostream& operator<<(std::ostream& os, const MyString& str);

std::istream& operator>>(std::istream& is, MyString& str);