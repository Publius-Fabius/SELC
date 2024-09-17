
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
        const char *name,
        const char *desc)
{
        struct sel_reg **reg = sel_reg_st();
        node->code = code;
        node->pair[0] = name;
        node->pair[1] = desc;
        node->next = *reg;
        *reg = node;
}

void sel_init()
{
        SEL_BIND(SEL_ERR_OK, "SEL_ERR_OK", "All OK");
        SEL_BIND(SEL_ERR_SYS, "SEL_ERR_SYS", "System Error");
}

const char **sel_lookup(const sel_err_t code)
{
        for(struct sel_reg *reg = *sel_reg_st(); reg; reg = reg->next) {
                if(reg->code == code) {
                        return reg->pair;
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
        const char *name = "Unknown";
        const char *desc = "Error";
        const char **pair = sel_lookup(error);
        if(pair) {
                name = pair[0];
                desc = pair[1];
        }
        fprintf(stderr, 
                "\n%s: %s(..) line %i: REPORT: error %i %s %s \n", 
                file,
                func,
                line,
                error,
                name,
                desc);
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