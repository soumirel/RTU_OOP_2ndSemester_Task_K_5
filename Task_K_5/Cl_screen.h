#ifndef CL_SCREEN_H
#define CL_SCREEN_H

#include "Cl_base.h"

class Cl_screen :
    public Cl_base
{
private:
	bool isSetupFinished = false;

public:

	Cl_screen(string objectName, Cl_base* parentPtr) :
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
			string token = message.substr(0, message.find(" "));
			message.erase(0, message.find(" ") + 1);

			if (token == "SYSTEM_SHOW_BALANCE")
			{
				cout << "The amount: " << message << '\n';
			}
		}
	}


	size_t getClassNumber()
	{
		return 7;
	}
};

#endif
