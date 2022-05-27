#ifndef CL_BRANCH_2_H
#define CL_BRANCH_2_H

#include "Cl_base.h"

class Cl_branch_2 :
	public Cl_base
{
public:

	Cl_branch_2(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path) override
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