#ifndef CL_COFFEMACHINE_H
#define CL_COFFEMACHINE_H

#include  "Cl_base.h"

class Cl_coffeMachine : 
	public Cl_base 
{
private:
	//Поля-статусы загрузки в автомат кофе и сдачи
	bool statusCoffeLoad = false;
	bool statusCoinsLoad = false;

public:
	//Конструктор
	Cl_coffeMachine(string objectName = "coffeMachineObject", Cl_base* parentPtr = nullptr) :
		Cl_base(objectName, parentPtr) {};

	//Геттеры и сеттеры статусов загрузки сдачи и кофе
	bool getStatusCoffeLoad() override;
	bool getStatusCoinsLoad() override;
	void setStatusCoffeLoad(bool status) override;
	void setStatusCoinsLoad(bool status) override;

	//Сигнал и обработчик
	void signal_v(string path, string message) override;

	void handler_v(string path, string message) override;

	size_t getClassNumber() override;

	//Запуск этапа ввода для построения дерева
	void buildTree();

	//Запуск этапа ввода для установки готовностей объектов
	void enterReadiness();

	//Запуск этапа ввода для установки связей между объектами
	void enterConnections();

	//Запуск этапа ввода для осуществления манипуляций над объектами при помощи команд
	void enterCommands();

	//Запуск объекта приложения
	int runMachine();

};

#endif



