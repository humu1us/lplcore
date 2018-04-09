#include <lplcore/header.h>
#include <lplcore/types.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>


header_t *create_list()
{
    const char *names[] = {"First", "Second", "Third"};
    const lpl_type_t types[] = {lpl_int8, lpl_int16, lpl_float32};
    const int size = 3;

    header_t *h = lpl_header_new(size, names, types);

    return h;
}


void compare_list(header_t *h, const char *name, lpl_type_t type)
{
    if (!name)
        assert(!lpl_header_name(h));
    else
        assert(strcmp(lpl_header_name(h), name) == 0);
    assert(lpl_header_type(h) == type);
}


void show_header(header_t *h, char *where)
{
    printf("* Moving to %s:\n", where);
    printf("\t- Name: %s\n", lpl_header_name(h));
    printf("\t- Type: %d\n", lpl_header_type(h));
}


int main()
{
    header_t *h = create_list();
    assert(h);

    lpl_header_search(h, "Third");
    show_header(h, "Third");
    compare_list(h, "Third", lpl_float32);

    lpl_header_search(h, "Second");
    show_header(h, "Second");
    compare_list(h, "Second", lpl_int16);

    lpl_header_search(h, "First");
    show_header(h, "First");
    compare_list(h, "First", lpl_int8);

    lpl_header_search(h, "not found");
    show_header(h, "\"not found\"");
    compare_list(h, NULL, lpl_no_type);

    lpl_header_destroy(h);

    return 0;
}
