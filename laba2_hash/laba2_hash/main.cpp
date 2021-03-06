// laba2_hash.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "myhash.h"
#include "user.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <utility>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <string>

using std::cin;
using std::cout;
using std::vector;
using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;
using std::iterator;
using std::pair;
using std::unordered_map;
using std::unordered_set;
using std::endl;
using std::string;
using std::ios;
using std::stoi;

struct Back 
{
	user SaveData[5];		// 5 записей для отката
};

typedef void(*FuncMass[7])(myhashBook<string, user>& );

void putData(user &dat)
{
	cout << "input surname " << endl;
	cin >> dat.surname;

	cout << "input name " << endl;
	cin >> dat.name;

	cout << "input patronym " << endl;
	cin >> dat.patronym;

	string email = "";
	while (true)
	{
		email.clear();
		cout << "input email " << endl;
		cin >> email;
		
		if (email == "*")
		{
			dat.email = email;
			break;
		}
		else if (email.find("@") == std::string::npos) 
		{
			cout << "wrong format" << endl;
			continue;
		}

		dat.email = email;
		break;
	}

	cout << "input company " << endl;
	cin >> dat.company;

	cout << "input position " << endl;
	cin >> dat.position;
}

string putNumber()
{
	string key = "";
	cin >> key;
	
	if ((key[0] != '+') || (key.length() != 12))		// string to int ?
	{
		return string();
	}

	for (size_t i = 1; i < key.size(); i++)
	{
		if (!isdigit(key[i]))
			return string();
	}
	
	return key;
}

void input(myhashBook<string, user>& obj)
{
	user data;
	
	cout << "input telephone number " << endl;
	string key = putNumber();
	if (key == string())	//неудачно	
	{
		cout << "wrong format" << endl;
		return;
	}

	auto bFind = obj.existence(key);
	if (bFind)
	{
		cout << "this contact already exists, do you want to change it? y/n" << endl;
		string comm2 = " ";
		cin >> comm2;

		if (comm2 == "y")
		{
			putData(data);
			obj.insert(key, data);
		}
	}
	else
	{
		putData(data);
		obj.insert(key, data);
	}
}

void change(myhashBook<string, user>& obj)
{
	user data;
	
	cout << "input telephone number to change person" << endl;
	string key = putNumber();
	if (key == string())	//неудачно	
	{
		cout << "wrong format" << endl;
		return;
	}

	bool bfind = obj.existence(key);
	if (bfind)
	{
		putData(data);
		obj[key] = data;
	}
	else
	{
		cout << "no match" << endl;
		return;
	}
}

void erase(myhashBook<string, user>& obj)
{
	cout << "input telephone number" << endl;
	string key = putNumber();
	if (key == string())	//неудачно	
	{
		cout << "wrong format" << endl;
		return;
	}

	bool bfind = obj.existence(key);
	if (!bfind)
	{
		cout << "no match" << endl;
	}
	else
		obj.erase(key);
}

void kfind(myhashBook<string, user>& obj)
{
	cout << "input telephone number" << endl;
	string key = putNumber();
	if (key == string())	//неудачно	
	{
		cout << "wrong format" << endl;
		return;
	}
	
	if (!obj.existence(key))
	{
		cout << "no match" << endl;
	}
	else
	{
		auto ifind = obj.Find(key);
		cout << ifind->second << endl;
	}
}

void dfind(myhashBook<string, user>& obj)
{
	string strfield = "";
	vector<user> Users;		// массив структур данных о найденных пользователях
	user FindData;
	cout << "field for search (all data: 'all', by position: 'pos', by company: 'comp', by email: 'email')" << endl;
	cin >> strfield;

	if (strfield == "all")
	{
		cout << "if you want to skip any field, input '*' " << endl;
		putData(FindData);
		Users = obj.find_data(FindData);
	}
	else if (strfield == "pos")
	{
		string posit = "";
		cout << "input position" << endl;
		cin >> posit;
		FindData.position = posit;
		Users = obj.find_data(FindData);
	}
	else if (strfield == "email")
	{
		string email = "";
		cout << "input email" << endl;
		cin >> email;
		FindData.email = email;
		Users = obj.find_data(FindData);
	}
	else if (strfield == "comp")
	{
		string company = "";
		cout << "input company" << endl;
		cin >> company;
		FindData.company = company;
		Users = obj.find_data(FindData);
	}
	else
	{
		cout << "field not found" << endl;
		return;
	}

	if (Users.size() == 0)
	{
		cout << "users not found " << endl;
		return;
	}

	for (auto Iter = Users.begin(); Iter != Users.end(); ++Iter)
		cout << *Iter << endl;
}

void show(myhashBook<string, user>& obj)
{
	cout << obj;
}

void clear(myhashBook<string, user>& obj)
{
	obj.clear();
}

int main()
{
	myhashBook<string, user> hash;
	vector<string> massComm = { "input", "change", "erase",
							    "kfind", "dfind", "show", "clear" };
	
	FuncMass massFunc[] = { input, change, erase, kfind, dfind, show, clear };

	ifstream fin("data.txt");
	fin >> hash;
	fin.close();

	string comm = " ";

	while (true)
	{
		cout << "\n'exit', 'show', 'change', 'input', 'erase', 'kfind' (by tel number), 'clear', 'dfind' (by data) " << endl;
		cin >> comm;
	
		if (comm == "exit")
			break;

		auto iFind = find(massComm.begin(), massComm.end(), comm);
		
		if (iFind == massComm.end())
		{
			cout << "command not found" << endl;
			continue;
		}

		for (int i = 0; i < massComm.size(); i++)
			if (comm == massComm[i])
			{
				(*massFunc)[i](hash);
				break;		// закрываем только этот for
			}
	}

	ofstream fout("data.txt", ios::out);
	fout << hash;
	fout.close();

	//myhash<string, char> cHash;
	//cHash["rr"] = '2';
	//cout << cHash << endl;
	//
	//cHash.insert("11", 'Q');
	//cout << cHash << endl;

    return 0;
}
