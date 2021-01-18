#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;

//class LoginSignup
/*
this class will be used for login/signup.
in main function, we will ask user to login/signup and
then according to choice,function will be execute and
valuess will be set through setters,and the destructor
or logout function will be used for logout purpose.
*/


class LoginSignup
{
private:
	string name;
	string password;
	string fav_currencies[5];
public:
	LoginSignup();

	//setters
	//not used
	void setName(string);
	void setPassword(string);

	//getters
	string getName();
	string getPassword();
	void getFav();


	//functions	
	bool Login();							//this function will handle the login

	void SignUp();							//this function will handle the signup

	void PasswordValidation(string&);		//used at the time of signup and will handle the password validation section

	bool usernameValidation(string&);		//used at the time of signup and will handle the validation for username

	int displayUserInfo();					//here we display user's info that will be used for currenct session

	int logout();							//we can simply show a good bye msg or we can skip this and used 
											//destructos for this purpose

	void exit();							//this function will simply display the good bye greetings


	int welcome();

	//destructor
	~LoginSignup();
};

LoginSignup::LoginSignup()
{
	//default constructor
	name = "";
	password = "";

	//top/last used 3 currencies will be stores as fav/top currencies of user
	for (int i = 0; i < 5; i++)
	{
		fav_currencies[i] = "NULL";
	}
}
//getters
string LoginSignup::getName()
{
	return name;
}
string LoginSignup::getPassword()
{
	return password;
}
void LoginSignup::getFav()
{
	int i;
	bool exist=false;
	for (i = 0; i < 5; i++)
	{
		for(int j=0;j<i;j++)
		{
			if(fav_currencies[i]==fav_currencies[j])
			exist=true;
		}
		if(fav_currencies[i]=="NULL")
		{
			cout<<"---\n";
		}
		if(exist==false && fav_currencies[i]!="NULL")
			cout << fav_currencies[i] << endl;
	}
	cout << "\b";
}

//functions
int LoginSignup::welcome()						//A welcome screen along with choice of input
{
	bool loginconfirm=false;
	int input;
	system("cls");
	//cout << "*******************************************************************************" << endl;
	cout << "\n\t\t\tWELCOME!\n" << endl;
	cout << "*******************************************************************************" << endl;
	cout << "\n\t->  Enter 1 for login\n\n\t->  Enter 2 for signup\n\n\t->  Enter 3 for exit\n" << endl;
	cin >> input;

	//input validation
	while (input < 1 || input>3)
	{
		cout << "Invalid Choice!\n" << endl;
		cout << "\t->  Enter 1 for login\n\n\t->  Enter 2 for signup\n\n\t->  Enter 3 for Exit" << endl;
		cin >> input;
	}
	cout << "*******************************************************************************" << endl;

	//deciding on input, login,signup function will execute		
	if (input == 1)
	{
		while (loginconfirm == false)
		{
			//by-default loginconfim will be false

			//checking if login is confirmed or not
			loginconfirm = this->Login();
			cout << "*******************************************************************************" << endl;
			if (loginconfirm == true)
			{
				//cout<<endl;
				//cout << "*******************************************************************************" << endl;
			}

			else
			{
				//user wil be direct here if username is not exist in file
				int loginchoice;
				cout << "Record not found" << endl;
				cout << "Looks like you have done some mistake in typing your username..." << endl;
				cout << "\n1. Want to try again\n";
				cout << "2. Go to Signup Page\n";
				cout << "Your choice: ";
				cin >> loginchoice;
				while (loginchoice < 1 || loginchoice>2)
				{
					cout << "Error in input!!...\n";
					cout << "\n1. Want to try again\n";
					cout << "2. Go to Signup Page\n";
					cout << "Your choice: ";
					cin >> loginchoice;
				}
				if (loginchoice == 1)
				{
					//if user press 1, user will be adirected to login section [start of loop]
					loginconfirm = false;
				}
				else
				{
					//if user press 2, user will be directed to signup section
					SignUp();
					loginconfirm = true;
				}

			}
		}
	}
	else if (input == 2)
	{
		//to signup function
		SignUp();
	}
	else
	{
		//	if user press 3, then the value will be reutrned in main()
		//	and 'exit()' will be execute
		return input;
	}

}


