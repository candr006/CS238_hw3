#include<iostream>
#include<vector>
#include <fstream>
#include <bits/stdc++.h>
#include <iterator>
#include <string> 
#include <algorithm>   
#include <utility> 

using namespace std;

//set the constant values here 
int match=5;
int mismtch=-4;
int indel=-8;

int size_seq1=0;
int size_seq2=0;
int size_seq3=0;

void addGap(char* seq, int gap_pos){
	for(int i=sizeof(seq); i>gap_pos; i--)
	{
		seq[i]=seq[i-1];
	}
	seq[gap_pos]='-';
	return;
}

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

int getMax2D(int v1, int v2, int v3, char* s1, char* s2, int i, int j){
	int max;
	
	if(v1>=v2){
		max=v1;
		if (v3>v1){
			return v3;
		}
		else{
			cout <<"BEFORE: "<< s2 << endl;
			addGap(s2,j);
			cout << "AFTER: " << s2 << endl;
			return v1;
		}
	}else{
		max=v2;
		if (v3>v2){
			return v3;
		}
		else{
			cout <<"BEFORE: "<< s2 << endl;
			addGap(s1,i);
			cout << "AFTER: " << s2 << endl;
			return v2;
		}
	}
	
};


int getMaxIndex2D(int **s, int col, int size){
	int i=0;
	int max=0;
	int max_i=0;

	while (i<size){
		if(s[i][col] > max){
			max=s[i][col];
			max_i=i;
		}
		i++;
	}

	return max_i;
}

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
			s[i][j]=getMax2D(s[i-1][j]+getScore(seq1[i],'-'),
					s[i][j-1]+getScore('-',seq2[j]),
					s[i-1][j-1]+getScore(seq1[i],seq2[j]), seq1, seq2, i, j);
			
				//cout << i << "," << j << ": " << s[i][j] << endl;
							
			j++;
		}
		
		i++;
	}

	j=sizeof(seq2);

	//traceback
	string seq1_align="";
	string seq2_align="";
	while(j>0){
		//getMax
		int k=0;
		int max=0;
		int max_i=0;

		while (k<sizeof(seq1)){
			if(s[k][j] > max){
				max=s[k][j];
				max_i=k;
			}
			k++;
		}

		i=max_i;
		
		string s1_i;
		s1_i+=seq1[i];
		string s2_j;
		s2_j+=seq1[j];

		seq1_align.insert(0,s1_i);
		seq2_align.insert(0,s2_j);

		j--;

	}

	cout << seq1_align << endl;
	cout << seq2_align << endl;

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
	size_seq1=sizeof(s1);
	
	//sequence 2
	ifstream ifs2(argv[2]);
	string s2_t;
	s2_t.assign( (istreambuf_iterator<char>(ifs2) ),
					(istreambuf_iterator<char>()));
    char s2[s2_t.length()+1]; 
	strcpy(s2, s2_t.c_str());
	size_seq2=sizeof(s2);
	
	//sequence 3
	ifstream ifs3(argv[3]);
	string s3_t;
	s3_t.assign( (istreambuf_iterator<char>(ifs3) ),
					(istreambuf_iterator<char>()));
    char s3[s3_t.length()+1]; 
	strcpy(s3, s3_t.c_str());
	size_seq3=sizeof(s3);
	
	pairAlign(s1,s2);
	
}
