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
int match=5;
int mismtch=-4;
int indel=-8;

int base_case_size=3;

int size_seq1=0;
int size_seq2=0;
int size_seq3=0;

string seq1_align="";
string seq2_align="";

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

int getMax2D(int v1, int v2, int v3){
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

//returns the score of the alignment
pair<int,string> pairAlign(char *seq1, char *seq2, int size1, int size2){
	int score=0; 
	
	//cout << "PAIR ALIGN" << seq1 << " - " << seq2 << endl;
	
	int s[size1][size2];
	for(int i=0; i< size2; i++){
		if(i==0)
			s[0][i]=0;
		else{
			s[0][i]=((i)*indel);
		}
	}

	for(int j=0; j<size1;j++){
		if(j==0)
			s[j][0]=0;
		else{
			s[j][0]=((j)*indel);
		}
	}
	int i=1;
	int j=1;


	while (i<size1){
		j=1;
		while (j<size2){
			
			s[i][j]=getMax2D(s[i-1][j]+getScore(seq1[i-1],'-'),
					s[i][j-1]+getScore('-',seq2[j-1]),
					s[i-1][j-1]+getScore(seq1[i-1],seq2[j-1]));
			
				//cout << seq1[i-1] <<" - " << seq2[j-1];
				//cout <<":["<< s[i][j] <<"] ";
							
			j++;
		}
		i++;
		//cout <<endl;
	}

	
	int rows =  sizeof s / sizeof s[0]; 
	int cols = sizeof s[0] / sizeof(int); 

	j=cols-1;
	//traceback
	bool gap1=false;
	bool gap2=false;
	bool first_run=true;

	while(i!=0 && j!=0){
		//getMax
		int k=1;
		int max=-100000000;
		int max_i=0;
		string s1_i;
		string s2_j;
		
		if(first_run){
			//start at the max value in the last column
			while (k<(rows)){
				if(s[k][j] >= max){
					max=s[k][j];
					max_i=k;
				}
				k++;
			}

			i=max_i;
			if(i!=(size1-1)){
				int diff=(size1-1)-i;
				k=1;
				//add gaps to seq 2 here
				while (diff>0){
					s1_i+=seq1[size1-k];
					seq1_align.insert(0,s1_i);
					seq2_align.insert(0,"-");
					diff--;
					k++;
					score+=indel;
				}
			}
		}
		s1_i="";
		
			if((!gap1 && !gap2)){
					s1_i+=seq1[i-1];
					s2_j+=seq2[j-1];
					
					if(s1_i==s2_j){
						score+=match;
					}else{
						score+=mismtch;
					}
					
					seq1_align.insert(0,s1_i);
					seq2_align.insert(0,s2_j);
			}
			else if(gap1){
				seq1_align.insert(0,"-");
				s2_j+=seq2[j-1];
				seq2_align.insert(0,s2_j);
				score+=indel;
			}
			else if(gap2){
				s1_i+=seq1[i-1];
				seq1_align.insert(0,s1_i);
				seq2_align.insert(0,"-");
				score+=indel;
			}
			
			
			first_run=false;
			gap1=false;
			gap2=false;
			//update pointers to max value neighbor
			int neigh_up=s[i-1][j];
			int neigh_left=s[i][j-1];
			int neigh_diag=s[i-1][j-1];
			int max_neigh=getMax2D(neigh_up,neigh_left,neigh_diag);
			if(max_neigh==neigh_diag){
				i-=1;
				j-=1;
				gap1=false;
				gap2=false;
			}
			else if(max_neigh==neigh_up){
				//add gap to seq 2
				i-=1;
				gap2=true;
				gap1=false;
				
			}
			else if(max_neigh==neigh_left){
				//add gap to seq 1
				j-=1;
				gap1=true;
				gap2=false;
			}

	}


	string str= seq1_align+"^"+seq2_align;
	pair<int, string> p = make_pair(score, str);
	return p;

}



int getScore3D(char s1, char s2, char s3){
	int p1=getScore(s1,s2);
	int p2=getScore(s2,s3);
	int p3=getScore(s1,s3);
	
	return (p1+p2+p3);
}


int getMax3D(int v1, int v2, int v3, int v4, int v5, int v6, int v7){
	int m1=getMax2D(v1,v2,v3);
	int m2=getMax2D(v4,v5,v6);
	int m3=getMax2D(m1,m2,v7);
	
	return m3;
}

string getPart(string s, string delimiter, int part){
	int found = s.find(delimiter);
	if(part==1){
		return s.substr(0,found);
	}else{
		return s.substr((found+1));
	}
}

string s1temp="";
string s2temp="";
string s3temp="";
int score=0;
int threeSeqAlign(char s1[], char s2[], char s3[], int size1, int size2, int size3){
	int s[size1][size2][size3];
	string seq1_align_3d="";
	string seq2_align_3d="";
	string seq3_align_3d="";

	//cout << "s1-" << size1 <<": "<< s1 << endl;
	//cout << "s2-" << size2 <<": "<< s2 << endl;
	//cout << "s3-" << size3 <<": "<< s3 << endl;
	
	
	//----initialization of 3D dp table----
	for(int j=0; j< size2; j++){
		for(int k=0; k<size3; k++){
			pair<int, string> p=pairAlign(s2,s3, size2, size3);
			s[0][j][k]=p.first;
		}
	}
	
	for(int i=0; i< size1; i++){
		for(int k=0; k<size3; k++){
			pair<int, string> p=pairAlign(s2,s3, size2, size3);
			s[i][0][k]=p.first;
		}
	}
	
	for(int i=0; i< size1; i++){
		for(int j=0; j<size2; j++){
			pair<int, string> p=pairAlign(s2,s3, size2, size3);
			s[i][j][0]=p.first;
		}
	}
	
	//break into halves for Divide and Conquer
	int s1_half=size1/2;
	char s1_first[s1_half];
	char s1_second[size1-s1_half];
	int k=0;
	for(int i=0; i< size1; i++){
		if(i<s1_half){
			s1_first[i]=s1[i];
		}else{
			s1_second[k]=s1[i];
			k++;
		}
	}
	int s2_half=size2/2;
	char s2_first[s2_half];
	char s2_second[size2-s2_half];
	k=0;
	for(int i=0; i< size2; i++){
		if(i<s2_half){
			s2_first[i]=s2[i];
		}else{
			s2_second[k]=s2[i];
			k++;
		}
	}
	int s3_half=size3/2;
	char s3_first[s3_half];
	char s3_second[size3-s3_half];
	k=0;
	for(int i=0; i< size3; i++){
		if(i<s3_half){
			s3_first[i]=s3[i];
		}else{
			s3_second[k]=s3[i];
			k++;
		}
	}
	
	
		
	if(size1<base_case_size || size2<base_case_size || size3<base_case_size){
	// if you can't divide sequences further, make dp table
		for(int i=1; i<size1; i++){
			for(int j=1; j<size2; j++){
				for(int k=1; k<size3; k++){

					s[i][j][k]=getMax3D((s[i-1][j][k]+ getScore3D(s1[i],'-','-')),
										(s[i][j-1][k]+ getScore3D('-',s2[j],'-')),
										(s[i][j][k-1]+ getScore3D('-','-',s3[k])),
										(s[i-1][j-1][k]+ getScore3D(s1[i],s2[j],'-')),
										(s[i-1][j][k-1]+ getScore3D(s1[i],'-',s3[k])),
										(s[i][j-1][k-1]+ getScore3D('-',s2[j],s3[k])),
										(s[i-1][j-1][k-1]+ getScore3D(s1[i],s2[j],s3[k]))
										);
				}
			}
		}
		cout << "Finished s" << endl;
		seq1_align_3d+=seq1_align_3d;
		seq2_align_3d+=seq2_align_3d;
		seq3_align_3d+=seq3_align_3d;


		//traceback
		int i=size1-1;
		int j=size2-1;
		int k=size3-1;
		


		while(i>0 || j>0 || k>0){
			cout << "s["<< i <<","<< j <<","<< k <<"]: ";
			if(i==0 && j==0){
				cout << "if 1" << endl;
				seq1_align_3d.insert(0,"-");
				seq2_align_3d.insert(0,"-");
				string s3k;
				s3k+=s3[k-1];
				seq3_align_3d.insert(0,s3k);
				score+=(2*indel);
				k--;
			}
			else if (i == 0 && k == 0) {
			    cout << "if 2" << endl;
			    seq1_align_3d.insert(0,"-");
			    string s2j;
			    s2j+=s2[j-1];
			    seq2_align_3d.insert(0,s2j);
			    seq3_align_3d.insert(0,"-");
			    score+=(2*indel);
			    j--;
			}
			else if (j == 0 && k == 0) {
			    cout << "if 3" << endl;
			    string s1i;
			    s1i+=s1[i-1];
			    seq1_align_3d.insert(0,s1i);
			    seq2_align_3d.insert(0,"-");
			    seq3_align_3d.insert(0,"-");
			    score+=(2*indel);
			    i--;
			}
			else if (i == 0) {
cout << "if 4" << endl;
			    seq1_align_3d.insert(0,"-");
			    string s2j;
			    s2j+=s2[j-1];
			    seq2_align_3d.insert(0,s2j);
			    string s3k;
			    s3k+=s3[k-1];
			    seq3_align_3d.insert(0,s3k);

			    score+=(2*indel);
			    score+=((s3k==s2j)?match:mismtch);
			    j--;
			    k--;
			}
			else if (j == 0) {
cout << "if 5" << endl;
			    string s1i;
			    s1i+=s1[i-1];
			    seq1_align_3d.insert(0,s1i);
			    seq2_align_3d.insert(0,"-");
			    string s3k;
			    s3k+=s3[k-1];
			    seq3_align_3d.insert(0,s3k);

			    score+=(2*indel);
			    score+=((s1i==s3k)?match:mismtch);
			    i--;
			    k--;
			}
			else if (k == 0) {
cout << "if 6" << endl;
			    string s1i;
			    s1i+=s1[i-1];
			    seq1_align_3d.insert(0,s1i);
			    string s2j;
			    s2j+=s2[j-1];
			    seq2_align_3d.insert(0,s2j);
			    seq3_align_3d.insert(0,"-");

			    score+=(2*indel);
			    score+=((s1i==s2j)?match:mismtch);
			    i--;
			    j--;
			}

			else if (i>0 && j>0 && k>0) {
cout << "if 7" << endl;
			    string s1i;
			    s1i+=s1[i-1];
			    seq1_align_3d.insert(0,s1i);
			    string s2j;
			    s2j+=s2[j-1];
			    seq2_align_3d.insert(0,s2j);
			    string s3k;
			    s3k+=s3[k-1];
			    seq3_align_3d.insert(0,s3k);

			    score+=((s1i==s2j)?match:mismtch);
			    score+=((s1i==s3k)?match:mismtch);
			    score+=((s2j==s3k)?match:mismtch);
			    i--;
			    j--;
			    k--;
			}
			else if (i>0 && j>0 && k==0) {
cout << "if 8" << endl;
			    string s1i;
			    s1i+=s1[i-1];
			    seq1_align_3d.insert(0,s1i);
			    string s2j;
			    s2j+=s2[j-1];
			    seq2_align_3d.insert(0,s2j);
			    seq3_align_3d.insert(0,"-");

			    score+=(2*indel);
			    score+=((s1i==s2j)?match:mismtch);			    
			    i--;
			    j--;
			}
			else if (i>0 && j==0 && k>0) {
cout << "if 9" << endl;
			    string s1i;
			    s1i+=s1[i-1];
			    seq1_align_3d.insert(0,s1i);
			    seq2_align_3d.insert(0,"-");
			    string s3k;
			    s3k+=s3[k-1];
			    seq3_align_3d.insert(0,s3k);

			    score+=(2*indel);
			    score+=((s1i==s3k)?match:mismtch);
			    i--;
			    k--;
			}
			else if (i==0 && j>0 && k==0) {
cout << "if 10" << endl;
			    seq1_align_3d.insert(0,"-");
			    string s2j;
			    s2j+=s2[j-1];
			    seq2_align_3d.insert(0,s2j);
			    string s3k;
			    s3k+=s3[k-1];
			    seq3_align_3d.insert(0,s3k);

			    score+=(2*indel);
			    score+=((s3k==s2j)?match:mismtch);
			    j--;
			    k--;
			}
			else if (i>0 && j==0 && k==0) {
cout << "if 11" << endl;
			    string s1i;
			    s1i+=s1[i-1];
			    seq1_align_3d.insert(0,s1i);
			    seq2_align_3d.insert(0,"-");
			    seq3_align_3d.insert(0,"-");
			    score+=(2*indel);
			    i--;
			}
			else if (i>0 && j>0 && k==0) {
cout << "if 12" << endl;
			    seq1_align_3d.insert(0,"-");
			    string s2j;
			    s2j+=s2[j-1];
			    seq2_align_3d.insert(0,s2j);
			    seq3_align_3d.insert(0,"-");
			    score+=(2*indel);
			    j--;
			}
			else if (i>0 && j==0 && k>0) {
cout << "if 13" << endl;
			    seq1_align_3d.insert(0,"-");
			    seq2_align_3d.insert(0,"-");
			    string s3k;
			    s3k+=s3[k-1];
			    seq3_align_3d.insert(0,s3k);
			    score+=(2*indel);
			    k--;
			}
			cout << score << endl;

		}


		cout << "----------------------ALIGNMENT-------------------------" << endl;
		s1temp+=seq1_align_3d;
		s2temp+=seq2_align_3d;
		s3temp+=seq3_align_3d;
			
		cout << seq1_align_3d << endl;
		cout << seq2_align_3d << endl;
		cout << seq3_align_3d << endl;

		
		return score+=score;
	}
	


	

	
	//Recursively call on first half
	int score_first = threeSeqAlign(s1_first, s2_first, s3_first, sizeof(s1_first), sizeof(s2_first), sizeof(s3_first));

	//Recursively call on second half
	int score_second = threeSeqAlign(s1_second, s2_second, s3_second, sizeof(s1_second), sizeof(s2_second), sizeof(s3_second));
	
	score=score_first+score_second;
	cout << s1temp << endl;
	cout << s2temp << endl;
	cout << s3temp << endl;
	return score;
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
	cout << "s3: " << s3 << endl;
	
	threeSeqAlign(s1,s2, s3, sizeof(s1), sizeof(s2), sizeof(s3));


}