bool LoginSignup::Login()
{
	// this function will display some text before and then will take username,password
	//for login purpose
	system("cls");
	cin.ignore();
	cout << "*******************************************************************************" << endl;
	cout << "\n\t\tLogin here" << endl;


	bool namecheck = false, passcheck = false;		//check for username,password
	//taking user input
	string name, pass;
	cout << "\n\t\tUsername: ";
	getline(cin, name, '\n');
	cout << "\t\tPassword: ";
	getline(cin, pass, '\n');

	//userinput ends here

	//this loop will convert user input into smaller case, [by-default]
	for (int i = 0; i < name.length(); i++)
		name[i] = tolower(name[i]);

	//matching username,password from file

	//opening file
	ifstream inputfile;
	inputfile.open("profile.txt");

	//variable for fetching data from file
	string file_name, file_password, fav[5];
	string fav2;
	//loop begin until eof
	while (!inputfile.eof())
	{

		//checking from file	
		getline(inputfile, file_name, ',');			//fetching username

		getline(inputfile, file_password, ',');  	//fecthing password


		//fetching fav currencies
		for (int i = 0; i < 5; i++)
		{
			getline(inputfile, fav[i], ',');
		}
		getline(inputfile, fav2, '\n');

		//checking if the 'username' have present in the file	
		if (file_name == name)
		{
			//namecheck will be turn true, if name matches
			namecheck = true;

			//checking if password also matches or not
			if (file_password == pass)
			{
				//loop will be break if password matches
				passcheck = true;
				break;
			}
			else
			{
				//user will be given 3 attempts for password

				int forgot = 1;
				cout<<"Your password doesn't matches..\n";
				cout << "\n\nYou have three attempts to re-type your password...\n";
				while (forgot < 4)
				{

					cout << "\nAttempt number " << forgot << "...\n";

					cout << "Password: ";
					getline(cin, pass, '\n');

					//checking if user has type the correct password or not
					if (file_password == pass)
					{
						//if user typed correct password then
						//loop will be break
						passcheck = true;
						break;
					}

					else
					{
						//else loop will continue
						forgot++;
						cout << "Wrong password....\nTry again\n";
					}


				}
				//taking new password from user in case they have 
				//forgot their password

				//forgot password section//
				if (passcheck != true)
				{
					system("cls");
					cout << "*******************************************************************************" << endl;
					cout << "\n\t*******Forgot password section*********\n\n";
					cout << "*******************************************************************************" << endl;
					cout << "\nType your new password\n";
					cout << "Password: ";
					getline(cin, pass, '\n');
					PasswordValidation(pass);
					passcheck = true;
				}



			}
			passcheck = true;
			break;
		}
	}
	if (namecheck == true && passcheck == true)
	{
		//asigning values to data members
		this->name = name;
		this->password = pass;
		for (int i = 0; i < 5; i++)
			this->fav_currencies[i] = fav[i];

		for (int i = 0; i < 100; i += 5)
		{
			system("cls");
			cout << "Loading " << i << " %";
			if (i == 95)
				system("cls");
		}
		cout << "\n\tLogin Sucessful...\n\n";
		cout << "*******************************************************************************" << endl;
		system("pause");
		system("cls");

		return true;

	}
	else
	{
		//	cout<<"Record not found...\n";
		return false;
	}

	//closing the file
	inputfile.close();

}

void LoginSignup::SignUp()
{
	//this is signup function

	system("cls");
	cout << "*******************************************************************************" << endl;
	cin.ignore();
	string fav = "NULL";
	cout << "\n\t\tEnter your name without space & in lower case\n";

	string names, pass;
	bool namecheck = false;
	cout << "\n\t\tUsername: ";
	getline(cin, names, '\n');

	//converting given username to lower
	//->this is a built-in function for our program

	for (int i = 0; i < names.length(); i++)
	{
		names[i] = tolower(names[i]);
	}

	//space validation for name
	for (int i = 0; i < names.length(); i++)
	{
		if (names[i] == ' ')
		{
			cout << "\n\t\tWrite a name without space\n";
			cout << "\t\tUsername: ";
			getline(cin, names, '\n');
		}
	}

	//putting validation if the same name exist or not already
	namecheck = usernameValidation(names);

	while (namecheck == false)
	{
		system("cls");
		cout << "*******************************************************************************" << endl;
		cout << "\tUsername already exits!!\n\t\tUsername: ";
		cout << "\n*******************************************************************************" << endl;
		getline(cin, names, '\n');
		namecheck = usernameValidation(names);
	}

	//validation ends...
	for (int i = 0; i < 100; i += 5)
	{
		system("cls");
		cout << "Loading " << i << " %";
		if (i == 95)
			system("cls");
	}

	//displaying confirmation msg for username
	if (namecheck == true)
	{
		//system("cls");
		cout << "*******************************************************************************" << endl;
		cout << "\tUsername Confirmed...."<<endl;
		cout << "*******************************************************************************" << endl;
	}	



	//taking password*//
	cout << "\n\n\t\tEnter Password \n[Example asad1234 OR 12345678] : ";
	getline(cin, pass, '\n');

	//password validaton
	PasswordValidation(pass);

	system("cls");
	for (int i = 0; i < 100; i+=5)
	{
		system("cls");
		cout << "Loading " << i << " %";
		if (i == 95)
		system("cls");
	}
	cout << "*******************************************************************************" << endl;
	cout << "Signup Succesfull\n";
	cout << "*******************************************************************************" << endl;	
	this->name = names;
	this->password = pass;

	cout << "\n\t\tUsername: " << getName() << endl;
	cout << "\t\tPassword: " << getPassword() << endl;

	cout << "\nRemember this credentials!!!!\n\n\n";
	cout << "\n\n*******************************************************************************" << endl;
	system("pause");
	system("cls");
	//setting fav currencies to NULL by default
	for (int i = 0; i < 5; i++)
		this->fav_currencies[i] = "NULL";

	cout << "*******************************************************************************" << endl;
	//sending data to file
	ofstream file;
	file.open("profile.txt", ios::app);
	file << names << "," << pass << ",";
	//  file<<"\n" << names << "," << pass << "," << "NULL" << "," << "NULL"<<","<<"NULL"<<","<<"\n";
	for (int i = 0; i < 3; i++)
	{
		file << "NULL" << ",";
	}
	file << "\n";

	//closing file after sending data of new user
	file.close();
}

