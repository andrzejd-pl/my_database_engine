#pragma once
#include "Element.h"
#include <string>

class Intiger :
	public Element
{

private:
	int _value;

public:
	Intiger(Element* next, Element* previous, const std::string& name, int value): 
		Element(DataBaseElement::Intiger, name, next, previous), _value(value) {}

	std::string toString() const;

};

