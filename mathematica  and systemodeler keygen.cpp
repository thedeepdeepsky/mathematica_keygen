#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int f1(int n, char abyte, int c) {
	for (int ibit = 0; ibit < 8; ibit++) {
		int bit = (abyte >> ibit) & 1;
		if (bit + ((n - bit) & ~1) == n) {
			n = (n - bit) >> 1;
		}
		else {
			n = ((c - bit) ^ n) >> 1;
		}
	}
	return n;
}

string genPassword(string str,int hash) {
	for (int ibyte = str.size() - 1; ibyte >= 0; ibyte--) {
		hash = f1(hash, str[ibyte], 0x105C3);
	}

	int n1 = 0;
	while (f1(f1(hash, n1 & 0xFF, 0x105C3), n1 >> 8, 0x105C3) != 0xA5B6) {
		if (++n1 >= 0xFFFF) {
			return "Error";
		}
	}

	n1 = floor(((n1 + 0x72FA) & 0xFFFF) * 99999.0 / 0xFFFF);
	string n1strtmp = (string("0000") + to_string(n1));
	string n1str = n1strtmp.substr(n1strtmp.size() - 5, 5);

	int temp = stoi(
		n1str.substr(0, n1str.size() - 3)
		+ n1str.substr(n1str.size() - 2, 2)
		+ n1str.substr(n1str.size() - 3, 1));
	temp = ceil((temp / 99999.0) * 0xFFFF);
	temp = f1(f1(0, temp & 0xFF, 0x1064B), temp >> 8, 0x1064B);

	for (int ibyte = str.size() - 1; ibyte >= 0; ibyte--) {
		temp = f1(temp, str[ibyte], 0x1064B);
	}

	int n2 = 0;
	while (f1(f1(temp, n2 & 0xFF, 0x1064B), n2 >> 8, 0x1064B) != 0xA5B6) {
		if (++n2 >= 0xFFFF) {
			return "Error";
		}
	}

	n2 = floor((n2 & 0xFFFF) * 99999.0 / 0xFFFF);
	string n2strtmp = (string("0000") + to_string(n2));
	string n2str = n2strtmp.substr(n2strtmp.size() - 5, 5);

	string password;
	password.push_back(n2str[3]);
	password.push_back(n1str[3]);
	password.push_back(n1str[1]);
	password.push_back(n1str[0]);
	password.push_back('-');
	password.push_back(n2str[4]);
	password.push_back(n1str[2]);
	password.push_back(n2str[0]);
	password.push_back('-');
	password.push_back(n2str[2]);
	password.push_back(n1str[4]);
	password.push_back(n2str[1]);
	password.append("::1");
	return password;
}

string genFromMathId(string mathId, string activationKey,int magicnumber) {
	string password = genPassword(mathId + "$1&" + activationKey,magicnumber);
	return password;
}

