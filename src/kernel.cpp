extern "C" {
    void ksh_start(unsigned int mod_start, unsigned int mod_end);

    struct multiboot_info {
        unsigned int flags;
        unsigned int mem_lower;
        unsigned int mem_upper;
        unsigned int boot_device;
        unsigned int cmdline;
        unsigned int mods_count;
        unsigned int mods_addr;
    };

    struct multiboot_mod {
        unsigned int mod_start;
        unsigned int mod_end;
        unsigned int string;
        unsigned int reserved;
    };

    void clear_screen() {
        char* vidptr = (char*)0xb8000;
        for (int i = 0; i < 80 * 25 * 2; i += 2) {
            vidptr[i] = ' ';
            vidptr[i+1] = 0x07;
        }
    }

    unsigned char inb(unsigned short port) {
        unsigned char ret;
        __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
        return ret;
    }

    char get_input_char() {
        static char last_char = 0;
        unsigned char scancode = inb(0x60);
        if (!(scancode & 0x80)) { 
            char map[] = {0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0, 
                          'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 
                          'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 
                          'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '};
            if (scancode < sizeof(map) && map[scancode] != last_char) {
                last_char = map[scancode];
                return last_char;
            }
        } else {
            last_char = 0; 
        }
        return 0;
    }

    void print_string(const char* str) {
        static int cursor = 0;
        char* vidptr = (char*)0xb8000;
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == '\n') {
                cursor = (cursor / 160 + 1) * 160;
            } else if (str[i] == '\b') {
                if (cursor > 0) {
                    cursor -= 2;
                    vidptr[cursor] = ' ';
                    vidptr[cursor+1] = 0x07;
                }
            } else {
                vidptr[cursor++] = str[i];
                vidptr[cursor++] = 0x07;
            }
        }
    }

    void kernel_main(multiboot_info* mbi, unsigned int magic) {
        clear_screen();
        if (magic != 0x2BADB002) {
            print_string("Error: Boot Magic Mismatch\n");
            return;
        }
        print_string("KMC-1 Kernel Active\n");
        if (mbi->mods_count > 0) {
            multiboot_mod* mod = (multiboot_mod*)mbi->mods_addr;
            print_string("Root Module Found\n");
            ksh_start(mod->mod_start, mod->mod_end);
        } else {
            print_string("Error: No Root Module\n");
            ksh_start(0, 0);
        }
        while (1) { __asm__("hlt"); }
    }
}