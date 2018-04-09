#include <lplcore/header.h>
#include <lplcore/types.h>

#include <assert.h>
#include <stdio.h>


int main()
{
    header_t *h = lpl_header_new_empty();
    lpl_header_append(h, "First", lpl_int8);
    lpl_header_append(h, "Second", lpl_int16);
    lpl_header_append(h, "Third", lpl_float32);
    lpl_header_append(h, "Fourth", lpl_int32);

    size_t size = lpl_header_size(h);
    char *names[] = {"First", "Third", "Fourth", "Second"};
    int i = 0;

    while (!lpl_header_is_empty(h))
    {
        assert(lpl_header_size(h) == size - i);
        printf("* List size: %zd\n", lpl_header_size(h));
        lpl_header_remove_by_name(h, names[i]);
        ++i;
    }
    lpl_header_destroy(h);

    return 0;
}
