#include <lplcore/header.h>
#include <lplcore/types.h>

#include <string.h>
#include <assert.h>
#include <stdio.h>


int main()
{
    const char *names[] = {"First", "Second", "Third"};
    const lpl_type_t types[] = {lpl_int8, lpl_int16, lpl_float32};
    const int size = 3;

    header_t *h = lpl_header_new(size, names, types);

    assert(h);

    int i = 0;

    while (h)
    {
        assert(strcmp(names[i], lpl_header_name(h)) == 0);
        assert(types[i] == lpl_header_type(h));

        printf("* Node: %d\n", i);
        printf("* Name: %s\n", lpl_header_name(h));
        printf("* Type: %d\n\n", lpl_header_type(h));

        h = lpl_header_next(h);
        ++i;
    }

    assert(i == size);

    return 0;
}
