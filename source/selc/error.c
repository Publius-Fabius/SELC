
#include "selc/error.h"
#include <stdio.h>
#include <stdlib.h>

static struct sel_reg **sel_reg_st()
{
        static struct sel_reg *reg = NULL;
        return &reg;
}

void sel_bind(
        struct sel_reg *node, 
        const sel_err_t code, 
        const char *string)
{
        struct sel_reg **reg = sel_reg_st();
        node->code = code;
        node->string = string;
        node->next = *reg;
        *reg = node;
}

void sel_init()
{
        SEL_BIND(SEL_ERR_OK, "All OK");
        SEL_BIND(SEL_ERR_SYS, "System Error");
}

const char *sel_strerror(const sel_err_t code)
{
        for(struct sel_reg *reg = *sel_reg_st(); reg; reg = reg->next) {
                if(reg->code == code) {
                        return reg->string;
                }
        }
        return NULL;
}

sel_err_t sel_abort(
        const char *file,
        const char *func,
        const int line)
{
        fprintf(stderr, 
                "%s: %s(..) line %i: ABORT\r\n",
                file,
                func,
                line);
        abort();
}

sel_err_t sel_report(
        const sel_err_t error,
        const char *file,
        const char *func,
        const int line)
{
        const char *str = sel_strerror(error);
        str = str ? str : "UNKNOWN";
        fprintf(stderr, 
                "%s: %s(..) line %i: error (%i) %s\r\n", 
                file,
                func,
                line,
                error,
                str);
        return error;
}

void sel_info(
        const char *file,
        const char *func,
        const int line)
{
        printf( "%s: %s(..) line %i \n", 
                file, 
                func,
                line);
}