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

    int index = 0;
    int count = 0;
    for (; count < 6; ++count)
    {
        printf("* Node: %d\n", count);
        printf("* Name: %s\n", lpl_header_name(h));
        printf("* Type: %d\n", lpl_header_type(h));
        printf("* indx: %d\n\n", index);
        assert(strcmp(names[index], lpl_header_name(h)) == 0);
        assert(types[index] == lpl_header_type(h));

        h = lpl_header_next(h);

        if (count > 0 && ((count + 1) % 3) == 0)
            index = 0;
        else
            ++index;
    }

    assert(count / 2 == size);

    lpl_header_destroy(h);

    return 0;
}
