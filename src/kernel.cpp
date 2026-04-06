extern "C" {
    void ksh_start();

    void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags) {
        ksh_start();
        while (1) {
            __asm__("wfi");
        }
    }
}