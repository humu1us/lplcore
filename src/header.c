#include <lplcore/header.h>
#include <stdlib.h>
#include <string.h>


struct node
{
    char *name;
    lpl_type_t type;
    struct node *next;
};
typedef struct node node_t;


struct _header
{
    node_t *list;
    node_t *cur;
    node_t *beg;
    node_t *end;
    size_t size;
};


// Private functions

node_t *node_new(const char *name, const lpl_type_t type)
{
    node_t *n = (node_t *) malloc(sizeof(node_t));

    if (!n)
        return NULL;

    if (name)
        n->name = strdup(name);
    else
        n->name = NULL;

    n->type = type;
    n->next = NULL;

    return n;
}


void node_destroy(node_t *n)
{
    free(n->name);
    n->name = NULL;
    n->next = NULL;
    n->type = 0;
    free(n);
}


// Public API

header_t *lpl_header_new_empty()
{
    header_t *h = (header_t *) malloc(sizeof(header_t));
    if (!h)
        return NULL;

    h->list = NULL;
    h->beg = NULL;
    h->end = NULL;
    h->size = 0;
    return h;
}


header_t *lpl_header_new(size_t size,
                         const char **names,
                         const lpl_type_t *types)
{

    header_t *h = lpl_header_new_empty();
    if (!h)
        return NULL;

    h->list = node_new(names[0], types[0]);
    if (!h->list)
    {
        return NULL;
    }

    node_t *ptr = h->list;

    size_t i = 1;
    for (; i < size; ++i)
    {
        ptr->next = node_new(names[i], types[i]);
        ptr = ptr->next;
    }

    h->size = i;

    ptr->next = h->list;
    h->cur = h->list;
    h->beg = h->list;
    h->end = ptr;

    return h;
}


void lpl_header_destroy(header_t *h)
{

    node_t *del = h->beg;
    node_t *ptr = NULL;

    for (size_t i = 0; i < h->size; ++i)
    {
        ptr = del->next;
        node_destroy(del);
        del = ptr;
    }
    free(h);
}


char *lpl_header_name(header_t *h)
{
    return h->cur ? h->cur->name : NULL;
}


lpl_type_t lpl_header_type(header_t *h)
{
    return h->cur ? h->cur->type : lpl_no_type;
}


void lpl_header_next(header_t *h)
{
    h->cur = h->cur->next;
}


bool lpl_header_is_empty(header_t *h)
{
    return !h ? true : h->list == NULL;
}


void lpl_header_append(header_t *h, const char *name, const lpl_type_t type)
{
    if (!h->list)
    {
        h->list = node_new(name, type);
        h->beg = h->list;
        h->end = h->list;
        h->cur = h->list;
        ++h->size;
        return;
    }

    node_t *n = node_new(name, type);

    h->end->next = n;
    n->next = h->beg;
    h->end = n;
    ++h->size;
}


void lpl_header_remove_by_name(header_t *h, const char *name)
{
    node_t *prev = h->beg;

    bool found = false;
    for (size_t i = 0; i < h->size; ++i)
    {
        if (strcmp(prev->next->name, name) != 0)
        {
            found = true;
            break;
        }
        prev = prev->next;
    }

    if (!found)
        return;

    node_t *del = prev->next;
    prev->next = prev->next->next;
    node_destroy(del);
    --h->size;

    if (h->size == 0)
        h->list = NULL;
}


void lpl_header_remove_current(header_t *h)
{
    node_t *prev = h->beg;
    while (prev->next != h->cur)
        prev = prev->next;

    prev->next = prev->next->next;
    node_destroy(h->cur);
    h->cur = prev;
    --h->size;
}


void lpl_header_search(header_t *h, const char *name)
{
    node_t *ptr = h->beg;

    for (size_t i = 0; i < h->size; ++i)
    {
        if (strcmp(ptr->name, name) == 0)
        {
            h->cur = ptr;
            return;
        }
        ptr = ptr->next;
    }
    h->cur = NULL;
}


void lpl_header_first(header_t *h)
{
    h->cur = h->beg;
}


void lpl_header_last(header_t *h)
{
    h->cur = h->end;
}


size_t lpl_header_size(header_t *h)
{
    return h->size;
}
