#include "Cl_coffeeMachine.h"

int main()
{
	Cl_coffeeMachine machineObject;

	//Построение системы объектов
	machineObject.buildTree();

	return machineObject.runMachine();
}