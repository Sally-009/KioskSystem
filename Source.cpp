// Name: Saori Kojima
// Program Description: Menu System
// Date: 10/17/22 - 10/23/22


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

			int choice = selection(6);

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
					changeOrder();

			break;

			case 6:
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

	// user input only for top menu and change order
	int selection(int size)
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
			error = inputError(choice, size);

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

	// user input for order history
	int selectionO()
	{
		int choice;

		bool error = false;

		cout << "-------------------------------------" << endl;
		cout << "Enter your choice by number" << endl;

		do
		{
			cout << ">> ";
			cin >> choice;

			// check error
			error = inputError(choice, oName);

		} while (error == true);

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
		cout << "5. *Change Order" << endl;
		cout << "6. *Go to Check" << endl;

		showOrder();
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

		cout << name.size() + 1 << ". " << left << setw(25) << "(Go Back)" << endl;

		showOrder();

	}

	// show current order with price + subtotal
	void showOrder()
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

			for (int a = 0; a < oName.size(); a++)
				cout << left << setw(27) << oName[a] << setw(3) << oQty[a] << setw(1) << "$" << right << setw(6) << oPrice[a] << endl;

			cout << endl;
			cout << left << setw(27) << "Subtotal" << right << setw(4) << "$" << setw(6) << subtotal << endl;
		}


	}

	// change any item in the order
	void changeOrder()
	{
		int choice;
		int choice2;

		logo();

		cout << "Which item do you want to change?" << endl;
		cout << endl;

		// show items
		for (int a = 0; a < oName.size(); a++)
			cout << right << setw(2) << a + 1 << left << setw(2) << ". " << setw(23) << oName[a] << setw(3) << oQty[a] << setw(1) << "$" << right << setw(6) << oPrice[a] << endl;

		cout << right << setw(2) << oName.size() + 1 << left << setw(2) << ". (Go Back)" << endl;

		cout << endl;

		choice = selectionO();

		// show the way to change
		if (choice != oName.size() + 1)
		{
			logo();

			cout << "How do you want to change the item?" << endl;
			cout << endl;
			cout << "1. Change Quantity" << endl;
			cout << "2. Remove" << endl;
			cout << "3. (Go Back)" << endl;

			cout << endl;

			choice2 = selection(3);

			switch (choice2)
			{
			case 1:
				changeQty(choice-1);
				break;

			case 2:
				cancelOrder(choice-1);
				break;

			case 3:

				break;

			default:
				break;
			}
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

		// subtruct quantity
		catQty[choice - 1] = catQty[choice - 1] - quantity;
	}

	// change quantity
	void changeQty(int position)
	{
		logo();

		// show current item
		cout << "Current: " << endl;
		cout << setw(27) << oName[position] << setw(3) << oQty[position] << setw(1) << "$" << right << setw(6) << oPrice[position] << endl;
		cout << endl;

		// search item by each category
		bool isHere = false;
		int orgPosition;	// position for searched item

		// search in APPETIZER
		orgPosition = searchItem(position, oName, appName, isHere);

		// update quantity
		if (isHere == true)
		{
			appQty[orgPosition] = appQty[orgPosition] + oQty[position];
			qtyUpdate(position, orgPosition, appQty);
		}
		else
		{
			// search in DRINK
			orgPosition = searchItem(position, oName, drinkName, isHere);

			if (isHere == true)
			{
				drinkQty[orgPosition] = drinkQty[orgPosition] + oQty[position];
				qtyUpdate(position, orgPosition, drinkQty);
			}
			else
			{
				// search in DESERT
				orgPosition = searchItem(position, oName, desName, isHere);

				if (isHere == true)
				{
					desQty[orgPosition] = desQty[orgPosition] + oQty[position];
					qtyUpdate(position, orgPosition, desQty);
				}
				else
				{
					// search in ENTREE
					orgPosition = searchItem(position, oName, entName, isHere);

					if (isHere == true)
					{
						entQty[orgPosition] = entQty[orgPosition] + oQty[position];
						qtyUpdate(position, orgPosition, entQty);
					}
				}
			}
		}

	}

	void qtyUpdate(int sourceP, int catP, vector<int>& catQty)
	{
		int nQty;	// new quantity
		bool error = false;

		// substitute subtotal

		subtotal = subtotal - (oPrice[sourceP] * oQty[sourceP]);

		cout << "-------------------------------------" << endl;
		cout << "Enter NEW Quantity" << endl;

		do
		{
			cout << ">> ";
			cin >> nQty;

			// error check
			if (nQty < 0)
			{
				cout << "*Input Error*" << endl;
				cout << "Please Re-Enter a Valid Number." << endl;

				error = true;
			}
			else if (nQty > catQty[catP])
			{
				cout << "I'm sorry. We cannot serve that many." << endl;
				cout << "You can order up to " << catQty[catP] << " for this menu." << endl;

				error = true;
			}
			else if (nQty == 0)
			{
				subtotal = subtotal + (oPrice[sourceP] * oQty[sourceP]);	// it will substitude again in the next function

				cancelOrder(sourceP);
				break;
			}
			else
				error = false;

		} while (error == true);

		if (nQty != 0)
		{
			oQty[sourceP] = nQty;

			// update stock
			catQty[catP] = catQty[catP] - nQty;

			// update subtotal
			subtotal = subtotal + oPrice[sourceP] * nQty;
		}

	}

	// cancel order from the order list
	// position = the position required to be removed
	void cancelOrder(int position)
	{
		// fix subtotal
		subtotal = subtotal - (oPrice[position] * oQty[position]);

		// fix quantity
		resetQty(position);

		// erase the item data
		oName.erase(oName.begin() + position);
		oPrice.erase(oPrice.begin() + position);
		oQty.erase(oQty.begin() + position);
	}

	void resetQty(int i)	// i = position
	{
		// search item by each category
		bool isHere = false;
		int orgPosition;	// position for searched item

		// search in APPETIZER
		orgPosition = searchItem(i, oName, appName, isHere);

		if (isHere == true)
		{
			appQty[orgPosition] = appQty[orgPosition] + oQty[i];
		}
		else
		{
			// search in DRINK
			orgPosition = searchItem(i, oName, drinkName, isHere);

			if (isHere == true)
			{
				drinkQty[orgPosition] = drinkQty[orgPosition] + oQty[i];
			}
			else
			{
				// search in DESERT
				orgPosition = searchItem(i, oName, desName, isHere);

				if (isHere == true)
				{
					desQty[orgPosition] = desQty[orgPosition] + oQty[i];
				}
				else
				{
					// search in ENTREE
					orgPosition = searchItem(i, oName, entName, isHere);

					if (isHere == true)
					{
						entQty[orgPosition] = entQty[orgPosition] + oQty[i];
					}
				}
			}
		}
	}

	// search the position that matches to the string content in source[i]
	int searchItem(int i, vector<string>& source, vector<string>& catName, bool& isHere)
	{
		int position;

		for (int a = 0; a < catName.size(); a++)
		{
			if (source[i] == catName[a])
			{
				position = a;
				isHere = true;
				break;
			}
			else
				position = 0;
				isHere = false;
		}

		return position;
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
		showOrder();

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
	bool inputError(int choice, int size)
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

	bool qtyError(int catChoice, int qtyChoice, vector<int>& catQty)
	{
		bool error = true;

		if (qtyChoice < 0)
		{
			cout << "*Input Error*" << endl;
			cout << "Please Re-Enter a Valid Number." << endl;

			error = true;
		}
		else if (qtyChoice > catQty[catChoice - 1])
		{
			cout << "I'm sorry. We cannot serve that many." << endl;
			cout << "You can order up to " << catQty[catChoice - 1] << " for this menu." << endl;

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

*/
