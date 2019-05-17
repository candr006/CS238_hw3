#include<iostream>
#include<vector>
#include <fstream>
#include <bits/stdc++.h>
#include <iterator>
#include <string>   

using namespace std;

//set the constant values here 
const int match=5;
const int mismatch=-4;
const int indel=-8;

//vector<int> sorted_sp_vals{match,mismatch,indel};
//sort descending order
//sort(v.begin(), v.end(), greater<int>()); 


void printVector(vector<char> v, string message){
	string comma="";
	cout << message << endl;
	
	for(int i=0; i < v.size(); i++){
		cout << comma << v[i];
		comma=", ";
	}
	cout << endl;
	return;
}


int SPScore(string x, string y, string z){
	int score=0;
	
	if(x==y){
		score+=match;
	}
	
	
	return score;
}

vector<char> getHalfVector(string half, vector<char> v){
	if(v.size()>1){
		int half_size = v.size() / 2;
		if (half=="first"){
			vector<char> first(v.begin(), v.begin() + half_size);
			return first;
		}else{
			vector<char> second(v.begin() + half_size, v.end());
			return second;
		}
	}
}


vector<vector<char> > threeSeqAlign(vector<char> s1,vector<char> s2, vector<char> s3){
	cout << "pos1" << endl;
	int max=s1.size();
	max=(s2.size()>max)?s2.size():max;
	max=(s3.size()>max)?s3.size():max;
	
	int min= s1.size();
	min=(s2.size()<min)?s2.size():min;
	min=(s3.size()<min)?s3.size():min;
	cout << "pos2" << endl;
	
	cout << endl << endl;
	printVector(s1, "--------------- s1, size: "+to_string(s1.size())+"----------------");
	printVector(s2, "--------------- s2, size: "+to_string(s2.size())+"----------------");
	printVector(s3, "--------------- s3, size: "+to_string(s3.size())+"----------------");
	
	cout << "pos3" << endl;
	
	if (min<=1 || max<=1 || s1.empty() || s2.empty() || s3.empty()){
		cout << "HERE!" << endl;
		vector<vector<char> > align;
		align.push_back(s1);
		align.push_back(s2);
		align.push_back(s3);
		return align;
	}
	cout << "pos4" << endl;
	
	if(s1.size()>1 && s2.size() > 1 && s3.size()>1){
		//divide and conquer sequence
		//recursively call first half of sequences
		cout << "pos5" << endl;
		vector<vector<char> > first_half = threeSeqAlign(getHalfVector("first",s1),getHalfVector("first",s2), getHalfVector("first",s3));
		cout << "half1 complete" << endl;
		
		//recursively call second half of sequences
		cout << "pos6" << endl;
		vector<vector<char> > second_half = threeSeqAlign(getHalfVector("second",s1),getHalfVector("second",s2), getHalfVector("second",s3));
		for(int i=0; i<second_half.size(); i++){
			printVector(second_half[i], "----------Contents of second half for s"+to_string(i+1)+"-----------------");
		}
	}
	
}
	

int main(int argc, char** argv){
	
	//sequence 1
	ifstream ifs(argv[1]);
	string s1_t;
	s1_t.assign( (istreambuf_iterator<char>(ifs) ),
					(istreambuf_iterator<char>()));
	vector<char> s1(s1_t.begin(), s1_t.end()); 
	
	//sequence 2
	ifstream ifs2(argv[2]);
	string s2_t;
	s2_t.assign( (istreambuf_iterator<char>(ifs2) ),
					(istreambuf_iterator<char>()));
	vector<char> s2(s2_t.begin(), s2_t.end()); 
	
	//sequence 3
	ifstream ifs3(argv[3]);
	string s3_t;
	s3_t.assign( (istreambuf_iterator<char>(ifs3) ),
					(istreambuf_iterator<char>()));
	vector<char> s3(s3_t.begin(), s3_t.end()); 
	
	threeSeqAlign(s1, s2, s3);
	
}