#include <lplcore/header.h>
#include <lplcore/types.h>

#include <assert.h>
#include <stdio.h>


void show_header(header_t *h)
{
    printf("\t* Name: %s\n", lpl_header_name(h));
    printf("\t* Type: %d\n\n", lpl_header_type(h));
}


int main()
{
    const char *names[] = {"First"};
    const lpl_type_t types[] = {lpl_int8};

    header_t *h = lpl_header_new(1, names, types);
    assert(h);

    lpl_header_append(h, "Second", lpl_int16);

    for (int i = 0; i < 2; ++i)
    {
        show_header(h);
        h = lpl_header_next(h);
    }

    lpl_header_destroy(h);
    return 0;
}
