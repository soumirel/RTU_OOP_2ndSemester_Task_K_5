#ifndef CL_COMMANDHANDLER_H
#define CL_COMMANDHANDLER_H

#include "Cl_base.h"

class Cl_console :
	public Cl_base
{
public:

	Cl_console(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path, string message) override
	{
		return;
	}


	void handler_v(string path, string message) override
	{
		if (message == "MACHINE:CONSOLE_START")
		{
			string currentCommand = "";
			do
			{
				getline(cin, currentCommand);

				/*if (currentCommand == "50")
				{
					cout << "check\n";
				}*/

				this->realizeEmit(currentCommand);
				
			} while (currentCommand != "Cancel");
		}

		this->realizeEmit("CONSOLE:SCREEN_SAYTURNEDOFF");
	}


	size_t getClassNumber()
	{
		return 2;
	}
};

#endif