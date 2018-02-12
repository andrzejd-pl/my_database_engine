#include "DataBase.h"



DataBase::DataBase(const DataBaseConf& config): _config(config) 
{
	size_t i = 0;
	for(const auto& el : _config.tables)
	{
		_tables[el.name] = Table(el);
		++i;
	}
}

Table DataBase::select(const std::string& what, const std::string& from, const std::string& where) const
{
	const Table& from_table = _tables.at(from);

	if (what == "*") {
		return from_table;
	}

	return from_table.select(what, where);
}



//DataBase::~DataBase()
//{
//}
