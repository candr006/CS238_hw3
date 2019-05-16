#include<iostream>
#include<vector>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

//set the constant values here 
const int match=5;
const int mismatch=-4;
const int indel=-8;

//vector<int> sorted_sp_vals{match,mismatch,indel};
//sort descending order
//sort(v.begin(), v.end(), greater<int>()); 


int SPScore(string x, string y, string z){
	int score=0;
	
	if(x==y){
		score+=match;
	}
	
	
	return score;
}

vector<string> threeSeqAlign(vector<string> s1,vector<string> s2, vector<string> s3){
	vector<string> test;
	return test;
}
	

int main(int argc, char** argv){
	
	//sequence 1
	ifstream ifs(argv[1]);
	string s1;
	s1.assign( (istreambuf_iterator<char>(ifs) ),
					(istreambuf_iterator<char>()));
	
	cout << "String " << argv[1] << " " << s1 << endl;
	
	//sequence 2
	ifstream ifs2(argv[2]);
	string s2;
	s2.assign( (istreambuf_iterator<char>(ifs2) ),
					(istreambuf_iterator<char>()));
	
	cout << "String " << argv[2] << " " << s2 << endl;
	
	//sequence 3
	ifstream ifs3(argv[3]);
	string s3;
	s3.assign( (istreambuf_iterator<char>(ifs3) ),
					(istreambuf_iterator<char>()));
	
	cout << "String " << argv[3] << " " << s3 << endl;
	
}