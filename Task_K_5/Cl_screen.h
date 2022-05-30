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
		cout << message << '\n';
	}


	void handler_v(string path, string message) override
	{
		if (this->getHeadPtr()->getStatusCoffeLoad() == true
			&& this->getHeadPtr()->getStatusCoinsLoad() == true)
		{
			size_t colonIndex = message.find(":");
			size_t spaceIndex = message.find(" ");
			string token = message.substr(colonIndex + 1, spaceIndex - colonIndex - 1);
			message.erase(0, spaceIndex + 1);

			if (token == "SCREEN_SAYTURNEDOFF")
			{
				this->realizeEmit("Turned off");
			}

			if (token == "SCREEN_SAYREADY")
			{
				this->realizeEmit("Ready to work");
			}

			if (token == "SCREEN_MESSAGE")
			{
				this->realizeEmit(message);
			}
		}
	}


	size_t getClassNumber()
	{
		return 7;
	}
};

#endif
