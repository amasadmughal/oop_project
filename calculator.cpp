#include<iostream>
#include<string>
#include<fstream>
#include"login.h"
#include"Currency.h"
#include"Profile.h"
using namespace std;


int main()
{
	int choice = 2, choicecal;
	int input;
	bool loginconfirm;
	LoginSignup login;
	int choice2;
	Currency c;
	string currency1, currency2;
	float amount;
	
	//loop to begin the program
	while (choice == 2)
	{
		//this function will handle login,singup
		input = login.welcome();
		if (input == 3)
		{
			break;
		}
		choicecal = login.displayUserInfo();
		if (choicecal == 1)
		{
			do
			{
				//currency converter
				c.setConvertedAmount(currency1, currency2, amount);
			
				//making/upgrading profile
				Profile p(currency1, currency2, login.getName());

				//logout or again use calculator
				choice2 = login.logout();

			} while (choice2 == 1);
			{

			}

		}

	}
	login.exit();
	system("pause");

}
