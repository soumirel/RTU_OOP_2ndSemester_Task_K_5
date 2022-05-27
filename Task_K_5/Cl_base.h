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
private:
	// Имя объекта
	string objectName = "";

	// Указатель на родителя объекта
	Cl_base* parentPtr = nullptr;

	// Состояние готовности объекта
	bool readiness = true;

	// Структура информации о связи объектов
	struct connectionInfo
	{
		TYPE_SIGNAL signalPtr;
		Cl_base* objectPtr;
		TYPE_HANDLER handlerPtr;
	};

	// Вектор информаций о соединениях
	vector<connectionInfo*> connections;

public:
	// Объект root - "родитель" всех объектов
	static Cl_base* root;

	// Вектор указателей дочерних объектов
	vector<Cl_base*> childrenList;

	// Конструкторы
	Cl_base() { parentPtr = nullptr; };
	Cl_base(string objectName, Cl_base* parentPtr = nullptr);

	// Сетеры
	void setName(string objectName);
	void setParent(Cl_base* parentPtr);
	void setReadiness(long long numericReadiness);

	// Гетеры
	Cl_base* getParent();
	string getName();
	bool getReadiness();
	virtual size_t getClassNumber();

	// Виртуальный метод сигнала и обработчика
	virtual void signal_v(string path);
	virtual void handler_v(string path, string message);

	// Получение указателя на объект через его имя
	Cl_base* getObjectByName(string name);

	//Получение указателя на объект через заданный путь
	Cl_base* getObjectByPath(string path);

	// Получение абс.координаты до объекта
	string getAbsPath();

	// Установщик связи
	void setConnection(TYPE_SIGNAL signalPtr, Cl_base* objectPtr,
		TYPE_HANDLER handlerPtr);

	// Метод разрыва связи
	void deleteConnection(TYPE_SIGNAL signalPtr, Cl_base* objectPtr,
		TYPE_HANDLER handlerPtr);

	// Запуск обработки сигнала
	void emitSignal(TYPE_SIGNAL signalPtr, string& message);

	// Посредник установки связи между объектами
	void realizeConnection(Cl_base* firstObjectPtr, Cl_base* secondObjectPtr);

	// Посредник передатчика сигнала
	void realizeEmit(string message);

	// Посредник удаления связи
	void removeConnection(Cl_base* firstObjectPtr, Cl_base* secondObjectPtr);

	// Вывод дерева объектов
	void printTree(bool isPrintReadiness, unsigned tabLevel = 0);

};

#endif