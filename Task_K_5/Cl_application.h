#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H

#include  "Cl_base.h"

class Cl_application : public Cl_base {
public:
	//Конструктор
	Cl_application(Cl_base* parentPtr = nullptr);

	//Запуск этапа ввода для построения дерева
	void buildTree();

	//Запуск этапа ввода для установки готовностей объектов
	void enterReadiness();

	//Запуск этапа ввода для установки связей между объектами
	void enterConnections();

	//Запуск этапа ввода для осуществления манипуляций над объектами при помощи команд
	void enterCommands();

	//Запуск объекта приложения
	int execApp();

};

#endif



