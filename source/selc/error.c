
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

sel_err_t sel_halt(
        FILE *stream,
        const char *file,
        const char *func,
        const int line)
{
        fprintf(stream, 
                "halt %i \"%s\" %s(..)\r\n",
                line,
                file,
                func);
        abort();
}

sel_err_t sel_report(
        FILE *stream,
        const sel_err_t error,
        const char *file,
        const char *func,
        const int line)
{
        const char *str = sel_strerror(error);
        str = str ? str : "unknown";
        fprintf(stream,
                "error %i \"%s\" %s(..) %i %s\r\n", 
                line,
                file,
                func,
                error,
                str);
        return error;
}

void sel_info(
        FILE *stream,
        const char *file,
        const char *func,
        const int line)
{
        fprintf(stream, 
                "info %i \"%s\" %s(..)\r\n",
                line,
                file,
                func);
}