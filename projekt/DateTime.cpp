#include "DateTime.h"

DateTime::DateTime(Element* next, Element* previous, std::string data) :Element(DataBaseElement::DateTime, next ,previous)
{
	_day = std::atoi(data.substr(0, data.find('/')).c_str());
	data = data.substr(data.find('/') + 1);
	_month = std::atoi(data.substr(0, data.find('/')).c_str());
	data = data.substr(data.find('/') + 1);
	_year = std::atoi(data.substr(0, data.find(' ')).c_str());
	data = data.substr(data.find(' '));
	
	_hour = std::atoi(data.substr(0, data.find(':')).c_str());
	data = data.substr(data.find(':') + 1);
	_minutes = std::atoi(data.substr(0, data.find(':')).c_str());
	data = data.substr(data.find(':') + 1);
	_seconds = std::atoi(data.substr(0, data.find('.')).c_str());
	data = data.substr(data.find('.') + 1);
	_miliseconds = std::atoi(data.c_str());
}

std::string DateTime::toString() const
{
	return std::to_string(_day) + "/" + std::to_string(_month) + "/" + std::to_string(_year) + " " +
		std::to_string(_hour) + ":" + std::to_string(_minutes) + ":" + std::to_string(_seconds) + "." + std::to_string(_miliseconds);
}