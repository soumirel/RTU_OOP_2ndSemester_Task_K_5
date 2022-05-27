#ifndef CL_BRANCH_H
#define CL_BRANCH_H

#include "Cl_base.h"

class Cl_branch :
	public Cl_base
{
public:

	Cl_branch(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path) override
	{
		cout << '\n' << "Signal from " << path;
	}


	void handler_v(string path, string message) override
	{
		cout << '\n' << "Signal to " << path
			<< " Text: " << message << " (class: 2)";
	}


	size_t getClassNumber()
	{
		return 2;
	}
};

#endif