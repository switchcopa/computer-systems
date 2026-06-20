#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

static void get_password(char *restrict buffer, size_t size);
size_t read_bytes(const char *restrict filename, long offset, size_t length, char *restrict dest);

const char *_fpasswdname = "password.txt";

#define PASSWD_BUF_SIZE 128

int main(void) {
	static char _fpasswd_buff[PASSWD_BUF_SIZE];
	static char _password[PASSWD_BUF_SIZE];
	
	read_bytes(_fpasswdname, 0, PASSWD_BUF_SIZE, _fpasswd_buff);
	get_password(_password, 128);
	
	if (strcmp(_fpasswd_buff, _password) == 0)
		printf("Authenticated!\n");
	return 0;
};

static void get_password(char *restrict buffer, size_t size) {
	struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	printf("Enter password: ");
	fflush(stdout);
	
	int c, i;
	i = 0;
	while (i < size - 1 && (c = getchar()) != EOF && c != '\n')
		buffer[i++] = c;
	buffer[i] = '\0';

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	printf("\n");
};

size_t read_bytes(const char *restrict filename, long offset, size_t length, char *restrict dest) {
	FILE *fp = fopen(filename, "r");
	if (!fp)
		return 0;

	if (fseek(fp, offset, SEEK_SET) != 0) {
		fclose(fp);
		return 0;
	}

	size_t len = fread(dest, sizeof(char), length, fp);
	if (len > 0 && dest[len - 1] == '\n') {
		dest[len - 1] = '\0';
		len--;
	}
	fclose(fp);

	return len;
}
