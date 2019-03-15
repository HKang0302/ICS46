// String.cpp
//
// ICS 46 Winter 2019
// Project #0: Getting to Know the ICS 46 VM
//
// Implement all of your String member functions in this file.
//
// Note that the entire standard library -- both the C Standard
// Library and the C++ Standard Library -- is off-limits for this
// task, as the goal is to exercise your low-level implementation
// skills (pointers, memory management, and so on).

#include "String.hpp"
#include "OutOfBoundsException.hpp"

namespace
{
	const unsigned int initialCapacity = 100;

	// initialize a new char array
	void emptyInit(char* charArr, int capacity)
	{
		for(int i=0; i<capacity; i++)
		{
			charArr[i] = '\0';
		}
	}

}

String::String()
	: l{0}, c{new char[initialCapacity]}, cap{initialCapacity}
{
	emptyInit(c, cap);
}

String::String(const char* chars)
	:c{new char[initialCapacity]}, cap{initialCapacity}
{
	l = 0;
	emptyInit(c, cap);
	while(chars[l]!='\0')
	{
		this->c[l] = chars[l];
		l++;
	}
}

String::String(const String& s)
	: l{s.l}, c{new char[s.cap]}, cap{s.cap}
{
	emptyInit(c, cap);
	copy(c, s, l);
}

String::~String() noexcept
{
	emptyInit(c, cap);
	delete[] this->c;
}

String& String::operator=(const String& s)
{
	if(this != &s)
	{
		copyArr(s);
	}

	return *this;
}

void String::append(const String& s)
{
	int leng = this->length();
	char* temp = this->c;
	int i=0;

	while(s.c[i]!='\0')
	{
		temp[leng] = s.c[i];
		i++;
		leng++;
	}

	this->l = leng;
	this->c = temp;
}

char String::at(unsigned int index) const
{
	if(index>=l)
	{
		throw OutOfBoundsException();
	}
	else
	{
		return c[index];
	}
}

char& String::at(unsigned int index)
{
	if(index>=this->l)
	{
		throw OutOfBoundsException();
	}
	else
	{
		return c[index];
	}
}

void String::clear()
{
	emptyInit(c, cap);
	l = 0;
}

int String::compareTo(const String& s) const noexcept
{
	return (s.length()-this->length());
}

String String::concatenate(const String& s) const
{
	String result{this->c};
	for(int i=0; i<s.length(); i++)
	{
		result.c[result.length()] = s.c[i];
		result.l = result.length()+1;
	}

	return result;
}

bool String::contains(const String& substring) const noexcept
{
	int thisLeng = this->length();
	int subLeng = substring.length();
	for(int i=0; i<(thisLeng-subLeng+1); i++)
	{
		String tempSub = this->substring(i, i + substring.length());
		if(compareChar(tempSub, substring))
		{
			return true;
		}
	}

	return false;
}

bool String::equals(const String& s) const noexcept
{
	if(this->l == s.l)
	{
		for(int i=0; i<s.l; i++)
		{
			if(this->c[i]!=s.c[i])
				return false;
		}
		return true;	
	}
	return false;
}

int String::find(const String& substring) const noexcept
{
	int index = 0;
	if(this->contains(substring))
	{
		for(int i=0; i<this->length(); i++)
		{
			String tempSub = this->substring(index, index + substring.length());
			if(compareChar(tempSub, substring))
			{
				return index;
			}
			else
				index++;
		}
	}

	return -1;
}

bool String::isEmpty() const noexcept
{
	if(l == 0)
	{
		if(this->c[0]=='\0')
			return true;
	}
	return false;
}

unsigned int String::length() const noexcept
{
	return l;
}

String String::substring(unsigned int startIndex, unsigned int endIndex) const
{
	int leng = this->length();
	if(endIndex>leng)
		throw OutOfBoundsException();
	else
	{
		String substr;
		int i=0;

		for(int index=startIndex; index<endIndex; index++)
		{
			substr.c[i]=this->c[index];
			i++;
		}

		substr.l = i;

		return substr;	
	}
	
}

const char* String::toChars() const noexcept
{
	return this->c;
}

void String::copyArr(const String& source)
{
	this->l = source.length();
	this->cap = source.cap;
	char* charArr = new char[source.cap];
	emptyInit(charArr, cap);
	copy(charArr, source, l);

	delete[] c;
	this->c = charArr;	
}

// to copy string to another string
void String::copy(char* charArr, const String& source, unsigned int leng)
{
	for(int i=0; i<leng; i++)
	{
		charArr[i] = source.c[i];
	}
}

bool String::compareChar(String s1, String s2) const
{
	for(int i=0; i<s1.length();i++)
	{
		if(s1.c[i]!=s2.c[i])
			return false;
	}
	return true;
}