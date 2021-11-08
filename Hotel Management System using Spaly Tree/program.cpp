#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <stack>
#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

class Room
{
	struct node
	{
		int count ;
		int room_num;
		string cus_name;
		int no_of_days;
		string room_type;
		node *left;
		node *right;
		node()
		{
			count = 0;
		}
	};
	
	public:
		static int count;
		Room();
		~Room();
		node *nullRecord, *root;
		void Book_Room(int,string,int,string);
		void Leave_room(int);
		void splay(int, node *&);
		bool contains(int);
		bool Is_Empty();
		void Make_Empty(node *&);
		void Display_Rooms(node *);
		void print(node *&);
		void rotate_with_left_child(node *&);
		void rotate_with_right_child(node *&);
		void search_Room(int);
		void Frequent_keys();
		void sort(vector<node *>&);
        void search_by_name(const string &);
        bool name_found( string &);
        void search_by_name(node * n, const string &);
        bool name_found(node * n, const string &);
        void Calc_amount(string,int);
};




int accept_room_num();
string accept_cus_name();
int accept_no_of_days();
string accept_type();

int main()
{
	Room rm;
	int ch;
	cout << "\n======================== HOTEL MANAGEMENT SYSTEM USING SPLAY TREE ============================\n "; 

	do
	{
		cout << "\n1. Book a Room\n";
		cout << "2. Leave a Room\n";
		cout << "3. Display the Rooms Booked Information\n";
		cout << "4. Check the availability of Room\n";
		cout << "5. Search By customer Name\n";
		cout << "6. Frequently searched Room number\n";
		cout << "7. Find the cost of Room\n";
		cout << "8. Exit\n\n";
		cout << "Enter your choice : ";
		cin >> ch;
		switch (ch)
		{
		case 1:
		{
			string cus_name, room_type;
			string pay_amt_ch;
			int no_of_days,room_num;
			cus_name = accept_cus_name();
			room_num = accept_room_num();
			room_type = accept_type();
			no_of_days =accept_no_of_days();
			rm.Book_Room(room_num,cus_name,no_of_days,room_type);
			cout<<"\nDo you want to pay amount Now? (Y/N) :";
			cin>>pay_amt_ch;
			string cho = "Y";
			if(pay_amt_ch == cho){
			    rm.Calc_amount(room_type,no_of_days);
			}
			else{
			    cout<<"\nThanks for booking the Room, You can Pay amount Later!\n";
			}
			break;
		}

		case 2:
		{
			int room_num;
			room_num = accept_room_num();
			rm.Leave_room(room_num);
			cout << "\nYou left the room successfully! \n Thanks for Visiting!!\n";
			break;
		}

		case 3:
		{
			rm.count = 0;
			if (rm.Is_Empty())
			{
				cout << endl
					 << "\n No Rooms are Booked Yet !!! \n";
				break;
			}
			rm.Display_Rooms(rm.root);
			cout << endl;
			break;
		}

		case 4:
		{
			int room_num;
			room_num = accept_room_num();
			rm.search_Room(room_num);
			break;
		}

		case 5:
		{
			string search_name;
			search_name = accept_cus_name();

			if (!rm.name_found(search_name))
				cout << "\nThere are no records with customer name " << search_name << endl;

			else
			{
			    cout << "\n-------------------------------------------------------------------------------------------------------------\n";
                cout << "Customer Name\t\t\tRoom number\t\t\tRoom Type\t\t\tNo Of Days Stay" << endl;
                cout << "---------------------------------------------------------------------------------------------------------------\n";
            	rm.search_by_name(search_name);
            	cout << "---------------------------------------------------------------------------------------------------------------\n";
        	}
			break;
		}

		
		case 6:
		{
			rm.Frequent_keys();
			break;
		}

		case 7:
		{  
            string room_type=accept_type();
            int no_of_days = accept_no_of_days();
            rm.Calc_amount(room_type,no_of_days);
            break;
		}


		}

	} while (ch != 8);
	cout << "\nExiting....Thank you! ............Visit Again!!\n";
	return 0;
}

