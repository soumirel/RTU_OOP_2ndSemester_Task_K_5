#include "Cl_coffeMachine.h"

int main()
{
	Cl_coffeMachine machineObject;

	//���������� ������� ��������
	machineObject.buildTree();

	return machineObject.runMachine();
}