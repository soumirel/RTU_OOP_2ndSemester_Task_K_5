
#include "Cl_coffeMachine.h"
#include "Cl_console.h"
#include "Cl_controller.h"
#include "Cl_cashReceiver.h"
#include "Cl_coinsReturner.h"
#include "Cl_coffemaker.h"
#include "Cl_screen.h"


bool Cl_coffeMachine::getStatusCoffeLoad()
{
	return statusCoffeLoad;
}

bool Cl_coffeMachine::getStatusCoinsLoad()
{
	return statusCoinsLoad;
}

void Cl_coffeMachine::setStatusCoffeLoad(bool status)
{
	this->statusCoffeLoad = status;
}

void Cl_coffeMachine::setStatusCoinsLoad(bool status)
{
	this->statusCoinsLoad = status;
}

//Запуск этапа ввода для построения дерева
void Cl_coffeMachine::buildTree()
{
	//Иннициализация объектов-компонентов кофемашины
	Cl_base* p_consoleObject = new Cl_console("consoleObject", this);

	Cl_base* p_controllerObject = new Cl_controller("controllerObject", this);

	Cl_base* p_cashReceiverObject = new Cl_cashReceiver("cashReceiverObject", this);

	Cl_base* p_coinsReturner = new Cl_coinsReturner("coinsReturner", this);

	Cl_base* p_coffemakerObject = new Cl_coffemaker("coffemakerObject", this);

	Cl_base* p_screenObject = new Cl_screen("screenObject", this);

	//Связка системы и объекта-обработчика консольных команд
	this->realizeConnection(this, p_consoleObject);

	//Установка связей испускатель-обработчик между объектами
	for (size_t i = 1; i < this->childrenList.size() - 1; i++)
	{
		p_consoleObject->realizeConnection(
			p_consoleObject , this->childrenList.at(i));
	}

	//Соединение логически связанных объектов
	p_cashReceiverObject->realizeConnection(p_cashReceiverObject, p_screenObject);

	p_controllerObject->realizeConnection(p_controllerObject, p_coinsReturner);

	p_controllerObject->realizeConnection(p_controllerObject, p_coffemakerObject);

	p_coffemakerObject->realizeConnection(p_coffemakerObject, p_coinsReturner);

	p_cashReceiverObject->realizeConnection(p_cashReceiverObject, p_coinsReturner);

	p_coinsReturner->realizeConnection(p_coinsReturner, p_cashReceiverObject);

	p_coffemakerObject->realizeConnection(p_coffemakerObject, p_controllerObject);

	p_coinsReturner->removeConnection(p_coinsReturner, p_controllerObject);

	return;
}


//Запуск этапа ввода для установки готовностей объектов
void Cl_coffeMachine::enterReadiness()
{
	string objectName;
	long long numericReadiness;
	while (cin >> objectName >> numericReadiness)
	{
		(this->getObjectByName(objectName))->setReadiness(numericReadiness);
	}
}


//Запуск этапа ввода для установки связей между объектами
void Cl_coffeMachine::enterConnections()
{
	string signalPath, handlerPath;
	cin >> signalPath;
	while (signalPath != "end_of_connections")
	{
		cin >> handlerPath;

		Cl_base* firstObjectPtr = this->getObjectByPath(signalPath);
		Cl_base* secondObjectPtr = this->getObjectByPath(handlerPath);

		firstObjectPtr->realizeConnection(firstObjectPtr, secondObjectPtr);

		cin >> signalPath;
	}
}


//Запуск этапа ввода для осуществления манипуляций над объектами при помощи команд
void Cl_coffeMachine::enterCommands()
{
	Cl_base* setedObjectPtr = this;
	Cl_base* objectFromPath;

	string command, path;

	cin >> command;

	while (command != "END")
	{
		cin >> path;

		objectFromPath = setedObjectPtr->getObjectByPath(path);

		// Обработка команды установки текущего объекта
		if (command == "SET")
		{
			if (objectFromPath)
			{
				setedObjectPtr = objectFromPath;
				cout << "Object is set: " << setedObjectPtr->getName();
			}
			else
			{
				cout << "Object is not found: " << setedObjectPtr->getName() << " " << path;
			}
		}

		// Обработка команды поиска объекта по координате
		if (command == "FIND")
		{
			if (objectFromPath)
			{
				cout << path << "     Object name: " << objectFromPath->getName();
			}
			else
			{
				cout << path << "     Object is not found";
			}
		}

		// Обработка команды принятия вызова
		if (command == "EMIT")
		{
			string message;
			getline(cin, message);

			if (objectFromPath)
			{
				objectFromPath->realizeEmit(message);
			}
			else
			{
				cout << '\n' << "Object " << path << " not found";
			}
		}

		// Обработка команды установки значения объекта
		if (command == "SET_CONDITION")
		{
			int condition;
			cin >> condition;

			Cl_base* tempObjectPtr;
			tempObjectPtr = this->getObjectByPath(path);

			if (tempObjectPtr)
			{
				tempObjectPtr->setReadiness(condition);
			}
			else
			{
				cout << endl << "Object " << path << " not found";
			}
		}

		// Обработка команд установки и разрыва связи между объектами
		if (command == "SET_CONNECT" || command == "DELETE_CONNECT")
		{
			string connectPath;
			cin >> connectPath;

			Cl_base* tempObjectPtr;
			tempObjectPtr = this->getObjectByPath(connectPath);

			//Проверка на существование объектов по координатам
			if (objectFromPath == nullptr || tempObjectPtr == nullptr)
			{
				if (objectFromPath == nullptr)
				{
					cout << endl << "Object " << path << " not found";
				}
				if (tempObjectPtr == nullptr)
				{
					cout << endl << "Handler object " << connectPath << " not found";
				}
			}
			else
			{
				if (command == "SET_CONNECT")
				{
					objectFromPath->realizeConnection(objectFromPath, tempObjectPtr);
				}
				else
				{
					objectFromPath->removeConnection(objectFromPath, tempObjectPtr);
				}
			}
		}

		cin >> command;
	}
}


void Cl_coffeMachine::signal_v(string path, string message)
{
}


void Cl_coffeMachine::handler_v(string path, string message)
{
}

size_t Cl_coffeMachine::getClassNumber()
{
	return 1;
}


//Запуск объекта приложения
int Cl_coffeMachine::runMachine()
{
	this->setReadiness(1);

	this->realizeEmit("SYSTEM_START");

	return 0;
}

