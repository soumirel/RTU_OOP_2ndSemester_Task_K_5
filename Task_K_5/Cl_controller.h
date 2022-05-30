#ifndef CL_CONTROLLER_H
#define CL_CONTROLLER_H

#include "Cl_base.h"

class Cl_controller :
	public Cl_base
{
private:
	size_t currentReceivedMoney = 0;
	size_t currentCoffeePrice = 0;
	string currentCoffeeType = "";

public:

	Cl_controller(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path, string message) override
	{
		return;
	}

	void handler_v(string path, string message) override
	{
		if (this->getHeadPtr()->getStatusCoffeLoad() == true
			&& this->getHeadPtr()->getStatusCoinsLoad() == true)
		{
			string token = message.substr(0, message.find(' '));
			message.erase(0, message.find(' ') + 1);

			if (token == "Coffee")
			{
				currentCoffeeType = message;
				this->realizeEmit("CONTROLLER:COFFEEMAKER_GETPRICE " + message);
			}

			if (token == "Refund")
			{
				this->realizeEmit("CONTOLLER:COINSRETURNER_REFUND");
			}

			if (token == "COFFEEMAKER:CONTROLLER_GIVEPRICE")
			{
				currentCoffeePrice = stoi(message);
				this->realizeEmit("CONTROLLER:COINSRETURNER_GETBALANCE " + message);
			}

			if (token == "COINSRETURNER:CONTROLLER_GIVEBALANCE")
			{
				currentReceivedMoney = stoi(message);
				if (currentCoffeePrice <= currentReceivedMoney)
				{
					this->realizeEmit("CONTROLLER:COFFEEMAKER_MAKECOFFEE " + currentCoffeeType);
				}
				else
				{
					this->realizeEmit("COINSRETURNER:SCREEN_MESSAGE There is not enough money");
				}
				
			}
		}
	}


	size_t getClassNumber()
	{
		return 3;
	}
};

#endif