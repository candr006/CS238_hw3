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
int pairAlign(char *seq1, char *seq2, int size1, int size2){
	gap_locations2D.clear();
	int score=0; 
	
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
			while (k<(rows)){
				if(s[k][j] >= max){
					max=s[k][j];
					max_i=k;
				}
				k++;
			}

			i=max_i;
		}
		
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
			//check neighbors
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

	//cout << seq1_align << endl;
	//cout << seq2_align << endl;
	
	return score;

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


void threeSeqAlign(char s1[], char s2[], char s3[], int size1, int size2, int size3){
	int s[size1][size2][size3];
	
	//initialization
	for(int j=0; j< size2; j++){
		for(int k=0; k<size3; k++){
			s[0][j][k]=pairAlign(s2[j],s3[k]);
		}
	}
	
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

	int p = pairAlign(s1,s2, sizeof(s1), sizeof(s2));
}
