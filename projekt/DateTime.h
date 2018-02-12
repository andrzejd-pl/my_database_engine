#pragma once
#include "Element.h"

class DateTime :
	public Element
{
private:

	unsigned int _day;
	unsigned int _month;
	unsigned int _year;

	unsigned int _hour;
	unsigned int _minutes;
	unsigned int _seconds;
	unsigned int _miliseconds;
public:
	DateTime(Element* next, Element* previous, const std::string& name, std::string data);

	virtual std::string toString() const;

};

