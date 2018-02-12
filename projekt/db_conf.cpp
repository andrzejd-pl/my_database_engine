#include "db_conf.h"
#include <fstream>
#include <iterator>
#include "db_conf_ex.h"

namespace fs = boost::filesystem;

DataBaseConf::DataBaseConf(const std::string& path) {
	this->loadFromFile(path);
}


void DataBaseConf::loadFromFile(const std::string& path)
{
	std::string s;

	{
		std::fstream plik;
		plik.open(path, std::ios::in);
		
		if (plik.is_open()) { copy(std::istream_iterator<char>(plik), std::istream_iterator<char>(), back_inserter(s)); }
		else throw db_conf_ex("Configuration file does not exist !!!!");
		
		plik.close();
	}

	auto json_db = json::parse(s.c_str());
	this->name = json_db.at("name").get<std::string>();

	{
		auto tables = json_db.at("tables").get<json>();
		for (auto tb = tables.begin(); tb != tables.end(); ++tb)
		{
			TableConf tb_conf;
			
			tb_conf.name = tb->at("name").get<std::string>();
			tb_conf.primary_key = tb->at("primary_key").get<std::string>();
			
			if (tb_conf.primary_key == "")
				throw db_conf_ex("In \"" + tb_conf.name + "\" table, primary key does not exist !!!");
			
			auto elements = tb->at("elements").get<json>();
			
			for (auto el = elements.begin(); el != elements.end(); ++el)
			{
				tb_conf.types[el->at("name").get<std::string>()] = el->at("type").get<std::string>();
			}

			this->tables.push_back(tb_conf);
		}
	}
}

void DataBaseConf::saveToFile(const std::string& path) const {

	json json_db;

	json_db["name"] = this->name;
	json tables;
	for (size_t i = 0; i < this->tables.size(); ++i) { //pêtla iteruj¹ca po tabelach
		json table;

		table["name"] = this->tables[i].name;
		table["primary_key"] = this->tables[i].primary_key;

		json elements;
		size_t j = 0;
		for (const auto& type: this->tables[i].types) { // pêtla iteruj¹ca po typach elementów
			json element;
			
			element["name"] = type.first;
			element["type"] = type.second;

			elements[std::to_string(j)] = element;
			++j;
		}

		table["elements"] = elements;
		tables[std::to_string(i)] = table;
	}
	json_db["tables"] = tables;

	std::ofstream file;
	if (!fs::exists(path) || !fs::is_directory(path))
		file.open(path);
	else
		file.open(path, std::ios::trunc);

	file << json_db << std::endl;

	file.close();

}

Configuration::Configuration() {
	load();
}

Configuration::~Configuration() {
	save();
}

void Configuration::load() {
	fs::path dir("./configuration");

	if (!fs::exists(dir) || !fs::is_directory(dir))
		throw db_conf_ex("Configuration folder does not exist !!!");

	std::vector<fs::path> files;
	std::copy(fs::directory_iterator(dir), fs::directory_iterator(), std::back_inserter(files));

	if (_configs.size() != 0) _configs.clear();

	for (const auto& file : files) {
		DataBaseConf db_config(file.generic_string());

		_configs[db_config.name] = db_config;
	}
}

void Configuration::save() {
	fs::path dir("./configuration");

	if (!fs::exists(dir) || !fs::is_directory(dir))
		fs::create_directory(dir);

	for (const auto& config : _configs) {
		config.second.saveToFile(dir.generic_string() + "/" + config.first + ".conf");
	}
}

void Configuration::add(const DataBaseConf& db) {
	if (_configs.find(db.name) == _configs.end())
		_configs[db.name] = db;
}

const DataBaseConf Configuration::getConf(const std::string& name) const {
	return _configs.at(name);
}

DataBaseConf Configuration::getConf(const std::string& name) {
	return _configs[name];
}

const DataBaseConf Configuration::operator[](const std::string name) const {
	return _configs.at(name);
}

DataBaseConf Configuration::operator[](const std::string name) {
	return _configs[name];
}
