#pragma once
#include <unordered_map>
#include "db_conf.h"
#include "Table.h"

class DataBase {
private:
	DataBaseConf _config;
	//std::vector<Table> _tables;
	std::unordered_map<std::string, Table> _tables;
public:
	DataBase(const DataBaseConf& config);

	Table select(const std::string& what, const std::string& from , const std::string& where) const;

	//~DataBase();
};