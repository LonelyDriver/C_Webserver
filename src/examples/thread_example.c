#include "thread_al.h"
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

typedef struct person {
    char name[12];
    unsigned int age;
    const char* addr;
} Person;

void wait( int seconds )
{   // Pretty crossplatform, both ALL POSIX compliant systems AND Windows
    #ifdef _WIN32
        Sleep( 1000 * seconds );
    #else
        sleep( seconds );
    #endif
}

thread_function hello(thread_args args) {
    printf("Hello from thread\n");
    wait(2);
}

thread_function struct_test(thread_args args) {
    Person* p;
    p = args;
    wait(1);
    printf("Got Person\nName:%s\nAge=%d\nAddress=%s\n", p->name, p->age, p->addr);

}

int main() {
    thread_t id[3];
    Person pp = {
        "Fritz",
        25,
        "Alte Straße, 22"
    };


    thread_info_t* info = make_thread_info(hello, NULL);
    thread_info_t* info2 = make_thread_info(struct_test, (Person*)&pp);

    printf("Thread1 started: %d\n", create_thread(&id[0], info));
    printf("Thread2 started: %d\n", create_thread(&id[1], info2));

    wait(1);
    printf("Joining thread!\n");
    printf("Joined: %d\n", join_thread(id[0]));
    printf("Joined: %d\n", join_thread(id[1]));
    delete_thread_info(info);
    delete_thread_info(info2);

}