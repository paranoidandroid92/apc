
static const char STRING_TERMINATOR = 0x00;


int strlength(const char* string){
	int len=0;
	while(string[len]){
		len++;
	}
	return len;

}


