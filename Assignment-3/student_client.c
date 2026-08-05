#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "student.h"

int main(int argc, char *argv[])
{
    CLIENT *cl;
    student s;
    int marks;
    struct timeval timeout = { 25, 0 };
    enum clnt_stat status;

    if (argc < 3) {
        printf("Usage: %s <server_ip> <student_id>\n", argv[0]);
        return 1;
    }

    cl = clnt_create(argv[1], STUDENT_PROG, STUDENT_VERS, "tcp");
    if (cl == NULL) {
        clnt_pcreateerror("RPC failed");
        return 1;
    }

    s.id = atoi(argv[2]);
    status = clnt_call(cl,
                       GETMARKS,
                       (xdrproc_t) xdr_student,
                       &s,
                       (xdrproc_t) xdr_int,
                       &marks,
                       timeout);

    if (status != RPC_SUCCESS) {
        clnt_perror(cl, "RPC call failed");
        clnt_destroy(cl);
        return 1;
    }

    printf("Student Marks for ID %d = %d\n", s.id, marks);
    clnt_destroy(cl);
    return 0;
}
