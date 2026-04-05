void kernel_main() {
    const char* str = "Hello from KiddoZ OS!";
    char* vidptr = (char*)0xb8000;
    unsigned int i = 0;
    unsigned int j = 0;

    while (j < 80 * 25 * 2) {
        vidptr[j] = ' ';
        vidptr[j + 1] = 0x07;
        j = j + 2;
    }

    j = 0;
    while (str[i] != '\0') {
        vidptr[j] = str[i];
        vidptr[j + 1] = 0x07;
        i++;
        j = j + 2;
    }

    while (1);
}