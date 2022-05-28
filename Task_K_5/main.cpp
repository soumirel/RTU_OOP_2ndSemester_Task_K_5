#include "Cl_coffeMachine.h"

int main()
{
	Cl_coffeMachine machineObject;

	//Построение системы объектов
	machineObject.buildTree();

	return machineObject.runMachine();
}