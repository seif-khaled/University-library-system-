//// university _library_system.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
#include<string>
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<stdlib.h>
#include<stdio.h>
#include <sstream>
#include <iostream>
#include<filesystem>
#include<typeinfo>
using namespace std;
class admin {
private:
	string admin_name, admin_id, admin_password;
	fstream admin_file,admin_file_read,admin_file_empty;
	
	
public:
	
	bool add_admins(string name,string id,string password) {
		//checking for duplicate id before appending to file//
	
		//check for name validty
		for (int i = 0; i < name.size(); i++)
		{
			if ((name[i] >= 97 && name[i] <= 122) || (name[i] >= 65 && name[i] <= 90) || (name[i] == 32)) {
				continue;
			}
			else
			{
				cout << "name should only include characters not numbers";
				return false;
			}
		}
		//check for id validty
		for (int i = 0; i < id.size(); i++)
		{
			if (id[i]>=48 && id[i]<=57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers";
				return false;
			}
		}
		admin_file.open("admin.txt", ios::app);
		admin_file.close();
		//admin_file_empty.open("admin.txt", ios::ate);
		admin_file_read.open("admin.txt", ios::in);
		char chr;
		int empty_f = 0;
		while (!admin_file_read.eof())
		{
			admin_file_read.get(chr);
			if (chr >= 33 && chr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		admin_file_read.close();
		//bool empty_file = admin_file_empty.tellg() == 0;
		if (empty_f ==0) {
			admin_name = name;
			admin_id = id;
			admin_password = password;
			admin_file_empty.close();
			admin_file.open("admin.txt", ios::app);
			admin_file << "admin name=" << admin_name << "," << "id=" << admin_id << "," << "admin pass=" << admin_password << "\n";
			admin_file.close();
			//admin_file.close();
			return true;
		}
		/*admin_file_empty.close();*/
		else {
			admin_file_read.open("admin.txt", ios::in);
			char c;
			string check = "";
			while (!admin_file_read.eof())
			{
				admin_file_read.get(c);
				if (c == ',' || c == '=' || c == ':'||c=='\n') {
					if (check == id || check == password)
					{
						cout << "cant append an id or password that already exists";

						return false;
						//exit(EXIT_FAILURE);
						//break;
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;

				}
			}
			admin_file_read.close();
			admin_name = name;
			admin_id = id;
			admin_password = password;
			admin_file.open("admin.txt", ios::app);
			admin_file << "admin name=" << admin_name << "," << "id=" << admin_id << "," << "admin pass=" << admin_password << "\n";
			admin_file.close();
			return true;
		}
	}
	bool get_admin(string id) {
		for (int i = 0; i < id.size(); i++)
		{
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers";
				return false;
			}
		}
		char chr;
		int empty_f = 0;
		admin_file_read.open("admin.txt", ios::in);
		while (!admin_file_read.eof())
		{
			admin_file_read.get(chr);
			if (chr >= 33 && chr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		admin_file_read.close();
		//bool empty_file = admin_file_empty.tellg() == 0;
		if (empty_f == 0)
		{
			cout << "empty file";
			//admin_file_empty.close();
			return false;
		}
		else
		{
			//admin_file_empty.close();
			admin_file_read.open("admin.txt", ios::in);
			char c;
			string check = "";
			int index = 0;
			int counter = 0;
			int exist=0;
			while (!admin_file_read.eof())
			{
				admin_file_read.get(c);
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (c=='\n')
					{
						counter++;
					}
					if (check == id )
					{
						index = counter;
						exist = 1;
						break;
					}
					else
					{
						check += c;
						check = "";
					}
				}
				else
				{
					check += c;

				}
			}
			admin_file_read.close();
			if (exist==1)
			{
				admin_file_read.open("admin.txt", ios::in);
				string l;
				int counter2 = 0;
				while (getline(admin_file_read, l))
				{
					if (counter2 == index)
					{
						cout << l << endl;
						break;
					}
					counter2++;
				}
				admin_file_read.close();
				return true;
			}
			else if(exist==0)
			{
				cout << "no such id exist "<<endl;
				return false;
			}
			
		}
	}
	bool login(string name,string password) {
		admin_file_read.open("admin.txt", ios::in);
		char c;
		int flag = 0;
		while (!admin_file_read.eof())
		{
			admin_file_read.get(c);
			if (c >= 33 && c <= 126)
			{
				flag = 1;
				break;
			}
		}
		admin_file_read.close();
		if (flag == 0)
		{
			cout << "no admins in the admin file in order to find a matching password\n";
			cout << "please add an admin in order to proceed....\n";
			string lib_name, lib_id, lib_pass;
			getline(cin, lib_name);
			cin >> lib_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, lib_pass);
			//add_librarians(lib_name, lib_id, lib_pass);
			this->add_admins(lib_name, lib_id, lib_pass);
		}
		else
		{
			char c;
			string check = "";
			int name_check = -1, password_check = -1;
			admin_file_read.open("admin.txt", ios::in);
			while (!admin_file_read.eof())
			{
				admin_file_read.get(c);
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (check == password)
					{
						password_check = 1;
						break;
						/*cout << "logged in" << endl;
						return true;*/
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;

				}
			}
			admin_file_read.close();
			admin_file_read.open("admin.txt", ios::in);
			while (!admin_file_read.eof())
			{
				admin_file_read.get(c);
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (check == name)
					{
						name_check = 1;
						break;
						/*cout << "logged in" << endl;
						return true;*/
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;

				}
			}
			admin_file_read.close();
			if (name_check == 1 && password_check == 1)
			{
				cout << "logged in" << endl;
				return true;
			}
			else
			{
				cout << "incorrect username or password" << endl;
				return false;
			}

			//return false;
		}


	}
	void logout() {
		cout << "logged out" << endl;
		exit(0);
	}
	bool remove_admins(string id) {
		//check for id validty
		for (int i = 0; i < id.size(); i++)
		{
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers";
				return false;
			}
		}
		char chr;
		int empty_f = 0;
		admin_file_read.open("admin.txt", ios::in);

		while (!admin_file_read.eof())
		{
			admin_file_read.get(chr);
			if (chr >= 33 && chr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		admin_file_read.close();
		//bool empty_file = admin_file_empty.tellg() == 0;
		if (empty_f == 0)
		{
			cout << "empty file";
			//admin_file_empty.close();

			return false;
		}
		else
		{
			admin_file_read.open("admin.txt", ios::in);
			char c;
			string check = "";
			int counter = 0;
			int row_num_tobe_removed=-1;
			bool id_found = false;
			while (!admin_file_read.eof())
			{
				admin_file_read.get(c);
				if (c=='\n')
				{
					counter ++;
				}
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (check == id )
					{
						row_num_tobe_removed = counter;
						id_found = true;
						
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;
				}
			}
			admin_file_read.close();

			vector<string>lines;
			if (id_found == true) {
				admin_file_read.open("admin.txt", ios::in);
				string line;
				char c2;
	
				//int counter2 = 0;
				while (!admin_file_read.eof())
				{
		
					admin_file_read.get(c2);
					if (c2 == '\n')
					{
				
						line += c2;
						lines.push_back(line);
						line = "";
					
					}
					else
					{
						line += c2;
	
					}
				}
				admin_file_read.close();
				remove("admin.txt");
				fstream new_file; 
				new_file.open("admin2.txt", ios::app);
				for (int i = 0; i < lines.size(); i++)
				{
					if (i==row_num_tobe_removed)
					{
						continue;
					}
					else
					{
						new_file << lines[i];
						//cout << lines[i];
					}
				}
				new_file.close();
				rename("admin2.txt", "admin.txt");
				return true;
			}
			else
			{
				cout << "no such admin exist";
				return false;
			}
			
			
		}

	}
};
class librarian {
private:
	string librarian_name, librarian_id, librarian_pass;
	fstream librarian_file,librarian_file_empty,librarian_file_read;
public:
	bool add_librarians(string name, string id, string password) {
		//check for name validty
		for (int i = 0; i < name.size(); i++)
		{
			if ((name[i] >= 97 && name[i] <= 122) || (name[i] >= 65 && name[i] <= 90) || (name[i] == 32)) {
				continue;
			}
			else
			{
				cout << "name should only include characters not numbers";
				return false;
			}
		}
		//check for id validty
		for (int i = 0; i < id.size(); i++)
		{
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers";
				return false;
			}
		}
		librarian_file.open("librarian.txt", ios::app);
		librarian_file.close();
		char chr;
		int empty_f = 0;
		librarian_file_read.open("librarian.txt", ios::in);
		while (!librarian_file_read.eof())
		{
			librarian_file_read.get(chr);
			if (chr >= 33 && chr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		librarian_file_read.close();
		//bool empty_file = admin_file_empty.tellg() == 0;
		if (empty_f == 0) {
			librarian_name = name;
			librarian_id = id;
			librarian_pass = password;
			librarian_file_empty.close();
			librarian_file.open("librarian.txt", ios::app);
			librarian_file << "librarian name=" << librarian_name << "," << "id=" << librarian_id << "," << "librarian pass=" << librarian_pass << "\n";
			librarian_file.close();
			return true;
		}
		else {
			char c;
			string check = "";
			librarian_file_read.open("librarian.txt", ios::in);
			while (!librarian_file_read.eof())
			{
				librarian_file_read.get(c);
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (check == id || check == password)
					{
						cout << "cant append an id or password that already exists";
						return false;
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;

				}
			}
			librarian_file_read.close();
			librarian_name = name;
			librarian_id = id;
			librarian_pass = password;
			librarian_file.open("librarian.txt", ios::app);
			librarian_file << "librarian name=" << librarian_name << "," << "id=" << librarian_id << "," << "librarian pass=" << librarian_pass << "\n";
			librarian_file.close();
			return true;
		}
	}
	bool get_librarian(string id) {
		for (int i = 0; i < id.size(); i++)
		{
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers"<<endl;
				return false;
			}
		}
		char chr;
		int empty_f = 0;
		librarian_file_read.open("librarian.txt", ios::in);
		while (!librarian_file_read.eof())
		{
			librarian_file_read.get(chr);
			if (chr >= 33 && chr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		librarian_file_read.close();
		//bool empty_file = admin_file_empty.tellg() == 0;
		if (empty_f == 0)
		{
			cout << "empty file"<<endl;
			//librarian_file_empty.close();
			return false;
		}
		else
		{
			//librarian_file_empty.close();
			librarian_file_read.open("librarian.txt", ios::in);
			char c;
			string check = "";
			int index = 0;
			int counter = 0;
			int exist = 0;
			while (!librarian_file_read.eof())
			{
				librarian_file_read.get(c);
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (c == '\n')
					{
						counter++;
					}
					if (check == id)
					{
						index = counter;
						exist = 1;
						break;
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;

				}
			}
			librarian_file_read.close();
			if (exist==1)
			{
				librarian_file_read.open("librarian.txt", ios::in);
				string l;
				int counter2 = 0;
				while (getline(librarian_file_read, l))
				{
					if (counter2 == index)
					{
						cout << l << endl;
						break;
					}
					counter2++;
				}
				librarian_file_read.close();
				return true;
			}
			else if(exist==0)
			{
				cout << "no such id exists";
				return false;
			}
			
		}
	}
	bool login(string name,string password) {
		librarian_file_read.open("librarian.txt", ios::in);
		char c;
		int flag = 0;
		while (!librarian_file_read.eof())
		{
			librarian_file_read.get(c);
			if(c >= 33 && c <= 126)
			{
				flag = 1;
				break;
			}
		}
		librarian_file_read.close();
		if (flag==0)
		{
			cout << "no librarians in the librarian file in order to find a matching password\n";
			cout << "please add a librarian in order to proceed....\n";
			string lib_name, lib_id, lib_pass;
			getline(cin, lib_name);
			cin >> lib_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, lib_pass);
			//add_librarians(lib_name, lib_id, lib_pass);
			this->add_librarians(lib_name, lib_id, lib_pass);
		}
		else
		{
			char c;
			string check = "";
			int name_check = -1, password_check = -1;
			librarian_file_read.open("librarian.txt", ios::in);
			while (!librarian_file_read.eof())
			{
				librarian_file_read.get(c);
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (check == password)
					{
						password_check = 1;
						break;
						/*cout << "logged in" << endl;
						return true;*/
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;

				}
			}
			librarian_file_read.close();
			librarian_file_read.open("librarian.txt", ios::in);
			while (!librarian_file_read.eof())
			{
				librarian_file_read.get(c);
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (check == name)
					{
						name_check = 1;
						break;
						/*cout << "logged in" << endl;
						return true;*/
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;

				}
			}
			librarian_file_read.close();
			if (name_check == 1 && password_check == 1)
			{
				cout << "logged in" << endl;
				return true;
			}
			else
			{
				cout << "incorrect username or password" << endl;
				return false;
			}

			//return false;
		}
		
		
	}
	void logout() {
		cout << "logged out" << endl;
		exit(0);
	}
	bool remove_librarian(string id) {
		for (int i = 0; i < id.size(); i++)
		{
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers";
				return false;
			}
		}
		char chr;
		int empty_f = 0;
		librarian_file_read.open("librarian.txt", ios::in);
		while (!librarian_file_read.eof())
		{
			librarian_file_read.get(chr);
			if (chr >= 33 && chr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		librarian_file_read.close();
		//bool empty_file = admin_file_empty.tellg() == 0;
		if (empty_f == 0)
		{
			cout << "empty file";
			librarian_file_empty.close();

			return false;
		}
		else
		{
			librarian_file_read.open("librarian.txt", ios::in);
			char c;
			string check = "";
			int counter = 0;
			int row_num_tobe_removed = -1;
			bool id_found = false;
			while (!librarian_file_read.eof())
			{
				librarian_file_read.get(c);
				if (c == '\n')
				{
					counter++;
				}
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (check == id)
					{
						row_num_tobe_removed = counter;
						id_found = true;

					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;


				}
			} 
			librarian_file_read.close();

			vector<string>lines;
			if (id_found == true) {
				librarian_file_read.open("librarian.txt", ios::in);
				string line;
				char c2;

				//int counter2 = 0;
				while (!librarian_file_read.eof())
				{

					librarian_file_read.get(c2);
					if (c2 == '\n')
					{

						line += c2;
						lines.push_back(line);
						line = "";

					}
					else
					{
						line += c2;

					}
				}
				librarian_file_read.close();
				remove("librarian.txt");
				fstream new_file;
				new_file.open("librarian2.txt", ios::app);
				for (int i = 0; i < lines.size(); i++)
				{
					if (i == row_num_tobe_removed)
					{
						continue;
					}
					else
					{
						new_file << lines[i];
						//cout << lines[i];
					}
				}
				new_file.close();
				rename("librarian2.txt", "librarian.txt");
				return true;
			}
			else
			{
				cout << "no such librarian exist";
				return false;
			}


		}
	}

};
class student {
private:
	string student_name, student_id, student_birthday, student_email, mobile_number;
	fstream studentdata_file,student_file_read,student_file_empty;

public:
	bool add_students(string name,string id,string birthday,string email,string mobile_num) {
		//check for name validty
		int validator1 = 0;
		for (int i = 0; i < name.size(); i++)
		{
			if ((name[i] >= 97 && name[i] <= 122) || (name[i] >= 65 && name[i] <= 90) || (name[i] == 32)) {
				continue;
			}
			else
			{
				cout << "name should only include characters not numbers\n";
				break;
				validator1 = 1;
				return false;
			}
		}
		int validator2 = 0;
		if (validator1 == 1) {
			cout << "couldnt excute";
		}
		else
		{
			//check for id validty
			for (int i = 0; i < id.size(); i++)
			{
				if (id[i] >= 48 && id[i] <= 57) {
					continue;
				}
				else
				{
					cout << "id should only contain numbers\n";
					validator2 = 1;
					break;
					return false;
				}
			}
		}
		if (validator2 == 1 && validator1 == 1) {
			cout << "couldnt excute";
		}
		else
		{
			studentdata_file.open("student.txt", ios::app);
			studentdata_file.close();
			char chr;
			int empty_f = 0;
			student_file_read.open("student.txt", ios::in);
			while (!student_file_read.eof())
			{
				student_file_read.get(chr);
				if (chr >= 33 && chr <= 126)
				{
					empty_f = 1;
					break;
				}
			}
			student_file_read.close();
			//bool empty_file = admin_file_empty.tellg() == 0;
			if (empty_f == 0) {
				//cout << "ana hna ya joe";
				student_name = name;
				student_id = id;
				student_birthday = birthday;
				student_email = email;
				mobile_number = mobile_num;
				//student_file_empty.close();
				studentdata_file.open("student.txt", ios::app);
				studentdata_file << "student name=" << student_name << "," << "id=" << student_id << "," << "student birthday=" << student_birthday << "," << "student email=" << student_email << "," << "student mobile number=" << mobile_number << "\n";
				studentdata_file.close();
				return true;
			}
			else {
				char c;
				string check = "";
				int validator3 = 0;
				student_file_read.open("student.txt", ios::in);
				while (!student_file_read.eof())
				{
					student_file_read.get(c);
					if (c == ',' || c == '=' || c == ':' || c == '\n') {	   
						if ((check == id) || (check == email) || (check == mobile_num))
						{
							cout << "cant append an id or email or mobile num that already exists\n";
							validator3 = 1;
							break;
							//return false;
							/*if (validator3==1)
							{
								cout << "couldnt excute\n";
								break;
							}*/
						}
						else
						{
							check += c;
							check = "";

						}
					}
					else
					{
						check += c;

					}
				}
				student_file_read.close();
				if (validator3==1)
				{
					cout << "cant excute\n";
				}
				else {
					student_name = name;
					student_id = id;
					student_birthday = birthday;
					student_email = email;
					mobile_number = mobile_num;
					studentdata_file.open("student.txt", ios::app);
					studentdata_file << "student name=" << student_name << "," << "id=" << student_id << "," << "student birthday=" << student_birthday << "," << "student email=" << student_email << "," << "student mobile number=" << mobile_number << "\n";
					studentdata_file.close();
				}
				
				return true;
			}
		}
		
	}
	bool get_student(string id) {
		for (int i = 0; i < id.size(); i++)
		{
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers" << endl;
				return false;
			}
		}
		char chr;
		int empty_f = 0;
		student_file_read.open("student.txt", ios::in);
		while (!student_file_read.eof())
		{
			student_file_read.get(chr);
			if (chr >= 33 && chr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		student_file_read.close();
		//bool empty_file = admin_file_empty.tellg() == 0;
		if (empty_f == 0)
		{
			cout << "empty file" << endl;
			//student_file_empty.close();
			return false;
		}
		else
		{
			//student_file_empty.close();
			student_file_read.open("student.txt", ios::in);
			char c;
			string check = "";
			int index = 0;
			int counter = 0;
			int exist = 0;
			while (!student_file_read.eof())
			{
				student_file_read.get(c);
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (c == '\n')
					{
						counter++;
					}
					if (check == id)
					{
						index = counter;
						exist = 1;
						break;
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;

				}
			}
			student_file_read.close();
			if (exist == 1)
			{
				student_file_read.open("student.txt", ios::in);
				string l;
				int counter2 = 0;
				while (getline(student_file_read, l))
				{
					if (counter2 == index)
					{
						cout << l << endl;
						break;
					}
					counter2++;
				}
				student_file_read.close();
				cout << "\n";
				return true;
			}
			else if (exist == 0)
			{
				cout << "no such id exists\n";
				return false;
			}

		}
	}
	bool remove_students(string id) {
		for (int i = 0; i < id.size(); i++) {
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers\n";
				return false;
			}
		}
		studentdata_file.open("student.txt", ios::app);
		studentdata_file.close();
		char chr;
		int empty_f = 0;
		student_file_read.open("student.txt", ios::in);
		while (!student_file_read.eof())
		{
			student_file_read.get(chr);
			if (chr >= 33 && chr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		student_file_read.close();
		if (empty_f == 0)
		{
			cout << "empty file\n";
			//student_file_empty.close();

			return false;
		}
	/*	else if ()
		{

		}*/
		else
		{
			student_file_read.open("student.txt", ios::in);
			char c;
			string check = "";
			int counter = 0;
			int row_num_tobe_removed = -1;
			bool id_found = false;
			while (!student_file_read.eof())
			{
				student_file_read.get(c);
				if (c == '\n')
				{
					counter++;
				}
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (check == id)
					{
						row_num_tobe_removed = counter;
						id_found = true;

					}
					else
					{
						check += c;
						check = "";
					}
				}
				else
				{
					check += c;
				}
			}
			student_file_read.close();
			vector<string>lines;
			if (id_found == true) {
				student_file_read.open("student.txt", ios::in);
				string line;
				char c2;

				//int counter2 = 0;
				while (!student_file_read.eof())
				{

					student_file_read.get(c2);
					if (c2 == '\n')
					{

						line += c2;
						lines.push_back(line);
						line = "";

					}
					else
					{
						line += c2;

					}
				}
				student_file_read.close();
				remove("student.txt");
				fstream new_file;
				new_file.open("student2.txt", ios::app);
				for (int i = 0; i < lines.size(); i++)
				{
					if (i == row_num_tobe_removed)
					{
						continue;
					}
					else
					{
						new_file << lines[i];
						//cout << lines[i];
					}
				}
				new_file.close();
				rename("student2.txt", "student.txt");
				cout << "\n";
				return true;
			}
			else
			{
				cout << "no such student exist in the file\n";
				return false;
			}


		}
	}

};
class issued_books {
private:
	string procedure_id;
	string book_id, student_id,book_name;
	bool returned=false;

	fstream issuedbooks_file,issuedbooks_file_read,issuedbooks_file_empty;
	fstream studentf_read, bookf_read,studentf_empty,bookf_empty,bookf_write;
public:
	void issue_book(string b_id, string s_id) {

		int current_loop = 0;
		//check for student id and book id validty
		for (int i = 0, j = 0; i < b_id.size() && j < s_id.size(); i++, j++) {
			if (b_id[i] >= 48 && b_id[i] <= 57) {
				if (s_id[j] >= 48 && s_id[j] <= 57) {
					continue;
				}
				else
				{
					cout << "student id should only contain numbers";
					current_loop = 1;
					break;
					//return false;
				}
			}
			else
			{
				cout << "book id should only contain numbers";
				current_loop = 1;

				break;
				//return false;
			}
		}
		if (current_loop == 1) {
			cout << "couldnt excute";
		}
		else
		{
			
			char chr;
			int empty_f = 0;
			bookf_read.open("books.txt", ios::in);
			while (!bookf_read.eof())
			{
				bookf_read.get(chr);
				if (chr >= 33 && chr <= 126)
				{
					empty_f = 1;
					break;
				}
			}
			bookf_read.close();
			//bool empty_file = admin_file_empty.tellg() == 0;
			
			int found = -1;
			if (empty_f == 0) {
				cout << "book file is empty cant issue book ";
				bookf_empty.close();
			}
			else
			{
				//bookf_empty.close();

				srand(time(0));
				int procedure = rand() % 10000 + 1000;
				string p = to_string(procedure);
				procedure_id = p;
				bookf_read.open("books.txt", ios::in);
				char c;
				string check = "";
				int index = 0;
				while (!bookf_read.eof())
				{
					bookf_read.get(c);
					if (c == '\n') {
						index++;
					}
					if (c == ',' || c == '=' || c == ':' || c == '\n') {
						if (check == b_id)
						{
							book_id = b_id;
							found = index;
							break;
							//return false;
						}
						else
						{
							check += c;
							check = "";

						}
					}
					else
					{
						check += c;

					}
				}
				//cout << found;
				bookf_read.close();
				if (found == -1)
				{
					cout << "no such id exist";
				}
				else
				{
					bookf_read.open("books.txt", ios::in);
					string ll;
					int count = 0;
					while (getline(bookf_read, ll))
					{
						if (count==found)
						{
							break;
						}
						count++;
					}
					bookf_read.close();
					//cout << ll;
					int fourth_equal = 0;
					string b;
					for (int i = 0; i < ll.size(); i++)
					{
						if (fourth_equal==3 && ll[i]!=',')
						{
							b += ll[i];
						}
						if (ll[i]=='=')
						{
							fourth_equal++;
							continue;
						}
						cout << b<<endl;
					}
					//bookf_read.close();
					//cout << b;
					int books_availble = -1;
					stringstream num(b);
					int num_b=0;
					num >> num_b;
					//cout << num_b;
					if (num_b>48)
					{
						books_availble = 1;
					}
					if (books_availble==-1)
					{
						cout << "cant issue this books  no availble qunatity";
					}
					else
					{
						int fifth_equal = 0;
						string issu_num;
						for (int i = 0; i < ll.size(); i++)
						{
							if (fifth_equal == 4 && ll[i] != '\n')
							{
								issu_num += ll[i];
							}
							if (ll[i] == '=')
							{
								fifth_equal++;
								continue;
							}
						}
						stringstream num2(issu_num);
						int num_b2 = 0;
						num2 >> num_b2;
						
						num_b -= 1;
						num_b2 += 1;
						string compare,str_num=to_string(num_b),str_num2=to_string(num_b2);

						string replaced_ll;
						replaced_ll += "book name=";
						replaced_ll += book_name;
						replaced_ll += ",";
						int second_comma=0;
						int line_to_be_replaced=0;
						bookf_read.open("books.txt", ios::in);
						string loop_lines;
						while (getline(bookf_read,loop_lines))
						{
							if (second_comma>1)
							{
								break;
							}
							else
							{
								if (line_to_be_replaced==found)
								{
									for (int i = 0; i < loop_lines.size(); i++)
									{
										if (second_comma>0 && second_comma<3 )
										{
											replaced_ll += loop_lines[i];
										}
										if (loop_lines[i]==','){
											second_comma++;
											continue;
										}
									}
								}
								line_to_be_replaced++;
							}
						}
						bookf_read.close();
						replaced_ll += ",";
						replaced_ll += "availble quantity=";
						replaced_ll += str_num;
						replaced_ll += ",";
						replaced_ll += "issued quantity=";
						replaced_ll += str_num2;
						replaced_ll += ",";
						replaced_ll += "returned=";
						replaced_ll += "false";
						vector<string> lines;
						string l2;
						bookf_read.open("books.txt", ios::in);
						while (getline(bookf_read,l2))
						{

							lines.push_back(l2);
						}
						bookf_read.close();
						//fstream newf;
						bookf_write.open("books2.txt", ios::app);
						for (int i = 0; i < lines.size(); i++)
						{
							if (i==found)
							{
								bookf_write << replaced_ll;
							}
							else
							{
								bookf_write << lines[i];

							}
						}
						bookf_write.close();
						remove("books.txt");
						rename("books2.txt", "books.txt");
						bookf_read.open("books.txt", ios::in);
						char cc;
						string l;
						int counter2 = 0;
						int first_comma = 1;
						string n;
						int found_equal = -1;
						while (getline(bookf_read, l))
						{
							if (counter2 == found)
							{
								for (int i = 0; l[i] != ','; i++)
								{
									if (l[i] == '=')
									{
										found_equal = 1;
										continue;
									}
									if (found_equal == 1)
									{
										//cout << n << endl;
										n += l[i];
									}
								}
								first_comma++;
							}
							else
							{
								counter2++;
							}
							if (first_comma != 1)
							{
								break;
							}
						}

						bookf_read.close();
						book_name = n;
						//n = "";
						//cout << book_name;
					}
					if (found == -1)
					{
						cout << "couldnt excute" << endl;
					}
					else
					{
						//char chr;
						char chrr;
						//char chr;
						int empty_f = 0;
						bookf_read.open("books.txt", ios::in);
						while (!bookf_read.eof())
						{
							bookf_read.get(chrr);
							if (chrr >= 33 && chrr <= 126)
							{
								empty_f = 1;
								break;
							}
						}
						bookf_read.close();
						int found4 = -1;
						if (empty_f == 0)
						{
							cout << "student file is empty no student to issue a book";
							studentf_empty.close();
						}
						else
						{
							char c;
							string check = "";
							
							studentf_read.open("student.txt", ios::in);
							while (!studentf_read.eof())
							{
								studentf_read.get(c);
								if (c == ',' || c == '=' || c == ':' || c == '\n') {
									if (check == s_id)
									{
										student_id = s_id;
										found4 = 1;

									}
									else
									{
										check += c;
										check = "";

									}
								}
								else
								{
									check += c;

								}
							}
							studentf_read.close();

						}
						int same_book = -1;
						int same_student = -1;
						if (found4 == -1)
						{
							cout << "no such id" << endl;
						}
						else
						{

							char chrr2;
							//char chr;
							int empty_f = 0;
							issuedbooks_file_read.open("issued.txt", ios::in);
							while (!issuedbooks_file_read.eof())
							{
								issuedbooks_file_read.get(chrr2);
								if (chrr2 >= 33 && chrr2 <= 126)
								{
									empty_f = 1;
									break;
								}
							}
							issuedbooks_file_read.close();
							//int found4 = -1;
							//if (empty_f == 0)
								if (empty_f == 0)
							{
								//issuedbooks_file_empty.close();
								issuedbooks_file.open("issued.txt", ios::app);
								issuedbooks_file << "book name=" << book_name << "," << "book id=" << book_id << "," << "student id=" << student_id << "," << "procedure id=" << procedure_id << "," << "returned=" << boolalpha << returned << "\n";
								issuedbooks_file.close();
							}
							else
							{
								issuedbooks_file_empty.close();
								issuedbooks_file_read.open("issued.txt", ios::in);
								/*char c;*/
								char c;
								string check = "";
								while (!issuedbooks_file_read.eof())
								{
									issuedbooks_file_read.get(c);
									if (c == ',' || c == '=' || c == ':' || c == '\n') {
										 if (check == book_id) {
												same_book = 1;

												break;

										 }
										 else
										 {
											 check += c;
											 check = "";
										 }
									}
									else
									{
										check += c;

									}
								}
							}
							issuedbooks_file_read.close();
						    issuedbooks_file_read.open("issued.txt", ios::in);
							char c2;
							string checker2;
							while (!issuedbooks_file_read.eof())
								{
								  issuedbooks_file_read.get(c2);
								  if (c2 == ',' || c2 == '=' || c2 == ':' || c2 == '\n') {
									       if (checker2 == student_id) 
										   {
											same_student = 1;
											break;
											
										   }
										else
										{
											checker2 += c2;
											checker2 = "";

										}
								  }
								  else
									{
										checker2 += c2;

								  }
							}
							issuedbooks_file_read.close();
						}
						if (same_book == same_student)
						{
							student_id = "";
							book_name = "";
							book_id = "";
							procedure_id = "";
							cout << "cant issue the same book to the same student";
						}
						else
						{
							issuedbooks_file.open("issued.txt", ios::app);
							issuedbooks_file << "book name=" << book_name << "," << "book id=" << book_id << "," << "student id=" << student_id << "," << "procedure id=" << procedure_id << "," << "returned=" << boolalpha << returned << "\n";
							issuedbooks_file.close();
						}
					}	
				}
			}				
	    }				
	}
	void return_book(string id,string st_id) {
		int ids_only = 1,st_ids_only=-1;
		for (int i = 0; i < id.size(); i++) {
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers\n";
				ids_only = -1;
				break;
				//return false;
			}
		}
		for (int i = 0; i < st_id.size(); i++) {
				if (st_id[i] >= 48 && st_id[i] <= 57) {
					continue;
				}
				else
				{
					cout << "id should only contain numbers\n";
					st_ids_only = -1;
					break;
					//return false;
				}
		}
		if (ids_only==-1 || st_ids_only==-1){
				cout << "couldnt excute program";
		}
		else
			{
				char cc1, cc2;
				string check1, check2;
				int found_sid = -1, found_bid = -1;
				int b_line_index = 0;
				issuedbooks_file_read.open("issued.txt", ios::in);
				while (!issuedbooks_file_read.eof())
				{
					issuedbooks_file_read.get(cc2);
					if (cc2 == '\n')
					{
						b_line_index++;
					}
					if (cc2 == ',' || cc2 == '=' || cc2 == ':' || cc2 == '\n') {
						
						if (check2 == id)
						{
							found_bid = 1;
							break;
							/*student_id = s
							found4 = 1;*/

						}
						else
						{
							check2 += cc2;
							check2 = "";

						}
					}
					else
					{
						check2 += cc2;

					}
				}
				issuedbooks_file_read.close();
				issuedbooks_file_read.open("issued.txt", ios::in);
				while (!issuedbooks_file_read.eof())
				{
					issuedbooks_file_read.get(cc1);
					
					if (cc1 == ',' || cc1 == '=' || cc1 == ':' || cc1 == '\n') {

						if (check1 == st_id)
						{
							found_sid = 1;
							break;
							/*student_id = s
							found4 = 1;*/

						}
						else
						{
							check1 += cc1;
							check1 = "";

						}
					}
					else
					{
						check1 += cc1;

					}
				}
				issuedbooks_file_read.close();
				
				if (found_bid==-1 || found_sid==-1)
				{
					cout << "cant find macthing id\n";
				}
				else
				{
					int issued_check = -1,issued_line_index=0,condition=-1,line_found=0;
					char cc3;
					string issued_q,check3;
					bookf_read.open("books.txt",ios::in);
					while (!bookf_read.eof())
					{
						bookf_read.get(cc3);
						if (cc3 == '\n')
						{
							issued_line_index++;
						}
						if (condition==1 && line_found==issued_line_index)
						{
							issued_q += cc3;
						}
						if (cc3 == ',' || cc3 == '=' || cc3 == ':' || cc3 == '\n') {
							check3 += cc3;
							if (check3 == "issued quantity=")
							{
								line_found = issued_line_index;
								condition = 1;
								continue;
								
								/*found_sid = 1;
								break;*/
								/*student_id = s
								found4 = 1;*/

							}
							
							else
							{
								//check3 += cc3;
								check3 = "";

							}
						}
						else
						{
							check3 += cc3;

						}
					}
					bookf_read.close();
					stringstream num(issued_q);
					int flag1 = 0;
					int num_b = 0;
					int conidtion2 = 0;
					num >> num_b;
					if (num_b>48)
					{
						char cc4;
						bookf_read.open("books.txt", ios::in);
						string line,check4,ava_b;
						int counter = 0;
						while (!bookf_read.eof())
						{
							bookf_read.get(cc4);
							if (cc4 == '\n')
							{
								counter++;
							}
							if (conidtion2 == 1 && line_found == counter)
							{
								ava_b += cc4;
							}
							if (cc4 == ',' || cc4 == '=' || cc4 == ':' || cc4 == '\n') {
								check4 += cc4;
								if (check4 == "availble quantity=")
								{
									line_found = counter;
									conidtion2 = 1;
									continue;

								}

								else
								{
									//check3 += cc3;
									check4 = "";

								}
							}
							else
							{
								check4 += cc4;

							}
						}
						bookf_read.close();
						stringstream num2(ava_b);
						int num_b2 = 0;
						num2 >> num_b2;
						num_b -= 1;
						num_b2 += 1;
						string replaced_ll;
						replaced_ll += "book name=";
						replaced_ll += book_name;
						replaced_ll += ",";
						int second_comma = 0;
						int line_to_be_replaced = 0;
						bookf_read.open("books.txt", ios::in);
						string loop_lines;
						while (getline(bookf_read, loop_lines))
						{
							if (second_comma > 1)
							{
								break;
							}
							else
							{
								if (line_to_be_replaced == line_found)
								{
									for (int i = 0; i < loop_lines.size(); i++)
									{
										if (second_comma > 0 && second_comma < 3)
										{
											replaced_ll += loop_lines[i];
										}
										if (loop_lines[i] == ',') {
											second_comma++;
											continue;
										}
									}
								}
								line_to_be_replaced++;
							}
						}
						bookf_read.close();
						string str_num1 = to_string(num_b), str_num2 = to_string(num_b2);
						replaced_ll += ",";
						replaced_ll += "availble quantity=";
						replaced_ll += num_b;
						replaced_ll += ",";
						replaced_ll += "issued quantity=";
						replaced_ll += num_b2;
						replaced_ll += ",";
						replaced_ll += "returned=";
						replaced_ll += "true";
						vector<string>lines;
						string l2;
						bookf_read.open("books.txt", ios::in);
						while (getline(bookf_read, l2))
						{
							

							lines.push_back(l2);
						}
						bookf_read.close();
						bookf_write.open("books2.txt", ios::app);
						for (int i = 0; i < lines.size(); i++)
						{
							if (i == line_found)
							{
								bookf_write << replaced_ll;
							}
							else
							{
								bookf_write << lines[i];

							}
						}
						bookf_write.close();
						remove("books.txt");
						rename("books2.txt", "books.txt");


					}
					else if (num_b == 48) {
						flag1 = 1;
						cout << "cant return book there is no issued quantity inorder to return a book " <<endl;
					}

				}
				
				

			/*}*/
		}
	}
};
//	

class books {
private:

	string book_id, book_name, auther_name, available_quantity, issued_quantity;
	fstream books_file,books_file_read,books_file_empty,issued_book_read;
public:
	bool add_book(string name, string id, string auther, string quantity, string issued) {
		//check for quanitity validty and issued validty
		for (int i = 0; i < quantity.size(); i++)
		{
			if (quantity[i] >= 48 && quantity[i] <= 57) {
				continue;
			}
			else
			{
				cout << " quantity should only contain numbers";
				return false;
			}
		}
		
		for (int i = 0; i < issued.size(); i++)
		{
			if (issued[i] >= 48 && issued[i] <= 57) {
				continue;
			}
			else
			{
				cout << "issued quantity should only contain numbers";
				return false;
			}
		}
		//check for id validty
		for (int i = 0; i < id.size(); i++)
		{
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers";
				return false;
			}
		}
		//check for auther validity//
		for (int i = 0; i < auther.size(); i++)
		{
			if ((auther[i] >= 97 && auther[i] <= 122) || (auther[i] >= 65 && auther[i] <= 90) || (auther[i] == 32)) {
				continue;
			}
			else
			{
				cout << "name should only include characters not numbers";
				return false;
			}
		}
		books_file.open("books.txt", ios::app);
		books_file.close();
		char chrr;
		//char chr;
		int empty_f = 0;
		books_file_read.open("books.txt", ios::in);
		while (!books_file_read.eof())
		{
			books_file_read.get(chrr);
			if (chrr >= 33 && chrr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		books_file_read.close(); 
		if(empty_f==0){
			book_name = name;
			book_id = id;
			auther_name = auther;
			available_quantity = quantity;
			issued_quantity = issued;
			//books_file_empty.close();
			books_file.open("books.txt", ios::app);
			books_file << "book name=" << book_name << "," << "id=" << book_id << "," << " auther name=" << auther_name << ","<<"availble quantity="<<available_quantity<<","<<"issued quantity="<<issued_quantity<<"\n";
			books_file.close();
			return true;
		}
		else {
			books_file_read.open("books.txt", ios::in);
			char c;
			string check = "";
			while (!books_file_read.eof())
			{
				books_file_read.get(c);
				//cout << "working ";
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (check == id )
					{
						cout << "cant append an id that already exists for a book";
		
						/*break;*/
						return false;
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;

				}
			}
			books_file_read.close();
			book_name = name;
			book_id = id;
			auther_name = auther;
			available_quantity = quantity;
			issued_quantity = issued;
			books_file.open("books.txt", ios::app);
			books_file << "book name=" << book_name << "," << "id=" << book_id << "," << " auther name=" << auther_name << "," << "availble quantity=" << available_quantity << "," << "issued quantity=" << issued_quantity << "\n";
			books_file.close();
			return true;
		}
    }
	void search_by_id(string id) 
	{
		int id_valid = 1;
		//check for id validity
		for (int i = 0; i < id.size(); i++)
		{
			//cout << id_valid;
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout<< "id should only contain numbers";
				id_valid = -1;
				break;
				//cout << "id should only contain numbers";
				//return false;
			}
		}
		if (id_valid==1)
		{
			//cout << id_valid;
			//check if the file is empty before searching
			char chrr;
			//char chr;
			int empty_f = 0;
			books_file_read.open("books.txt", ios::in);
			while (!books_file_read.eof())
			{
				books_file_read.get(chrr);
				if (chrr >= 33 && chrr <= 126)
				{
					empty_f = 1;
					break;
				}
			}
			books_file_read.close();
			if (empty_f == 0)
			{
				cout << "empty file" << endl;
				//books_file_empty.close();
				//return "empty file";
			}
			else
			{
				//books_file_empty.close();
				char c;
				string check = "";
				int flag = -1;
				int index = 0;
				int counter = 0;
				books_file_read.open("books.txt", ios::in);
				while (!books_file_read.eof())
				{
					books_file_read.get(c);
					if (c == '\n')
					{
						counter++;
					}
					//cout << "working ";
					if (c == ',' || c == '=' || c == ':' || c == '\n') {
						cout << index;
						if (check == id)
						{
							flag = 1;
							index = counter;
							cout << "id found" << endl;
							//break;

						}
						else
						{
							check += c;
							check = "";

						}
					}
					else
					{
						check += c;

					}
				}
				books_file_read.close();
				cout << flag;
				//cout << index;
				if (flag == -1)
				{
					cout<< "no such id exist in order to search for it";
				}
				else if (flag == 1)
				{
					//cout << "yes";
					//char c2;
					string s2;
					//int equal_found=-1;
					int counter2 = 0;
					books_file_read.open("books.txt", ios::in);
					while (getline(books_file_read, s2))
					{
						if (counter2 == index)
						{
							cout << s2 << endl;
							/*return s2;*/
						}
						else
						{
							counter2++;
						}
					}
					books_file_read.close();

				}

			}
		}
		
	}
	//get books//
	void view_books() {
		char chrr;
		int empty_f = 0;
		books_file_read.open("books.txt", ios::in);
		while (!books_file_read.eof())
		{
			books_file_read.get(chrr);
			if (chrr >= 33 && chrr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		books_file_read.close();
		if (empty_f == 0)
		{
			cout << "empty file ....cant view an empty file";
			//books_file_empty.close();
		}
		else
		{
			//appending book names///
			//books_file_empty.close();
			books_file_read.open("books.txt", ios::in);
			string b;
		
			while (getline(books_file_read,b))
			{
		
				cout << b<<"\n";
				//lines.push_back(b);
			}
			books_file_read.close();
		}
	}
	void view_issued() {
		char chrr;
		int empty_f = 0;
		issued_book_read.open("issued.txt", ios::in);
		while (!issued_book_read.eof())
		{
			issued_book_read.get(chrr);
			if (chrr >= 33 && chrr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		issued_book_read.close();
		if (empty_f == 0)
		{
			cout << "empty file ....cant view an empty file";
			//books_file_empty.close();
		}
		else
		{
			//appending book names///
			//books_file_empty.close();
			issued_book_read.open("issued.txt", ios::in);
			string b;

			while (getline(issued_book_read, b))
			{

				cout << b << "\n";
				//lines.push_back(b);
			}
			issued_book_read.close();
		}
	}
	void search_by_name(string book_n) {
		vector<int> indcies;
		int counter = 0;
		int compare = -1;
		char chrr;
		//char chr;
		int empty_f = 0;
		books_file_read.open("books.txt", ios::in);
		while (!books_file_read.eof())
		{
			books_file_read.get(chrr);
			if (chrr >= 33 && chrr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		books_file_read.close();
		if (empty_f == 0)
		{
			cout << "empty file" << endl;
			//books_file_empty.close();
			//return "empty file";
		}
		else
		{
			//books_file_empty.close();
			books_file_read.open("books.txt", ios::in);
			char c;
			string check = "";
			int checked = 0;
			while (!books_file_read.eof())
			{
				books_file_read.get(c);
				//cout << "working ";
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (c=='\n')
					{
						counter++;
					}
					if (check == book_n)
					{
						checked = 1;
						compare = counter;
						indcies.push_back(compare);
					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;

				}
			}
			books_file_read.close();
			if (checked==0)
			{
				cout<< "this name doesnt exist"<<endl;
			}
			else if (checked==1)
			{
				books_file_read.open("books.txt", ios::in);
				string line;
				int counter2 = 0;
				int flag = 0;
				while (getline(books_file_read, line))
				{
					for (int i = 0; i < indcies.size(); i++)
					{
						if (counter2 == indcies[i])
						{
							cout << line << endl;
						}
					}
					counter2++;
				}
				books_file_read.close();

			}
			
		}

	}
	void remove_books(string id) {
		for (int i = 0; i < id.size(); i++) {
			if (id[i] >= 48 && id[i] <= 57) {
				continue;
			}
			else
			{
				cout << "id should only contain numbers\n";
				//return false;
			}
		}
		char chrr;
		//char chr;
		int empty_f = 0;
		books_file_read.open("books.txt", ios::in);
		while (!books_file_read.eof())
		{
			books_file_read.get(chrr);
			if (chrr >= 33 && chrr <= 126)
			{
				empty_f = 1;
				break;
			}
		}
		books_file_read.close();
		if (empty_f == 0)
		{
			cout << "empty file";
		}
		/*else if (books_file_read.fail())
		{
			cout << "no such file exists";
		}*/
		else
		{
			//books_file_empty.close();
			books_file_read.open("books.txt", ios::in);
			char c;
			string check = "";
			int counter = 0;
			int row_num_tobe_removed = -1;
			bool id_found = false;
			while (!books_file_read.eof())
			{
				books_file_read.get(c);
				if (c == '\n')
				{
					counter++;
				}
				if (c == ',' || c == '=' || c == ':' || c == '\n') {
					if (check == id)
					{
						row_num_tobe_removed = counter;
						id_found = true;

					}
					else
					{
						check += c;
						check = "";

					}
				}
				else
				{
					check += c;


				}
			}
			books_file_read.close();

			vector<string>lines;
			if (id_found == true) {
				books_file_read.open("books.txt", ios::in);
				string line;
				char c2;

				//int counter2 = 0;
				while (!books_file_read.eof())
				{

					books_file_read.get(c2);
					if (c2 == '\n')
					{

						line += c2;
						lines.push_back(line);
						line = "";

					}
					else
					{
						line += c2;

					}
				}
				books_file_read.close();
				remove("books.txt");
				fstream new_file;
				new_file.open("books2.txt", ios::app);
				for (int i = 0; i < lines.size(); i++)
				{
					if (i == row_num_tobe_removed)
					{
						continue;
					}
					else
					{
						new_file << lines[i];
						//cout << lines[i];
					}
				}
				new_file.close();
				rename("books2.txt", "books.txt");
				//return true;
			}
			else
			{
				cout << "\nno such book exist in the file\n";
				//return false;
			}


		}
	}
};
void librarian_view() {
	books b;
	librarian lib;
	issued_books iss_b;
	int choice;
	do {
		cout << "1-login" << endl;
		cout << "2-add books" << endl;
		cout << "3-delete books" << endl;
		cout << "4- view books" << endl;
		cout << "5- view issued books" << endl;
		cout << "6- search by name for book" << endl;
		cout << "7- search by id for book" << endl;
		cout << "8- issue book" << endl;
		cout << "9- return book" << endl;
		cout << "10-log_out" << endl;
		//cout << "7- log out" << endl;
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (choice == 1) {

			string name, pass;
			getline(cin, name);
			cin >> pass;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << lib.login(name, pass);
		}

		else if (choice == 2)
		{
			string book_n, book_id, book_auther, availble_quantiy, issued_quantity;
			getline(cin, book_n);
			cin >> book_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, book_auther);
			cin >> availble_quantiy;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> issued_quantity;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << b.add_book(book_n, book_id, book_auther, availble_quantiy, issued_quantity);
			/*cout << ad.add_admins(admin_name, admin_id, admins_pass);*/


		}
		else if (choice == 3) {
			//string
			string book_id;
			cin >> book_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			b.remove_books(book_id);
		}
		else if (choice == 4) {
			b.view_books();
			
		}
		else if (choice == 5) {
			
			b.view_issued();

		}
		else if (choice == 6) {
			string book_name;
			getline(cin, book_name);
			b.search_by_name(book_name);
			//string st_id;
			//cin >> st_id;
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			////cout << std.remove_students(st_id);

		}
		else if (choice == 7) {
			string book_id;
			cin >> book_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			b.search_by_id(book_id);
			//cout << std.get_student(st_id);
		}
		else if (choice == 8) {
			string book_id, student_id;
			
			cin >> book_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> student_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			iss_b.issue_book(book_id, student_id);
			
			/*cout << lib.add_librarians(librarian_name, librarian_id, librarian_password);*/
		}
		else if (choice == 9) {
			string book_id, student_id;
			cin >> book_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> student_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			iss_b.issue_book(book_id, student_id);
		}
		else if(choice ==10)
		{
			lib.logout();
		}
	} while (choice <= 10);
}


void admin_view() {
	admin ad;
	student std;
	librarian lib;
	int choice;
	do
	{
		cout << "1-add admins" << endl;
		cout << "2-remove admins" << endl;
		cout << "3- get admin" << endl;
		cout << "4- add students" << endl;
		cout << "5- remove students" << endl;
		cout << "6- get student" << endl;
		cout << "7- add librarians" << endl;
		cout << "8- remove librarians" << endl;
		cout << "9- get librarian" << endl;
		cout << "10-log_out" << endl;
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		if (choice == 1)
		{
			string admin_name, admin_id, admins_pass;
			getline(cin, admin_name);
			cin >> admin_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, admins_pass);
			cout<<ad.add_admins(admin_name, admin_id, admins_pass);
			

		}
		else if (choice == 2) {
			string admin_id;
			cin >> admin_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ad.remove_admins(admin_id);
		}
		else if (choice == 3) {
			string admin_id;
			cin >> admin_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ad.get_admin(admin_id);
		}
		else if (choice==4) {
			string student_n, std_id, std_birthday, std_email, std_mobile;
			getline(cin, student_n);
			cin >> std_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, std_birthday);
			getline(cin, std_email);
			cin >> std_mobile;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout<<std.add_students(student_n, std_id, std_birthday, std_email, std_mobile);

		}
		else if (choice==5) {
			string st_id;
			cin >> st_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout<<std.remove_students(st_id);

		}
		else if (choice == 6) {
			string st_id;
			cin >> st_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout<<std.get_student(st_id);
		}
		else if (choice == 7) {
			string librarian_name, librarian_id, librarian_password;
			getline(cin, librarian_name);
			cin >> librarian_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, librarian_password);
			cout<<lib.add_librarians(librarian_name, librarian_id, librarian_password);
		}
		else if (choice == 8) {
			string lib_id;
			cin >> lib_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout<<lib.remove_librarian(lib_id);
		}
		else if (choice == 9) {
			string lib_id;
			cin >> lib_id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout<<lib.get_librarian(lib_id);
		}
		else if (choice == 10) {
			ad.logout();

		}
		

	} while (choice <= 10);
}

int main() {
	int master_choice;
	cout << "1-admin"<<endl;
	cout << "2-librarian" << endl;
	cin >> master_choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (master_choice==1)
	{
		admin ad;
		string name, pass;
		getline(cin, name);
		getline(cin, pass);
		int x = ad.login(name,pass);
		if (x == true) {
			admin_view();
		}
		
	}
	else
	{
		librarian lib;
		string name, pass;
		getline(cin, name);
		getline(cin, pass);
		int x = lib.login(name, pass);
		if (x == true) {
			librarian_view();
		}

	}

	return 0;
}