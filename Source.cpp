#include"RBT.h"

#include<iostream>
#include<fstream>
using namespace std;

void Menu();
void Operation(RBT<int> & R);

int main()
{

	RBT<int> T;
	T.Insert(25);
	T.Insert(36);
	T.Insert(85);
	T.Insert(22);
	T.Insert(78);
	T.Insert(77);
	T.Insert(76);
	T.Insert(66);

	T.Display_Parent();

	//T.Print(5);
	cout << endl;

	return 0;
}

void Read_File(RBT<int> &R,char *arr)
{
	ifstream fin;
	fin.open(arr);
	if (!fin)
	{
		cout << "File not found !!!!!!!!!..........\n";
		return;
	}
	int V;
	while (fin)
	{
		fin >> V;
		if (fin)
		{
			R.Insert(V);
		}
	}
	fin.close();
}
void Operation(RBT<int> & R)
{
	int opt = 0;
	char ch = 'y';
	Menu();
	cout << "\n\nEnter you option :  ";
	cin >> opt;
	while (ch!='\n')
	{
		cout << "\n\nEnter you option :  ";
		cin >> opt;
		switch (opt)
		{
		case 1:
			Read_File(R, "input.txt");
			break;
		case 2:
			cout << "\nEnter a value to delete a node in tree : ";
			cin >> opt;
			R.Delete(opt);
			break;
		case 3:
			cout << "\nEnter a value to search a node in tree : ";
			cin >> opt;
			R.Seaching(opt);
		case 4:
			R.Print(opt);
			break;
		case 5:
			R.Print(opt);
			break;
		case 6:
			R.Print(opt);
			break;
		case 7:
			R.Print(opt);
			break;
		case 8:
			R.Print(opt);
			break;
		case 9:
			R.Print(opt);
			break;
		case 10:
			R.Destory();
		case 11:
			break;
		case 12:
			R.Display_Parent();
		case 13:
			Read_File(R, "input.txt");
			break;
		case 14:
			break;
		case 15:
			R.Copy();
			break;
		case 16:
			R.Destory();
		case 17:
			break;
			

		default:
			break;
		}
	}
}
void Menu()
{
	cout << "*******Red Black Tree********\n";
	cout << "Press 1 to insert values in the tree";
	cout << "\nPress 2 to delete a value from the tree";
	cout << "\nPress 3 for searching a value from the tree";
	cout << "\nPress 4 for pre-order traversal NLR";
	cout << "\nPress 5 for in-order traversal LNR";
	cout << "\nPress 6 for post-order traversal LRN";
	cout << "\nPress 7 for pre-order traversal 2 NRL";
	cout << "\nPress 8 for in-order traversal 2 RNL";
	cout << "\nPress 9 for post-order traversal 2 RLN";
	cout << "\nPress 10 to destroy the tree(all nodes must be deleted)";
	cout << "\nPress 11 to delete all values in the tree greater than X";
	cout << "\nPress 12 for displaying parent of a node present in Tree";
	cout << "\nPress 13 to read integer values from the file “input.txt ";
	cout << "\nPress 14 to delete all duplicate values from the tree";
	cout << "\nPress 15 to create copy of the tree";
	cout << "\nPress 16 to destroy the complete tree";
	cout << "\nPress 17 to EXIT";

}
