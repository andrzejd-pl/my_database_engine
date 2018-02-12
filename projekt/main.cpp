#include <iostream>
#include "db_conf.h"
#include "Table.h"
#include "DateTime.h"
#include "Intiger.h"
#include "String.h"
#include "Real.h"

int main()
{
	try
	{
		Configuration conf;

		DateTime* dt = new DateTime(nullptr, nullptr, "dt", "27/05/2017 13:28:30.520"); //-- dzia³a
		Intiger* i = new Intiger(dt, nullptr, "i", 6);
		String* s = new String(i, nullptr, "s", "dsfdsgas");
		Real* r = new Real(s ,nullptr, "r", 5.75456);//----dzia³a do tego miejsca*/
		Table tab = Table(conf["baza_tmp"].tables[0]);
		std::unordered_map<Element*, int> tmp;
		std::unordered_map<Element*, Table> tmp2;

		tmp2[dt] = tab;

		tmp[dt] = 5;
		tmp[i] = 4;
		tmp[s] = 7;
		tmp[r] = 9;

		tmp[dt] = 8;

		getchar();
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	getchar();

	return 0;
}//--------main------------------------------