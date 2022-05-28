#ifndef CL_COFFEMACHINE_H
#define CL_COFFEMACHINE_H

#include  "Cl_base.h"

class Cl_coffeMachine : 
	public Cl_base 
{
private:
	//����-������� �������� � ������� ���� � �����
	bool statusCoffeLoad = false;
	bool statusCoinsLoad = false;

public:


	//�����������
	Cl_coffeMachine(string objectName = "coffeMachineObject", Cl_base* parentPtr = nullptr) :
		Cl_base(objectName, parentPtr) {};

	//������� �������� �������� ����� � ����
	bool getStatusCoffeLoad() override;
	bool getStatusCoinsLoad() override;

	//������ ����� ����� ��� ���������� ������
	void buildTree();

	//������ ����� ����� ��� ��������� ����������� ��������
	void enterReadiness();

	//������ ����� ����� ��� ��������� ������ ����� ���������
	void enterConnections();

	//������ ����� ����� ��� ������������� ����������� ��� ��������� ��� ������ ������
	void enterCommands();

	//������ ������� ����������
	int runMachine();

};

#endif



