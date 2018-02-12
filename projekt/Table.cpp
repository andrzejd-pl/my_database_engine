#include "Table.h"
#include "Intiger.h"
#include "Real.h"
#include "DateTime.h"
#include "String.h"
#include "db_conf_ex.h"


//---------------List--------------------------------
List::List(std::map<std::string, std::string>& types, std::vector<std::string>& values, Element* index): index(index) {
	if (types.size() != values.size())
		throw db_insert_ex("Bad number of insered elements");

	first = new Element(DataBaseElement::NullElement, "", nullptr, nullptr);
	Element* iterator = first;

	size_t i = 0;
	for(const auto& type: types) {
		if (type.second == "int")
			iterator->_next = new Intiger(nullptr, iterator, type.first, std::atoi(values[i].c_str()));
		else if(type.second == "double")
			iterator->_next = new Real(nullptr, iterator, type.first, std::atof(values[i].c_str()));
		else if(type.second == "date_time")
			iterator->_next = new DateTime(nullptr, iterator, type.first, values[i]);
		else if(type.second == "string")
			iterator->_next = new String(nullptr, iterator, type.first, values[i]);

		iterator = iterator->_next;
		++i;
	}

	end = iterator;
}

List::~List() { if (first == nullptr) delete first; }

void List::addElement(Element* el) {
	end->_next = el;
	end = end->_next;
}

Element* List::getElement(size_t it) const {
	Element* tmp = first;
	for (size_t i = 0; i <= it; ++i)
		tmp = tmp->_next;

	return tmp;
}

bool List::isEqual(const Element& el, const size_t& nr) const {
	Element* searchElement = first;
	for (size_t i = 0; i <= nr; ++i)
		searchElement = searchElement->_next;

	return el == *searchElement;
}

//------------------------------------------------------------

//-----------------Table--------------------------------------
Table::Table(const DataBaseConf::TableConf& config) : _config(config) {
	
}

Table Table::select(std::string what, const std::string& where) const {
	if (what == "*")
		return *this;

	std::vector<std::string> select_types;

	DataBaseConf::TableConf new_conf;
	new_conf.name = "select " + what + " from " + this->_config.name;
	new_conf.primary_key = this->_config.primary_key;

	std::string::size_type n;
	do {
		n = what.find(',');
		select_types.push_back(what.substr(0, n));
		what = what.substr(n + 1);
	} while (n != std::string::npos);

	for (const auto& type_s : select_types) {
		std::pair<std::string, std::string> t;
		for (const auto& type_t : this->_config.types) {
			if (type_t.first == type_s) {
				t = type_t;
				break;
			}
		}
		new_conf.types.push_back(t);
	}

	Table select_tab(new_conf);

	return select_tab;
}

void Table::insertRow(const List& row) {
	_values[row.index] = row;
}
