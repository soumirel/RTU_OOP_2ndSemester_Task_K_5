#ifndef CL_COINSRETURNER_H
#define CL_COINSRETURNER_H

#include "Cl_base.h"

class Cl_coinsReturner :
	public Cl_base
{
private:
	//Количество десяток и пятёрок в автомате
	size_t tennerNumber = 0;
	size_t fiverNumber = 0;

	//Кол-во денежных средств в автомате
	size_t actualMoney = 0;

public:

	Cl_coinsReturner(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path, string message) override
	{
		string token = message.substr(0, message.find(" "));
		message.erase(0, message.find(" ") + 1);
		if ((isNumber(token) == false) || (isNumber(message) == false))
		{
			return;
		}

		cout << "Take the change: 10 *  " 
			<< message.substr(0, message.find(" ") + 1);
		message.erase(0, message.find(" ") + 1);
		cout << " rub.,  5 * "
			<< message.substr(0, message.find(" ") + 1) << " rub.\n";
	}


	void handler_v(string path, string message) override
	{
		if (this->getHeadPtr()->getStatusCoffeLoad() == true
			&& this->getHeadPtr()->getStatusCoinsLoad() == false)
		{
			fiverNumber = stoi(message.substr(0, message.find(" ") + 1));
			message.erase(0, message.find(" "));
			tennerNumber = stoi(message.substr(0, message.size()));
			this->getHeadPtr()->setStatusCoinsLoad(true);
			cout << "Ready to work\n";
		} 
		else if (this->getHeadPtr()->getStatusCoffeLoad() == true 
			&& this->getHeadPtr()->getStatusCoinsLoad() == true)
		{
			string token = message.substr(0, message.find(" "));
			message.erase(0, message.find(" ") + 1);

			if (token == "SYSTEM_CHANGE")
			{
				
				size_t moneyToReturn = actualMoney - stoi(message);
				size_t tennerToReturn = moneyToReturn / 10;
				size_t fiverToReturn = moneyToReturn % 10;
				this->realizeEmit(to_string(tennerToReturn) + to_string(fiverToReturn));
			}

			if (token == "SYSTEM_REFUND")
			{
				cout << "Take the money back, no change\n";
				actualMoney = 0;
				this->realizeEmit("SYSTEM_RECEIVE 0");
			}

			if (token == "SYSTEM_CHECK_COINS")
			{
				size_t receivedMoney = stoi(message);
				size_t necessaryTenner = receivedMoney / 10;
				size_t neccessaryFiver = receivedMoney % 10;
				if (necessaryTenner <= tennerNumber && neccessaryFiver <= fiverNumber)
				{
					if (receivedMoney == 0)
					{
						actualMoney = receivedMoney;
					}
					else
					{
						actualMoney += receivedMoney;
					}
		
					this->realizeEmit("SYSTEM_RECEIVE " + to_string(receivedMoney));
				}
				else
				{
					this->realizeEmit("SYSTEM_RETURN_BANKNOTE");
				}
			}

			if (token == "SYSTEM_GET_BALANCE")
			{
				this->realizeEmit("SYSTEM_RECIVE_BALANCE " + to_string(actualMoney));
			}
		}
	}


	size_t getClassNumber()
	{
		return 5;
	}
};

#endif