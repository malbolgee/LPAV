#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/lista.h"
#include "../include/types.h"
#include "../include/utils.h"

bool list_add_start(void *_item, list_t **list)
{

    list_t *newnode;
    newnode = (list_t *)malloc(sizeof(list_t));
    _alloc_check(newnode, "Falha na alocação da lista");

    newnode->item = _item;
    newnode->next = *list;
    *list = newnode;

    return true;
}

bool list_add_end(void *_item, list_t **list)
{

    if (*list == NULL)
    {

        *list = (list_t *)malloc(sizeof(list_t));
        _alloc_check(*list, "Falha na alocação da lista");
        (*list)->item = _item;
        (*list)->next = NULL;

        return true;
    }
    else
    {

        list_t *_tmp = *list;
        while (_tmp->next != NULL)
            _tmp = _tmp->next;

        _tmp->next = (list_t *)malloc(sizeof(list_t));
        _alloc_check(_tmp->next, "Falha na alocação da lista");

        _tmp->next->item = _item;
        _tmp->next->next = NULL;

        return true;
    }
}

bool list_add_ord(void *_item, list_t **list, __compar_t compare)
{

    if (*list == NULL || compare((*list)->item, _item))
        return list_add_start(_item, list);
    else
    {

        list_t *_current = *list;
        // TODO: Olhar a condição da função de comparação
        while (_current->next != NULL && compare(_current->next->item, _item))
            _current = _current->next;

        list_t *new_node = (list_t *)malloc(sizeof(list_t));
        _alloc_check(new_node, "Falha na alocação da lista");

        new_node->item = _item;
        new_node->next = _current->next;
        _current->next = new_node;

        return true;
    }
}

ptr_list_ref_t *list_search(const void *_item, list_t *_list, ptr_list_ref_t *_ret, __compar_t compare)
{

    if (_list == NULL)
        return NULL;
    else if (compare(_list->item, _item) == 0)
    {

        _ret->prev = NULL;
        _ret->cur = _list;
        _ret->_next = _list->next;
        return _ret;
    }
    else
    {

        list_t *_tmp = _list->next;
        while (_tmp->next != NULL)
        {

            if (compare(_tmp->next->item, _item) != 0)
            {

                _ret->prev = _tmp;
                _ret->cur = _tmp->next;
                _ret->_next = _tmp->next->next;
                return _ret;
            }

            _tmp = _tmp->next;
        }

        return NULL;
    }
}

bool list_erase(const void *_item, list_t **_list, __compar_t compare)
{

    if (*_list == NULL)
        return false;
    else if (compare((*_list)->item, _item) == 0)
    {

        list_t *_tmp = *_list;
        *_list = (*_list)->next;
        free(_tmp->item);
        _tmp->item = NULL;
        free(_tmp);
        _tmp = NULL;
        return true;
    }
    else
    {

        list_t *_tmp = *_list;
        ptr_list_ref_t ret = {0};
        list_search(_item, _tmp, &ret, compare);

        if (ret.cur == NULL)
            return false;

        ret.prev->next = ret._next;
        free(ret.cur->item);
        ret.cur->item = NULL;
        free(ret.cur);
        ret.cur = NULL;
        return true;
    }
}

void list_free(list_t **list)
{

    list_t *_tmp = NULL;
    list_t *_current = *list;

    while (_current)
    {

        _tmp = _current;
        _current = _current->next;

        free(_tmp->item);
        _tmp->item = NULL;
        free(_tmp);
        _tmp = NULL;
    }
}
