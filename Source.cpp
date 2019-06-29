#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>
#include<cmath>
using namespace std;
/**
conunt rows by counting the number of ;
@param x  string of the matrix
@return number of rows
*/
int countRows(string x) {
	int rows = 0;
	for (int i = 0; i < x.length(); i++) {
		if (x[i] == ';') rows++;
	}
	return rows;
}
/**
converts a string to a vector of vector of strings         XXX_   there is \empty strings inside it   _XXX
@param x the string that will be converted
@return matrix of strings
*/
vector<vector<string> > mat(string x) {
	vector<vector<string> > matr;
	int rows = countRows(x), j = 0, k = 0;

	for (int i = 0; i <= rows; i++) {
		vector<string> temp;

		for (int j = k; j < x.length() - 1; j++) {
			char c = x[j];

			if (x[j] == ';') { k = j + 1;   break; } //end the current row and update counter to start a new one 
			string col;
			if (j > 0 && (x[j - 1] == ' ' || x[j - 1] == '[' || x[j - 1] == ';') && (x[j + 1] == ';' || x[j + 1] == ' ' || x[j + 1] == ']'))
				col.push_back(c); //add one character 
			else if (j > 0 && (x[j - 1] == ' ' || x[j - 1] == '[' || x[j - 1] == ';') && (x[j + 1] != ';' || x[j + 1] != ' ' || x[j + 1] != ']')) {
				// multable character so i will make a loop over them to add them as a string
				for (int k = j; ; k++) {
					col.push_back(x[k]); //add multy character
					if ((x[k + 1] == ';' || x[k + 1] == ' ' || x[k + 1] == ']')) break; //end of string  
				}
			}
			temp.push_back(col);
		}
		matr.push_back(temp);
	}
	return matr;
}
/**
erase empty string from the matrix
@param matrix1 vector of vectors of strings that have some empty strings inside it
@return a matrix that has no empty strings inside it          XXX _ - sign issue still unfixed _ XXX
*/
vector<vector<string> >smatrix(vector<vector <string> >matrix1) {
	vector<vector<string> > actualMat;
	string col;
	for (int i = 0; i < matrix1.size(); i++) {
		vector<string> temp;
		for (int j = 0; j < matrix1[i].size(); j++) {
			if (matrix1[i][j] != "")
				temp.push_back(matrix1[i][j]);
		}
		actualMat.push_back(temp);
	}
	return actualMat;
}
/**
convert a matrix of strings to a matrix of floats        :)   -sign issue fixed   :)
@param sm vector of vectors of strings
@return THE MATRIXXXXXXX :o
*/
vector<vector<float> >fmatrix(vector<vector<string> >sm) {
	vector<vector<float> > r;
	for (int f = 0; f < sm.size(); f++) {
		vector<float> temp;
		for (int g = 0; g < sm[f].size(); g++) {
			if (sm[f][g] == "-")
				temp.push_back(-atof(sm[f][g + 1].c_str()));

			else if ((sm[f][0] == "-") || (g>0 && sm[f][g - 1] == "-"))
				continue;

			else
				temp.push_back(atof(sm[f][g].c_str()));
		}
		r.push_back(temp);
	}
	return r;
}
// convert float vector to string vector
vector<vector<string> >ftsVector(vector<vector<float> > f) {
	vector<vector<string> >result;

	for (int i = 0; i < f.size(); i++) {
		vector<string >temp;
		for (int j = 0; j < f[i].size(); j++) {
			string str;
			ostringstream ss;
			ss << f[i][j];
			str = ss.str();
			temp.push_back(str);
		}
		result.push_back(temp);
	}
	return result;
}

void pvs(vector<vector<string> > THE_MATRIX) {
	cout << "[";
	for (int i = 0; i < THE_MATRIX.size(); i++) {
		for (int j = 0; j < THE_MATRIX[i].size(); j++) {
			cout << THE_MATRIX[i][j];
			if (j != THE_MATRIX[i].size() - 1)
				cout << " ";
		}
		if (i != THE_MATRIX.size() - 1)
			cout << ";";
	}
	cout << "]" << endl;
}

//***************************************************************************
vector<vector<float> > multiply(vector<vector<float> >m1, vector<vector<float> >m2) {
	//2*3 3*4 >>2*4       3*5 5*5 >>3*5
	vector<vector<float> >r;

	for (int c = 0; c < m1.size(); c++) {
		vector<float>temp;
		for (int i = 0; i < m1[0].size(); i++) { //loop over m1 rows
			float x = 0;
			for (int j = 0; j < m1[0].size(); j++) { //loop over m1 cols
				x += (m1[c][j] * m2[j][i]); //row m1  *  col m2
			}
			temp.push_back(x);
		}
		r.push_back(temp);
	}
	return r;
}

