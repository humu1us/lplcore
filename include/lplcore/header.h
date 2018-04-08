#ifndef LUPULUS_HEADER_H
#define LUPULUS_HEADER_H

#include <lplcore/types.h>
#include <stddef.h>


struct _header;
typedef struct _header header_t;

header_t *lpl_header_new(size_t size,
                         const char **names,
                         const lpl_type_t *types);

header_t *lpl_header_new_empty();
void lpl_header_destroy(header_t *h);
char *lpl_header_name(header_t *h);
lpl_type_t lpl_header_type(header_t *h);
header_t *lpl_header_next(header_t *h);

void lpl_header_append(header_t *h, const char *name, const lpl_type_t type);
void lpl_header_remove(header_t *h, const char *name);
header_t *lpl_header_search(header_t *h, const char *name);
header_t *lpl_header_first(header_t *h);
header_t *lpl_header_last(header_t *h);
size_t lpl_header_size(header_t *h);

#endif
