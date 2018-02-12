#pragma once
#include <vector>
#include <nlohmann/json.hpp>
#include <boost/filesystem.hpp>
#include <map>

/*
 * Struktura przechowuj¹ca konfiguracjê bazy danych
 */
struct DataBaseConf {

	using json = nlohmann::json;
	/*
	* Struktura przechowuj¹ca konfiguracjê tabeli
	*/
	struct TableConf {
		std::string name;
		std::string primary_key;
		std::map<std::string, std::string> types;//first - nazwa, second - typ
	};//********TableConf**************

	std::string name;
	std::vector<TableConf> tables;

	DataBaseConf() = default;
	DataBaseConf(const std::string& path);

	void loadFromFile(const std::string& path);
	void saveToFile(const std::string& path) const;

};//********DataBaseConf**********


class Configuration {
private:
	std::map<std::string, DataBaseConf> _configs;
public:
	Configuration();
	~Configuration();

	void add(const DataBaseConf& db);
	const DataBaseConf getConf(const std::string& name) const;
	DataBaseConf getConf(const std::string& name);
	const DataBaseConf operator[](const std::string name) const;
	DataBaseConf operator[](const std::string name);

	void load();
	void save();
};