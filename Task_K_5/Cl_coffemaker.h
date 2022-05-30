#ifndef CL_COFFEMAKER_H
#define CL_COFFEMAKER_H

#include "Cl_base.h"
#include "Cl_coffeeMachine.h"

class Cl_coffemaker :
	public Cl_base
{
private:

	// Структура с информацией о связи сорт-цена
	struct coffeeInfo
	{
		string name_;
		size_t price_;
		
		coffeeInfo(string name = "", size_t price = 0)
		{
			price_ = price;
			name_ = name;
		}
	};

	vector<coffeeInfo> coffeeInMachine;

	int coffeeTypesNumber = -1;
	vector<string> coffeeTypesNames;

public:

	Cl_coffemaker(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path, string message) override
	{
		string token = "";

		if (message.find(" ") == string::npos)
		{
			token = message;
		}
		else
		{
			token = message.substr(0, message.find(" "));
		}

		for (size_t i = 0; i < coffeeInMachine.size(); i++)
		{
			if (token == coffeeInMachine.at(i).name_)
			{
				string sentMessage = "Take the coffee " + message;
				this->realizeEmit("COINSRETURNER:SCREEN_MESSAGE " + sentMessage);
				return;
			}
		}
	}


	size_t getPrice(string coffeeType)
	{
		for (size_t i = 0; i < coffeeInMachine.size(); i++)
		{
			if (coffeeType == coffeeInMachine.at(i).name_)
			{
				return coffeeInMachine.at(i).price_;
			}
		}
	}

	void handler_v(string path, string message) override
	{
		if (this->getHeadPtr()->getStatusCoffeLoad() == false)
		{
			size_t delimeterPosition = 0;
			if (coffeeTypesNumber == -1)
			{
				while ((delimeterPosition = message.find(" ")) != string::npos)
				{
					if (coffeeTypesNumber == -1)
					{
						coffeeTypesNumber = stoi(message.substr(0, delimeterPosition));
					}
					else
					{
						coffeeTypesNames.push_back(message.substr(0, delimeterPosition));
					}
					message.erase(0, delimeterPosition + 1);
				}
				coffeeTypesNames.push_back(message.substr(0, message.size()));
			}
			else
			{
				string token = "";
				while ((delimeterPosition = message.find(" ")) != string::npos)
				{
					token = message.substr(0, delimeterPosition);
					message.erase(0, delimeterPosition + 1);

					coffeeInMachine.push_back(coffeeInfo(coffeeTypesNames.front(), stoi(token)));
					coffeeTypesNames.erase(coffeeTypesNames.begin());
				}
				token = message.substr(0, message.size());
				coffeeInMachine.push_back(coffeeInfo(coffeeTypesNames.front(), stoi(token)));

				this->getHeadPtr()->setStatusCoffeLoad(true);
			}
		}

		if (this->getHeadPtr()->getStatusCoffeLoad() == true
			&& this->getHeadPtr()->getStatusCoinsLoad() == true)
		{
			string token = message.substr(0, message.find(" "));
			message.erase(0, message.find(" ") + 1);

			if (token == "CONTROLLER:COFFEEMAKER_MAKECOFFEE")
			{
				
				this->realizeEmit(message.substr(0, message.find(" ")));
				this->realizeEmit("COFFEEMAKER:COINSRETURNER_GIVECHANGE " + to_string(getPrice(message)));
				this->realizeEmit("COFFEMAKER:SCREEN_SAYREADY");
			}
			
			if (token == "CONTROLLER:COFFEEMAKER_GETPRICE")
			{
				this->realizeEmit("COFFEEMAKER:CONTROLLER_GIVEPRICE " + to_string(getPrice(message)));
			}
		}
	}




	size_t getClassNumber()
	{
		return 6;
	}
};

#endif