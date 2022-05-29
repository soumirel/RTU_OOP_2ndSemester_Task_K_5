#ifndef CL_CASHRECEIVER_H
#define CL_CASHRECEIVER_H

#include "Cl_base.h"

class Cl_cashReceiver :
	public Cl_base
{
private:
	size_t cashInMachine = 0;

public:

	Cl_cashReceiver(string objectName, Cl_base* parentPtr) :
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
			string token = message.substr(0, message.find(" ") + 1);
			message.erase(0, message.find(" ") + 1);

			if (isNumber(token) == true)
			{
				this->realizeEmit("SYSTEM_CHEK_COINS " + token);
			}

			if (token == "SYSTEM_REFUND")
			{
				cout << "Take the money back, no change";
				cashInMachine = 0;
				this->realizeEmit("SYSTEM_CHEK_COINS 0");
			}

			if (token == "SYSTEM_RECEIVE")
			{
				cashInMachine += stoi(message);
				this->realizeEmit("SYSTEM_SHOW_BALANCE " + to_string(cashInMachine));
			}
		}
	}


	


	size_t getClassNumber()
	{
		return 4;
	}
};

#endif