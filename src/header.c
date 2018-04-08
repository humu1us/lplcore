#include <lplcore/header.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


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


bool is_node_empty(header_t *h)
{
    return (!h || (!h->name && !h->type));
}


void node_destroy(header_t *h)
{
    free(h->name);
    h->name = NULL;
    h->next = NULL;
    h->type = 0;
    free(h);
}


// Public API

header_t *lpl_header_new(size_t size,
                         const char **names,
                         const lpl_type_t *types)
{
    header_t *h = node_new(names[0], types[0], 0);
    if (!h)
        return NULL;

    header_t *ptr = h;

    for (size_t i = 1; i < size; ++i)
    {
        ptr->next = node_new(names[i], types[i], i);
        ptr = ptr->next;
    }

    ptr->next = h;

    return h;
}


header_t *lpl_header_new_empty()
{
    header_t *h = node_new(NULL, lpl_no_type, 0);
    h->next = h;
    return h;
}


void lpl_header_destroy(header_t *h)
{
    h = lpl_header_first(h);
    header_t *ptr = NULL;

    size_t size = lpl_header_size(h);
    for (size_t i = 0; i < size; ++i)
    {
        ptr = h->next;
        node_destroy(h);
        h = ptr;
    }
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
    return h->next;
}


void lpl_header_append(header_t *h, const char *name, const lpl_type_t type)
{
    if (is_node_empty(h))
    {
        h->name = strdup(name);
        h->type = type;
        return;
    }

    header_t* last = lpl_header_last(h);
    header_t *new = node_new(name, type, last->index + 1);

    if (!new)
        return;

    new->next = last->next;
    last->next = new;
}


void lpl_header_remove(header_t *h, const char *name)
{
}


header_t *lpl_header_search(header_t *h, const char *name)
{
    if (!h)
        return NULL;

    header_t *ptr = h;
    size_t current = h->index;

    do
    {
        if (strcmp(ptr->name, name) == 0)
            return ptr;
        ptr = ptr->next;
    }
    while (ptr->index != current);

    return NULL;
}


header_t *lpl_header_first(header_t *h)
{
    header_t *ptr = h;

    while (ptr->index != 0)
        ptr = ptr->next;
    return ptr;
}


header_t *lpl_header_last(header_t *h)
{
    header_t *ptr = h;
    while (ptr->next->index != 0)
        ptr = ptr->next;
    return ptr;
}


size_t lpl_header_size(header_t *h)
{
    return lpl_header_last(h)->index + 1;
}
