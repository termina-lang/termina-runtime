#ifndef __TERMINA__OS__CONFIG_H__
#define __TERMINA__OS__CONFIG_H__

#include <stdint.h>

#include <termina/platform/config.h>

#define NEXT_OBJECT_NAME(c1, c2, c3, c4)             \
    do {                                             \
        if (c4 == '9') {                             \
            if (c3 == '9') {                         \
                if (c2 == 'z') {                     \
                    if (c1 == 'z') {                 \
                        rtems_shutdown_executive(1); \
                    } else {                         \
                        c1++;                        \
                    }                                \
                    c2 = 'a';                        \
                } else {                             \
                    c2++;                            \
                }                                    \
                c3 = '0';                            \
            } else {                                 \
                c3++;                                \
            }                                        \
            c4 = '0';                                \
        }                                            \
        else {                                       \
            c4++;                                    \
        }                                            \
    } while (0)

extern int8_t ntask_name[5];
extern int8_t nsem_name[5];
extern int8_t nmsg_queue_name[5];
extern int8_t ntimer_name[5];

#endif // __TERMINA__OS__CONFIG_H__
