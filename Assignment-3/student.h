#ifndef _STUDENT_H_RPCGEN
#define _STUDENT_H_RPCGEN

#include <rpc/rpc.h>

#ifdef __cplusplus
extern "C" {
#endif

struct student {
    int id;
};
typedef struct student student;

#define STUDENT_PROG 0x31234567
#define STUDENT_VERS 1
#define GETMARKS 1

#if defined(__STDC__) || defined(__cplusplus)
extern int *getmarks_1(student *, CLIENT *);
extern int *getmarks_1_svc(student *, struct svc_req *);
extern void student_prog_1(struct svc_req *, SVCXPRT *);
extern bool_t xdr_student(XDR *, student *);
#else
extern int *getmarks_1();
extern int *getmarks_1_svc();
extern void student_prog_1();
extern bool_t xdr_student();
#endif

#ifdef __cplusplus
}
#endif

#endif /* !_STUDENT_H_RPCGEN */
