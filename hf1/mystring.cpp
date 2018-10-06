#define _CRT_SECURE_NO_WARNINGS
#include "mystring.h"

#include <cstring>

MyString::MyString(const char* rhs) {
	strval = new StringValue{ rhs };
}

MyString::MyString(const MyString& rhs) {
	strval = rhs.strval;
	strval->incrementRefCount();
}

MyString& MyString::operator=(const MyString& rhs) {
	if (this != &rhs) {
		remove_str_val();

		strval = rhs.strval;
		strval->incrementRefCount();
	}

	return *this;
}

MyString::MyString(MyString&& rhs) {
	strval = rhs.strval;
	strval->incrementRefCount();
}

MyString& MyString::operator=(MyString&& rhs) {
	if (this != &rhs) {
		remove_str_val();

		strval = rhs.strval;
		strval->incrementRefCount();
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

char& MyString::operator[](size_t i) {
	if (strval->getRefCount() != 1) {
		StringValue* newval = new StringValue(strval->getData());
		strval->decrementRefCount();
		strval = newval;
	}
	
	return strval->getData()[i];
}

const char& MyString::operator[](size_t i) const {
	return strval->getData()[i];
}

const char* MyString::c_str() const {
	return strval->getData();
}

void MyString::remove_str_val() {
	strval->decrementRefCount();
	if (strval->getRefCount() == 0) {
		delete strval;
	}
}

MyString::StringValue::StringValue(const char* rhs) {
	data = new char[strlen(rhs) + 1];
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

void MyString::StringValue::incrementRefCount() {
	cnt++;
}

void MyString::StringValue::decrementRefCount() {
	cnt--;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
	os << str.c_str();
	return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
	char* data = new char[1];
	is >> data;
	str = MyString{ data };
	delete[] data; // !!
	return is;
}
