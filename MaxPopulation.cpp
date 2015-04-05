/*
 *  File: MaxPopulation.cpp
 *  Created: Greg Myers on 4/4/15
 *  Description: Given a table of names, birth, and death years between 1900 and 2000,
 *				 calculate the year with this most people alive
 *
 */
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main( int argc, char *argv[] )
{
	//initial usage check:
	if(argc != 2)
	{
		cout<< "Bad input! " <<endl;
		cout<< "Usage: MaxPopulation \"filename.txt\" " <<endl;
		cout<< "Exiting... " <<endl;
		exit(0);
	}
//-------------------------read in data:--------------------------------//
	string fname = argv[1];
	string line;
	ifstream inFile;
	string first_name, last_name;
	int by, dy;
	vector<int> birthyear; 
	vector<int> deathyear;
	
	inFile.open(fname.c_str());
	if(inFile.good()){
		while(getline(inFile, line))
		{
			istringstream iss(line);
			iss >> last_name >> first_name >> by >> dy;
			birthyear.push_back( by );
			deathyear.push_back( dy );
		}
	}
	else
	{ 
		cout <<"Input file is messed up or non-existant"<<endl;
		cout <<"Exiting..." <<endl;
		exit(0);
	}
	inFile.close();
	
	//make sure birth/death year vectors have the same size:
	if(birthyear.size()!=deathyear.size())
	{
		cout<< "birth and death year mismatch " <<endl;
		cout<< "Exiting... " <<endl;
		exit(0);
	}
//-----------------------------calculations:-----------------------------//
	int start_year=1900;
	int end_year=2001;
	int living_people=0;
	int max_people=0;
	int result_year_i=1900;
	int result_year_f=1900;
	for(int ii=start_year;ii<end_year;ii++)
	{
		living_people = 0;
		for(int jj=0;jj<birthyear.size();jj++)
		{
			if(birthyear[jj]<=ii && deathyear[jj]>=ii)
			{
				living_people+=1;
			}
		}		
		//keep track of the year with the most people:
		if(living_people>=max_people)
		{
			//if the max occurs multiple years, find the interval:
			if(living_people==max_people)
			{
				max_people = living_people;
				result_year_f = ii;
			}
			//else: the max occurs only during a single year:
			else
			{
				max_people = living_people;
				result_year_i = ii; 
				result_year_f = ii;
			}
		}
		
	}
		
//----------------------------display results:------------------------------//
	if(result_year_i==result_year_f)
	{
		cout<< "The largest number of people alive was "<< max_people <<", and it occured in the year "
			<< result_year_i <<endl;
	}
	else
	{
		cout<< "The largest number of people alive was "<< max_people <<", and it occured between the years "
			<< result_year_i <<" and "<< result_year_f <<endl;
	}
	
	return 0;
}