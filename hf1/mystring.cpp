#define _CRT_SECURE_NO_WARNINGS
#include "mystring.h"

#include <cstring>

std::map<const char*, MyString::StringValue*> MyString::string_storage;

MyString::MyString(const char* rhs) : strval{ new StringValue{ rhs } } { 
	string_storage[rhs] = strval;
}

MyString::MyString(const MyString& rhs) : strval{ rhs.strval } {
	strval->increment_ref_count();
}

MyString& MyString::operator=(const MyString& rhs) {
	if (this != &rhs) {
		remove_str_val();

		strval = rhs.strval;
		strval->increment_ref_count();
	}

	return *this;
}

MyString::MyString(MyString&& rhs) {
	strval = rhs.strval;
	strval->increment_ref_count();
}

MyString& MyString::operator=(MyString&& rhs) {
	if (this != &rhs) {
		remove_str_val();

		strval = rhs.strval;
		strval->increment_ref_count();
	}
	
	return *this;
}

MyString::~MyString() {
	remove_str_val();
}

MyString MyString::operator+(const MyString& rhs) const {
	char* newdata = new char[length() + rhs.length() + 1];
	strcpy(newdata, strval->getData());
	strcat(newdata, rhs.strval->getData());

	MyString ret{ newdata };

	delete[] newdata;
	return ret;
}

MyString& MyString::operator+=(const MyString& rhs) {
	*this = *this + rhs;
	return *this;
}

MyString MyString::operator+(char rhs) const {
	size_t len = length() + 1;
	char* newdata = new char[len + 1];
	strcpy(newdata, strval->getData());
	newdata[len - 1] = rhs;
	newdata[len] = '\0';

	MyString ret{ newdata };

	delete[] newdata;
	return ret;
}

MyString& MyString::operator+=(char rhs) {
	*this = *this + rhs;
	return *this;
}

size_t MyString::length() const {
	return strlen(strval->getData());
}

MyString::CharProxy MyString::operator[](size_t i) {
	/*if (strval->getRefCount() != 1) {
		StringValue* newval = new StringValue(strval->getData());
		strval->decrementRefCount();
		strval = newval;
	}
	
	return strval->getData()[i];*/
	return CharProxy{ *this, i };
}

const char& MyString::operator[](size_t i) const {
	return strval->getData()[i];
}

const char* MyString::c_str() const {
	return strval->getData();
}

void MyString::remove_str_val() {
	strval->decrement_ref_count();
	if (strval->getRefCount() == 0) {
		delete strval;
	}
}

MyString::StringValue::StringValue(const char* rhs) : data{ new char[strlen(rhs) + 1] } {
	strcpy(data, rhs);
}

MyString::StringValue::~StringValue() {
	delete[] data;
}

char* MyString::StringValue::getData() {
	return data;
}

unsigned int MyString::StringValue::getRefCount() const {
	return cnt;
}

void MyString::StringValue::increment_ref_count() {
	cnt++;
}

void MyString::StringValue::decrement_ref_count() {
	cnt--;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
	os << str.c_str();
	return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
	char data[100]; // ?
	is >> data;
	str = MyString{ data };
	return is;
}

MyString::CharProxy::CharProxy(MyString& str, size_t idx) : str(str), idx(idx) { }

MyString::CharProxy& MyString::CharProxy::operator=(char c) {
	if (str.strval->getRefCount() != 1) {
		StringValue* newval = new StringValue(str.strval->getData());
		str.strval->decrement_ref_count();
		str.strval = newval;
	}

	str.strval->getData()[idx] = c;

	return *this;
}

MyString::CharProxy::operator char() const {
	return str.strval->getData()[idx];
}
