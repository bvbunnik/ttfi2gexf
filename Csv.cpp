/* Copyright (C) 1999 Lucent Technologies */
/* Adapted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "Csv.h"

using namespace std;


int Csv::endofline(char c)
// endofline: check for and consume \r, \n, \r\n, or EOF
{
	int eol;

	eol = (c=='\r' || c=='\n');
	if (c == '\r') {
		fin.get(c);
		if (!fin.eof() && c != '\n')
			fin.putback(c);	// read too far
	}
	return eol;
}


// getline: get one line, grow as needed
int Csv::getline(string& str)
{
	char c;
	for (line = ""; fin.get(c) && !endofline(c); )
		line += c;
	split();
	str = line;
	return !fin.eof();
}

// split: split line into fields
int Csv::split()
{
	string fld;
	unsigned int i, j;

	nfield = 0;
	if (line.length() == 0)
		return 0;
	i = 0;

	do {
		if (i < line.length() && line[i] == '"')
			j = advquoted(line, fld, ++i);	// skip quote
		else
			j = advplain(line, fld, i);
		if (nfield >= field.size())
			field.push_back(fld);
		else
			field[nfield] = fld;
		nfield++;
		i = j + 1;
	} while (j < line.length());

	return nfield;
}

// advquoted: quoted field; return index of next separator
int Csv::advquoted(const string& s, string& fld, int i)
{
	unsigned int j;

	fld = "";
	for (j = i; j < s.length(); j++) {
		if (s[j] == '"' && s[++j] != '"') {
			unsigned int k = s.find_first_of(fieldsep, j);
			if (k > s.length())	// no separator found
				k = s.length();
			for (k -= j; k-- > 0; )
				fld += s[j++];
			break;
		}
		fld += s[j];
	}
	return j;
}

// advplain: unquoted field; return index of next separator
int Csv::advplain(const string& s, string& fld, int i)
{
	unsigned int j;

	j = s.find_first_of(fieldsep, i); // look for separator
	if (j > s.length())               // none found
		j = s.length();
	fld = string(s, i, j-i);
	return j;
}


// getfield: return n-th field
string Csv::getfield(unsigned int n)
{
    if (n >= nfield)
		return "";
	else
		return field[n];
}

int Csv::getHeader(std::vector<std::string> &data){
    if(hasHeader){
        data = header;
    } else {
        return 0;
    }
    return 1;
}

int Csv::getall(vector<vector<int> > &data){
	string line;
	vector<int> row;
    if(hasHeader){
        this->getline(line);
        header = field;
    }
	while(this->getline(line)!=0){
		for (int i = 0; i < getnfield(); i++){
			 row.push_back(atoi(getfield(i).c_str()));
		}
		data.push_back(row);
		row.clear();
	}
	return 1;
}


int Csv::getall(vector<vector<double> > &data){
	string line;
	vector<double> row;
	while(this->getline(line)!=0){
		for (int i = 0; i < getnfield(); i++){
			 row.push_back(atof(getfield(i).c_str()));
		}
		data.push_back(row);
		row.clear();
	}
	return 1;
}


int Csv::getall(vector<vector<string> > &data){
	string line;
	vector<string> row;
	while(this->getline(line)!=0){
		for (int i = 0; i < getnfield(); i++){
			 row.push_back(getfield(i));
		}
		data.push_back(row);
		row.clear();
	}
	return 1;
}

