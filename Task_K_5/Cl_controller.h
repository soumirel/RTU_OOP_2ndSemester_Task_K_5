#ifndef CL_CONTROLLER_H
#define CL_CONTROLLER_H

#include "Cl_base.h"

class Cl_controller :
	public Cl_base
{
public:

	Cl_controller(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path, string message) override
	{
		cout << '\n' << "Signal from " << path;
	}

	void handler_v(string path, string message) override
	{
		if (this->getHeadPtr()->getStatusCoffeLoad() == true
			&& this->getHeadPtr()->getStatusCoinsLoad() == true)
		{
			string token = message.substr(0, message.find(' ') + 1);
			message.erase(0, message.find(' ') + 1);
			if (token == "Coffe")
			{
				this->realizeEmit("SYSTEM_COFFE" + message);
			}
			else if (token == "Refund")
			{

			}

		}
	}


	size_t getClassNumber()
	{
		return 3;
	}
};

#endif