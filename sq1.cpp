#include<iostream>
#include<vector>
#include <fstream>
#include <bits/stdc++.h>
#include <iterator>
#include <string> 
#include <algorithm>   

using namespace std;

//set the constant values here 
int match=5;
int mismtch=-4;
int indel=-8;

int getScore(char s1, char s2){
	if((s1==s2) && (s1!='-')){
		return match;
	}
	if(s1!=s2 && (s1!='-') && (s2!='-')){
		return mismtch;
	}
	if((s1=='-' && s2!='-') || (s1!='-' && s2=='-')){
		return indel;
	}
	else {
		return 0;
	}

}

int getMax(int v1, int v2, int v3){
	int max;
	
	if(v1>=v2){
		max=v1;
		if (v3>v1){
			return v3;
		}
		else{
			return v1;
		}
	}else{
		max=v2;
		if (v3>v2){
			return v3;
		}
		else{
			return v2;
		}
	}
	
};

void pairAlign(char seq1[], char seq2[]){
	int s[sizeof(seq1)][sizeof(seq2)];
	
	for(int i=0; i< sizeof(seq1); i++){
		s[0][i]=0;
	}
	
	for(int j=0; j<sizeof(seq2);j++){
		s[j][0]=0;	
	}
	int i=1;
	int j=1;

	cout << sizeof(seq1) << endl;
	
	while (i<sizeof(seq1)){
		j=1;
		while (j<sizeof(seq2)){
			s[i][j]=getMax(s[i-1][j]+getScore(seq1[i],'-'),
							s[i][j-1]+getScore('-',seq2[j]),
							s[i-1][j-1]+getScore(seq1[i],seq2[j]));
			
				cout << i << "," << j << ": " << s[i][j] << endl;
							
			j++;
		}
		
		i++;
	}
	

}

void threeSeqAlign(char s1[], char s2[], char s3[]){
	
	return;
}

int main(int argc, char** argv){
	
	//sequence 1
	ifstream ifs(argv[1]);
	string s1_t;
	s1_t.assign( (istreambuf_iterator<char>(ifs) ),
					(istreambuf_iterator<char>()));
    char s1[s1_t.length() + 1]; 
	strcpy(s1, s1_t.c_str());
	
	//sequence 2
	ifstream ifs2(argv[2]);
	string s2_t;
	s2_t.assign( (istreambuf_iterator<char>(ifs2) ),
					(istreambuf_iterator<char>()));
    char s2[s2_t.length()+1]; 
	strcpy(s2, s2_t.c_str());
	
	//sequence 3
	ifstream ifs3(argv[3]);
	string s3_t;
	s3_t.assign( (istreambuf_iterator<char>(ifs3) ),
					(istreambuf_iterator<char>()));
    char s3[s3_t.length()+1]; 
	strcpy(s3, s3_t.c_str());
	
	pairAlign(s1,s2);
	
}
