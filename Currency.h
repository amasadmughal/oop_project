#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;

//class Currency

class Currency 
{
private:
	float rate_wrt_USD;				//currency's rates w.r.t USD
	string Currency_name;			//currency's name
	string OBV;						//currency's obrivations
	float ConvertedAmount;			//the resultant amount that will we give user after conversion
	string CurrencyName[21];		//string array to store currency names and obrivations that would be fetched from file
	string CurrencyOBV[21];			//string array to store currency names and obrivations that would be fetched from file
	float CurrencyRates[21];		//string array to store currency rates that would be fetched from file
public:
	//constructors
	Currency();
	Currency(string, string, float);

	void setConvertedAmount(string&, string&, float&);

	//getters
	double getRate_wrt_USD();
	string getOBV();
	string getCurrencyName();
	string getConvertedAmount();

	//functions
	string displayMenuCurrency();
	void displayCurrency();
	void checkCurrencyName(string& choice);
	//destructor
	//	~Currency();

};





Currency::Currency()
{
	//default constructor
	//in this constructor, all the data from currency file
	//[name,obv,rate] , will be fetched and stored in arrays

	//Reading data from file
	ifstream inputfile;
	inputfile.open("Currency.csv");
	string name, obv;
	for (int i = 0; i < 21; i++)
	{
		getline(inputfile, name, ',');		//fetching currencyname
		getline(inputfile, obv, ',');		//fetching obbrevations
		inputfile >> CurrencyRates[i];		//fetching rates
		CurrencyName[i] = name;
		CurrencyOBV[i] = obv;
	}
	//closing the file
	inputfile.close();

}

//getters
string Currency::getOBV()
{
	return OBV;
}
double Currency::getRate_wrt_USD()
{
	return rate_wrt_USD;
}
string Currency::getCurrencyName()
{
	return Currency_name;
}

void Currency::setConvertedAmount(string& currency1, string& currency2, float& amount)
{
	//the most important function...
	//in this function, currency will be conerted


	//taking input for both currenies name
	system("cls");
	cout << "Type the currency from which you want to convert.." << endl << endl;
	currency1 = displayMenuCurrency();
	cout << "*******************************************************************************" << endl;
	
	system("cls");
	cout << "Choose the currency to which you want result.." << endl << endl;
	currency2 = displayMenuCurrency();
	system("cls");

	//taking user input for amount
	cout << "\n*******************************************************************************" << endl;
	cout << "\n\n\tEnter the amount: ";
	cin >> amount;
	cout << "\n\n*******************************************************************************" << endl;


	string currency1_name;
	float currency1_rate;

	//assigning rate and name of the currency that is given to converted, with
	//the hellp of symbol

	for (int i = 0; i < 21; i++)
	{
		if (CurrencyOBV[i] == currency1)
		{
			currency1_rate = CurrencyRates[i];
			currency1_name = CurrencyName[i];
			break;
		}
	}



	//assigning rate and name to the currency that is the resultant, with
	//the hellp of symbol
	for (int i = 0; i < 21; i++)
	{
		if (CurrencyOBV[i] == currency2)
		{
			//assigning to private data member
			this->rate_wrt_USD = CurrencyRates[i];
			this->Currency_name = CurrencyName[i];
			this->OBV = currency2;
			break;
		}
	}
	//.....formula used for converision....
	/*
	example....
	currency 1=Omani rial
	currency2=PKR
	amount=40
	converting_to_dollar = amount is divided by the rate of PKR against USD [which is suppose 160pkr for a dollar]
	// //  //  //  //  // = 40/0.0062         [0.0062=1/160]
	convertedamount=converting_to_dollar is being multiuplied by omani rial's rate against USD

	*/


	//now actual opeartion of conversion
	float convereting_to_dollar;

	//converting the given currency amount to US dollar
	//dividing the given amount with the resultant currency rate_wrt_USD
	convereting_to_dollar = amount / rate_wrt_USD;

	//now multiplyong to the given currency rate_wrt_USD
	//converting to required currency
	ConvertedAmount = convereting_to_dollar * currency1_rate;

	for (int i = 0; i < 100; i += 5)
	{
		system("cls");
		cout << "Loading " << i << " %";
		if (i == 95)
			system("cls");
	}
	cout << "\n\n*******************************************************************************" << endl << endl;
	cout << setprecision(3)<< "\n\t\tYour " << amount << " " << currency1 << " = "<< setprecision(3) << ConvertedAmount << " in " << OBV << "\n" << endl;
	cout << "\n*******************************************************************************" << endl;
	system("pause");
}

void Currency::checkCurrencyName(string& choice)
{
	//this function will validate user input for currency OBV

	bool choicecheck = false;
	for (int i = 0; i < choice.length(); i++)
	{
		choice[i] = toupper(choice[i]);
	}

	//checking if the user have typed correct input or not
	while (choice.length() != 3)
	{
		cout << "Input must be only of 3 characters [Example \"PKR\"]";
		cout << "\nyour choice: ";
		cin >> choice;
	}
	int i = 0;
	while (choicecheck == false && i < 21)
	{
		//total currencies are 21
		if (CurrencyOBV[i] == choice)
		{
			//if input matches with any of 21 currencies, loop will be break
			choicecheck = true;
			break;
		}
		else
		{
			choicecheck = false;
		}
		if (i == 20)
		{
			//if all currencies have checked, user will be once again asked for input
			i = -1;
			cout << "Kindly type input for availibe Currencies [Example \"PKR\"]";
			cout << "\nyour choice: ";
			cin >> choice;

			for (int j = 0; j < choice.length(); j++)
			{
				choice[j] = toupper(choice[j]);
			}
		}

		i++;
	}
}

//extra
void Currency::displayCurrency()
{
	cout << rate_wrt_USD << " " << "\b" << Currency_name << " " << OBV;
}

string Currency::displayMenuCurrency()
{
	//this function will display the list of availible currency and will also take input for currency

	string currency;
//	system("cls");
	cout << "*******************************************************************************" << endl;
	cout << "Note: Type the abbrevations..." << endl;
	cout << "Example: for Paksitani currency press type PKR" << endl;
	cout << "*******************************************************************************" << endl;


	bool choicecheck = false;
	string choice;

	//displaying list of all currency
	for (int i = 0; i < 21; i++)
	{
		cout << CurrencyName[i] << " (";

		cout << CurrencyOBV[i] << ")\t\t\t";
	}

	cout << "\n\nYour choice: ";
	cin >> currency;
	checkCurrencyName(currency);
	system("cls");
	return currency;

}
