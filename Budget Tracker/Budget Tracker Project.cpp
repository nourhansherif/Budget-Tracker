#include <iostream>
#include <string>
#include <fstream>
using namespace std;
ifstream inputdata;
ofstream outputdata;

struct Date {
	int day;
	int month;
	int year;
};
struct income
{
	string name;
	float money;
	Date date_income;
};
struct expenses
{
	string name;
	float money;
	Date date_expenses;
	string type;
};
struct recurringcosts {
	string name;
	float money;
	Date date_recurringcosts;
	string type;
};
void recurringcost_fn(recurringcosts recurringcosts_array[], int & recurringcostsindex, float & incometotal, float & recurringcoststotal, float&visacardtotal);
void recurringcostlist(recurringcosts  recurringcosts_array[], int & recurringcostsindex, float & recurringcoststotal);
void expenses_fn(expenses expenses_arr[], int & expensesindex, float & incometotal, float & expensestotal, float&n);
void edit_fn(expenses expenses_arr[], recurringcosts recurringcosts_array[], income income_arr[], int & incomeindex, int & expensesindex, int & recurringcostsindex, float & incometotal, float & expensestotal, float & recurringcoststotal);
void income_fn(income income_arr[], int & incomeindex, float & incometotal);
void incomelist(income income_arr[], int & incomeindex, float & incometotal);
void expenseslist(expenses[], int & expensesindex, float & expensestotal);
void currentStatus_fn(float, float, float);
void detailedstatus_fn(float incometotal, float expensestotal, float recurringcoststotal);
void deletefn(expenses expenses_arr[], recurringcosts recurringcosts_array[], income income_arr[], int & incomeindex, int & expensesindex, int & recurringcostsindex, float & incometotal, float & expensestotal, float & recurringcoststotal);
void savedata(expenses expenses_arr[], recurringcosts recurringcosts_array[], income income_arr[], int & incomeindex, int & expensesindex, int & recurringcostsindex, float &visacardtotal, float &visacardlimit);
void readdata(expenses expenses_arr[], recurringcosts recurringcosts_array[], income income_arr[], int & incomeindex, int & expensesindex, int & recurringcostsindex, float & incometotal, float & expensestotal, float & recurringcoststotal, float &visacardtotal, float &visacardlimit);
void NetFlow(expenses expenses_arr[], recurringcosts recurringcosts_array[], income income_arr[], int & incomeindex, int & expensesindex, int & recurringcostsindex, float visacardtotal, float visacardlimit);
void visaCard_fn(expenses expenses_arr[], recurringcosts recurringcosts_array[], float &visacardtotal, int &expensesindex, int&recurringcostsindex, float &visacardlimit);
int main()
{
	float visacardtotal = 0, visacardlimit = 0;
	int recurringcostsindex = 0, expensesindex = 0, incomeindex = 0;
	float incometotal = 0, expensestotal = 0, recurringcoststotal = 0;
	const int size = 100;
	income income_arr[size];
	expenses expenses_arr[size];
	recurringcosts recurringcosts_array[size];
	cout << "Do you want to get your previous saved data ? (y/n)";
	char ask; cin >> ask;
	while (true)
	{
		if (ask == 'y' || ask == 'Y' || ask == 'n' || ask == 'N') break;
		cout << "Invalid entry, Please enter y/n" << endl;
		cin >> ask;
	}
	if (ask == 'y' || ask == 'Y') {
		readdata(expenses_arr, recurringcosts_array, income_arr, incomeindex, expensesindex, recurringcostsindex, incometotal, expensestotal, recurringcoststotal, visacardtotal, visacardlimit);
		if (incomeindex == 0 && expensesindex == 0 && recurringcostsindex == 0) cout << "You don't have any saved data !" << endl;
	}
	while (true) {
		int index;
		cout << "Choose what do you want to do" << endl;
		cout << " 1)Income \t 2)Recurring costs \t \n 3)Expenses \t 4)Edit \t \n 5)Delete \t 6)List \t \n 7)Status \t 8)NetFlowOfMoney \n 9)Visa card \t 10)Exit " << endl;
		cin >> index;
		while (cin.fail() || index > 10 || index < 1) {
			cin.clear();//clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n');//ignore last input
			cout << "Invalid entry, Please choose a number from the menu above" << endl;
			cin >> index;
		}
		switch (index) {
		case 1: income_fn(income_arr, incomeindex, incometotal);  break;
		case 2:recurringcost_fn(recurringcosts_array, recurringcostsindex, incometotal, recurringcoststotal, visacardtotal); break;
		case 3:expenses_fn(expenses_arr, expensesindex, incometotal, expensestotal, visacardtotal); break;
		case 4:edit_fn(expenses_arr, recurringcosts_array, income_arr, incomeindex, expensesindex, recurringcostsindex, incometotal, expensestotal, recurringcoststotal); break;
		case 5:deletefn(expenses_arr, recurringcosts_array, income_arr, incomeindex, expensesindex, recurringcostsindex, incometotal, expensestotal, recurringcoststotal); break;
		case 6:cout << "Choose what to list" << endl << "1) Income \t 2)Recurring costs \t 3)Expenses \t 4)All" << endl;
			cin >> index;
			while (cin.fail() || index > 4 || index < 1) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid entry, Please choose a number from the menu above" << endl;
				cin >> index;
			}
			if (index == 1)  incomelist(income_arr, incomeindex, incometotal);
			else if (index == 2)   recurringcostlist(recurringcosts_array, recurringcostsindex, recurringcoststotal);
			else if (index == 3)  expenseslist(expenses_arr, expensesindex, expensestotal);
			else {
				cout << "Income:" << endl;; incomelist(income_arr, incomeindex, incometotal);
				cout << "Recurring costs:" << endl; recurringcostlist(recurringcosts_array, recurringcostsindex, recurringcoststotal);
				cout << "Expenses:" << endl; expenseslist(expenses_arr, expensesindex, expensestotal);
			}
			break;
		case 7:char status;
			cout << "Do you want a current or detailed status?\nEnter C for current or D for detailed or R to return to menu" << endl;
			cin >> status;
			while (true) {
				if (status == 'c' || status == 'C' || status == 'd' || status == 'D' || status == 'r' || status == 'R')
					break;
				cout << "Invalid entry, Please re-enter a letter" << endl;
				cin >> status;
			}
			if (status == 'r' || status == 'R')break;
			else if (status == 'c' || status == 'C')
				currentStatus_fn(incometotal, expensestotal, recurringcoststotal);
			else if (status == 'd' || status == 'D')
				detailedstatus_fn(incometotal, expensestotal, recurringcoststotal); break;
		case 8: NetFlow(expenses_arr, recurringcosts_array, income_arr, incomeindex, expensesindex, recurringcostsindex, visacardtotal, visacardlimit); break;
		case 9:visaCard_fn(expenses_arr, recurringcosts_array, visacardtotal, expensesindex, recurringcostsindex, visacardlimit); break;
		}if (index == 10) {
			cout << "Do you want to save your data ?(y/n)"; cin >> ask;
			while (true) {
				if (ask == 'y' || ask == 'Y' || ask == 'n' || ask == 'N') break;
				cout << "Invalid entry, Please re-enter a letter" << endl;
				cin >> ask;
			} if (ask == 'y' || ask == 'Y') {
				savedata(expenses_arr, recurringcosts_array, income_arr, incomeindex, expensesindex, recurringcostsindex, visacardtotal, visacardlimit);
				cout << "Data Saved!" << endl;
				break;
			}
			else break;
		}
	}
	system("pause");
	return 0;
}
void expenses_fn(expenses expenses_arr[], int & expensesindex, float & incometotal, float & expensestotal, float& visacardtotal)
{
	int index;
	do {
		if (incometotal == 0 && visacardtotal == 0) {
			cout << "You don't have any income or money in your visacard!" << endl;
			break;
		}
		int s;
		cout << "Choose how did you pay 1) cash \t 2)visa" << endl;
		cin >> s;
		while (cin.fail() || s > 2 || s < 1) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, Please choose a number from the menu above" << endl;
			cin >> s;
		}
		if (s == 1) {
			if (incometotal == 0) {
				cout << "You didn't enter any sources of income" << endl;
				break;
			}
			expenses_arr[expensesindex].type = "cash";
		}
		else {
			if (visacardtotal == 0) {
				cout << "You didn't enter your visacard total" << endl;
				break;
			}
			expenses_arr[expensesindex].type = "visa";
		}
		cout << "Enter Date (Day Month Year): " << endl;
		cin >> expenses_arr[expensesindex].date_expenses.day >> expenses_arr[expensesindex].date_expenses.month >> expenses_arr[expensesindex].date_expenses.year;
		while (cin.fail() || expenses_arr[expensesindex].date_expenses.day > 31
			|| expenses_arr[expensesindex].date_expenses.day < 1
			|| expenses_arr[expensesindex].date_expenses.month < 1
			|| expenses_arr[expensesindex].date_expenses.month > 12) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, Please re-enter the date with the right format" << endl;
			cin >> expenses_arr[expensesindex].date_expenses.day >> expenses_arr[expensesindex].date_expenses.month >> expenses_arr[expensesindex].date_expenses.year;
		}
		cout << "Enter expense:" << endl;
		cin >> expenses_arr[expensesindex].name;
		cout << "Enter the money paid:" << endl;
		cin >> expenses_arr[expensesindex].money;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, Please re-enter the money you paid" << endl;
			cin >> expenses_arr[expensesindex].money;
		}if (expenses_arr[expensesindex].type == "visa") visacardtotal -= expenses_arr[expensesindex].money;
		expensestotal += expenses_arr[expensesindex].money;
		expensesindex++;
		cout << "1) Add new \t 2)exit" << endl;
		cin >> index;
		while (cin.fail() || index > 2 || index < 1) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, Please choose a number from the menu above" << endl;
			cin >> index;
		}
		cout << "The total expenses is " << expensestotal << endl;
	} while (index == 1);

}
void expenseslist(expenses expenses_arr[], int & expensesindex, float & expensestotal)
{
	if (expensestotal == 0) cout << "You have no data to list" << endl;
	else {
		cout << "Name  \t\t cost" << endl;
		for (int i = 0; i < expensesindex; i++) {
			cout << i + 1 << ")" << expenses_arr[i].name << "\t" << expenses_arr[i].money << endl;
		}
		cout << "The total expenses:" << expensestotal << endl;
	}
}
void recurringcost_fn(recurringcosts recurringcosts_array[], int & recurringcostsindex, float & incometotal, float & recurringcoststotal, float& visacardtotal)
{
	while (true) {
		if (incometotal == 0 && visacardtotal == 0) {
			cout << "You don't have any income sources or money in your visa " << endl;
			break;
		}
		int index;
		cout << "1) Rent" << endl << "2) ElectricityBill" << endl << "3) Fuel " << endl << "4) Add new " << endl << "5) Exit" << endl;
		cin >> index;
		while (cin.fail() || index > 5 || index < 1) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, Please choose a number from the menu above" << endl;
			cin >> index;
		}
		if (index == 5) break;
		else if (index == 1)recurringcosts_array[recurringcostsindex].name = "Rent";
		else if (index == 2)recurringcosts_array[recurringcostsindex].name = "ElectricityBill";
		else if (index == 3)recurringcosts_array[recurringcostsindex].name = "Fuel";
		else if (index == 4) {
			cout << "Enter name of new recurring cost: ";
			cin >> recurringcosts_array[recurringcostsindex].name;
		}int s;
		cout << "Choose how did you pay 1) cash \t 2)visa" << endl;
		cin >> s;
		while (cin.fail() || s > 2 || s < 1) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please choose a number from the menu above" << endl;
			cin >> s;
		}
		if (s == 1) {
			if (incometotal == 0) {
				cout << "You didn't enter any sources of income" << endl;
				break;
			}recurringcosts_array[recurringcostsindex].type = "cash";
		}
		else {
			if (visacardtotal == 0) {
				cout << "You didn't enter your visacard total" << endl;
				break;
			}
			recurringcosts_array[recurringcostsindex].type = "visa";
		}
		cout << "Enter Date (Day Month Year): " << endl;
		cin >> recurringcosts_array[recurringcostsindex].date_recurringcosts.day >> recurringcosts_array[recurringcostsindex].date_recurringcosts.month >> recurringcosts_array[recurringcostsindex].date_recurringcosts.year;
		while (cin.fail() || recurringcosts_array[recurringcostsindex].date_recurringcosts.day > 31
			|| recurringcosts_array[recurringcostsindex].date_recurringcosts.day < 1
			|| recurringcosts_array[recurringcostsindex].date_recurringcosts.month < 1
			|| recurringcosts_array[recurringcostsindex].date_recurringcosts.month > 12) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please enter a date with the right format" << endl;
			cin >> recurringcosts_array[recurringcostsindex].date_recurringcosts.day >> recurringcosts_array[recurringcostsindex].date_recurringcosts.month >> recurringcosts_array[recurringcostsindex].date_recurringcosts.year;
		}
		cout << "Enter how much you pay :"; cin >> recurringcosts_array[recurringcostsindex].money;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, Please re-enter the money you paid" << endl;
			cin >> recurringcosts_array[recurringcostsindex].money;
		}
		if (recurringcosts_array[recurringcostsindex].type == "visa") visacardtotal -= recurringcosts_array[recurringcostsindex].money;
		recurringcoststotal += recurringcosts_array[recurringcostsindex].money;
		recurringcostsindex++;
	}

	cout << "The total recurring cost is " << recurringcoststotal << endl;
}

