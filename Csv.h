/*
 * CSVparser.h
 *
 *      Author: Bram van Bunnik
 */

#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>


class Csv {	// read and parse comma-separated values

  public:
    Csv(std::istream& fin = std::cin, std::string sep = ",", bool hasHeader = false) :
        fin(fin), nfield(0), fieldsep(sep), hasHeader(hasHeader) {}

	int getline(std::string&);
	std::string getfield(unsigned int n);
	int getnfield() const { return nfield; }
    int getHeader(std::vector<std::string>&);
	int getall(std::vector<std::vector<int> >&);
	int getall(std::vector<std::vector<double> >&);
	int getall(std::vector<std::vector<std::string> >&);

  private:
    bool hasHeader;
    std::vector<std::string> header;
	std::istream& fin;			// input file pointer
	std::string line;			// input line
	std::vector<std::string> field;	// field strings
	unsigned int nfield;				// number of fields
	std::string fieldsep;		// separator characters

	int split();
	int endofline(char);
	int advplain(const std::string& line, std::string& fld, int);
	int advquoted(const std::string& line, std::string& fld, int);
};
