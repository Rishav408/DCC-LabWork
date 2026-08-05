struct student {
    int id;
};
program STUDENT_PROG {
    version STUDENT_VERS {
        int GETMARKS(student) = 1;
    } = 1;
} = 0x31234567;
