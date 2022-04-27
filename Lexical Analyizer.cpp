#include <fstream>
#include <iostream>
using namespace std;

char KEYWORDS[][20] = {"ARRAY", "BEGIN", "DIV", "DO", "ELSE", "END",
"FUNCTION", "IF", "INTEGER", "MOD", "NOT", "OF", "PROCEDURE", "PROGRAM",
"REAL", "READLN", "THEN", "VAR", "WHILE", "WRITELN"};
char OPERATORS[][16] = {"+", "-", "*", "/", "%", "<", ">", ">=", "<=", "<>", "!=", "=", "DIV", ":=", "OR", "AND"};

void idifyer(char x[], int n, int line) {
	int flag  = -1, flagC = -1;
	for (int s = 0; s < 20; s++) {
		if (strcmp(x, KEYWORDS[s]) == 0) {
			cout << "Line " << line << ": " << x << " : keyword\n";
			return;
		}
	}
	for (int s = 0; s < 16; s++) {
		if (strcmp(x, OPERATORS[s]) == 0) {
			cout << "Line " << line << ": " << x << " : operator\n";
			return;
		}
	}
	for (int s = 0; s < n; s++) {
		if (s == 0 and (x[s] >= 'a' and x[s] <= 'z' or x[s] >= 'A' and x[s] <= 'Z' or x[s] == '_')) {
			flag = 1;
		}
		else if (s != 0 and (x[s] >= 'a' and x[s] <= 'z' or x[s] >= 'A' and x[s] <= 'Z' or x[s] >= '0' and x[s] <= '9' or x[s] == '_')) {
			flag = 1;
		}
		else {
			flag = 0;
			for (int s = 0; s < n; s++) {
				if (x[s] >= '0' and x[s] <= '9') {
					flagC = 1;
				}
				else {
					flagC = 0;

					cout << "Line " << line << ": " << x << " : invalid token\n";
					return;
				}
			}
			if (flagC == 1) {
				cout << "Line " << line << ": " << x << " : constant\n";
				return;
			}
			cout << "Line " << line << ": " << x << " : invalid token\n";
			return;
		}
	}
	if (flag == 1) {
		cout << "Line " << line << ": " << x << " : identifier\n";
	}
	
}

void scanner(char buf[], int n) {
	char x[10] = ""; int i = 0; static int line = 1;
	for (int s = 0; s < n; s++) {
		if (buf[s] == ' ' and buf[s + 1] != 'i') {
			idifyer(x, i, line);
			i = 0;
			for (int d = 0; d < 10; d++) {
				x[d] = 0;
			}
		}
		else if (buf[s] == ';' and buf[s + 1] == ' ' or buf[s + 1] == '\n' or buf[s] == ',') {
			if (buf[s + 1] == '\n') {
				idifyer(x, i, line);
				line++;
			}
			else {
				idifyer(x, i, line);
			}
			i = 0;
			for (int d = 0; d < 10; d++) {
				x[d] = 0;
			}
			s++;
		}
		else if (buf[s] == ';' and buf[s + 1] != ' ' or buf[s + 1] == '\n') {
			if (buf[s + 1] == '\n') {
				idifyer(x, i, line);
				line++;
			}
			else {
				idifyer(x, i, line);
			}
			i = 0;
			for (int d = 0; d < 10; d++) {
				x[d] = 0;
			}
		}
		else {
			x[i] = buf[s];
			i++;
		}
	}
}

int main() {
	ifstream file;
	file.open("IDE.txt");
	int index = 0;
	while (!file.eof()) {
		file.get();
		index++;
	}
	file.close();
	char* buffer = new char[index];
	index = 0; int line = 1;
	cout << "Program:\n__________________________________\n";
	file.open("IDE.txt");
	while (!file.eof()) {
		*(buffer + index) = file.get();
		cout << *(buffer + index);
		index++;
	}
	file.close();
	cout << endl << endl << "__________________________________\n";

	scanner(buffer, index);
}



