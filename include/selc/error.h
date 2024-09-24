#ifndef SELC_ERROR_H
#define SELC_ERROR_H

#include <stdio.h>

/** Simple Error Type */
typedef int sel_err_t;

/** Built-In Errors */
enum sel_err_type {
        SEL_ERR_OK      = 0,            /** All OK */
        SEL_ERR_SYS     = -1            /** System Call Error */
};

/** Error Registry */
struct sel_reg {
        sel_err_t code;                 /** Error Code */
        const char *string;             /** Error String */
        struct sel_reg *next;           /** Next Error */
};

/**
 * Initialize Registry
 */
void sel_init();

/**
 * Bind a string to an error code.
 * @param registry Registry node.
 * @param error The error code.
 * @param string The error code's string.
 */
void sel_bind(
        struct sel_reg *registry, 
        const sel_err_t error, 
        const char *string);

/**
 * Get an error's string.
 * @param error The error code.
 * @return The error code's string.
 */
const char *sel_strerror(const sel_err_t error);

/**
 * Bind a string to an error code
 * @param error Error code.
 * @param desc The error code's description.
 */
#define SEL_BIND(ERROR, DESC) { \
        static struct sel_reg NODE; \
        sel_bind(&NODE, ERROR, DESC); \
}

/**
 * Abort the process. 
 * @param file The file where the process was aborted.
 * @param func The function where the process was aborted.
 * @param line The line number where the process was aborted.
 * @return does not return
 */
sel_err_t sel_abort(
        FILE *stream,
        const char *file,
        const char *func,
        const int line);

/**
 * Abort the process, printing out some error information.
 */
#define SEL_ABORT() sel_abort(stderr, __FILE__, __func__, __LINE__)

/**
 * If the expression evaluates to false, abort the process.  This macro
 * expands to nothing when __OPTIMIZE__ is defined.
 * @param EXPR The expression
 */
#ifndef __OPTIMIZE__
#define SEL_ASSERT(EXPR) \
        if(!(EXPR)) { \
                sel_abort(stderr, __FILE__, __func__, __LINE__); \
        }
#else
#define SEL_ASSERT(EXPR) 
#endif

/**
 * Does the same thing as SEL_ASSERT, but the macro definition is 
 * not affected by the __OPTIMIZE__ flag.
 * @param EXPR The expression
 */
#define SEL_TEST(EXPR) \
        if(!(EXPR)) { \
                sel_abort(stderr, __FILE__, __func__, __LINE__); \
        }

/**
 * Report an error, printing out useful information to stderr.
 * @param file The file where the error occurred.
 * @param func The function where the error occurred.
 * @param line The line number where the error occurred.
 * @return error
 */
sel_err_t sel_report(
        FILE *stream,
        const sel_err_t error,
        const char *file,
        const char *func,
        const int line);

/** 
 * Report an error.
 */
#define SEL_FREPORT(STREAM, ERROR)      \
        sel_report(                     \
                STREAM,                 \
                ERROR,                  \
                __FILE__,               \
                __func__,               \
                __LINE__)

/** 
 * Report an error.
 */
#define SEL_REPORT(ERROR) SEL_FREPORT(stderr, ERROR)

/**
 * Report and return an error.
 */
#define SEL_FTHROW(STREAM, ERROR) return SEL_FREPORT(STREAM, ERROR)

/**
 * Report and return an error.
 */
#define SEL_THROW(ERROR) SEL_FTHROW(stderr, ERROR);

/**
 * If the expression evaluates to an error throw it. 
 */
#define SEL_FTRY(STREAM, EXPR) {                        \
        const sel_err_t SEL_TRY_ERR = EXPR;             \
        if(SEL_TRY_ERR != SEL_ERR_OK) {                 \
                SEL_FTHROW(STREAM, SEL_TRY_ERR);        \
        }                                               \
}

/**
 * If the expression evaluates to an error throw it. 
 */
#define SEL_TRY(EXPR) SEL_FTRY(stderr, EXPR)

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

/**
 * If the expression evaluates to less than 0, throw an IO error.
 */
#define SEL_FIO(STREAM, EXPR) {                         \
        const int SEL_IO_ERR = EXPR;                    \
        if(SEL_IO_ERR < 0) {                            \
                SEL_FTHROW(STREAM, SEL_IO_ERR)  \
        }                                               \
}

/**
 * If the expression evaluates to less than 0, return an IO error.
 */
#define SEL_IO_QUIETLY(EXPR) {                          \
        const int SEL_IO_ERR = EXPR;                    \
        if(SEL_IO_ERR < 0) {                            \
                return SEL_ERR_SYS;                     \
        }                                               \
}

/**
 * Print out info.
 */
void sel_info(
        FILE *stream,
        const char *file,
        const char *func,
        const int line);

/**
 * Report info about the current line of code.
 */
#define SEL_INFO() sel_info(stdout, __FILE__, __func__, __LINE__)

#endif