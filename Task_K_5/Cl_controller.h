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
		cout << '\n' << "Signal to " << path
			<< " Text: " << message << " (class: 3)";
	}


	size_t getClassNumber()
	{
		return 3;
	}
};

#endif