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


void printVectorOfVectors(vector<vector<char> > v, string message){
	cout << message << endl;
	for(int i=0; i<v.size(); i++){
		printVector(v[i], "----- s" + to_string((i+1)) + " ------" );
	}
}

bool indexExists(int i, vector<char> seq){
	if(seq.size()>=(i+1)){
		return true;
	}else{
		return false;
	}
}

int compareChars(int r1, int r2, char s1,char s2, char s3, int score){
		if((s1==s2) && s1!=""){
			return (score+match);
		}
		if(s1!=s2 && (s1!="") && (s2!="")){
			return (score+mismatch);
		}
		if((s1=="" && s2!="") || (s1!="" && s2=="")){
			return (score+indel);
		}
		else return score;
}


int SPScore(vector<char> s1,vector<char> s2, vector<char> s3, int max_size){
	int score=0;
	
	for(i=0; i<max_size; i++){
		if(s1.size()>=(i+1)){
			if(s2.size()>=(i+1)){
				if(s1[i]==s2[i]){
					score+=match;
				}
				else{
					score+=mismatch;
				}
					
			}else{
				score+=indel;
			}
		}
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
	int max=s1.size();
	max=(s2.size()>max)?s2.size():max;
	max=(s3.size()>max)?s3.size():max;
	
	int min= s1.size();
	min=(s2.size()<min)?s2.size():min;
	min=(s3.size()<min)?s3.size():min;
	
	cout << endl << endl;
	printVector(s1, "--------------- s1, size: "+to_string(s1.size())+"----------------");
	printVector(s2, "--------------- s2, size: "+to_string(s2.size())+"----------------");
	printVector(s3, "--------------- s3, size: "+to_string(s3.size())+"----------------");

	
	if (min<=1 || max<=1 || s1.empty() || s2.empty() || s3.empty()){
		vector<vector<char> > align;
		align.push_back(s1);
		align.push_back(s2);
		align.push_back(s3);
		//printVectorOfVectors(align,"");
		return align;
	}
	
	if(s1.size()>1 && s2.size() > 1 && s3.size()>1){
		//divide and conquer sequence
		//recursively call first half of sequences
		threeSeqAlign(getHalfVector("first",s1),getHalfVector("first",s2), getHalfVector("first",s3));
		
		//recursively call second half of sequences
		return threeSeqAlign(getHalfVector("second",s1),getHalfVector("second",s2), getHalfVector("second",s3));
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