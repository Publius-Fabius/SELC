
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
        
        SEL_TEST(!strcmp(sel_lookup(SEL_ERR_OK)[0], "SEL_ERR_OK"));
        SEL_TEST(!strcmp(sel_lookup(SEL_ERR_SYS)[0], "SEL_ERR_SYS"));
}

void test_addons()
{
        SEL_INFO();
        
        SEL_TEST(!strcmp(sel_lookup(ERROR_A)[0], "ERROR_A"));
        SEL_TEST(!strcmp(sel_lookup(ERROR_A)[1], "Error A"));
        SEL_TEST(!strcmp(sel_lookup(ERROR_B)[0], "ERROR_B"));
        SEL_TEST(!strcmp(sel_lookup(ERROR_B)[1], "Error B"));
}

int main(int argc, char **argv)
{
        SEL_INFO();
        
        sel_init();

        SEL_BIND(ERROR_A, "ERROR_A", "Error A");
        SEL_BIND(ERROR_B, "ERROR_B", "Error B");

        test_builtins();
        test_addons();
}