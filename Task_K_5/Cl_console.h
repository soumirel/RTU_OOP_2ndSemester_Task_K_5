#ifndef CL_COMMANDHANDLER_H
#define CL_COMMANDHANDLER_H

#include "Cl_base.h"

class Cl_console :
	public Cl_base
{
private:
	bool isSetupFinished = false;

public:

	Cl_console(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path, string message) override
	{
		return;
	}


	void handler_v(string path, string message) override
	{
		string currentCommand = "";
		do
		{
			getline(cin, currentCommand);
			this->realizeEmit(currentCommand);
		} while (currentCommand != "Cancel");
	}


	size_t getClassNumber()
	{
		return 2;
	}
};

#endif