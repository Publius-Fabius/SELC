#ifndef SELC_ERROR_H
#define SELC_ERROR_H

/** Simple Error Type */
typedef int sel_err_t;

/** Built-In Errors */
enum sel_err_type {
        SEL_ERR_OK      = 0,            /** All Ok */
        SEL_ERR_SYS     = -1            /** System Error (errno) */
};

/** Error Registry */
struct sel_reg {
        sel_err_t code;                 /** Error Code */
        const char *pair[2];            /** Name, Description Pair */
        struct sel_reg *next;           /** Next Error */
};

/**
 * Initialize Registry
 */
void sel_init();

/**
 * Bind a string to an error code.
 * @param registry Registry node.
 * @param error Error code.
 * @param name The error's name.
 * @param desc The error's description.
 */
void sel_bind(
        struct sel_reg *registry, 
        const sel_err_t error, 
        const char *name,
        const char *desc);

/**
 * Lookup an error.
 */
const char **sel_lookup(const sel_err_t error);

/**
 * Bind a string to an error code
 * @param error Error code.
 * @param desc The error code's description.
 */
#define SEL_BIND(ERROR, DESC) { \
        static struct sel_reg NODE; \
        sel_bind(&NODE, ERROR, #ERROR, DESC); \
}

/**
 * Abort the process. 
 * @param file The file where the process was aborted.
 * @param func The function where the process was aborted.
 * @param line The line number where the process was aborted.
 * @return does not return
 */
sel_err_t sel_abort(
        const char *file,
        const char *func,
        const int line);

/**
 * Abort the process, printing out some error information.
 */
#define SEL_ABORT() sel_abort(__FILE__, __func__, __LINE__)

/**
 * If the expression evaluates to false, abort the process.  This macro
 * expands to nothing when __OPTIMIZE__ is defined.
 * @param EXPR The expression
 */
#ifndef __OPTIMIZE__
#define SEL_ASSERT(EXPR) \
        if(!(EXPR)) { \
                sel_abort(__FILE__, __func__, __LINE__); \
        }
#else
#define SEL_ASSERT(EXPR) 
#endif

/**
 * Does the same thing as SELASSERT, but the macro definition is 
 * not affected by the __OPTIMIZE__ flag.
 * @param EXPR The expression
 */
#define SEL_TEST(EXPR) \
        if(!(EXPR)) { \
                sel_abort(__FILE__, __func__, __LINE__); \
        }

/**
 * Report an error, printing out useful information to stderr.
 * @param file The file where the error occurred.
 * @param func The function where the error occurred.
 * @param line The line number where the error occurred.
 * @return error
 */
sel_err_t sel_report(
        const sel_err_t error,
        const char *file,
        const char *func,
        const int line);

/**
 * Report and return an error.
 */
#define SEL_THROW(ERROR) \
        return sel_report(ERROR, __FILE__, __func__, __LINE__); 

/**
 * If the expression evaluates to an error throw it. 
 * @param EXPR An expression that may produce an error.
 */
#define SEL_TRY(EXPR) {\
        const sel_err_t SEL_TRY_ERR = EXPR;\
        if((SEL_TRY_ERR) != SEL_ERR_OK) {\
                return sel_report(SEL_TRY_ERR, __FILE__, __func__, __LINE__);\
        }\
}

/**
 * If the expression evaluates to an error return it. 
 * @param EXPR An expression that may produce an error.
 */
#define SEL_TRY_QUIETLY(EXPR) { \
        const sel_err_t SEL_TRY_ERR = EXPR; \
        if(SEL_TRY_ERR != SEL_ERR_OK) { \
                return SEL_TRY_ERR; \
        } \
}

#define SEL_IO(EXPR) { \
        const int SEL_IO_ERR = EXPR; \
        if(SEL_IO_ERR < 0) { \
                return sel_report(SEL_ERR_SYS, __FILE__, __func__, __LINE__); \
        } \
}

#define SEL_IO_QUIETLY(EXPR) { \
        const int SEL_IO_ERR = EXPR; \
        if(SEL_IO_ERR < 0) { \
                return SEL_ERR_SYS; \
        } \
}

void sel_info(
        const char *file,
        const char *func,
        const int line);

#define SEL_INFO() sel_info(__FILE__, __func__, __LINE__)

#endif