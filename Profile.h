#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;

//class profile
class Profile :public LoginSignup
{
public:
	Profile();
	Profile(string c1, string c2, string name);
};


Profile::Profile(string c1, string c2, string name)
{
	string file_name, file_pass, fav[5], fav2;
	bool exist=false;
	ofstream newfile;
	ifstream oldfile;
	string usefav[5];
	//fetching data from old file
	oldfile.open("profile.txt");
	newfile.open("prof.txt");			//new file to transfer data from old to new
	
	//fetching data from old file
	while (!oldfile.eof())
	{
		getline(oldfile, file_name, ',');

		getline(oldfile, file_pass, ',');
		for(int i=0;i<5;i++)
		{
			getline(oldfile, fav[i], ',');
		}
	
		getline(oldfile, fav2, '\n');

		//the present user's data will be altered...
		
		//assigning fav currencies to a local string array
		if (file_name == name)
		{
			for (int i = 0; i < 5; i++)
			{
				usefav[i] = fav[i];			//storing data to a local array fro later use
			}
			
			//sending the recent currencies to user profile
			//the two recenty currencies will be send from here
			newfile << file_name << "," << file_pass << "," << c1 << "," << c2 << ",";

			for (int i = 0; i < 3; i++)
			{
				//and the old currenices such as on no # 3,4,5 will be send as it is
				newfile << fav[i] << ",";
			}
			newfile << "\n";

		}
		//rest will be transfer as it is
		else
		{
			newfile << file_name << "," << file_pass << ",";
		
			for (int i = 0; i < 5; i++)
			{
				newfile << fav[i] << ",";
			
			}
			newfile << "\n";
			if(oldfile.eof())
				break;
		}

	}
	//closing files
	oldfile.close();
	newfile.close();
	
	//renaming files
	remove("profile.txt");
	rename("prof.txt", "profile.txt");
	
	system("cls");
	cout << "\n\t\tUpgrading Profile......Please Wait\n\n\n";
	cout << "*******************************************************************************" << endl;
	for (int i = 0; i < 200; i++)
	{
		cout<<"\r..";
	}
	system("pause");
	system("cls");
	cout << "\n\tUpgrading Done...\n"<<endl;
	cout << "*******************************************************************************" << endl;
	system("pause");
	system("cls");
	
	//displaying profile again
	cout << "*******************************************************************************" << endl;
	cout << "\t\tWelcome " << name << endl;
	cout << "*******************************************************************************" << endl;
	cout << "\nFav currencies: " << endl << endl;
	cout << c1 << "\n" << c2 << " \n";
	
	//loop for showing currencies
	for (int i = 0; i < 3; i++)
	{
		for(int j=0;j<i;j++)
		{
			if(usefav[j]==usefav[i] || usefav[j]==c1 || usefav[j]==c2 || usefav[i]=="NULL")
			{
				exist=true;
				break;
			}
		}
		if(exist==false)
			cout << usefav[i] << "\n";
	}
		
	

}
