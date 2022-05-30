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
			size_t delimeterPosotion = message.find(" ");
			string token = "";
			if (delimeterPosotion == string::npos)
			{
				token = message;
			}
			else
			{
				token = message.substr(0, message.find(" "));
			}
			
			if (isNumber(message) == true)
			{
				this->realizeEmit("SYSTEM_CHECK_COINS " + token);
			}

			message.erase(0, message.find(" ") + 1);

			if (token == "SYSTEM_RECEIVE")
			{
				if (message == "0")
				{
				cashInMachine = stoi(message);
				}
				else
				{
				cashInMachine += stoi(message);
				}
				this->realizeEmit("SYSTEM_SHOW_BALANCE " + to_string(cashInMachine));
			}

			if (token == "SYSTEM_RETURN_BANKNOTE")
			{
				cout << "Take the money back, no change\n";
			}

			if (token == "SYSTEM_REDUCE_BALANCE_1")
			{
				cashInMachine -= stoi(message);
			}
		}
	}


	


	size_t getClassNumber()
	{
		return 4;
	}
};

#endif