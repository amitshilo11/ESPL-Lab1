#include <stdio.h>
#include <string.h>

// pointers
FILE *input, *output;
void (*func)(char);

void charToAscii(char c) {
    fprintf(output,"%d ", c);
}

void charToBin(char c) {
    for (int i=7; i>=0; --i) {
        putc((c & (1 << i)) ? '1' : '0', output);
    }
    putc(' ', output);
}

void upperToLower(char c) {
    if(c >= 'a' && c <= 'z')
        fprintf(output,"%c", c-32);
    if(c >= 'A' && c <= 'Z')
        fprintf(output,"%c", c+32);
}

int main(int argc, char *argv[]) {
    // setting pointers to Default settings
    func = &charToAscii;
    input = stdin;
    output = stdout;

    // reads program args and looks for flags
    for(int i=0; i<argc; i++) {
        if (argv[i][0] != '-')  // if '-' at the beginning go to next arg
            continue;
        switch (argv[i][1]) {
            case 'b':
                func = &charToBin;
                break;
            case 'c':
                func = &upperToLower;
                break;
            case 'i':
                input = fopen(argv[i+1], "r");
                i++;
                break;
            case 'o':
                output = fopen(argv[i+1], "w+");
                i++;
                break;
        }
    }

    // main loop - get from input and send to the corresponding function to print to output
    char c;
    while((c = getc(input)) != EOF) {
        (*func)(c);
    }

    fclose(input);
    fclose(output);
    return 0;
}