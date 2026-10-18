extern int app_value(void);

int main(void)
{
    return app_value() == 42 ? 0 : 1;
}
