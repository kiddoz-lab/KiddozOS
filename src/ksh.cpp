extern "C" {
    volatile unsigned int* const UART0_DR = (unsigned int*)0x20201000;
    volatile unsigned int* const UART0_FR = (unsigned int*)0x20201018;

    void uart_putc(char c) {
        while (*UART0_FR & (1 << 5));
        *UART0_DR = c;
    }

    char uart_getc() {
        if (!(*UART0_FR & (1 << 4))) {
            return (char)(*UART0_DR & 0xFF);
        }
        return 0;
    }

    int strcmp(const char* s1, const char* s2) {
        while (*s1 && (*s1 == *s2)) {
            s1++;
            s2++;
        }
        return (unsigned char)*s1 - (unsigned char)*s2;
    }

    void print_string(const char* str) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == '\n') uart_putc('\r');
            uart_putc(str[i]);
        }
    }

    void ksh_start() {
        char cmd[64];
        int idx = 0;

        print_string("\nKiddozOS ARCHITECTURE ONLINE\n");
        print_string("System Root Loaded. Type 'help' for commands.\n\n");

        while (1) {
            print_string("kiddoz~ $ ");
            idx = 0;
            while (1) {
                char c = uart_getc();
                if (c == 0) continue;

                if (c == '\r' || c == '\n') {
                    cmd[idx] = '\0';
                    print_string("\n");
                    break;
                } else if (c == 127 || c == '\b') {
                    if (idx > 0) {
                        idx--;
                        print_string("\b \b");
                    }
                } else if (idx < 63) {
                    cmd[idx++] = c;
                    uart_putc(c);
                }
            }

            if (strcmp(cmd, "ls") == 0) {
                print_string("FILES IN /ROOT/:\n");
                print_string("file.txt\nhello.txt\nteam.txt\n");
            } else if (cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == ' ') {
                print_string("Shifting focus to List: ");
                print_string(&cmd[3]);
                print_string("\n");
            } else if (cmd[0] == '~' && cmd[1] == ' ') {
                print_string("Opening file stream: ");
                print_string(&cmd[2]);
                print_string("\n---\n");
                print_string("---\n");
            } else if (strcmp(cmd, "help") == 0) {
                print_string("KiddozOS SHELL COMMANDS:\n");
                print_string("ls    - View files in root\n");
                print_string("cl    - Change directory/list\n");
                print_string("~     - Read file contents\n");
                print_string("help  - Show this menu\n");
            } else if (idx > 0) {
                print_string("Error: Command '");
                print_string(cmd);
                print_string("' not recognized.\n");
            }
        }
    }
}