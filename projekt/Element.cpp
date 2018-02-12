#include "Element.h"
#include "Intiger.h"
#include "Real.h"
#include "DateTime.h"
#include "String.h"


inline std::string Element::toString()
{
	throw std::exception("Nie mo¿na zamieniæ na string");
	return "";
}

std::string Element::getName() const {
	return _name;
}

inline DataBaseElement Element::getType() const
{
	return _db_type;
}

inline Element::~Element()
{
	if (_next != nullptr)
		delete _next;
	if (_previous != nullptr)
		delete _previous;
}

bool operator==(const Element& element1, const Element& element2)
{
	Element* el1 = new Element(element1);
	Element* el2 = new Element(element2);

	if (el1->getType() != el2->getType())
		return false;

	else if (el1->getType() == DataBaseElement::NullElement)
		return true;
	else if (el1->getType() == DataBaseElement::Intiger)
	{
		return (dynamic_cast<Intiger*>(el1) == dynamic_cast<Intiger*>(el2));
	}
	else if (el1->getType() == DataBaseElement::Real)
	{
		return (dynamic_cast<Real*>(el1) == dynamic_cast<Real*>(el2));

	}
	else if (el1->getType() == DataBaseElement::DateTime)
	{
		return (dynamic_cast<DateTime*>(el1) == dynamic_cast<DateTime*>(el2));
	}
	else
	{
		return (dynamic_cast<String*>(el1) == dynamic_cast<String*>(el2));
	}
}
