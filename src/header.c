#include <lplcore/header.h>
#include <stdlib.h>
#include <string.h>

struct _header
{
    char *name;
    size_t index;
    lpl_type_t type;

    header_t *next;
};


// Private functions

header_t *node_new(const char *name, const lpl_type_t type, int index)
{
    header_t *h = (header_t *) malloc(sizeof(header_t));

    if (!h)
        return NULL;

    if (name)
        h->name = strdup(name);
    else
        h->name = NULL;

    h->type = type;
    h->index = index;
    h->next = NULL;

    return h;
}


void node_destroy(header_t *h)
{
    free(h->name);
    h->name = NULL;
    h->next = NULL;
    h->type = 0;
    free(h);
}


header_t *move_to_init(header_t *h)
{
    header_t *ptr = h;

    while (ptr->index != 0)
        ptr = ptr->next;
    return ptr;
}


// Public API

header_t *lpl_header_new(size_t size,
                         const char **names,
                         const lpl_type_t *types)
{
    header_t *init = node_new(NULL, lpl_no_type, 0);
    if (!init)
        return NULL;

    header_t *ptr = init;

    for (size_t i = 0; i < size; ++i)
    {
        ptr->next = node_new(names[i], types[i], i + 1);
        ptr = ptr->next;
    }

    ptr->next = init;

    return init->next;
}


void lpl_header_destroy(header_t *h)
{
    h = lpl_header_first(h);
    header_t *ptr = NULL;

    do
    {
        ptr = h->next;
        node_destroy(h);
        h = ptr;
    }
    while (h->index != 0);
    node_destroy(h);
}


char *lpl_header_name(header_t *h)
{
    return h->name;
}


lpl_type_t lpl_header_type(header_t *h)
{
    return h->type;
}


header_t *lpl_header_next(header_t *h)
{
    if (h->next->index == 0)
        return h->next->next;
    return h->next;
}


void lpl_header_append(header_t *h, const char *name, const lpl_type_t type)
{
}


void lpl_header_remove(header_t *h, const char *name)
{
}


header_t *lpl_header_search(header_t *h, const char *name)
{
    if (!h)
        return NULL;

    header_t *ptr = h;

    while (ptr->index != 0)
    {
        if (strcmp(ptr->name, name) == 0)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

    return ptr;
}
