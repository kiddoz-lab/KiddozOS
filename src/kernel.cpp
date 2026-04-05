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

    void print_string(const char* str) {
        static int cursor = 0;
        char* vidptr = (char*)0xb8000;
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == '\n') {
                cursor = (cursor / 160 + 1) * 160;
            } else {
                vidptr[cursor++] = str[i];
                vidptr[cursor++] = 0x07;
            }
        }
    }

    void kernel_main(multiboot_info* mbi, unsigned int magic) {
        clear_screen();

        if (magic != 0x2BADB002) {
            print_string("Error: Mismatch of hexcode\n");
            return;
        }

        print_string("Kernel loading...\n");

        if (mbi->mods_count > 0) {
            multiboot_mod* mod = (multiboot_mod*)mbi->mods_addr;
            print_string("External Root Module Found\n");
            ksh_start(mod->mod_start, mod->mod_end);
        } else {
            print_string("Error: No Root Module found :( \n");
            ksh_start(0, 0);
        }

        while (1) {
            __asm__("hlt");
        }
    }
}