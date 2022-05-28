#ifndef CL_COFFEMAKER_H
#define CL_COFFEMAKER_H

#include "Cl_base.h"
#include "Cl_coffeMachine.h"

class Cl_coffemaker :
	public Cl_base
{
private:

	// Структура с информацией о связи сорт-цена
	struct coffeInfo
	{
		string name_;
		size_t price_;
		
		coffeInfo(string name = "", size_t price = 0)
		{
			price_ = price;
			name_ = name;
		}
	};

	vector<coffeInfo> coffeInMachine;

	int coffeTypesNumber = -1;
	vector<string> coffeTypesNames;

public:

	Cl_coffemaker(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path, string message) override
	{
		cout << message;
		this->realizeEmit("Ready to work");
	}


	void handler_v(string path, string message) override
	{
		if ((dynamic_cast<Cl_coffeMachine*>(this->getHeadPtr()))->getStatusCoffeLoad())
		{
			if (coffeTypesNumber == -1)
			{
				size_t delimeterPosition = 0;
				while ((delimeterPosition = message.find(" ")) != string::npos) 
				{
					if (coffeTypesNumber == -1)
					{
						coffeTypesNumber = stoi(message.substr(0, delimeterPosition));
					}
					else
					{
						coffeTypesNames.push_back(message.substr(0, delimeterPosition));
					}
					message.erase(0, delimeterPosition + 1);
				}
				coffeTypesNames.push_back(message.substr(0, message.size() - 1));

			}
			else
			{
				size_t delimeterPosition = 0;
				string token = "";
				while ((delimeterPosition = message.find(" ")) != string::npos) 
				{
					token = message.substr(0, delimeterPosition + 1);
					if (token == "SYSTEM_COFFE")
					{
						message.erase(0, message.find(" ") + 1);
						cout << "Take the coffe " << message << '\n';
					}
					else
					{
						return;
					}
				}
			}
		}
		else
		{
			size_t delimiterPosition = message.find(" ");
			if (delimiterPosition != string::npos)
			{
				string token = message.substr(0, delimiterPosition);
				if (token == "SYSTEM_MAKE_COFFE")
				{
					message.erase(0, delimiterPosition + 1);
					this->realizeEmit("Take the coffee " + message);
				}
			}
		}
	}


	size_t getClassNumber()
	{
		return 6;
	}
};

#endif