vector<vector<float> >oss(vector<vector<float> >m, int p) {

	vector<vector<float> > r = m;
	for (int i = 1; i < p; i++)  //repeat p times
		r = multiply(r, m);
	return r;

}

vector<vector<float> > transopse(vector<vector<float> >m) {
	vector<vector<float> > r;

	for (int i = 0; i < m[0].size(); i++) {
		vector<float> temp;
		for (int j = 0; j < m.size(); j++)
			temp.push_back(m[j][i]);
		r.push_back(temp);
	}
	return r;
}
//delete the row i and col j from a vector
vector<vector<float> >deleterc(vector<vector<float> >m, int i, int j) {
	/*cout << "i j " << i << j << "  " << setw(3);*/
	vector<vector<float> >r;
	for (int k = 0; k < m.size(); k++) {
		if (k != i) {
			vector<float>temp;
			for (int f = 0; f < m.size(); f++) {
				if (temp.size() >= m.size()) break;
				//fuckkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
				if (f != j) {
					temp.push_back(m[k][f]);
					//cout << setw(1) << " T=" << m[k][f] << " at kf " << k << f << "  ";
				}
			}
			r.push_back(temp);
		}
	}
	return r;
}

float determant2(vector<vector<float> > m) {
	float r;
	r = (m[0][0] * m[1][1]) - (m[1][0] * m[0][1]);
	return r;
}

int validate(vector<vector<float> >m, string op) {
	int flag = 1; //1 means no error 
	if (op == "T") {
		for (int i = 1; i < m.size(); i++) {
			if (m[i - 1].size() != m[i].size())
				flag = 0; //means error
		}
	}
	if (op == "D" || op == "^" || op == "I") {
		if (m[0].size() != m.size())
			flag = 0; //not square matrix
	}

	return flag;
}

float determant(vector<vector<float> > m) {
	float r = 0;
	int sign = 2;
	for (int j = 0; j < m.size(); j++) {
		if (m.size() > 2) {
			r += pow(-1, sign)*(m[0][j])*determant(deleterc(m, 0, j));
			sign++;
		}
		else if (m.size() == 2) {
			r += determant2(m);
			break;
		}
	}
	return r;
}

vector<vector<float> >inverse(vector<vector<float> >m) {
	vector<vector<float> >r;
	float invdet = (1 / determant(m));
	int sign = 0;

	for (int i = 0; i < m.size(); i++) {
		vector<float> temp;
		for (int j = 0; j < m.size(); j++) {
			temp.push_back(pow(-1, sign)*determant(deleterc(m, i, j)) *invdet);
			sign++;
		}
		r.push_back(temp);
	}
	r = transopse(r);
	return r;
}

vector<vector<float> >divide(vector<vector<float> > m1, vector<vector<float> >m2) {
	return multiply(m1, inverse(m2));
}

int validateD(vector<vector<float> >THE_MATRIX_1, vector<vector<float> >THE_MATRIX_2) {

	if (THE_MATRIX_1[0].size() == THE_MATRIX_2.size()) {
		return 1;
	}
	else {
		return 0;
	}

}

void decide(vector<vector<float> >THE_MATRIX_1, string op, string m2) {
	//POWER
	if (op == "^") {
		int p = atoi(m2.c_str());
		if (validate(THE_MATRIX_1, op)) {
			vector<vector<string> >stringMatrix = ftsVector(oss(THE_MATRIX_1, p));
			pvs(stringMatrix);
		}
		else cout << "ERROR";
	}
	//TRANSPOSE
	if (op == "T") {
		if (validate(THE_MATRIX_1, op)) {
			vector<vector<string> >stringMatrix = ftsVector(transopse(THE_MATRIX_1));
			pvs(stringMatrix);
		}
		else cout << "ERROR";

	}
	//DETERNANT
	if (op == "D") {
		if (validate(THE_MATRIX_1, op))
			cout << (determant(THE_MATRIX_1));
		else cout << "ERROR";
	}
	//INVERSE
	if (op == "I") {
		if (validate(THE_MATRIX_1, "D")) {
			vector<vector<string> >stringMatrix = ftsVector(inverse(THE_MATRIX_1));
			pvs(stringMatrix);
		}
		else cout << "ERROR";
	}
	//DiVISION
	if (op == "/") {
		vector<vector<float> > THE_MATRIX_2 = fmatrix(smatrix(mat(m2)));
		if (validateD(THE_MATRIX_1, THE_MATRIX_2)) {
			vector<vector<string> >stringMatrixx = ftsVector(divide(THE_MATRIX_1, THE_MATRIX_2));
			pvs(stringMatrixx);
		}
		else cout << "ERROR";
	}
}

int main() {
	string m1, op, m2;
	getline(cin, m1);        getline(cin, op);        getline(cin, m2);
	vector<vector<float> > THE_MATRIX_1 = fmatrix(smatrix(mat(m1)));

	decide(THE_MATRIX_1, op, m2);
	system("pause");
	return 0;
}