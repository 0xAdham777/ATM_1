#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string PhoneNumber;
	double AccountBalance;
};

stClient Client;
const string FileName = "Clients.txt";
const short QuickWithdrauValue[] = {20,50,100,200,400,600,800,1000};

enum enAtmPermison 
{
	enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3,
	enCheakBalnce = 4, enLogout = 5
};

void ATM_Skrean();
void  Lanch_ATM_System_Login_Skrean();
vector <stClient> LoadClientDateFromeFaile(string FileName);

void ClearSkrean()
{
	system("color 0F");
	system("cls");
}

void GoBackToATM_Skrean()
{
	cout << "\nPreass Any Key To Go Back To ATM Skrean..." << endl;
	system("pause>0");
	ATM_Skrean();
}

void  PrintSheakBalnceSkrean()
{
	cout << "\n=======================================" << endl; 
	cout << "\n          Cheak Balenc Skrean          " << endl; 
	cout << "\n=======================================" << endl;
	cout << "\n Your Balenc is : " << Client.AccountBalance << endl;
	cout << "\n=======================================" << endl;

}

void CheakBalnceSkrean()
{
	system("color 2F");
	PrintSheakBalnceSkrean();

}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{

	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.PhoneNumber + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;

}

vector <stClient> SaveCleintsDataToFile(string FileName, vector <stClient> vClients)
{

	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string DataLine;

	if (MyFile.is_open())
	{

		for (stClient C : vClients)
		{

			if (C.AccountNumber == Client.AccountNumber)
			{

				DataLine = ConvertRecordToLine(Client);
				MyFile << DataLine << endl;

			}
			else
			{
				MyFile << DataLine << endl;
			}

		}

		MyFile.close();

	}

	return vClients;

}

void Withdraw(vector <stClient> vclients, int Mony_Of_Withdraw)
{
	if ((Client.AccountBalance - Mony_Of_Withdraw) < 0)
	{
		cout << "\nErro Withdraw , your mony it is not enough " << endl;
		system("color 4F");
	}
	else
	{

		for (stClient client : vclients)
		{

			if (client.AccountNumber == Client.AccountNumber)
			{
				Client.AccountBalance -= Mony_Of_Withdraw;
			}
		}

		SaveCleintsDataToFile(FileName, vclients);
		cout << "\nDone Secssufely , Your Account Balenc is " 
			<< Client.AccountBalance << endl;;
		system("color 2F");
	}
}

void Withdraw_Takid(int Mony_Of_Withdraw)
{

	vector <stClient> vclients = LoadClientDateFromeFaile(FileName);
	char Answer = 'N';

	cout << "Are you Sure you Want To Perform this transaction  ? Y/N ?\n";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{
		Withdraw(vclients, Mony_Of_Withdraw);
	}
	else
	{
		cout << endl <<  "Ok You Calnled This operastion " << endl;
		system("color 4F");
	}
	


}

short ReadQwikWithDraw_Choise()
{

	short Choice = 0;
	do
	{

		cout << "Pleas Enter What To do You want ? [1 to 9] ? ";
		cin >> Choice;

	} while ((Choice > 9 || Choice < 1));

	return Choice;
}

void PrintQuickWithdrawSkrean()
{

	cout << "=======================================" << endl;
	cout << "          Quick Withdraw Skrean        " << endl;
	cout << "=======================================" << endl;
	cout << "       [1] 20          [2] 50          " << endl;
	cout << "       [3] 100         [4] 200         " << endl;
	cout << "       [5] 400         [6] 600         " << endl;
	cout << "       [7] 800         [8] 1000        " << endl;
	cout << "       [9] Exit                        " << endl;
	cout << "=======================================" << endl;

	cout << "\nYour Balence Is : " << Client.AccountBalance << endl;


}

void QuickWithdrawSkrean()
{
	PrintQuickWithdrawSkrean();
	
	short Choice = ReadQwikWithDraw_Choise();

	if (Choice == 9)
	{
		ATM_Skrean();
	}
	else
	{
		
		Withdraw_Takid(QuickWithdrauValue[Choice-1]);
	}

}

int ReadAmounth_Multiple_Of_5()
{
	int Amounth = 0;
	do
	{
		cout << "\Enter an amonth multiple of 5 ?  ";
		cin >> Amounth;
	} while ((!((Amounth % 5) ==0)) || Amounth < 0);
	return Amounth;
}

