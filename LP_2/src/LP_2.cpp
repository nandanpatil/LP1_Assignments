//============================================================================
// Name        : LP_2.cpp
// Author      : 31460
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define mnem_it unordered_map<string, pair<string, int>>::iterator
#define reg_it unordered_map<string, int>::iterator
#define st_it vector<pair<string, int>>::iterator

class Tables
{
	unordered_map<string, pair<string, int>> OPTAB;
	unordered_map<string, int> REG;
	unordered_map<string, int> CONDCS;
	vector<pair<string, int>> ST;

	Tables()
	{
		OPTAB["STOP"] = {"IS", 0};
		OPTAB["ADD"] = {"IS", 1};
		OPTAB["SUB"] = {"IS", 2};
		OPTAB["MULT"] = {"IS", 3};
		OPTAB["MOVER"] = {"IS", 4};
		OPTAB["MOVEM"] = {"IS", 5};
		OPTAB["COMP"] = {"IS", 6};
		OPTAB["BC"] = {"IS", 7};
		OPTAB["DIV"] = {"IS", 8};
		OPTAB["READ"] = {"IS", 9};
		OPTAB["PRINT"] = {"IS", 10};
		OPTAB["START"] = {"AD", 1};
		OPTAB["END"] = {"AD", 2};
		OPTAB["ORIGIN"] = {"AD", 3};
		OPTAB["EQU"] = {"AD", 4};
		OPTAB["LTORG"] = {"AD", 5};
		OPTAB["DC"] = {"DL", 1};
		OPTAB["DS"] = {"DL", 2};

		REG["AREG"] = 1;
		REG["BREG"] = 2;
		REG["CREG"] = 3;
		REG["DREG"] = 4;

		CONDCS["LT"] = 1;
		CONDCS["LE"] = 2;
		CONDCS["EQ"] = 3;
		CONDCS["GT"] = 4;
		CONDCS["GE"] = 5;
		CONDCS["ANY"] = 6;
		ST.push_back({"NULL", -99});
	}

	void show()
	{
		cout << "Mnemonic Class\tCode" << endl;
		for (auto x : OPTAB)
		{
			cout << x.first << "\t" << x.second.first << "\t" << x.second.second << endl;
		}
	}

	mnem_it find_in_mnemonic(string s)
	{
		mnem_it i = OPTAB.find(s);
		return i;
	}

	reg_it find_in_reg(string s)
	{
		reg_it i = REG.find(s);
		return i;
	}

	reg_it find_in_cond(string s)
	{
		reg_it i = CONDCS.find(s);
		return i;
	}

	st_it find_in_ST(string s)
	{
		st_it i = find_if(ST.begin(), ST.end(), [s](pair<string, int> const &a)
						  { return a.first == s; });
		return i;
	}

	void print_in_mnemonic(mnem_it i, fstream &obj)
	{
		string w = "(" + (*i).second.first + "," + to_string((*i).second.second) + ")" + " ";
		obj << w;
		// cout << "(" << (*i).second.first << "," << (*i).second.second << ")"<< " ";
	}
	void print_in_reg(reg_it i, fstream &obj)
	{
		string w = "(" + to_string((*i).second) + ")" + " ";
		obj << w;
		// cout << "(" << (*i).second << ")"<< " ";
	}
	friend class Pass1;
};

class Pass1
{
	Tables t1;
	fstream file;
	fstream file2;

public:
	Pass1(string f1, string f2)
	{
		file.open(f1, ios::in);
		file2.open(f2, ios::out);
		if (!file.is_open())
		{
			cout << "Error opening Source Code File" << endl;
		}
		if (!file2.is_open())
		{
			cout << "Error creating Intermediate Code File" << endl;
		}
	}

