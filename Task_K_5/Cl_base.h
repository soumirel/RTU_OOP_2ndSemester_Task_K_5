#ifndef CL_BASE_H
#define CL_BASE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define SIGNAL(signal_f) (TYPE_SIGNAL) (& signal_f)
#define HANDLER(handler_f) (TYPE_HANDLER) (& handler_f)

class Cl_base;

typedef void (Cl_base::* TYPE_SIGNAL) (string&);
typedef void (Cl_base::* TYPE_HANDLER) (string);

class Cl_base
{
protected:
	bool isSystemReady = false;

private:
	// ��� �������
	string objectName = "";

	// ��������� �� �������� �������
	Cl_base* parentPtr = nullptr;

	// ��������� ���������� �������
	bool readiness = false;

	// ��������� ���������� � ����� ��������
	struct connectionInfo
	{
		TYPE_SIGNAL signalPtr;
		Cl_base* objectPtr;
		TYPE_HANDLER handlerPtr;
	};

	// ������ ���������� � �����������
	vector<connectionInfo*> connections;

public:

	// ������ ���������� �������� ��������
	vector<Cl_base*> childrenList;

	// �����������
	Cl_base(string objectName, Cl_base* parentPtr);

	// ������
	void setName(string objectName);
	void setParent(Cl_base* parentPtr);
	void setReadiness(long long numericReadiness);

	// ������
	Cl_base* getParent();
	string getName();
	bool getReadiness();
	virtual size_t getClassNumber();

	// ����������� ����� ������� � �����������
	virtual void signal_v(string path, string message);
	virtual void handler_v(string path, string message);

	//���������� ������ ��� ������������� ������ ������ Cl_coffeMachine
	//��� ������������ ����� Cl_base
	virtual bool getStatusCoffeLoad();
	virtual bool getStatusCoinsLoad();

	//��������� ��������� �� �������� ������
	Cl_base* getHeadPtr();

	// ��������� ��������� �� ������ ����� ��� ���
	Cl_base* getObjectByName(string name);

	//��������� ��������� �� ������ ����� �������� ����
	Cl_base* getObjectByPath(string path);

	// ��������� ���.���������� �� �������
	string getAbsPath();

	// ���������� �����
	void setConnection(TYPE_SIGNAL signalPtr, Cl_base* objectPtr,
		TYPE_HANDLER handlerPtr);

	// ����� ������� �����
	void deleteConnection(TYPE_SIGNAL signalPtr, Cl_base* objectPtr,
		TYPE_HANDLER handlerPtr);

	// ������ ��������� �������
	void emitSignal(TYPE_SIGNAL signalPtr, string& message);

	// ��������� ��������� ����� ����� ���������
	void realizeConnection(Cl_base* firstObjectPtr, Cl_base* secondObjectPtr);

	// ��������� ����������� �������
	void realizeEmit(string message);

	// ��������� �������� �����
	void removeConnection(Cl_base* firstObjectPtr, Cl_base* secondObjectPtr);

	// ����� ������ ��������
	void printTree(bool isPrintReadiness, unsigned tabLevel = 0);

};

#endif