int ReadDeposit()
{
	int Amounth = 0;
	do
	{
		cout << "\Enter an amonth you Want Deposit ?  ";
		cin >> Amounth;
	} while (Amounth < 0);
	return Amounth;
}

void NOrmalWithDrawSkrea()
{
	cout << "==========================================" << endl;
	cout << "           Normal WithDraw Screan         " << endl;
	cout << "==========================================" << endl;

	int Amounth = ReadAmounth_Multiple_Of_5();

	Withdraw_Takid(Amounth);
}

void DepositSkrean()
{
	cout << "==========================================" << endl;
	cout << "           Normal Deposit Screan         " << endl;
	cout << "==========================================" << endl;

	int Amounth = ReadDeposit();

	Withdraw_Takid(Amounth*-1);
}

short ReadATM_Choise()
{

	short Choice = 0;
	do
	{

		cout << "Pleas Enter What To do You want ? [1 to 5] ? ";
		cin >> Choice;

	} while ((Choice > 5 || Choice < 1));

	return Choice;
}

void Lanch_ATM(enAtmPermison Permisonch)
{
	switch (Permisonch)
	{
	  case enAtmPermison::enQuickWithdraw:
	  {
		  ClearSkrean();
		  QuickWithdrawSkrean();
		  GoBackToATM_Skrean();
	  }
	  case enAtmPermison::enNormalWithdraw:
	  {
		  ClearSkrean();
		  NOrmalWithDrawSkrea();
		  GoBackToATM_Skrean();
	  }
	  case enAtmPermison::enDeposit:
	  {
		  ClearSkrean();
		  DepositSkrean();
		  GoBackToATM_Skrean();
	  }
	  case enAtmPermison::enCheakBalnce:
	  {
		  ClearSkrean();
		  CheakBalnceSkrean();
		  GoBackToATM_Skrean();
	  }
	  case enAtmPermison::enLogout:
	  {
		  ClearSkrean();
		  Lanch_ATM_System_Login_Skrean();
	  }
	}
}

void ATM_Skrean()
{
	ClearSkrean();


	cout << "============================================" << endl; 
	cout << "             ATM  Main Menu Screen          " << endl;
	cout << "============================================" << endl;
	cout << "         [1] Quick  Withdraw .               " << endl;
	cout << "         [2] Normal Withdraw .               " << endl;
	cout << "         [3] Deposit         .               " << endl;
	cout << "         [4] Chaeck  Balance .               " << endl;
	cout << "         [5] Log      Out    .               " << endl;
	cout << "============================================" << endl;


	Lanch_ATM((enAtmPermison)ReadATM_Choise());


}

vector<string> SplitString(string S1, string Delim = "#//#")
{

	vector<string> vString;

	short pos = 0;
	string sWord; // define a string variable  

	// use find() function to get the position of the delimiters  
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word   
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
	}

	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}

	return vString;

}

stClient ConvertLinetoRecord(string Line)
{
	stClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.PhoneNumber = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string to double


	return Client;
}

vector <stClient> LoadClientDateFromeFaile(string FileName)
{
	vector <stClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{

		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertLinetoRecord(Line);

			vClients.push_back(Client);
		}

		MyFile.close();

	}

	return vClients;
}

bool FinClientByAccountNumber_And_PinCode(stClient &client)
{
	vector <stClient> vClient = LoadClientDateFromeFaile(FileName);


	for (stClient cclient : vClient)
	{
		if (cclient.AccountNumber == client.AccountNumber && cclient.PinCode == client.PinCode)
		{
			client = cclient;
			return true;
		}

	}
	return false;
}

stClient ReadClientInfoForLogine()
{
	stClient client;
	
	cout << "\nPleas Entar Your Account Number ? ";
	getline(cin >> ws, client.AccountNumber);

	cout << "\nPleas Entar Your Pin Code ? ";
	getline(cin >> ws, client.PinCode);

	return client;

}

void Lanch_ATM_System_Login_Skrean()
{
	
	bool IsExiteClient = false;

	do
	{
		ClearSkrean();

		cout << "_________________________________________" << endl;
		cout << "              Login Skrean               " << endl;
		cout << "_________________________________________" << endl;

		if (IsExiteClient)
		{
			cout << "\nInvalide Account Number / Pin code ? " << endl;
		}

		Client = ReadClientInfoForLogine();

		IsExiteClient = true;


	} while (!FinClientByAccountNumber_And_PinCode(Client));


	ATM_Skrean();

}

int main()
{
	Lanch_ATM_System_Login_Skrean();
    system("pause>0");
	return 0;
}