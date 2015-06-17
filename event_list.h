//
// Created by xuan on 15-6-13.
//

#ifndef RASPI_RPC_EVENT_LIST_H
#define RASPI_RPC_EVENT_LIST_H

#include <malloc.h>

#define EVENT_LIST_FUNCTION_MODIFIERS_DEFAULT
#ifndef EVENT_LIST_FUNCTION_MODIFIERS
#define EVENT_LIST_FUNCTION_MODIFIERS EVENT_LIST_FUNCTION_MODIFIERS_DEFAULT
#endif
#define EVENT_LIST_FUNCTION_ATTRIBUTES_DEFAULT
#ifndef EVENT_LIST_FUNCTION_ATTRIBUTES
#define EVENT_LIST_FUNCTION_ATTRIBUTES EVENT_LIST_FUNCTION_ATTRIBUTES_DEFAULT
#endif


#define EVENT_LIST_PROTO(el_name, callback_t)           \
struct event_list_##el_name##_s;                        \
typedef callback_t event_list_##el_name##_cb;           \
typedef struct event_list_node_##el_name##_s {          \
    struct event_list_##el_name##_s *el;                \
    struct event_list_node_##el_name##_s *prev, *next;  \
    void *data;                                         \
    event_list_##el_name##_cb callback;                 \
} event_list_node_##el_name##_t;                        \
typedef struct event_list_##el_name##_s {               \
    const char *name;\
    event_list_node_##el_name##_t *first;               \
    event_list_node_##el_name##_t *last;                \
} event_list_##el_name##_t;                             \
EVENT_LIST_FUNCTION_MODIFIERS                           \
event_list_node_##el_name##_t *                         \
EVENT_LIST_FUNCTION_ATTRIBUTES                          \
el_##el_name##_attach(                                  \
        event_list_##el_name##_t *list,                 \
        event_list_##el_name##_cb callback,             \
        void *data);                                    \
EVENT_LIST_FUNCTION_MODIFIERS                           \
void EVENT_LIST_FUNCTION_ATTRIBUTES                     \
el_##el_name##_detach(                                  \
        event_list_node_##el_name##_t *list);

#define EVENT_LIST_DEFINE(el_name)                      \
EVENT_LIST_FUNCTION_MODIFIERS                           \
event_list_node_##el_name##_t *                         \
EVENT_LIST_FUNCTION_ATTRIBUTES                          \
el_##el_name##_attach(                                  \
        event_list_##el_name##_t *list,                 \
        event_list_##el_name##_cb callback,             \
        void *data) {                                   \
    event_list_node_##el_name##_t *node =               \
        (event_list_node_##el_name##_t *) malloc(       \
            sizeof(event_list_node_##el_name##_t));     \
    if (!node)                                          \
        return NULL;                                    \
    node->el = list;                                    \
    node->data = data;                                  \
    node->callback = callback;                          \
    node->next = NULL;                                  \
                                                        \
    node->prev = list->last;                            \
    if (!list->first)                                   \
        list->first = node;                             \
    if (list->last)                                     \
        list->last->next = node;                        \
    list->last = node;                                  \
                                                        \
    return node;                                        \
}                                                       \
EVENT_LIST_FUNCTION_MODIFIERS                           \
void EVENT_LIST_FUNCTION_ATTRIBUTES                     \
el_##el_name##_detach(                                  \
        event_list_node_##el_name##_t *node) {          \
    if (!node)                                          \
        return;                                         \
    if (!node->prev)                                    \
        node->el->first = node->next;                   \
    else                                                \
        node->prev->next = node->next;                  \
    if (!node->next)                                    \
        node->el->last = node->prev;                    \
    else                                                \
        node->next->prev = node->prev;                  \
                                                        \
    free(node);                                         \
}                                                       \
EVENT_LIST_FUNCTION_MODIFIERS                           \
void el_##el_name##_clear                               \
EVENT_LIST_FUNCTION_ATTRIBUTES(                         \
        event_list_##el_name##_t *list) {               \
    while (list->first) {                               \
        el_##el_name##_detach(list->first);             \
    }                                                   \
}
#define EVENT_LIST_FIRE(el, ...) {                      \
    typeof((el)->first) node = (el)->first, next;       \
    if (node) {                                         \
        do {                                            \
            next = node->next;                          \
            if (node->callback)                         \
                node->callback(node->data, __VA_ARGS__);\
            node = next;                                \
        } while(next);                                  \
    }                                                   \
}

#define EVENT_LIST_CALL(el) {                           \
    typeof((el)->first) node = (el)->first, next;       \
    if (node) {                                         \
        do {                                            \
            next = node->next;                          \
            if (node->callback)                         \
                node->callback(node->data);             \
            node = next;                                \
        } while(next);                                  \
    }                                                   \
}
#define EVENT_LIST_INIT(name) {(name), NULL, NULL}


#endif //RASPI_RPC_EVENT_LIST_H
