#pragma once
#include <string>

enum class DataBaseElement { Intiger, String, Real, DateTime, NullElement };

class Element {
private:
	DataBaseElement _db_type;
	std::string _name;
public:
	Element* _next;
	Element* _previous;

	Element(const DataBaseElement& type, const std::string& name, Element* next, Element* previous) :
		_db_type(type), _next(next), _previous(previous), _name(name) {}

	virtual std::string toString();
	virtual std::string getName() const;
	virtual DataBaseElement getType() const;

	virtual ~Element();
};

bool operator==(const Element& element1, const Element& element2);