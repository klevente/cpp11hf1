#define _CRT_SECURE_NO_WARNINGS
#include "mystring.h"

#include <cstring>
#include <algorithm>

std::set<MyString::StringValue*> MyString::string_storage;

MyString::MyString(const char* rhs) {
	const auto& it = std::find_if(string_storage.begin(), string_storage.end(), [&rhs](StringValue* s) {
		return strcmp(rhs, s->get_data()) == 0;
	});
	
	if (it != string_storage.end()) {
		strval = *it;
		strval->increment_ref_count();
	} else {
		strval = new StringValue{ rhs };
		string_storage.insert(strval);
	}
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
	rhs.strval = nullptr;
}

MyString& MyString::operator=(MyString&& rhs) {
	if (this != &rhs) {
		remove_str_val();

		strval = rhs.strval;
		rhs.strval = nullptr;
	}
	
	return *this;
}

MyString::~MyString() {
	remove_str_val();
}

MyString MyString::operator+(const MyString& rhs) const {
	char* newdata = new char[length() + rhs.length() + 1];
	strcpy(newdata, strval->get_data());
	strcat(newdata, rhs.strval->get_data());

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
	strcpy(newdata, strval->get_data());
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
	return strlen(strval->get_data());
}

MyString::CharProxy MyString::operator[](size_t i) {
	return CharProxy{ *this, i };
}

const char& MyString::operator[](size_t i) const {
	return strval->get_data()[i];
}

const char* MyString::c_str() const {
	return strval->get_data();
}

void MyString::remove_str_val() {
	if (strval) {
		strval->decrement_ref_count();
		if (strval->get_ref_count() == 0) {
			string_storage.erase(strval);
			delete strval;
		}
	}
}

MyString::StringValue::StringValue(const char* rhs) : data{ new char[strlen(rhs) + 1] } {
	strcpy(data, rhs);
}

MyString::StringValue::~StringValue() {
	delete[] data;
}

char* MyString::StringValue::get_data() {
	return data;
}

unsigned int MyString::StringValue::get_ref_count() const {
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
	MyString temp;
	char c;

	while (is.get(c)) {
		if (c == ' ') {
			break;
		}
		temp += c;
	}
	str = temp;
	return is;
}

MyString::CharProxy::CharProxy(MyString& str, size_t idx) : str{ str }, idx{ idx } { }

MyString::CharProxy& MyString::CharProxy::operator=(char c) {
	create_new_val();

	str.strval->get_data()[idx] = c;

	return *this;
}

MyString::CharProxy& MyString::CharProxy::operator=(const CharProxy& cp) {
	create_new_val();

	str.strval->get_data()[idx] = cp.str.c_str()[idx];

	return *this;
}

MyString::CharProxy::operator char() const {
	return str.strval->get_data()[idx];
}

void MyString::CharProxy::create_new_val() {
	if (str.strval->get_ref_count() != 1) {

		StringValue* newval = new StringValue(str.strval->get_data());
		str.strval->decrement_ref_count();
		str.strval = newval;
	}
}
