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

	//Переменные для расчёта количества возвращаемых монет
	size_t tennerToReturn = 0;
	size_t fiverToReturn = 0;

	//Кол-во денежных средств в автомате
	size_t actualMoney = 0;

public:

	Cl_coinsReturner(string objectName, Cl_base* parentPtr) :
		Cl_base(objectName, parentPtr) {};


	void signal_v(string path, string message) override
	{
		string label = message.substr(0, message.find(" "));
		message.erase(0, message.find(" ") + 1);

		if (label != "COINSRETURNER_CHANGE" && label != "COINSRETURNER_REFUND")
		{
			return;
		}

		string sentMessage;
		string token = message.substr(0, message.find(" "));

		if (label == "COINSRETURNER_CHANGE")
		{
			sentMessage = "Take the change: 10 * " + token;
		}
		else
		{
			sentMessage = "Take the money: 10 * " + token;
		}

		message.erase(0, message.find(" ") + 1);
		sentMessage += " rub.,  5 * " + message.substr(0, message.find(" ")) + " rub.";

		this->realizeEmit("COINSRETURNER:SCREEN_MESSAGE " + sentMessage);
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

			this->realizeEmit("COINSRETURNER:SCREEN_SAYREADY");
		}
		else if ((this->getHeadPtr()->getStatusCoffeLoad() == true) && (this->getHeadPtr()->getStatusCoinsLoad() == true))
		{
			string token = message.substr(0, message.find(" "));
			message.erase(0, message.find(" ") + 1);

			if (token == "COFFEEMAKER:COINSRETURNER_GIVECHANGE" || token == "CONTOLLER:COINSRETURNER_REFUND")
			{
				size_t moneyToReturn = 0;
				if (token == "COFFEEMAKER:COINSRETURNER_GIVECHANGE")
				{
					moneyToReturn = actualMoney - stoi(message);
				}
				else
				{
					moneyToReturn = actualMoney;
				}

				actualMoney = 0;

				while (tennerNumber > 0 && moneyToReturn >= 10)
				{
					tennerNumber--;
					tennerToReturn++;
					moneyToReturn -= 10;
				}

				fiverToReturn = moneyToReturn / 5;
				fiverNumber -= fiverToReturn;

				if (fiverToReturn != 0 || tennerToReturn != 0)
				{
					if (token == "COFFEEMAKER:COINSRETURNER_GIVECHANGE")
					{
						this->realizeEmit("COINSRETURNER_CHANGE " + to_string(tennerToReturn) + " " + to_string(fiverToReturn));
					}
					else
					{
						this->realizeEmit("COINSRETURNER_REFUND " + to_string(tennerToReturn) + " " + to_string(fiverToReturn));
					}
				}

				tennerToReturn = 0;
				fiverToReturn = 0;

				this->realizeEmit("COINSRETURNER:CASHRECEIVER_CLEARBALANCE");
			}

			if (token == "CASHRECEIVER:COINSRETURNER_CHECKCOINS")
			{
				tennerToReturn = 0;
				fiverToReturn = 0;

				size_t receivedMoney = stoi(message);

				if (receivedMoney == 10 || receivedMoney == 5)
				{
					actualMoney += receivedMoney;
					this->realizeEmit("COINSRETURNER:CASHRECEIVER_GIVEBALANCE " + to_string(receivedMoney));
				}

				if (receivedMoney == 50 || receivedMoney == 100)
				{
					size_t moneyToReturn = actualMoney + receivedMoney;

					if (fiverNumber * 5 + tennerNumber * 10 >= moneyToReturn)
					{
						this->realizeEmit("COINSRETURNER:CASHRECEIVER_GIVEBALANCE " + to_string(receivedMoney));

						actualMoney += receivedMoney;
					}
					else
					{
						this->realizeEmit("COINSRETURNER:CASHRECEIVER_RETURNBANKNOTE");
					}
				}
			}

			if (token == "CONTROLLER:COINSRETURNER_GETBALANCE")
			{
				this->realizeEmit("COINSRETURNER:CONTROLLER_GIVEBALANCE " + to_string(actualMoney));
			}
		}
	}


	size_t getClassNumber()
	{
		return 5;
	}
};

#endif