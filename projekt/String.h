#pragma once
#include "Element.h"

class String :
	public Element
{
private:
	std::string _value;
public:
	String(Element* next, Element* previous, const std::string& name, const std::string& value)
		:_value(value), Element(DataBaseElement::String, name, next, previous){}

	virtual std::string toString() const;

};

