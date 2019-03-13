#include <iostream>
#include <string>
#include <cstdlib>
#include <cinttypes>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	string str = "C90FDAA22168C2";
	uint8_t stuff[2048];
	int i = 0;
	for(int x = 0; x < str.size(); x+=2)
	{
		char tempStr[2];
		strncpy(tempStr, (str.substr(x, 2)).c_str(), 2);
		stuff[i] = (uint8_t)strtoul(tempStr, NULL, 16);
		printf("%#x\n", stuff[i]);
		i++;

	}

	cout << str << endl;

	return 0;
}
