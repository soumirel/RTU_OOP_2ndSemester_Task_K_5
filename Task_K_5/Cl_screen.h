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
		
	}


	void handler_v(string path, string message) override
	{
		
	}


	size_t getClassNumber()
	{
		return 7;
	}
};

#endif
