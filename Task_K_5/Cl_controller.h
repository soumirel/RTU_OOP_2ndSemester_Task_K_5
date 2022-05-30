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
				this->realizeEmit("SYSTEM_GET_PRICE " + message);
			}

			if (token == "SYSTEM_RECEIVE_PRICE")
			{
				currentCoffeePrice = stoi(message);
				this->realizeEmit("SYSTEM_GET_BALANCE " + message);
			}

			if (token == "SYSTEM_RECEIVE_BALANCE")
			{
				currentReceivedMoney = stoi(message);
				if (currentCoffeePrice <= currentReceivedMoney)
				{
					this->realizeEmit("SYSTEM_COFFEE " + currentCoffeeType);
					this->realizeEmit("SYSTEM_REDUCE_BALANCE " + to_string(currentCoffeePrice));
				}
				else
				{
					cout << "There is not enough money\n";
				}
				
			}

			if (token == "Refund")
			{
				this->realizeEmit("SYSTEM_REFUND");
			}
		}
	}


	size_t getClassNumber()
	{
		return 3;
	}
};

#endif