void recurringcostlist(recurringcosts  recurringcosts_array[], int & recurringcostsindex, float & recurringcoststotal)
{
	if (recurringcostsindex == 0) cout << "You have no data to list" << endl;
	else {
		cout << "Name  \t\t cost" << endl;
		for (int i = 0; i < recurringcostsindex; i++) {
			cout << i + 1 << ")" << recurringcosts_array[i].name << "\t" << recurringcosts_array[i].money << endl;
		}
		cout << "The total recurring costs paid:" << recurringcoststotal << endl;
	}
}

void income_fn(income income_arr[], int & incomeindex, float & incometotal)
{
	int index;
	do {
		cout << "Enter Date (Day Month Year): " << endl;
		cin >> income_arr[incomeindex].date_income.day >> income_arr[incomeindex].date_income.month >> income_arr[incomeindex].date_income.year;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please enter the right format" << endl;
			cin >> income_arr[incomeindex].date_income.day >> income_arr[incomeindex].date_income.month >> income_arr[incomeindex].date_income.year;
		}
		cout << "The source of income is:" << endl;
		cin >> income_arr[incomeindex].name;
		cout << "The income:" << endl;
		cin >> income_arr[incomeindex].money;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, Please re-enter your income" << endl;
			cin >> income_arr[incomeindex].money;
		}
		incometotal += income_arr[incomeindex].money;
		incomeindex++;
		cout << "1) Add new \t 2)exit" << endl;
		cin >> index;
		while (cin.fail() || index > 2 || index < 1) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please choose a number from the menu above" << endl;
			cin >> index;
		}
	} while (index == 1);
	cout << "The income total:" << incometotal << endl;
}
void incomelist(income income_arr[], int & incomeindex, float & incometotal)
{
	if (incomeindex == 0) cout << "You have no data to list" << endl;

	else {
		cout << "Name  \t\t cost" << endl;
		for (int i = 0; i < incomeindex; i++) {
			cout << i + 1 << ")" << income_arr[i].name << "\t" << income_arr[i].money << endl;
		}cout << "The total income is " << incometotal << endl;
	}

}
void edit_fn(expenses expenses_arr[], recurringcosts recurringcosts_array[], income income_arr[], int & incomeindex, int & expensesindex, int & recurringcostsindex, float & incometotal, float & expensestotal, float & recurringcoststotal)
{
	int edit_index, index;
	int n;
	char ch;
	do {
		cout << "What do you want to edit?" << endl;
		cout << "1)Income" << " " << "2)Recurring cost" << " " << "3)Expenses" << endl;
		cin >> edit_index; while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please enter a number" << endl;
			cin >> edit_index;
		}
		switch (edit_index) {
		case 1:
			if (incomeindex == 0)
			{
				cout << "You have no income to be edited" << endl; break;
			}incomelist(income_arr, incomeindex, incometotal);
			cout << "Enter the index of the income you want to edit: " << endl;
			cin >> index;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid entry,Please enter a number" << endl;
				cin >> index;
			}
			index--;
			cout << "Choose what you want to edit:";  cout << "1)Source" << " " << "2)Income" << " " << "3)Both" << endl;
			cin >> n; while (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid entry,Please enter a number" << endl;
				cin >> n;
			}
			if (n == 1) {
				cout << "Enter the new source name: " << endl;
				cin >> income_arr[index].name;
			}
			else if (n == 2)
			{
				cout << "Enter the new income: " << endl;
				incometotal -= income_arr[index].money;
				cin >> income_arr[index].money;
				while (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Invalid entry,Please enter a number" << endl;
					cin >> income_arr[index].money;
				}
				incometotal += income_arr[index].money;
			}
			else if (n == 3) {
				cout << "Name:";
				cin >> income_arr[index].name;
				cout << "Cost:";
				incometotal -= income_arr[index].money;
				cin >> income_arr[index].money;
				while (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Invalid entry,Please enter a number" << endl;
					cin >> income_arr[index].money;
				}
				incometotal += income_arr[index].money;
			}/*outputdata.open("income.txt", ios::trunc);
			 for (int i = 0; i < incomeindex; i++) {
			 outputdata << income_arr[i].date_income.day << "\t" << income_arr[i].date_income.month << "\t" << income_arr[i].date_income.year << endl;
			 outputdata << income_arr[i].name << "\t" << income_arr[i].money << endl;
			 }
			 outputdata.close();*/
			break;
		case 2: if (recurringcostsindex == 0)
		{
					cout << "You have no recurring costs to be edited" << endl; break;
		}
				recurringcostlist(recurringcosts_array, recurringcostsindex, recurringcoststotal);
				cout << "Enter the index of recurring cost you want to edit :" << endl;
				cin >> index;
				while (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Invalid entry,Please enter a number" << endl;
					cin >> index;
				}
				index--;
				cout << "Choose what you want to edit"; cout << "1)Name" << " " << "2)Cost" << " " << "3)Both" << endl;
				cin >> n;
				while (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Invalid entry,Please enter a number" << endl;
					cin >> n;
				}
				if (n == 1) {
					cout << "Enter the new recurring cost name: " << endl;
					cin >> recurringcosts_array[index].name;
				}
				else if (n == 2)
				{
					cout << "Enter the new recurringcost: " << endl;
					recurringcoststotal -= recurringcosts_array[index].money;
					cin >> recurringcosts_array[index].money;
					while (cin.fail()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << "Invalid entry,Please enter a number" << endl;
						cin >> recurringcosts_array[index].money;
					}
					recurringcoststotal += recurringcosts_array[index].money;
				}
				else if (n == 3)
				{
					cout << "Name:";
					cin >> recurringcosts_array[index].name;
					cout << "Cost:";
					recurringcoststotal -= recurringcosts_array[index].money;
					cin >> recurringcosts_array[index].money;
					while (cin.fail()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << "Invalid entry,Please enter a number" << endl;
						cin >> recurringcosts_array[index].money;
					}
					recurringcoststotal += recurringcosts_array[index].money;
				}/*outputdata.open("recurringcosts.txt", ios::trunc);
				 for (int i = 0; i < recurringcostsindex; i++) {
				 outputdata << recurringcosts_array[i].date_recurringcosts.day << "\t" << recurringcosts_array[i].date_recurringcosts.month << "\t" << recurringcosts_array[i].date_recurringcosts.year << endl;
				 outputdata << recurringcosts_array[i].name << "\t" << recurringcosts_array[i].money << endl;
				 }
				 outputdata.close();*/
				break;
		case 3: if (expensesindex == 0)
		{
					cout << "You have no expenses to be edited" << endl; break;
		}
				expenseslist(expenses_arr, expensesindex, expensestotal);
				cout << "Enter the index of the expense you want to edit: " << endl;
				cin >> index; while (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Invalid entry,Please enter a number" << endl;
					cin >> index;
				}
				index--;
				cout << "Choose what you want to edit"; cout << "1)Name" << " " << "2)Cost" << " " << "3)Both" << endl;
				cin >> n; while (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Invalid entry,Please enter a number" << endl;
					cin >> n;
				}
				if (n == 1) {
					cout << "Enter the new expense name: " << endl;
					cin >> expenses_arr[index].name;

				}
				else if (n == 2) {
					cout << "Enter the new expense: " << endl;
					expensestotal -= expenses_arr[index].money;
					cin >> expenses_arr[index].money;
					while (cin.fail()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << "Invalid entry,Please enter a number" << endl;
						cin >> expenses_arr[index].money;
					}
					expensestotal += expenses_arr[index].money;
				}
				else if (n == 3)
				{
					cout << "Name";
					cin >> expenses_arr[index].name;
					cout << "Cost:";
					expensestotal -= expenses_arr[index].money;
					cin >> expenses_arr[index].money;
					while (cin.fail()) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << "Invalid entry,Please enter a number" << endl;
						cin >> expenses_arr[index].money;
					}
					expensestotal += expenses_arr[index].money;
				}
				/*outputdata.open("expenses.txt", ios::trunc);
				for (int i = 0; i < expensesindex; i++) {
				outputdata << expenses_arr[i].date_expenses.day << "\t" << expenses_arr[i].date_expenses.month << "\t" << expenses_arr[i].date_expenses.year << endl;
				outputdata << expenses_arr[i].name << "\t" << income_arr[i].money << endl;
				}
				outputdata.close();*/
				break;
		}
		cout << "Do you want to edit again ? y/n" << endl;
		cin >> ch;
		while (true) {
			if (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N')break;
			cin.clear();
			cin.ignore();
			cout << "Invalid entry,Please enter either a y/n" << endl;
			cin >> ch;
		}

	} while (ch == 'y' || ch == 'Y');
}
void currentStatus_fn(float incometotal, float expensestotal, float recurringcoststotal)
{
	float result = incometotal - (expensestotal + recurringcoststotal);
	if (result == incometotal)
		cout << "You spent no money" << endl;
	else if (result > 0 && result < incometotal * 0.25)
		cout << "You nearly more the 75% of your money" << endl;
	else if (result == incometotal * 0.25)
		cout << "You spent 75% of your money" << endl;
	else if (result > incometotal * 0.25 && result < incometotal * 0.5)
		cout << "You nearly spent two thirds of your money" << endl;
	else if (result == incometotal * 0.5)
		cout << "You spent half of your money" << endl;
	else if (result > incometotal * 0.5 && result < incometotal * 0.75)
		cout << "You nearly spent one third of your money" << endl;
	else if (result == incometotal * 0.75)
		cout << "You spent 25% of your money" << endl;
	else if (result > incometotal*0.75)
		cout << "You spent less than 25% of your money" << endl;
	else if (result == 0)
		cout << "You spent all of your money" << endl;
}
void detailedstatus_fn(float incometotal, float  expensestotal, float  recurringcoststotal)
{
	currentStatus_fn(incometotal, expensestotal, recurringcoststotal);
	float result = incometotal - (expensestotal + recurringcoststotal);
	cout << "Your Total income \t" << incometotal << endl;
	cout << "You paid on recurring costs \t" << recurringcoststotal << endl;
	cout << "You paid on expenses \t" << expensestotal << endl;
	cout << "You spent\t " << incometotal - result << endl;
	cout << "You have \t" << result << endl;

}
void deletefn(expenses expenses_arr[], recurringcosts recurringcosts_array[], income income_arr[], int & incomeindex, int & expensesindex, int & recurringcostsindex, float & incometotal, float & expensestotal, float & recurringcoststotal)
{
	int delete_index, index;
	char ch;
	do {
		cout << "what do you want to delete?" << endl;
		cout << "1)Income" << " " << "2)Recurring cost" << " " << "3)Expenses" << endl;
		cin >> delete_index;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please enter a number" << endl;
			cin >> delete_index;
		}
		switch (delete_index)
		{
		case 1:
			if (incomeindex == 0)
			{
				cout << "You have no income to be deleted" << endl; break;
			}incomelist(income_arr, incomeindex, incometotal);
			cout << "Enter the index of the income you want to delete: " << endl;
			cin >> index;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid entry,Please enter a number" << endl;
				cin >> index;
			}
			index--;
			cout << "You deleted " << income_arr[index].name << endl;
			incometotal -= income_arr[index].money;
			for (int k = 0; k < incomeindex; k++) {
				if (k == index)
				{
					for (int j = k; j < incomeindex; j++) {
						income_arr[j].date_income.day = income_arr[j + 1].date_income.day;
						income_arr[j].date_income.month = income_arr[j + 1].date_income.month;
						income_arr[j].date_income.year = income_arr[j + 1].date_income.year;
						income_arr[j].name = income_arr[j + 1].name;
						income_arr[j].money = income_arr[j + 1].money;
					}
					incomeindex--;
				}
			}/*outputdata.open("income.txt", ios::trunc);
			 for (int i = 0; i < incomeindex; i++) {
			 outputdata << income_arr[i].date_income.day << "\t" << income_arr[i].date_income.month << "\t" << income_arr[i].date_income.year << endl;
			 outputdata << income_arr[i].name << "\t" << income_arr[i].money << endl;
			 }
			 outputdata.close();*/
			break;
		case 2:
			if (recurringcostsindex == 0)
			{
				cout << "You have no recurring costs to be deleted" << endl; break;
			}recurringcostlist(recurringcosts_array, recurringcostsindex, recurringcoststotal);
			cout << "Enter the index of the recurring cost you want to delete: " << endl;
			cin >> index;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid entry,Please enter a number" << endl;
				cin >> index;
			}
			index--;
			cout << "You deleted " << recurringcosts_array[index].name << endl;
			recurringcoststotal -= recurringcosts_array[index].money;
			for (int k = 0; k < recurringcostsindex; k++) {
				if (k == index)
				{
					for (int j = k; j < recurringcostsindex; j++) {
						recurringcosts_array[j].date_recurringcosts.day = recurringcosts_array[j + 1].date_recurringcosts.day;
						recurringcosts_array[j].date_recurringcosts.month = recurringcosts_array[j + 1].date_recurringcosts.month;
						recurringcosts_array[j].date_recurringcosts.year = recurringcosts_array[j + 1].date_recurringcosts.year;
						recurringcosts_array[j].name = recurringcosts_array[j + 1].name;
						recurringcosts_array[j].money = recurringcosts_array[j + 1].money;
						recurringcosts_array[j].type = recurringcosts_array[j + 1].type;
					}
					recurringcostsindex--;
				}
			}/*outputdata.open("recurringcosts.txt", ios::trunc);
			 for (int i = 0; i < recurringcostsindex; i++) {
			 outputdata << recurringcosts_array[i].date_recurringcosts.day << "\t" << recurringcosts_array[i].date_recurringcosts.month << "\t" << recurringcosts_array[i].date_recurringcosts.year << endl;
			 outputdata << recurringcosts_array[i].name << "\t" << recurringcosts_array[i].money << endl;
			 }
			 outputdata.close();*/
			break;
		case 3:
			if (expensesindex == 0)
			{
				cout << "You have no expenses to be deleted" << endl; break;
			}
			expenseslist(expenses_arr, expensesindex, expensestotal);
			cout << "Enter the index of the expenses you want to delete: " << endl;
			cin >> index; while (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid entry,Please enter a number" << endl;
				cin >> index;
			}
			index--;
			cout << "You deleted " << expenses_arr[index].name << endl;
			expensestotal -= expenses_arr[index].money;
			for (int k = 0; k < expensesindex; k++) {
				if (k == index)
				{
					for (int j = k; j < expensesindex; j++) {
						expenses_arr[j].date_expenses.day = expenses_arr[j + 1].date_expenses.day;
						expenses_arr[j].date_expenses.month = expenses_arr[j + 1].date_expenses.month;
						expenses_arr[j].date_expenses.year = expenses_arr[j + 1].date_expenses.year;
						expenses_arr[j].name = expenses_arr[j + 1].name;
						expenses_arr[j].money = expenses_arr[j + 1].money;
						expenses_arr[j].type = expenses_arr[j + 1].type;
					}
					expensesindex--;
				}
			}/*outputdata.open("expenses.txt", ios::trunc);
			 for (int i = 0; i < expensesindex; i++) {
			 outputdata << expenses_arr[i].date_expenses.day << "\t" << expenses_arr[i].date_expenses.month << "\t" << expenses_arr[i].date_expenses.year << endl;
			 outputdata << expenses_arr[i].name << "\t" << income_arr[i].money << endl;
			 }
			 outputdata.close();*/
			break;
		}cout << "Do you want to delete again? y/n" << endl;
		cin >> ch;
		while (true) {
			if (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N')break;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please enter either y/n" << endl;
			cin >> ch;
		}
	} while (ch == 'y' || ch == 'Y');
}void savedata(expenses expenses_arr[], recurringcosts recurringcosts_array[], income income_arr[], int & incomeindex, int & expensesindex, int & recurringcostsindex, float &visacardtotal, float &visacardlimit)
{
	cout << "Choose what do you want to save" << endl;
	cout << "1) Income\t 2) Recurring costs\t 3)Expenses\t 4) All" << endl;
	int index; cin >> index;
	if (index == 1 || index == 4) {
		outputdata.open("Income.txt", ios::trunc);
		for (int i = 0; i < incomeindex; i++) {
			outputdata << income_arr[i].date_income.day << "\t" << income_arr[i].date_income.month << "\t" << income_arr[i].date_income.year << endl;
			outputdata << income_arr[i].name << "\t" << income_arr[i].money << endl;
		}
		outputdata.close();
		outputdata.open("VisaCard.txt", ios::trunc);
		outputdata << visacardlimit << endl << visacardtotal;
		outputdata.close();
	}if (index == 2 || index == 4) {
		outputdata.open("Recurringcosts.txt", ios::trunc);
		for (int i = 0; i < recurringcostsindex; i++) {
			outputdata << recurringcosts_array[i].date_recurringcosts.day << "\t" << recurringcosts_array[i].date_recurringcosts.month << "\t" << recurringcosts_array[i].date_recurringcosts.year << endl;
			outputdata << recurringcosts_array[i].name << "\t" << recurringcosts_array[i].money << "\t" << recurringcosts_array[i].type << endl;
		}outputdata.close();
	}if (index == 3 || index == 4) {
		outputdata.open("Expenses.txt", ios::trunc);
		for (int i = 0; i < expensesindex; i++) {
			outputdata << expenses_arr[i].date_expenses.day << "\t" << expenses_arr[i].date_expenses.month << "\t" << expenses_arr[i].date_expenses.year << endl;
			outputdata << expenses_arr[i].name << "\t" << expenses_arr[i].money << "\t" << expenses_arr[i].type << endl;
		}outputdata.close();
	}
}
void readdata(expenses expenses_arr[], recurringcosts recurringcosts_array[], income income_arr[], int & incomeindex, int & expensesindex, int & recurringcostsindex, float & incometotal, float & expensestotal, float & recurringcoststotal, float &visacardtotal, float &visacardlimit) {
	string line, typee;
	float moneyy, visacard, visacardlimitt;
	int dayy, monthh, yearr;
	int begin, end;
	inputdata.open("income.txt");
	begin = inputdata.tellg();
	inputdata.seekg(0, ios::end);
	end = inputdata.tellg();
	if (end - begin != 0) {
		inputdata.seekg(0);
		while (!inputdata.eof()) {
			inputdata >> dayy >> monthh >> yearr >> line >> moneyy;
			income_arr[incomeindex].date_income.day = dayy;
			income_arr[incomeindex].date_income.month = monthh;
			income_arr[incomeindex].date_income.year = yearr;
			income_arr[incomeindex].name = line;
			income_arr[incomeindex].money = moneyy;
			incometotal += moneyy;
			incomeindex++;
		}incometotal -= moneyy;
		incomeindex--;
	}
	inputdata.close();
	inputdata.open("expenses.txt"); begin = 0; end = 0;
	begin = inputdata.tellg();
	inputdata.seekg(0, ios::end);
	end = inputdata.tellg();
	if (end - begin != 0) {
		inputdata.seekg(0);
		while (!inputdata.eof()) {
			inputdata >> dayy >> monthh >> yearr >> line >> moneyy >> typee;
			expenses_arr[expensesindex].date_expenses.day = dayy;
			expenses_arr[expensesindex].date_expenses.month = monthh;
			expenses_arr[expensesindex].date_expenses.year = yearr;
			expenses_arr[expensesindex].name = line;
			expenses_arr[expensesindex].money = moneyy;
			expenses_arr[expensesindex].type = typee;
			expensestotal += moneyy;
			expensesindex++;
		}expensestotal -= moneyy;

		expensesindex--;
	}
	inputdata.close();
	inputdata.open("recurringcosts.txt");
	begin = 0; end = 0;
	begin = inputdata.tellg();
	inputdata.seekg(0, ios::end);
	end = inputdata.tellg();
	if (end - begin != 0) {
		inputdata.seekg(0);
		while (!inputdata.eof()) {
			inputdata >> dayy >> monthh >> yearr >> line >> moneyy >> typee;
			recurringcosts_array[recurringcostsindex].date_recurringcosts.day = dayy;
			recurringcosts_array[recurringcostsindex].date_recurringcosts.month = monthh;
			recurringcosts_array[recurringcostsindex].date_recurringcosts.year = yearr;
			recurringcosts_array[recurringcostsindex].name = line;
			recurringcosts_array[recurringcostsindex].money = moneyy;
			recurringcosts_array[recurringcostsindex].type = typee;
			recurringcoststotal += moneyy;
			recurringcostsindex++;
		}
		recurringcoststotal -= moneyy;
		recurringcostsindex--;
	}
	inputdata.close();
	inputdata.open("VisaCard.txt");
	inputdata >> visacardlimitt >> visacard;
	inputdata.close();
	visacardlimit = visacardlimitt;
	visacardtotal = visacard;

}
void NetFlow(expenses expenses_arr[], recurringcosts recurringcosts_array[], income income_arr[], int & incomeindex, int & expensesindex, int & recurringcostsindex, float visacardtotal, float visacardlimit)
{
	float all_in = 0, all_out = 0, NetFlowOfMoney = 0;
	int d1, d2, m1, m2, y1, y2;
	cout << "Enter Date Range (Day Month Year): " << endl;
	cout << "From: ";
	cin >> d1 >> m1 >> y1;
	while (cin.fail() || d1 > 31 || d1 < 1 || m1 < 1 || m1 > 12) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid entry,Please enter the right format" << endl;
		cin >> d1 >> m1 >> y1;
	}
	cout << "To: ";
	cin >> d2 >> m2 >> y2;
	while (cin.fail() || d2 > 31 || d2 < 1 || m2 < 1 || m2 > 12) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid entry,Please enter the right format" << endl;
		cin >> d2 >> m2 >> y2;
	}
	int Date1 = (y1 * 10000) + (m1 * 100) + d1;
	int Date2 = (y2 * 10000) + (m2 * 100) + d2;
	int DateInBetween = 0;

	for (int i = 0; i < incomeindex; i++) {
		DateInBetween = (income_arr[i].date_income.year * 10000)
			+ (income_arr[i].date_income.month * 100) + income_arr[i].date_income.day;
		if (DateInBetween >= Date1 && DateInBetween <= Date2)
			all_in += income_arr[i].money;
	}

	for (int i = 0; i < expensesindex; i++) {
		DateInBetween = (expenses_arr[i].date_expenses.year * 10000)
			+ (expenses_arr[i].date_expenses.month * 100) + expenses_arr[i].date_expenses.day;
		if (DateInBetween >= Date1 && DateInBetween <= Date2)
			all_out += expenses_arr[i].money;
	}

	for (int i = 0; i < recurringcostsindex; i++) {
		DateInBetween = (recurringcosts_array[i].date_recurringcosts.year * 10000)
			+ (recurringcosts_array[i].date_recurringcosts.month * 100)
			+ recurringcosts_array[i].date_recurringcosts.day;
		if (DateInBetween >= Date1 && DateInBetween <= Date2)
			all_out += recurringcosts_array[i].money;
	}
	all_out -= (visacardlimit - visacardtotal);
	NetFlowOfMoney = all_in - all_out;
	cout << "The net flow of money in: " << all_in << endl << "The net flow of money out: " << all_out << endl;
	cout << "The total net flow money in and out for that period: " << NetFlowOfMoney << endl;
}


