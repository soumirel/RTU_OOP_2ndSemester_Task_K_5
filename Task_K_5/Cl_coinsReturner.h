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

		cout << "Take the change: 10 * " 
			<< token;
		message.erase(0, message.find(" ") + 1);
		cout << " rub.,  5 * "
			<< message.substr(0, message.find(" ")) << " rub.\n";
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
				tennerNumber -= tennerToReturn;
				fiverNumber -= fiverToReturn;
				this->realizeEmit(to_string(tennerToReturn) + " " + to_string(fiverToReturn));
			}

			if (token == "SYSTEM_REFUND")
			{
				size_t moneyToReturn = actualMoney;
				size_t tennerToReturn = moneyToReturn / 10;
				size_t fiverToReturn = moneyToReturn % 10;
				tennerNumber -= tennerToReturn;
				fiverNumber -= fiverToReturn;
				this->realizeEmit(to_string(tennerToReturn) + " " + to_string(fiverToReturn));
				actualMoney = 0;
				this->realizeEmit("SYSTEM_RECEIVE 0");
			}

			if (token == "SYSTEM_CHECK_COINS")
			{
				size_t receivedMoney = stoi(message);

				if (receivedMoney == 10 || receivedMoney == 5)
				{
					if (receivedMoney == 10)
					{
						tennerNumber += 1;
					}
					else
					{
						fiverNumber += 1;
					}

					actualMoney += receivedMoney;
					this->realizeEmit("SYSTEM_RECEIVE " + to_string(receivedMoney));
				}
				
				if (receivedMoney == 50 || receivedMoney == 100)
				{
					receivedMoney += actualMoney;
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
			}

			if (token == "SYSTEM_GET_BALANCE")
			{
				this->realizeEmit("SYSTEM_RECEIVE_BALANCE " + to_string(actualMoney));
			}

			if (token == "SYSTEM_REDUCE_BALANCE")
			{
				actualMoney -= stoi(message);
				this->realizeEmit("SYSTEM_REDUCE_BALANCE_1 " + message);
			}
		}
	}


	size_t getClassNumber()
	{
		return 5;
	}
};

#endif