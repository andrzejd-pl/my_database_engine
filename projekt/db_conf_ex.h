#pragma once
#include <stdexcept>

class db_conf_ex : public std::runtime_error {
public:
	db_conf_ex(const std::string& _Message): runtime_error(_Message) {}
	db_conf_ex(const char* _Message): runtime_error(_Message) {}
};

class db_insert_ex : public std::runtime_error {
public:
	db_insert_ex(const std::string& _Message) : runtime_error(_Message) {}
	db_insert_ex(const char* _Message) : runtime_error(_Message) {}
};