	void createIntermediateCode()
	{
		int LC = 00;
		if (file.is_open())
		{

			string line;

			while (getline(file, line))
			{
				vector<string> words;
				string w = "";
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] != ' ')
					{
						w += line[i];
					}
					else
					{
						words.push_back(w);
						w = "";
					}
				}
				words.push_back(w);
				if (words.size() == 4)
				{
					file2 << LC << " ";
					// cout << LC << " ";
					//  word 1 in symbol table
					t1.ST.push_back({words[0], LC});
					// word 2 in mnemonic table
					mnem_it i = t1.find_in_mnemonic(words[1]);
					t1.print_in_mnemonic(i, file2);
					// word 3 in reg
					reg_it i1 = t1.find_in_reg(words[2]);
					t1.print_in_reg(i1, file2);
					// last word in symbol table only
					st_it it2 = t1.find_in_ST(words[3]);
					if (it2 == t1.ST.end())
					{
						t1.ST.push_back({words[3], 00});
						string w = "(S," + to_string(t1.ST.size() - 1) + ")" + " ";
						file2 << w;
						// cout << "(S," << t1.ST.size() - 1 << ")"<< " ";
					}
					else
					{
						string w = "(S," + to_string(it2 - t1.ST.begin()) + ")" + " ";
						file2 << w;
						// cout << "(S," << it2 - t1.ST.begin() << ")"<< " ";
					}
					file2 << endl;
					// cout<<endl;
				}
				else if (words.size() == 3)
				{
					file2 << to_string(LC) + " ";
//					// cout << LC << " ";
//					st_it si = t1.find_in_ST(words[0]);
//					mnem_it it;
//					reg_it it1;
//					if (si != t1.ST.end())
//					{
//						(*si).second = LC;
//
//						it = t1.find_in_mnemonic(words[1]);
//						t1.print_in_mnemonic(it, file2);
//
//						string w = "(C," + words[2] + ") ";
//						file2 << w;
//						// cout << "(C," << words[2] << ")"<< " ";
//					}
//					else
//					{
//						it = t1.find_in_mnemonic(words[0]);
//						t1.print_in_mnemonic(it, file2);
//
//						it1 = t1.find_in_reg(words[1]);
//						if (it1 != t1.REG.end())
//							t1.print_in_reg(it1, file2);
//						else
//						{
//							it1 = t1.find_in_cond(words[1]);
//							t1.print_in_reg(it1, file2);
//						}
//						it1=t1.find_in_reg(words[2]);
//						if(it1!=t1.REG.end()){
//							t1.print_in_reg(it1, file2);
//						}
//						else{
//							si = t1.find_in_ST(words[2]);
//							if (si == t1.ST.end())
//							{
//								t1.ST.push_back({words[2], 00});
//								string w = "(S," + to_string(t1.ST.size() - 1) + ")" + " ";
//								file2 << w;
//								// cout << "(S," << t1.ST.size() - 1 << ")"<< " ";
//							}
//							else
//							{
//								string w = "(S," + to_string(si - t1.ST.begin()) + ")" + " ";
//								file2 << w;
//								// cout << "(S," << si - t1.ST.begin() << ")"<< " ";
//							}
//						}
//
//					}

					mnem_it it = t1.find_in_mnemonic(words[1]);
					st_it si;
					if(it!=t1.OPTAB.end()){
						if(words[1]=="EQU"){
							string w;
						si=t1.find_in_ST(words[2]);
						st_it temp = t1.find_in_ST(words[0]);
						if(temp!=t1.ST.end()){
							(*temp).second = (*si).second;
						 w = "(S," + to_string(si - t1.ST.begin()) + ")" + " ";
						file2 << w;
						}
						else{
							t1.ST.push_back({words[0],(*si).second});
						 w = "(S," + to_string(t1.ST.size() - 1) + ")" + " ";
						file2 << w;
						}
						
						t1.print_in_mnemonic(it,file2);


						 w = "(S," + to_string(si - t1.ST.begin()) + ")" + " ";
						file2 << w;
						}
						else{
							si = t1.find_in_ST(words[0]);
							if(si==t1.ST.end()){
								t1.ST.push_back({words[0],LC});
							}
							else{
								(*si).second = LC;
							}

							t1.print_in_mnemonic(it, file2);

							string w = "(C," + words[2] + ") ";
							file2 << w;
						}
					}
					else{

						it = t1.find_in_mnemonic(words[0]);
						t1.print_in_mnemonic(it, file2);


						reg_it it2 = t1.find_in_reg(words[1]);
						if (it2 != t1.REG.end())
							t1.print_in_reg(it2, file2);
						else
						{
							it2 = t1.find_in_cond(words[1]);
							t1.print_in_reg(it2, file2);
						}

						it2=t1.find_in_reg(words[2]);
						if(it2!=t1.REG.end()){
							t1.print_in_reg(it2, file2);
						}
						else{
							si = t1.find_in_ST(words[2]);
							if (si == t1.ST.end())
							{
								t1.ST.push_back({words[2], 00});
								string w = "(S," + to_string(t1.ST.size() - 1) + ")" + " ";
								file2 << w;
								// cout << "(S," << t1.ST.size() - 1 << ")"<< " ";
							}
							else
							{
								string w = "(S," + to_string(si - t1.ST.begin()) + ")" + " ";
								file2 << w;
								// cout << "(S," << si - t1.ST.begin() << ")"<< " ";
							}
					}
					}
					file2 << endl;
					// cout<<endl;
				}
				else if (words.size() == 2)
				{
					mnem_it it = t1.find_in_mnemonic(words[0]);
					if (words[0] == "START")
					{
						t1.print_in_mnemonic(it, file2);
						file2 << "(C," << words[1] << ")"
							  << " ";
						// cout << "(C," << words[1] << ")"<< " ";
						LC = stoi(words[1]) - 1;
					}
					else if(words[0]=="ORIGIN"){
						file2<<LC<<" ";
						t1.print_in_mnemonic(it,file2);

						st_it it1 = t1.find_in_ST(words[1]);
						LC = (*it1).second-1;

						string w = "(S," + to_string(it1 - t1.ST.begin()) + ")" + " ";
						file2 << w;

					}
					else
					{
						file2 << LC << " ";
						// cout<<LC<<" ";
						t1.print_in_mnemonic(it, file2);
						st_it si = t1.find_in_ST(words[0]);
						si = t1.find_in_ST(words[1]);
						if (si == t1.ST.end())
						{
							t1.ST.push_back({words[1], 00});
							string w = "(S," + to_string(t1.ST.size() - 1) + ")" + " ";
							file2 << w;
							// cout << "(S," << t1.ST.size() - 1 << ")"<< " ";
						}
						else
						{
							string w = "(S," + to_string(si - t1.ST.begin()) + ")" + " ";
							file2 << w;
							// cout << "(S," << si - t1.ST.begin() << ")"<< " ";
						}
					}
					file2 << endl;
					// cout<<endl;
				}
				else
				{
					if (words[0] != "END")
					{
						file2 << LC << " ";
					}
					// cout<<LC<<" ";}
					mnem_it i = t1.find_in_mnemonic(words[0]);
					t1.print_in_mnemonic(i, file2);
					// cout<<endl;
					file2 << endl;
				}
				LC++;
			}
		}
	}

	void showST()
	{
		cout << "No." << setw(10) << "Symbol" << setw(10) << "Referance" << endl;
		for (int i = 1; i < t1.ST.size(); i++)
		{
			cout << i << setw(10) << t1.ST[i].first << setw(10) << t1.ST[i].second << endl;
		}
	}
};

int main()
{
	Pass1 p("code.txt", "I_code.txt");
	p.createIntermediateCode();
	p.showST();
}
