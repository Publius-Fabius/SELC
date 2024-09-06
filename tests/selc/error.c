
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
        
        SEL_TEST(!strcmp(sel_lookup(SEL_ERR_OK), "SEL_ERR_OK"));
        SEL_TEST(!strcmp(sel_lookup(SEL_ERR_SYS), "SEL_ERR_SYS"));
}

void test_addons()
{
        SEL_INFO();
        
        SEL_TEST(!strcmp(sel_lookup(ERROR_A), "ERROR_A"));
        SEL_TEST(!strcmp(sel_lookup(ERROR_B), "ERROR_B"));
}

int main(int argc, char **argv)
{
        SEL_INFO();
        
        sel_init();

        SEL_BIND(ERROR_A, "ERROR_A");
        SEL_BIND(ERROR_B, "ERROR_B");

        test_builtins();
        test_addons();
}