void visaCard_fn(expenses expenses_arr[], recurringcosts recurringcosts_array[], float& visacardtotal, int &expensesindex, int&recurringcostsindex, float &visacardlimit)
{
	if (visacardtotal == 0) {
		cout << "How much do you have in your visa card?" << endl;
		cin >> visacardtotal;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry, Please re-enter the amount of your visa card" << endl;
			cin >> visacardtotal;
		}visacardlimit = visacardtotal;
	}
	cout << "Your Visa card limit is " << visacardlimit << endl;
	cout << "You now have:" << visacardtotal << "  left in your visa card" << endl;
	int index;
	int dayofpayment = 25, monthofpayment = 0, yearofpayment = 0;
	while (true) {
		cout << "1)Status\t" << "2)Exit" << endl;
		cin >> index;
		while (cin.fail() || index > 2 || index < 1) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please choose a number from the menu above" << endl;
			cin >> index;
		}
		if (index == 2) break;
		else {
			if (visacardtotal == visacardlimit) {

				cout << " You didn't use your visa " << endl;
				break;

			}
			cout << "1)Expenses\t" << "2)Recurringcosts\t" << "3)Both" << endl;
			cin >> index;
			while (cin.fail() || index > 3 || index < 1) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid entry,Please choose a number from the menu above" << endl;
				cin >> index;
			}
			if (index == 1 || index == 3) {
				for (int i = 0; i < expensesindex; i++) {
					if (expenses_arr[i].type == "visa") {
						if (expenses_arr[i].date_expenses.month == 12) {
							yearofpayment = expenses_arr[i].date_expenses.year + 1;
							monthofpayment = 1;
						}
						else {
							monthofpayment = expenses_arr[i].date_expenses.month + 1;
							yearofpayment = expenses_arr[i].date_expenses.year;
						}
						cout << "You paid " << expenses_arr[i].money << " for " << expenses_arr[i].name << " on date " << expenses_arr[i].date_expenses.day << "/" << expenses_arr[i].date_expenses.month << "/" << expenses_arr[i].date_expenses.year << endl;
						cout << "You have to pay it back to the bank before " << dayofpayment << "/" << monthofpayment << "/" << yearofpayment << endl;
					}
				}
			}
			if (index == 2 || index == 3) {
				for (int i = 0; i < recurringcostsindex; i++) {
					if (recurringcosts_array[i].type == "visa") {
						if (recurringcosts_array[i].date_recurringcosts.month == 12) {
							yearofpayment = recurringcosts_array[i].date_recurringcosts.year + 1;
							monthofpayment = 1;
						}
						else {
							monthofpayment = recurringcosts_array[i].date_recurringcosts.month + 1;
							yearofpayment = recurringcosts_array[i].date_recurringcosts.year;
						}
						cout << "You paid \n" << recurringcosts_array[i].money << " for " << recurringcosts_array[i].name << "on date" << recurringcosts_array[i].date_recurringcosts.day << "/" << recurringcosts_array[i].date_recurringcosts.month << "/" << recurringcosts_array[i].date_recurringcosts.year << endl;
						cout << "You have to pay it back to the bank before: \n " << dayofpayment << "/" << monthofpayment << "/" << yearofpayment << endl;
					}
				}
			}

		}
	}
}
