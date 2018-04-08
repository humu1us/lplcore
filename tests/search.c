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

    header_t *third = lpl_header_search(h, "Third");
    show_header(third, "Third");
    compare_list(third, "Third", lpl_float32);

    header_t *second = lpl_header_search(h, "Second");
    show_header(second, "Second");
    compare_list(second, "Second", lpl_int16);

    header_t *first = lpl_header_search(h, "First");
    show_header(first, "First");
    compare_list(first, "First", lpl_int8);

    header_t *null = lpl_header_search(h, "not found");
    assert(null == NULL);

    lpl_header_destroy(h);

    return 0;
}
