#include "mystring.h"

#include <cstring>

MyString::MyString(const char* rhs) {
	strval = new StringValue(rhs);
}

MyString::MyString(const MyString& rhs) {
	strval = rhs.strval;
	strval->incrementRefCount();
}

MyString& MyString::operator=(const MyString& rhs) {
	// TODO: insert return statement here
}

MyString::MyString(MyString&& rhs) {
}

MyString& MyString::operator=(MyString&& rhs) {
	// TODO: insert return statement here
}

MyString::~MyString() {
	strval->decrementRefCount();
	if (strval->getRefCount == 0) {
		delete strval;
	}
}

MyString MyString::operator+(const MyString& rhs) const {
	return MyString();
}

MyString& MyString::operator+=(const MyString& rhs) {
	// TODO: insert return statement here
}

size_t MyString::length() const {
	return strlen(strval->getData());
}

char& MyString::operator[](size_t i) {
	// TODO: insert return statement here
}

const char& MyString::operator[](size_t i) const {
	return strval->getData[i];
}

MyString::StringValue::StringValue(const char* rhs) {
	data = new char[strlen(rhs)];
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