int accept_room_num()
{
	int room_num;
	cout << endl
		 << "Enter the Room number you want : ";
	cin >> room_num;
	return room_num;
}

string accept_cus_name()
{
	string cus_name;
	cout << endl
		 << "Enter your name : ";
	getline(cin >> ws, cus_name);
	return cus_name;
}

string accept_type(){
    
	string room_type;
	cout<<endl<<"Enter Room type AC/Non_AC :";
	getline(cin >> ws, room_type);
	return room_type;
}


int accept_no_of_days(){
	int no_of_days;
	cout << endl
		 << "Enter Num of days you want to stay : ";
	cin >> no_of_days;
	return no_of_days;
}


Room :: Room()
{
	nullRecord = new node;
	nullRecord->left = nullRecord->right = nullRecord;
	root = nullRecord;
}

Room ::~Room()
{
	Make_Empty(root);
	delete root;
}

void Room :: Book_Room(int room_num, string cus_name,int no_of_days,string room_type )
{
    node *newRecord = new node;
	newRecord->left = newRecord->right = nullRecord;
	newRecord->room_num = room_num;
	newRecord->cus_name = cus_name;
	newRecord->no_of_days = no_of_days;
	newRecord->room_type = room_type;


	if (root == nullRecord)
		root = newRecord;

	else
	{
		splay(room_num,root);
		if (room_num < root->room_num)
		{
			newRecord->left = root->left;
			newRecord->right = root;
			root->left = nullRecord;
			root = newRecord;
		}

		else if (room_num > root->room_num)
		{
			newRecord->right = root->right;
			newRecord->left = root;
			root->right = nullRecord;
			root = newRecord;
		}

		else
			return;
	}
	cout << "\nYour Room is successfully Booked!! Have a Happy Stay :) \n";
}

void Room ::splay(int room_num, node *&t)
{
	node header;
	header.left = header.right = nullRecord;
	node *leftTreeMax, *rightTreeMin;
	leftTreeMax = rightTreeMin = &header;
	nullRecord->room_num = room_num;
	while (1)
	{
		if (room_num < t->room_num)
		{
			if (room_num < t->left->room_num)
				rotate_with_left_child(t);

			if (t->left == nullRecord)
				break;

			rightTreeMin->left = t;
			rightTreeMin = t;
			t = t->left;
		}

		else if (room_num > t->room_num)
		{
			if (room_num > t->right->room_num)
				rotate_with_right_child(t);

			if (t->right == nullRecord)
				break;

			leftTreeMax->right = t;
			leftTreeMax = t;
			t = t->right;
		}

		else
			break;
	}
	leftTreeMax->right = t->left;
	rightTreeMin->left = t->right;
	t->left = header.right;
	t->right = header.left;
}

void Room ::rotate_with_left_child(node *&k2)
{
	node *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1;
}

void Room ::rotate_with_right_child(node *&k2)
{
	node *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2 = k1;
}

void Room :: Leave_room(int room_num)
{
	node *newTree = NULL;
	if (!contains(room_num))
	{
		cout << room_num << " is not present Please enter your Correct Room Number!!\n\n";
		return;
	}

	if (root->right == nullRecord)
		newTree = root->left;

	else
	{
		newTree = root->right;
		splay(room_num, newTree);
		newTree->left = root->left;
	}
	delete root;
	root = newTree;
}

bool Room ::contains(int room_num)
{
	splay(room_num, root);
	return root->room_num == room_num;
}

bool Room ::Is_Empty()
{
	return root == nullRecord;
}

void Room ::Make_Empty(node *&t)
{
	while (t != nullRecord)
		Leave_room(t->room_num);
}

int Room::count = 0;

