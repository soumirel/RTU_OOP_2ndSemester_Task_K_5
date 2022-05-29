#ifndef CL_COINSRETURNER_H
#define CL_COINSRETURNER_H

#include "Cl_base.h"

class Cl_coinsReturner :
	public Cl_base
{
private:
	//Количество десяток и пятёрок в автомате
	size_t tennerNumber = 0;
	size_t fiverNumber = 0;

	//Кол-во денежных средств в автомате
	size_t actualMoney = 0;

public:

	Cl_coinsReturner(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path, string message) override
	{
		cout << "Take the change: 10 *  " 
			<< message.substr(0, message.find(" ") + 1);
		message.erase(0, message.find(" ") + 1);
		cout << " rub.,  5 * "
			<< message.substr(0, message.find(" ") + 1) << " rub.\n";
	}


	void handler_v(string path, string message) override
	{
		if (this->getHeadPtr()->getStatusCoffeLoad() == true
			&& this->getHeadPtr()->getStatusCoinsLoad() == false)
		{
			fiverNumber = stoi(message.substr(0, message.find(" ") + 1));
			message.erase(0, message.find(" ") + 1);
			tennerNumber = stoi(message.substr(0, message.find(" ") + 1));
			this->getHeadPtr()->setStatusCoinsLoad(true);
			cout << "Ready to work\n";
		}
		else
		{
			string token = message.substr(0, message.find(" ") + 1);
			if (token == "SYSTEM_CHANGE")
			{
				message.erase(0, message.find(" ") + 1);
				size_t moneyToReturn = actualMoney - stoi(message);
				size_t tennerToReturn = moneyToReturn / 10;
				moneyToReturn /= 10;
				size_t fiverToReturn = moneyToReturn;

				this->realizeEmit(to_string(tennerToReturn) + to_string(fiverToReturn));
			}
			else if (isNumber(token))
			{
				actualMoney = stoi(token);
			}
			else
			{
				return;
			}
		}
	}


	size_t getClassNumber()
	{
		return 5;
	}
};

#endif