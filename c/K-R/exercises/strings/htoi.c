#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 17

char line[MAXSIZE];

bool is_hex(char c);
int hex(char c);
unsigned long long int htoi(char s[]);
int getline();

int main(void) {
    int len; 
    unsigned long long int res;
    
    while ((len = getline()) > 0) {
        res = htoi(line);

        printf("the hex value of the input is: %llu with length %d\n", res, len);
    }

    return 0;
}

bool is_hex(char c) {
    return (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'); 
}

int hex(char c) {
    int hex_val; 
    
    hex_val = 0;
    if (c >= '0' && c <= '9') {
        hex_val = c - '0'; 
    }
    else if (c >= 'a' && c <= 'f') {
        hex_val = c - 'a' + 10; 
    }
    else if (c >= 'A' && c <= 'F') {
        hex_val = c - 'A' + 10;
    }

    return hex_val;
}

unsigned long long int htoi(char s[]) {
    int i, c; 
    unsigned long long int res;
    
    res = 0;

    for (i = 0; is_hex(s[i]); i++) {
        c = hex(s[i]);
        res = res * 16 + c;
    }

    return res;
}

int getline() {
    int c, i; 
    
    i = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (i < MAXSIZE - 1) 
            line[i] = c;

        i++;
    }

    line[i] = '\0';
    return i;
}
