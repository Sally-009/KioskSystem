// Name: Saori Kojima
// Program Description: Menu System
// Date: 10/17/22

/*
NOTE:

ƒƒjƒ…[A’•¶‚Ü‚Å³í

To-Do
>> cin Error ŽÀ‘•
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// ------------CLASS---------------
class menu {

public:
	// -----CONST VALUES-----

	// RATE >> %
	const double TAX_RATE = 10;

	const double TIP_RATE01 = 18;
	const double TIP_RATE02 = 20;
	const double TIP_RATE03 = 25;


	/* -----------------
		FOR CALL (main)
	   ----------------- */

	void kiosk()
	{
		getData(appIn, "appetizers.txt", appName, appPrice, appQty);
		getData(drinkIn, "drink.txt", drinkName, drinkPrice, drinkQty);
		getData(desIn, "desert.txt", desName, desPrice, desQty);
		getData(entIn, "entree.txt", entName, entPrice, entQty);

		do
		{
			// show top menu
			topMenu();

			int choice = selectionT();

			// move to each category
			int qty = 0;
			switch (choice)
			{
			case 1:
				menuOutput("Appetizers", appName, appPrice, appQty);
				order(choice, qty, appName, appPrice, appQty);

				break;

			case 2:
				menuOutput("Drink", drinkName, drinkPrice, drinkQty);
				order(choice, qty, drinkName, drinkPrice, drinkQty);

				break;

			case 3:
				menuOutput("Entree", entName, entPrice, entQty);
				order(choice, qty, entName, entPrice, entQty);

				break;

			case 4:
				menuOutput("Desert", desName, desPrice, desQty);
				order(choice, qty, desName, desPrice, desQty);

				break;

			case 5:
				if (subtotal != 0)
				{
					checkout();
					trigger = true;
				}

				break;

			default:
				break;
			}
		} while (trigger != true);
	}

	/* ---------
		 INPUT
	   --------- */
	void getData(ifstream& inFile, string fileName, vector<string>& name, vector<double>& price, vector<int>& quantity)
	{
		// open input files
		inFile.open(fileName);
		fileCheck(inFile, fileName);

		// temporary values
		string tName;
		double tPrice;
		int tQty;

			while (!inFile.eof())
			{
				getline(inFile, tName);
				name.push_back(tName);
				inFile >> tPrice;
				price.push_back(tPrice);
				inFile >> tQty;
				quantity.push_back(tQty);
				inFile.ignore();
			}

		// close input files
		inFile.close();
	}

	// user input only for top menu
	int selectionT()
	{
		int choice;
		bool error = true;

		cout << "-------------------------------------" << endl;
		cout << "Enter your choice by number" << endl;

		do
		{
			cout << ">> ";
			cin >> choice;

			// check error
			error = inputErrorT(choice, 5);

		} while (error == true);

		return choice;
	}

	// user input for each menu list
	int selectionM(vector<string>& catName, vector<int>& catQty)	// for menu list
	{
		int choice;
		bool error01 = true;
		bool error02 = true;

		cout << "-------------------------------------" << endl;
		cout << "Enter your choice by number" << endl;

		do
		{
			cout << ">> ";
			cin >> choice;

			// check error
			error01 = inputError(choice, catName);
			if (choice != catName.size() + 1 && error01 == false)
				error02 = soldoutError(choice, catQty);
			else
				error02 = false;

		} while (error01 == true || error02 == true);

		return choice;
	}

	// user input for quantity
	int qtyIn(int choice, vector<int>& catQty)
	{
		int qty;
		bool error = true;

		cout << "-------------------------------------" << endl;
		cout << "Enter quantity" << endl;

		do
		{
			cout << ">> ";
			cin >> qty;

			// check error
			error = qtyError(choice, qty, catQty);

		} while (error == true);

		catQty[choice - 1] = catQty[choice - 1] - qty;

		return qty;
	}

	/* --------
		OUTPUT		
	   -------- */
	void logo()
	{
		system("cls");
		cout << "-------------------------------------" << endl;
		cout << "             CAFE KIOSK              " << endl;
		cout << "-------------------------------------" << endl;
		cout << endl;
	}

	void topMenu()
	{
		logo();

		cout << "Choose a Category from Below." << endl;
		cout << "1. Appetizers" << endl;
		cout << "2. Drink" << endl;
		cout << "3. Entree" << endl;
		cout << "4. Desert" << endl;
		cout << "5. Go to Check" << endl;
		cout << endl;
		cout << "Subtotal: $" << subtotal << endl;

		showOrder(oName, oPrice, oQty);
	}
	
	// output as a list of menu
	void menuOutput(string title, vector<string>& name, vector<double>& price, vector<int>& qty)
	{
		logo();

		cout << title << ':' << endl;

		cout << fixed << showpoint;
		cout << setprecision(2);

		for (int a = 0; a < name.size(); a++)
		{
			if(qty[a] <= 0) //SOLD OUT
				cout << a + 1 << ". " << left << setw(25) << name[a] << setw(3) << "- $" << right << setw(6) << price[a] << "(SOLD OUT)" << endl;
			else //REGULAR
				cout << a + 1 << ". " << left << setw(25) << name[a] << setw(3) << "- $" << right << setw(6) << price[a] << endl;
		}

		cout << name.size() + 1 << ". " << left << setw(25) << "Go Back" << endl;

		cout << endl;
		cout << "Subtotal: $" << subtotal << endl;

		showOrder(oName, oPrice, oQty);

	}

	// show current order with price + subtotal
	void showOrder(vector<string>& name, vector<double>& price, vector<int>& quantity)
	{
		cout << endl;
		cout << "-------------------------------------" << endl;
		cout << "Your Current Order:" << endl;

		if (subtotal == 0)
			cout << "You have not order anything yet." << endl;
		else
		{
			cout << fixed << showpoint;
			cout << setprecision(2);

			for (int a = 0; a < name.size(); a++)
				cout << left << setw(27) << name[a] << setw(3) << quantity[a] << setw(1) << "$" << right << setw(6) << price[a] << endl;

			cout << endl;
			cout << left << setw(27) << "Subtotal" << right << setw(4) << "$" << setw(6) << subtotal << endl;
		}


	}

	/* ------------
		OPERATIONS
	   ------------ */

	// make an order
	void order(int choice, int quantity, vector<string>& catName, vector<double>& catPrice, vector<int>& catQty)
	{
		choice = selectionM(catName, catQty);

		if (choice != catName.size() + 1)
		{
			quantity = qtyIn(choice, catQty);
			addOrder(choice, quantity, catName, catPrice, catQty);
		}
	}

	// add to the order list
	void addOrder(int choice, int quantity, vector<string>& catName, vector<double>& catPrice, vector<int>& catQty)
	{
		// add to order
		string tName;
		double tPrice;

		tName = catName[choice - 1];
		tPrice = catPrice[choice - 1];

		oName.push_back(tName);
		oPrice.push_back(tPrice);
		oQty.push_back(quantity);

		// add subtotal
		subtotal = subtotal + tPrice * quantity;

		// subtruct quatity
		catQty[choice - 1] = catQty[choice - 1] - quantity;
	}

	// show orders and make a payment
	void checkout()
	{
		// decide tip
		tipRate = tipRateIn();

		// tip calculate
		tip = tipRateCal(tipRate);

		// tax calculate
		tax = subtotal * (TAX_RATE / 100);

		// total calculate
		total = subtotal + tip + tax;

		// output

		logo();
		cout << "Make a Payment" << endl;
		showOrder(oName, oPrice, oQty);

		cout << endl;

		cout << left << setw(5) << "Tip (" << setw(5) << right << tipRate << setw(17) << left << "%)" << right << setw(4) << "$" << setw(6) << tip << endl;
		cout << left << setw(5) << "Tax (" << setw(5) << TAX_RATE << setw(17) << "%)" << right << setw(4) << "$" << setw(6) << tax << endl;

		cout << endl;

		cout << left << setw(27) << "Total" << right << setw(4) << "$" << setw(6) << total << endl;

		cout << endl;

		// make a payment

		payment();

	}

	void payment()
	{
		double pay;
		double balance = total;
		double change;

		cout << "Enter the amount of payment." << endl;

		do {
			cout << ">> $";
			cin >> pay;

			// calculate balance

			balance = balance - pay;

			// check error
			if (pay <= 0)
			{
				cout << "*Invalid Input*" << endl;
				cout << "Input a valid payment." << endl;
			}
			else if (balance > 0)
			{
				cout << "*Insufficient Amount*" << endl;
				cout << "You have $" << balance << " left." << endl;
			}

			cout << endl;

		} while (balance > 0);

		// calculate change
		change = (-1) * balance;

		if (change == 0)
		{
			cout << "There is no change." << endl;
		}
		else
		{
			cout << "The change is $" << change << "." << endl;
		}

		cout << "Thank you for your purchase." << endl;
	}

	// decide and calculate tip
	double tipRateIn()
	{
		// tip-rate calculate
		double tip01 = tipRateCal(TIP_RATE01);
		double tip02 = tipRateCal(TIP_RATE02);
		double tip03 = tipRateCal(TIP_RATE03);

		double tipRate;
		bool tipError = false;

		// tip suggestion

		logo();

		cout << "Enter the amount of chip in the percentage(%) form. (Do not include % symbol)" << endl;
		cout << setw(16) << "Suggested Chip: " << setw(3) << right << TIP_RATE01 << "% . . . $" << tip01 << endl;
		cout << setw(16) << " " << setw(3) << right << TIP_RATE02 << "% . . . $" << tip02 << endl;
		cout << setw(16) << " " << setw(3) << right << TIP_RATE03 << "% . . . $" << tip03 << endl;

		do
		{
			cout << ">> ";
			cin >> tipRate;

			// check error

			if (tipRate < 0)
			{
				cout << "*Invalid Input*" << endl;
				cout << "Input a valid rate." << endl;

				tipError = true;
			}
		} while (tipError == true);

		return tipRate;
	}

	double tipRateCal(double taxRate)
	{
		double tax;

		tax = subtotal * (taxRate / 100);

		return tax;
	}

	/* --------------
		ERROR CHECKS
	   -------------- */

	// check if input file exists
	void fileCheck(ifstream& inFile, string text)
	{
		if (!inFile.is_open())
		{
			cout << text << " Not Found" << endl;
			exit(1);
		}
	}

	// check input error for Top Menu
	bool inputErrorT(int choice, int size)
	{
		if (choice < 1 || choice > size)
		{
			cout << "*Input Error*" << endl;
			cout << "Please Re-Enter a Valid Number." << endl;
			cin.clear();

			return true;
		}
		else
			return false;
	}

	// check inout error for menu
	bool inputError(int choice, vector<string>& name)
	{
		if (choice < 1 || choice > name.size() + 1)	// +1 suppose "go back" option
		{
			cout << "*Input Error*" << endl;
			cout << "Please Re-Enter a Valid Number." << endl;
			cin.clear();

			return true;
		}
		else
			return false;
	}

	bool soldoutError(int choice, vector<int>& catQty)
	{
		if (catQty[choice - 1] <= 0)
		{
			cout << "*Sold Out*" << endl;
			cout << "Please Re-Enter a Valid Number." << endl;
			cin.clear();

			return true;
		}
		else
			return false;
	}

	bool qtyError(int catChoice, int qtyChoice, vector<int>& quantity)
	{
		bool error = true;

		if (qtyChoice < 0)
		{
			cout << "*Input Error*" << endl;
			cout << "Please Re-Enter a Valid Number." << endl;
			cin.clear();

			error = true;
		}
		else if (qtyChoice > quantity[catChoice - 1])
		{
			cout << "I'm sorry. We cannot serve that many." << endl;
			cout << "You can order up to " << quantity[catChoice - 1] << " for this menu." << endl;
			cin.clear();

			error = true;
		}
		else if (qtyChoice == 0)
		{
			cout << "Order Cancelled" << endl;
			error = false;
		}
		else
			error = false;

		return error;
	}

private:

	// input file variables
	ifstream appIn, drinkIn, desIn, entIn;

	vector<string> appName, drinkName, desName, entName;
	vector<double> appPrice, drinkPrice, desPrice, entPrice;

	// quantity
	vector<int> appQty, drinkQty, desQty, entQty;

	// order lists
	vector<string> oName;
	vector<double> oPrice;
	vector<int> oQty;

	// calculation
	double subtotal, total, tipRate, tip, tax;

	// trigger for exit (after check out)
	bool trigger = false;

};

// ------------MAIN----------------
int main()
{
	menu cafe;

	cafe.kiosk();

}

// Error Lists
/*

1 ... input file not found
2 ... invalid input (not in the code yet)

*/