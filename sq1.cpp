#include<iostream>
#include<vector>
#include <fstream>
#include <bits/stdc++.h>
#include <iterator>
#include <string> 
#include <algorithm>   
#include <utility> 
#include <map>

using namespace std;

//set the constant values here 
int match=1;
int mismtch=-1;
int indel=-2;

int size_seq1=0;
int size_seq2=0;
int size_seq3=0;

string seq1_align="";
string seq2_align="";

map<pair<int,int>, int> gap_locations2D;

void addGap(char* seq, int gap_pos){

	char* seq_updated;
	
	for(int i=sizeof(seq); i>gap_pos; i--)
	{
		seq_updated[i]=seq[i-1];
	}
	seq_updated[gap_pos]='-';
	
	seq=seq_updated;
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
			//add gap to seq2
			pair<int,int> a (i,j);
			gap_locations2D[a]=2;
			return v1;
		}
	}else{
		max=v2;
		if (v3>v2){
			return v3;
		}
		else{
			//add gap to seq1
			pair<int,int> a (i,j);
			gap_locations2D[a]=1;
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

void pairAlign(char *seq1, char *seq2, int size1, int size2){
	gap_locations2D.clear();
	//seq1_align="";
	//seq2_align="";
	cout << "seq1 size: " << size1 << endl;
	cout << "seq2 size: " << size2 << endl;
	
	int s[size1][size2];
	
	//cout << "first row" << endl;
	for(int i=0; i< size2; i++){
		if(i==0)
			s[0][i]=0;
		else{
			s[0][i]=((i)*indel);
		}
		//cout << s[0][i] << ",";
	}
	cout <<endl;
	//cout << "first col" << endl;
	for(int j=0; j<size1;j++){
		if(j==0)
			s[j][0]=0;
		else{
			s[j][0]=((j)*indel);
		}
		//cout << s[j][0] << ",";
	}
	cout <<endl;
	int i=1;
	int j=1;


	while (i<size1){
		j=1;
		while (j<size2){
			
			s[i][j]=getMax2D(s[i-1][j]+getScore(seq1[i-1],'-'),
					s[i][j-1]+getScore('-',seq2[j-1]),
					s[i-1][j-1]+getScore(seq1[i-1],seq2[j-1]), seq1, seq2, i, j);
			
				cout << seq1[i-1] <<" - " << seq2[j-1];
				cout <<":["<< s[i][j] <<"] ";
							
			j++;
		}
		cout << endl;
		i++;
	}

	j=size2;


	//traceback

	while(j>=0){
		//getMax
		int k=0;
		int max=0;
		int max_i=0;

		while (k<size1){
			if(s[k][j] > max){
				max=s[k][j];
				max_i=k;
			}
			k++;
		}

		i=max_i;
		string s1_i;
		string s2_j;
		
		
		//check if a gap exists here
		pair<int,int> a (i,j);
		if(gap_locations2D.count(a)>0){
			if(gap_locations2D[a]==1){
				//add gap to seq 1
				s1_i+='-';			
				s2_j+=seq1[j];
				
			}else{
				//add gap to seq 2
				s1_i+=seq1[i];
				s2_j+='-';
			}
		}else{
			s1_i+=seq1[i];
			s2_j+=seq2[j];
		}

		//cout << "BEFORE: " << endl << seq1_align << " - " << endl;
		//cout << "BEFORE: " << endl << seq2_align << " - " << endl;
		seq1_align.insert(0,s1_i);
		seq2_align.insert(0,s2_j);
		
		//cout << "AFTER: " << endl << seq1_align << " - " << endl;
		//cout << "AFTER: " << endl << seq2_align << " - " << endl;

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
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	pairAlign(s1,s2, sizeof(s1), sizeof(s2));
	
}
