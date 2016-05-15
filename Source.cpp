#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <limits.h>
#include <string.h>
#include <queue>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>    
using namespace std;

struct commits{
	string commit;
	map<int, string> author;
};

struct author{
	string auth;
	int numcommit;
};

struct mergee{

	void mergeSort(struct author A[], int p, int r);
	void merge_(struct author A[], int p, int q, int r);
};

void mergee::mergeSort(struct author A[], int p, int r){
	if (p < r)
	{
		int q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		merge_(A, p, q, r);
	}
}

void mergee::merge_(struct author A[], int p, int q, int r){

	int n1 = q - p + 1;
	int n2 = r - q;
	struct author *L = new struct author[n1 + 1];
	struct author *R = new struct author[n2 + 1];

	for (int i = 1; i < n1 + 1; i++)
		L[i - 1] = A[(p + i) - 1];
	for (int j = 1; j < n2 + 1; j++)
		R[j - 1] = A[q + j];

	L[n1].numcommit = numeric_limits<int>::max();;
	R[n2].numcommit = numeric_limits<int>::max();;

	int i = 0;
	int j = 0;
	int k = p;
	for (k; k <= r; k++){
		if (L[i].numcommit <= R[j].numcommit)
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
	}

}


int main(){
	ifstream file;
	file.open("input.txt");
	vector<vector<string>> g;
	map<string, vector<string> > m;
	map<string, map<string, int>> matrix; // ith file jth developer.


	std::string com;
	std::string aut;
	std::string word;
	string temp;
	string temp2;
	int numCommit = 0;
	while (file >> word)
	{
		
		if (word == "Author:"){
			
			file >> aut;
			com = temp;
			file >> word;
			if (word[0] != '<'){
				aut = aut + word;
			}
				numCommit++;
				m[aut].push_back(com);
		}
		if (word == "Cr-Commit-Position:"){
			file >> word;
			file >> word;
		
		while (word == "M" || word == "D" || word == "A"){
			file >> word; 
			matrix[word][aut] = 1;
			file >> word;
		}
		}
		
		temp = word;
	}
	file.close();

	//all developers with their number of commits
	ofstream outFile;
	outFile.open("allAuthors.txt");

	// top developers in commit count sorted order
	ofstream outFileee;
	outFileee.open("topSorted.txt");

	// top developers to track matrix.adj in here top[0] mean first row and first column in matrix.adj
	ofstream outF;
	outF.open("top.txt");

	// all distinct file names
	ofstream o;
	o.open("filess.txt");

	//connection matrix betweenn each developers.
	ofstream adj;
	adj.open("matrix.adj");

	

	struct author *A = new struct author[m.size()];
	int i = 0;
	int s = 0;
	for (std::map<string, vector<string>>::iterator it = m.begin(); it != m.end(); ++it){
		//outFile << "The " << it->first << " has " << m[it->first].size() << " commits" << endl;
		outFile << it->first << " " << m[it->first].size() << endl;
		struct author a;
		a.auth = it->first;
		a.numcommit = m[it->first].size();
		s = s + m[it->first].size();
		A[i] = a;
		i++;
	}

	mergee mm;
	mm.mergeSort(A, 0, m.size() - 1);

	struct author *topDev = new struct author[m.size()];
	map<string, int> top;
	double sum = 0.0;
	int j = 0;
	for (int i = (m.size() - 1); i>(-1); i--){
		sum = sum + double(double((A[i].numcommit * 100)) / double(numCommit));
		if (sum >= 80){
			topDev[j] = A[i];
			top[A[i].auth] = A[i].numcommit;
			break;
		}
		else{
			topDev[j] = A[i];
			top[A[i].auth] = A[i].numcommit;
			j++;
		}
	}

	
	for (int i = 0; i < m.size(); i++){
		if (topDev[i].auth != ""){
			outFileee << topDev[i].auth << " " << topDev[i].numcommit << endl;
		}
	}

	map<string, map<string, int>> developers;


	string  *t = new string[top.size()];
	map<string, int> temp_top = top;

	
	for (auto const &ent1 : matrix) {
		int i = 0;
		o << ent1.first << endl;
		for (auto const &ent2 : ent1.second) {
			if (temp_top[ent2.first] > 0 && matrix[ent1.first][ent2.first] == 1){
				t[i] = ent2.first;
				i++;
			}
		}
		for (int j = 0; j < i; j++){
			for (int k = j + 1; k < i; k++){
				developers[t[j]][t[k]] = 1;
				developers[t[k]][t[j]] = 1;
			}
		}

	}

	string *arr = new string[top.size()];
	int index = 0;
	for (auto const &ent : top){
		arr[index] = ent.first;
		index++;
	}

	

	
	for (int i = 0; i <index ; i++){
		outF << arr[i] << endl;
		for (int j = 0; j < index; j++){
			adj << developers[arr[i]][arr[j]] << " ";
		}
		adj << endl;
	}
	outF.close();
	outFile.close();
	outFileee.close();
	system("PAUSE");
	return 0;
}