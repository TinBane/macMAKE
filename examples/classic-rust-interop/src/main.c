extern unsigned int macmake_rust_answer(unsigned int value);
extern void SysBeep(short duration);

int main(void)
{
    if (macmake_rust_answer(41U) == 42U) {
        SysBeep(2);
        return 0;
    }
    return 1;
}
