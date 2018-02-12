#pragma once
#include "DataBase.h"
#include "Element.h"


struct List {
	Element* first;
	Element* end;
	Element* index;

	List(std::map<std::string, std::string>& types, std::vector<std::string>& values, Element* index);

	~List();

	void addElement(Element* el);
	Element* getElement(size_t it) const;

	bool isEqual(const Element& el, const size_t& nr) const;

};


class Table {
	/*
	brak:
		-mo¿liwoœci sorotwania po danym elemencie
	*/
private:
	DataBaseConf::TableConf _config;
	//std::vector<List> _values;
	std::unordered_map<Element*, List> _values;
public:

	Table(const DataBaseConf::TableConf& config);
	Table() = default;

	Table select(std::string what, const std::string& where) const;
	void insertRow(const List& row);

	~Table() = default;
};

