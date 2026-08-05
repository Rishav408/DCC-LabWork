#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>
#include "student.h"

static int *
getmarks_1_svc(student *s, struct svc_req *req)
{
    static int result;
    result = s->id * 10;
    return &result;
}

bool_t
xdr_student(XDR *xdrs, student *objp)
{
    return xdr_int(xdrs, &objp->id);
}

void
student_prog_1(struct svc_req *rqstp, SVCXPRT *transp)
{
    union {
        student getmarks_1_arg;
    } argument;
    char *result;
    xdrproc_t _xdr_argument, _xdr_result;
    char *(*local)(char *, struct svc_req *);

    switch (rqstp->rq_proc) {
    case NULLPROC:
        svc_sendreply(transp, (xdrproc_t) xdr_void, NULL);
        return;

    case GETMARKS:
        _xdr_argument = (xdrproc_t) xdr_student;
        _xdr_result = (xdrproc_t) xdr_int;
        local = (char *(*)(char *, struct svc_req *)) getmarks_1_svc;
        break;

    default:
        svcerr_noproc(transp);
        return;
    }

    memset(&argument, 0, sizeof(argument));
    if (!svc_getargs(transp, _xdr_argument, (caddr_t) &argument)) {
        svcerr_decode(transp);
        return;
    }

    result = (*local)((char *) &argument, rqstp);
    if (result != NULL && !svc_sendreply(transp, _xdr_result, result)) {
        svcerr_systemerr(transp);
    }

    if (!svc_freeargs(transp, _xdr_argument, (caddr_t) &argument)) {
        fprintf(stderr, "unable to free arguments\n");
        exit(1);
    }
}

int
main(int argc, char *argv[])
{
    SVCXPRT *transp;

    pmap_unset(STUDENT_PROG, STUDENT_VERS);

    transp = svc_create(student_prog_1, STUDENT_PROG, STUDENT_VERS, "tcp");
    if (transp == NULL) {
        fprintf(stderr, "Cannot create TCP service.\n");
        exit(1);
    }

    printf("Student RPC server is running...\n");
    svc_run();
    fprintf(stderr, "svc_run returned\n");
    exit(1);
}