void LoginSignup::exit()
{
	//this function will simply display the good bye greetings
	system("cls");
	cout << "\n\n\tThankyou for using our calculator...\n";
	cout << "\tHope you enjoyed our app, we are working on Beta system\n";
	cout << "\tNeed your support..." << endl << endl;
	cout << "\n\n\n*******************************************************************************" << endl;
}
int LoginSignup::logout()
{
	//this function will execute once the user have used the calculator
	//this will ask user wheather if he/she want to use calculator again or want to logout

	int choice;
	cout << "\n*******************************************************************************" << endl;
	cout << "1. Go to calculaor again" << endl;
	cout << "2. Logout" << endl;
	cout << "\nyour choice: ";
	cin >> choice;
	while (choice < 1 || choice > 2)
	{
		cout << "There was an error in your input. Type again..." << endl;
		cout << "1. Go to calculator again" << endl;
		cout << "2. Logout" << endl;
		cout << "your choice: ";
		cin >> choice;
	}
	//if user choose logout, this msg will be display and user will be retur to main page
	//will be done by returning value to main()

	if (choice == 2)
	{
		system("cls");
		cout << "*******************************************************************************" << endl;
		cout << "\n\n\t\tLogout successfully...\n" << endl;
		cout << "*******************************************************************************" << endl;
		system("pause");
	}
	else
	{
		//is user ant to use want to use calculator again, then this value will be returned to main
		return choice;
	}


}

//validations function
void LoginSignup::PasswordValidation(string& pass)
{
	//this function will validate password input at Signup time

		//length validation start
	while (pass.length() < 8)
	{
		cout << "Password must be 8 characters long [example asad123@]\n";
		cout << "password : ";
		getline(cin, pass, '\n');
	}
	//length validation ends

	//white space validation starts
	for (int i = 0; i < pass.length(); i++)
	{
		if (pass[i] == ' ')
		{
			cout << "\nPassword must be without spaces [example 12345678 or asad6214]\n";
			cout << "Password: ";
			getline(cin, pass, '\n');
		}
	}
	//white space validation ends


	//password validation complete//


}

bool LoginSignup::usernameValidation(string& name)
{
	//this function handles the validation at the 
	//signup time. it will check if the username already exist or not

	//this will return true if name don't exist and vice versa

	string file_name, pass, go;
	ifstream inputfile;
	bool check = true;
	inputfile.open("profile.txt");
	while (!inputfile.eof())
	{
		getline(inputfile, file_name, ',');
		getline(inputfile, go, '\n');
		cout << endl;
		if (file_name == name)
		{
			//if name exist already, loop will be break and it will return false
			check = false;
			inputfile.close();
			break;
		}
	}
	inputfile.close();
	return check;
}

int LoginSignup::displayUserInfo()
{
	int choice1 = 0;
	cout << "\t\tWelcome " << getName() << endl;
	cout << "*******************************************************************************" << endl;
	cout << "\nFav currencies: " << endl << endl;
	getFav();
	cout << endl;
	cout << "*******************************************************************************" << endl;
	cout << "1. Proceed to Calculator" << endl;
	cout << "2. Logout" << endl;
	cin >> choice1;
	while (choice1 < 1 || choice1>2)
	{
		cout << "Invalid entry!\n1. Proceed to calculator" << endl;
		cout << "2. Logout" << endl;
		cin >> choice1;
	}
	return choice1;

}
LoginSignup::~LoginSignup()
{
	name = "NULL";
	password = "NULL";
}

