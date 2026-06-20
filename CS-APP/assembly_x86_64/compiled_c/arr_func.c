void copy(char *dest, char *src);

char global_buf[20];

int main(void) {
	char local_buf[20];
	copy(local_buf, "Hello! C :)\n");
	copy(global_buf, local_buf);
	
	return 0;
}

void copy(char *dest, char *src) {
	int i;
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
}
