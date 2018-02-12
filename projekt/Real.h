#pragma once
#include "Element.h"

class Real :
	public Element
{
private:
	double _value;
public:
	Real(Element* next, Element* previous, const std::string& name, const double value): 
		Element(DataBaseElement::Real, name, next, previous), _value(value) {}

	virtual std::string toString() const;

};

