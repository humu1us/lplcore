#include <lplcore/header.h>
#include <lplcore/types.h>

#include <assert.h>
#include <stdio.h>


void show_header(header_t *h)
{
    printf("* Name: %s\n", lpl_header_name(h));
    printf("* Type: %d\n\n", lpl_header_type(h));
}


int main()
{
    header_t *h = lpl_header_new_empty();
    assert(h);
    assert(lpl_header_size(h) == 0);

    lpl_header_append(h, "First", lpl_int8);
    assert(lpl_header_size(h) == 1);
    lpl_header_append(h, "Second", lpl_int16);
    assert(lpl_header_size(h) == 2);
    lpl_header_append(h, "Third", lpl_float32);
    assert(lpl_header_size(h) == 3);

    size_t size = lpl_header_size(h);

    for (size_t i = 0; i < size; ++i)
    {
        show_header(h);
        lpl_header_next(h);
    }

    lpl_header_destroy(h);
    return 0;
}
