#ifndef CL_COFFEMAKER_H
#define CL_COFFEMAKER_H

#include "Cl_base.h"
#include "Cl_coffeMachine.h"

class Cl_coffemaker :
	public Cl_base
{
private:

	// Структура с информацией о связи сорт-цена
	struct coffeInfo
	{
		string name_;
		size_t price_;
		
		coffeInfo(string name = "", size_t price = 0)
		{
			price_ = price;
			name_ = name;
		}
	};

	vector<coffeInfo> coffeInMachine;

	int coffeTypesNumber = -1;
	vector<string> coffeTypesNames;

public:

	Cl_coffemaker(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path, string message) override
	{
		string token = message.substr(0, message.find(" ") + 1);

		for (size_t i = 0; i < coffeInMachine.size(); i++)
		{
			if (token == coffeInMachine.at(i).name_)
			{
				cout << "Take the coffe " << message 
					<< "\nReady to work\n";
			}
		}
	}


	size_t getPrice(string coffeeType)
	{
		for (size_t i = 0; i < coffeInMachine.size(); i++)
		{
			if (coffeeType == coffeInMachine.at(i).name_)
			{
				return coffeInMachine.at(i).price_;
			}
		}
	}

	void handler_v(string path, string message) override
	{
		if (this->getHeadPtr()->getStatusCoffeLoad() == false)
		{
			size_t delimeterPosition = 0;
			while ((delimeterPosition = message.find(" ")) != string::npos)
			{
				if (coffeTypesNumber == -1)
				{
					coffeTypesNumber = stoi(message.substr(0, delimeterPosition));
				}
				else
				{
					coffeTypesNames.push_back(message.substr(0, delimeterPosition));
				}
				message.erase(0, delimeterPosition + 1);
			}
			coffeTypesNames.push_back(message.substr(0, message.size() - 1));
			this->getHeadPtr()->setStatusCoffeLoad(true);
		}

		if (this->getHeadPtr()->getStatusCoffeLoad() == true
			&& this->getHeadPtr()->getStatusCoinsLoad() == true)
		{
			string token = message.substr(0, message.find(" ") + 1);
			if (token == "SYSTEM_COFFE")
			{
				message.erase(0, message.find(" ") + 1);
				this->realizeEmit(message);
				this->realizeEmit("SYSTEM_CHANGE "
					+ to_string(getPrice(message)));
			}
			else
			{
				return;
			}
		}
	}




	size_t getClassNumber()
	{
		return 6;
	}
};

#endif