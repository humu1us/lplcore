#include <lplcore/header.h>
#include <stdlib.h>
#include <string.h>

struct _header
{
    char *name;
    lpl_type_t type;

    header_t *next;
};


header_t *node_new(const char *name, const lpl_type_t type)
{
    header_t *h = (header_t *) malloc(sizeof(header_t));

    if (!h)
        return NULL;

    size_t name_size = strlen(name);
    h->name = (char *) malloc(name_size + 1);

    if (!h->name)
    {
        free(h);
        return NULL;
    }

    strncpy(h->name, name, name_size);
    h->type = type;
    h->next = NULL;

    return h;
}


void node_destroy(header_t *h)
{
    free(h->name);
    free(h);
}


header_t *lpl_header_new(size_t size,
                         const char **names,
                         const lpl_type_t *types)
{
    header_t *h = node_new(names[0], types[0]);
    header_t *ptr = h;

    for (size_t i = 1; i < size; ++i)
    {
        ptr->next = node_new(names[i], types[i]);
        ptr = ptr->next;
    }

    return h;
}


void lpl_header_destroy(header_t *h)
{
    header_t *ptr = NULL;
    while (h)
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
}


void lpl_header_remove(header_t *h, const char *name)
{
}
