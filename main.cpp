#include "log.h"

int main()
{
    print_log(ERROR_LOG, "123");
    print_log("456");
    print_log("789\n");
    print_log(INFO_LOG, "789");
    return 0;
}