void Room :: Display_Rooms(node *t)
{
	if (t == NULL)
	{
		cout << "\nZero entries!!\n";
		return;
	}
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "Customer Name\t\t\tRoom number\t\t\tRoom Type\t\t\tNo Of Days Stay" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------\n";
	print(t);
	cout << "---------------------------------------------------------------------------------------------------------------\n";
}

void Room ::print(node *&t) //Preorder traversal
{
	if (t != t->left)
	{
		cout << t->cus_name << "\t\t\t" << t->room_num <<"\t\t\t\t"<<t->room_type<<"\t\t\t\t"<<t->no_of_days<<endl;
	
		print(t->left);
		print(t->right);
	}
}

void Room :: search_Room(int room_num)
{
	if (!contains(room_num))
	{
		cout << room_num << " is not Not booked yet! Is available for Booking !!!\n";
		return;
	}
	cout << endl;
	cout << "\n Room Number is already Booked !!\nDetails:\n";
	cout << "Customer Name : " << root->cus_name << endl;
	cout << "Room number : " << root->room_num << endl;
	cout<< "Room Type: " <<root->room_type << endl;
	cout<< "No of Days Stay: "<< root->no_of_days <<endl;
	root->count++;
}

void Room :: Calc_amount(string room_type,int no_of_days)
{
      float non_ac=500,ac=1000,total_amt;
      if(room_type=="Non_AC"){
          total_amt=non_ac*no_of_days;   
      }
      else{
          total_amt=ac*no_of_days;
      }
      cout<<"\n Amount to be paid is : "<<total_amt<<"\n";
}

void Room ::Frequent_keys()
{
	vector<node *> Frequents;
	stack<node *> TEMP_Stk;
	if (Is_Empty())
	{
		cout << "\nZero records !!\n";
		return;
	}
	TEMP_Stk.push(root);
	while (TEMP_Stk.size() != 0)
	{
		node *temp = TEMP_Stk.top();
		TEMP_Stk.pop();
		if (temp->count > 0)
		{
			Frequents.push_back(temp);
			sort(Frequents);
		}

		if (temp->right != nullRecord)
			TEMP_Stk.push(temp->right);

		if (temp->left != nullRecord)
			TEMP_Stk.push(temp->left);
	}

	if (Frequents.size() == 0)
	{
		cout << "\nNo Room was searched\n";
		return;
	}
	cout << endl;
	for (int i = 0; i < Frequents.size(); i++)
	{
		cout << "Customer Name : " << Frequents[i]->cus_name << endl;
		cout << "Room number : " << Frequents[i]->room_num << endl;
		cout << "Search frequency : " << Frequents[i]->count << endl
			 << endl;
	}
}

void Room  ::sort(vector<node *> &Frequents)
{
	int size = Frequents.size();
	node *last = Frequents[size - 1];
	int i = size - 2;
	while (i >= 0 && Frequents[i]->count < last->count)
	{
		Frequents[i + 1] = Frequents[i];
		i--;
	}
	Frequents[i + 1] = last;
}

bool Room ::name_found(node *n, const string &str)
{
	if (n == nullRecord)
		return false;

	string t = n->cus_name;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	if (t.compare(str) == 0)
		return true;

	return name_found(n->left, str) || name_found(n->right, str);
}

bool Room ::name_found(string &n)
{
	transform(n.begin(), n.end(), n.begin(), ::tolower);

	if (root == nullRecord)
		return false;

	return name_found(root, n);
}

void Room::search_by_name(node *n, const string &search_string)
{
	if (n == nullRecord)
		return;

	string s = n->cus_name;
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	if (s.compare(search_string) == 0)
	{
		cout << n->cus_name << "\t\t\t" << n->room_num << "\t\t\t" << n->room_type << "\t\t\t" << n->no_of_days << endl;
		n->count++;
	}

	search_by_name(n->left, search_string);
	search_by_name(n->right, search_string);
}

void Room ::search_by_name(const string &search_name)
{
	search_by_name(root, search_name);
}

