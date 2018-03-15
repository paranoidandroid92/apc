
int strlength(const char* string) {
	int len = 0;
	while (string[len]) {
		len++;
	}
	return len;
}

void reverse(char string[]) {
	int i, j;
	char temp;

	for (i = 0, j = strlength(string) - 1; i < j; i++, j--) {
		temp = string[i];
		string[i] = string[j];
		string[j] = temp;
	}
}

