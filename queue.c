#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q) {
        return NULL;
    }
    /* Initialize queue */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) {
        return;
    }
    /* TODO: How about freeing the list elements and the strings? */
    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = tmp->next;
        free(tmp->value);
        free(tmp);
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q) {
        return false;  // queue is null
    }
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;  // cannot allocate new list element
    }

    size_t s_len = strlen(s) + 1;  // +1 for '\0'
    newh->value = (char *) malloc(s_len * sizeof(char));
    if (!newh->value) {
        free(newh);
        return false;  // cannot allocate string
    }
    snprintf(newh->value, s_len, "%s",
             s);  // snprintf can auto deal with \0, strcpy strncpy have safety
                  // concern
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if (!q->tail) {
        q->tail = newh;
    }

    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;  // cannot allocate list element
    }
    size_t s_len = strlen(s) + 1;  // +1 for \0
    newt->value = (char *) malloc(s_len * sizeof(char));
    if (!newt->value) {
        free(newt);
        return false;  // cannot allocate string
    }
    snprintf(newt->value, s_len, "%s", s);
    newt->next = NULL;
    if (!q->tail) {
        q->tail = newt;
        q->head = newt;  // q->tail is null represent q->head is null as well
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head) {
        return false;
    }
    /* copy the removed string to *sp */
    if (sp) {
        size_t realbufsize =
            (strlen(q->head->value) < bufsize ? strlen(q->head->value)
                                              : bufsize - 1);
        memset(sp, '\0', realbufsize + 1);  // set memory for *sp include \0
        strncpy(sp, q->head->value,
                realbufsize);  // already made sure length and made \0 behind
    }

    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q) {
        return 0;
    }
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || !q->head || q->size == 1) {
        return;
    }
    list_ele_t *tmp = q->head->next;  // tmp is the current node
    q->tail->next = q->head;          // use tail to save previous node
    while (tmp != q->tail) {
        q->head->next = tmp->next;  // use head to save next node
        tmp->next = q->tail->next;
        q->tail->next = tmp;  // update prev node
        tmp = q->head->next;
    }
    q->head->next = NULL;
    q->tail = q->head;
    q->head = tmp;
    return;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