//6469-027-086::1
void mmagen(string mathId = "", string activationKey = "")
{
	int magicNumbers[] = { 10690, 12251, 17649, 24816, 33360, 35944, 36412, 42041, 42635, 44011, 53799, 56181, 58536, 59222, 61041 };
	for (int i = 0; i < 15; i++)
	{
		cout << genFromMathId(mathId, activationKey, magicNumbers[i]) << endl;
	}
}
void systemmodelergen(string mathId = "", string activationKey = "")
{
	int magicNumbers[] = { 4912, 4961, 22384, 24968, 30046, 31889, 42446, 43787, 48967, 61182, 62774 };
	for (int i = 0; i < 11; i++)
	{
		cout << genFromMathId(mathId, activationKey, magicNumbers[i]) << endl;
	}
}
bool checkmathId(string mathId)
{
	if (mathId.size() != 16) return 0;
	for (int i = 0; i < 4; i++)
	{
		if (mathId[i] > '9' || mathId[i] < '0') return 0;
	}
	if (mathId[4] != '-') return 0;
	for (int i = 5; i < 10; i++)
	{
		if (mathId[i] > '9' || mathId[i] < '0') return 0;
	}
	if (mathId[10] != '-') return 0;
	for (int i = 11; i < 16; i++)
	{
		if (mathId[i] > '9' || mathId[i] < '0') return 0;
	}
	return 1;
}
bool checkact(string actkey)
{
	if (actkey.size() != 16) return 0;
	for (int i = 0; i < 4; i++)
	{
		if (actkey[i] > '9' || actkey[i] < '0') return 0;
	}
	if (actkey[4] != '-') return 0;
	for (int i = 5; i < 9; i++)
	{
		if (actkey[i] > '9' || actkey[i] < '0') return 0;
	}
	if (actkey[9] != '-') return 0;
	for (int i = 10; i < 16; i += 2)
	{
		if (actkey[i] > '9' || actkey[i] < '0') return 0;
	}
	return 1;
}
string genact()
{
	srand(time(0));
	string actkey;
	for (int i = 0; i < 4; i++)
	{
		actkey.push_back('0' + rand() % 10);
	}
	actkey.push_back('-');
	for (int i = 5; i < 9; i++)
	{
		actkey.push_back('0' + rand() % 10);
	}
	actkey.push_back('-');
	for (int i = 10; i < 16; i += 2)
	{
		actkey.push_back('0' + rand() % 10);
		actkey.push_back('A' + rand() % 26);
	}
	return actkey;
}
int main()
{
	int k = 0;
	while (k != 1)
	{
		cout << "Welcome to wolfram mathematica keygenerator(press 0 to start ,press 1 for help)" << endl;
		int num;
		cin >> num;
		if (num == 1)
		{
			cout << "Hello" << endl;
			cout << "To get the mathId,please do the following steps↓" << endl;
			cout << "Step1,Open wolfram mathematica" << endl;
			cout << "Step 2,if your product is registered , it will take you to the welcome screen" << endl;
			cout << "you can press 2 below if your product is registered if not press other numbers" << endl;
			cout << "to continue , press 1 " << endl;
			cin >> num;
			if (num == 2) return 0;
			cout << "Step3,if your product is not activated , it will take you to wolfram product activate screen" << endl;
			cout << "Step 4,choose manual activation" << endl;
			cout << "Step 5,copy the mathid(it's format in xxxx-xxxxx-xxxxx)" << endl;
			cout << "Step 6,paste it under 'Please input your mathId below↓↓↓↓↓↓(In the correct format:xxxx-xxxxx-xxxxx)'here" << endl;
			cout << "Step 7,if you have a activation key or you want to use your own activation key," << endl;
			cout << "type it under 'Input your activation key↓↓↓↓↓↓(in this format:xxxx-xxxx-xxxxxx)'here";
			cout << "If no,press any thing you want" << endl;
			cout << "Step 8,press ENTER" << endl;
			cout << "Step 9,there are 15 passwords with an activation key" << endl;
			cout << "Step 10,copy a random password and and paste it into the registration screen" << endl;
			cout << "Step 11,paste the activation key into the registration screen" << endl;
			cout << "WOW,you've finished reading the tutorial,press enter to pass";
			string code;
			cin >> code;
		}
		cout << "Please input your mathId below↓↓↓↓↓↓(In the correct format:xxxx-xxxxx-xxxxx)" << endl;

		string mathid, actkey;
		cin >> mathid;
		while (checkmathId(mathid) != 1)
		{
			cout << "I'm sorry.Your mathid is not valid,please enter it in this format:xxxx-xxxxx-xxxxx" << endl;
			cin >> mathid;
		}
		cout << "Input your activation key↓↓↓↓↓↓(in this format:xxxx-xxxx-xxxxxx)" << endl;
		cin >> actkey;
		if (checkact(actkey) != 1)
		{
			cout << "Sorry , your input activation key is invalid , I'll generated one for you" << endl;
			actkey = genact();
		}
		cout << "Your activation key is:" << actkey << endl;
		cout << "pick one of the keys below for mathematica" << endl;
		mmagen(mathid, actkey);
		cout << "pick one of the keys below for system modeler" << endl;
		systemmodelergen(mathid, actkey);
		cout << "Thanks for using,feel free to email ***" << endl;
		cout << "press 1 to stop" << endl;
		cin >> k;
	}
}
