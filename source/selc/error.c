
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
        const char *name)
{
        struct sel_reg **reg = sel_reg_st();
        node->code = code;
        node->name = name;
        node->next = *reg;
        *reg = node;
}

void sel_init()
{
        SEL_BIND(0, "SEL_ERR_OK");
        SEL_BIND(-1, "SEL_ERR_SYS");
}

const char *sel_lookup(const sel_err_t code)
{
        for(struct sel_reg *reg = *sel_reg_st(); reg; reg = reg->next) {
                if(reg->code == code) {
                        return reg->name;
                }
        }
        return "UNKNOWN ERROR";
}

sel_err_t sel_abort(
        const char *file,
        const char *func,
        const int line)
{
        fprintf(stderr, 
                "\n%s: %s(..) line %i: ABORT \n",
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
        fprintf(stderr, 
                "\n%s: %s(..) line %i: REPORT: error %i %s \n", 
                file,
                func,
                line,
                error,
                sel_lookup(error));
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