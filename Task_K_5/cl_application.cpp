
#include "Cl_application.h"
#include "Cl_branch.h"
#include "Cl_branch_2.h"
#include "Cl_branch_3.h"
#include "Cl_branch_4.h"
#include "Cl_branch_5.h"


//Конструктор
Cl_application::Cl_application(Cl_base* parentPtr)
{
	//Использование сетеров обусловленно закрытостью полей
	Cl_base::root->setParent(parentPtr);
	Cl_base::root->setName("sys_root");
	Cl_base::root->setReadiness(1);
}


//Запуск этапа ввода для построения дерева
void Cl_application::buildTree()
{
	string headName = "", childName = "", path = "";
	int classNumber;

	cin >> headName;

	// Головной объект
	Cl_base* head = new Cl_base(headName);

	cin >> path;
	while (path != "endtree")
	{
		cin >> childName >> classNumber;

		Cl_base* currentParentPtr = root->childrenList.front()->getObjectByPath(path);

		//Досрочное завершение работы программы
		//если на этапе построения системы объектов возникла ошибка.
		if (currentParentPtr == nullptr)
		{
			cout << "Object tree";
			root->childrenList.front()->printTree(false);
			cout << "\nThe head object " << path << " is not found";

			exit(1);
		}

		// Создание дочернего объекта определённого класса
		// определяемого введённым номером
		switch (classNumber)
		{
		case 2:
		{
			Cl_base* child = new Cl_branch(childName, currentParentPtr);
			break;
		}

		case 3:
		{
			Cl_base* child = new Cl_branch_2(childName, currentParentPtr);
			break;
		}

		case 4:
		{
			Cl_base* child = new Cl_branch_3(childName, currentParentPtr);
			break;
		}

		case 5:
		{
			Cl_base* child = new Cl_branch_4(childName, currentParentPtr);
			break;
		}

		case 6:
		{
			Cl_base* child = new Cl_branch_5(childName, currentParentPtr);
			break;
		}

		}

		cin >> path;
	}

	enterConnections();

	return;
}


//Запуск этапа ввода для установки готовностей объектов
void Cl_application::enterReadiness()
{
	string objectName;
	long long numericReadiness;
	while (cin >> objectName >> numericReadiness)
	{
		(root->getObjectByName(objectName))->setReadiness(numericReadiness);
	}
}


//Запуск этапа ввода для установки связей между объектами
void Cl_application::enterConnections()
{
	string signalPath, handlerPath;
	cin >> signalPath;
	while (signalPath != "end_of_connections")
	{
		cin >> handlerPath;

		Cl_base* firstObjectPtr = root->childrenList.front()->getObjectByPath(signalPath);
		Cl_base* secondObjectPtr = root->childrenList.front()->getObjectByPath(handlerPath);

		firstObjectPtr->realizeConnection(firstObjectPtr, secondObjectPtr);

		cin >> signalPath;
	}
}


//Запуск этапа ввода для осуществления манипуляций над объектами при помощи команд
void Cl_application::enterCommands()
{
	Cl_base* setedObjectPtr = root->childrenList.front();
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
			tempObjectPtr = root->childrenList.front()->getObjectByPath(path);

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
			tempObjectPtr = root->childrenList.front()->getObjectByPath(connectPath);

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


//Запуск объекта приложения
int Cl_application::execApp()
{
	// Вывод построенного дерева;
	cout << "Object tree";
	root->childrenList.front()->printTree(false);

	//Запуск навигации по дереву
	this->enterCommands();

	return 0;
}
