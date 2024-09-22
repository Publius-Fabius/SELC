
#include "selc/error.h"
#include <stdio.h>
#include <string.h>

enum test_errors {
        ERROR_A         = -3,
        ERROR_B         = -4
};

void test_builtins()
{
        SEL_INFO();
        
        SEL_TEST(!strcmp(sel_strerror(SEL_ERR_OK), "All OK"));
        SEL_TEST(!strcmp(sel_strerror(SEL_ERR_SYS), "System Error"));
}

void test_addons()
{
        SEL_INFO();
        
        SEL_TEST(!strcmp(sel_strerror(ERROR_A), "A"));
        SEL_TEST(!strcmp(sel_strerror(ERROR_B), "B"));
}

int main(int argc, char **argv)
{
        SEL_INFO();
        
        sel_init();

        SEL_BIND(ERROR_A, "A");
        SEL_BIND(ERROR_B, "B");

        test_builtins();
        test_addons();
}