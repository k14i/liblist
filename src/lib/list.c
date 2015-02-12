/*
 *
 *  liblist
 *
 *    - Author: Keisuke TAKAHASHI <keithseahus &#64 gmail.com>
 *    - Site: https://github.com/keithseahus/liblist
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"


/*
 * List Object
 */

static int List_set_prev(List *self, List *target);
static int List_set_next(List *self, List *target);
static int List_join(List *self, List *target);
static int List_add(List *self, List *target);
static int List_set_tag(List *self, int tag);
static int List_add_tag(List *self, int tag);
static int List_add_with_tag(List *self, void *target, int tag);
static int List_terminate(List *self);
static int List_dump(List *self, List *list);
static int List_foreach(List *self, void *function, void *arg);
static int List_length(List *self);
static int List_initialize(List *self);
static int List_destroy(List *self);


static int List_set_prev(List *self, List *target) {
	if (!self || !target || self->prev || target->prev) goto err;
	List *ptr = self;

	ptr->prev = target;
	ptr = ptr->prev;
	ptr->next = self;

	return LIBLIST_RETVAL_SUCCESS;

err:
	return LIBLIST_RETVAL_FAILED;
}

static int List_set_next(List *self, List *target) {
	if (!self || !target || self->next) goto err;
	//if (!self || !target) goto err;
	List *ptr = self;

	/*
	if (ptr->next) {
		List *ptr_next = ptr->next;
		printf("0001: ptr_next = %p\n", ptr_next);
		ptr_next->foreach(ptr_next, &(ptr_next->destroy), NULL);
		printf("0002\n");
		ptr->next = NULL;
	}
	*/

	ptr->next = target;
	ptr = ptr->next;
	ptr->prev = self;

	return LIBLIST_RETVAL_SUCCESS;

err:
	return LIBLIST_RETVAL_FAILED;
}

static int List_join(List *self, List *target) {
	if (!self || self->prev || !target) goto err;

	List *ptr      = self;
	List *ptr_prev = NULL;

	if (ptr->prev) goto err;

	while (ptr->next) {
		ptr_prev = ptr;
		ptr = ptr->next;
		ptr->prev = ptr_prev;
	}

	ptr->next = target;

	//ptr = ptr->next;
	//ptr->prev = self;
	target->prev = ptr;
	return LIBLIST_RETVAL_SUCCESS;

err:
#ifdef DEBUG
printf("List_join: self->prev should be NULL.\n");
#endif
	return LIBLIST_RETVAL_FAILED;
}

static int List_add(List *self, List *target) {
	if (!self || self->prev || !target) goto err;

	int ret = 0;

	List list = ListElements;
	list.initialize(&list);
	memcpy(list.data, &target, sizeof(target));
	ret = self->join(self, &list);
	if (ret != LIBLIST_RETVAL_SUCCESS) goto err;

	return LIBLIST_RETVAL_SUCCESS;

err:
#ifdef DEBUG
printf("List_add: self->prev should be NULL.\n");
#endif
	return LIBLIST_RETVAL_FAILED;
}

static int List_set_tag(List *self, int tag) {
	self->tag = tag;
	return LIBLIST_RETVAL_SUCCESS;
}

static int List_add_tag(List *self, int tag) {
	if (!self || self->prev) goto err;

	List *ptr = self;

	while(ptr->next) ptr = ptr->next;

	self->set_tag(self, tag);
	return LIBLIST_RETVAL_SUCCESS;

err:
#ifdef DEBUG
printf("List_add_tag: self->prev should be NULL.\n");
#endif
	return LIBLIST_RETVAL_FAILED;
}

static int List_add_with_tag(List *self, void *target, int tag) {
	if (!self || self->prev || !target) goto err;

	int ret = 0;

	ret = self->add(self, target);
	if (ret != LIBLIST_RETVAL_SUCCESS) goto err;

	ret = self->add_tag(self, tag);
	if (ret != LIBLIST_RETVAL_SUCCESS) goto err;

	return LIBLIST_RETVAL_SUCCESS;

err:
#ifdef DEBUG
printf("List_add_with_tag: self->prev should be NULL.\n");
#endif
	return LIBLIST_RETVAL_FAILED;
}

static int List_terminate(List *self) {
	if (!self || self->prev) goto err;

	int ret = 0;

	void *buf = malloc(sizeof(List));
	List list = ListElements;
	memcpy(buf, &list, sizeof(list));
	ret = self->join(self, &list);
	list.destroy(&list);
	if (ret != LIBLIST_RETVAL_SUCCESS) goto err;

	return LIBLIST_RETVAL_SUCCESS;

err:
#ifdef DEBUG
printf("List_terminate: self->prev should be NULL.\n");
#endif
	return LIBLIST_RETVAL_FAILED;
}

static int List_dump(List *self, List *list) {
	if (!self || !list) goto err;

	printf("List_dump: list(%p)->data(%p) is %s\n", list, list->data, (char *)list->data);
	printf("List_dump: list(%p)->prev is %p\n", list, list->prev);
	printf("List_dump: list(%p)->next is %p\n", list, list->next);
	return LIBLIST_RETVAL_SUCCESS;

err:
#ifdef DEBUG
printf("List_dump: list should not be NULL.\n");
#endif
	return LIBLIST_RETVAL_FAILED;
}

static int List_foreach(List *self, void *function, void *arg) {
	if (!self || self->prev || !function) goto err;

	List *ptr = self;

	while (ptr->next) {
		if(!arg) {
			LibListFunc_0 *fun = function;
			(*fun)(self, ptr);
		} else {
			LibListFunc_1 *fun = function;
			(*fun)(self, ptr, arg);
		}
		ptr = ptr->next;
	}

	return LIBLIST_RETVAL_SUCCESS;

err:
#ifdef DEBUG
printf("List_foreach: self->prev should be NULL.\n");
#endif
	return LIBLIST_RETVAL_FAILED;
}

static int List_length(List *self) {
	if (!self || self->prev) goto err;

	List *ptr = self;
	int len = 1;

	for (len; ptr->next; len++) {
		ptr = ptr->next;
	}

	return len;

err:
#ifdef DEBUG
printf("List_length: self->prev should be NULL.\n");
#endif
	return -1;
}

static int List_initialize(List *self) {
	if (!self) goto err;

	self->data = malloc(sizeof(void*));
	memset(self->data, 0, sizeof(void*));
	return LIBLIST_RETVAL_SUCCESS;

err:
#ifdef DEBUG
printf("List_initialize: list should not be NULL.\n");
#endif
	return LIBLIST_RETVAL_FAILED;
}

static int List_destroy(List *self) {
	if (!self) goto err;

	List *ptr = self;
	List *ptr_next = NULL;

	while (ptr->next) ptr = ptr->next;

	if (!ptr->prev) goto destroy_self;

	while (ptr != self && ptr->prev) {
		//if (!ptr->prev) break;
#ifdef DEBUG
printf("List_destroy: 1: ptr = %p, ptr->prev = %p, ptr->next = %p\n", ptr, ptr->prev, ptr->next);
#endif
		ptr = ptr->prev;
#ifdef DEBUG
printf("List_destroy: 2: ptr = %p, ptr->prev = %p, ptr->next = %p\n", ptr, ptr->prev, ptr->next);
#endif
		ptr_next = ptr->next;
#ifdef DEBUG
printf("List_destroy: 3: ptr = %p, ptr->prev = %p, ptr->next = %p\n", ptr, ptr->prev, ptr->next);
#endif
		memset(ptr_next, 0, sizeof(ptr_next));
		free(ptr_next);
#ifdef DEBUG
printf("List_destroy: 4: ptr = %p, ptr->prev = %p, ptr->next = %p\n", ptr, ptr->prev, ptr->next);
printf("List_destroy: 5: ptr = %p, ptr->prev = %p, ptr->next = %p\n", ptr, ptr->prev, ptr->next);
#endif
		//if (!ptr->prev) break;
		//ptr = ptr->prev;
#ifdef DEBUG
printf("List_destroy: 6: ptr = %p, ptr->prev = %p, ptr->next = %p\n", ptr, ptr->prev, ptr->next);
#endif
	}
#ifdef DEBUG
printf("List_destroy: 7: ptr = %p, ptr->prev = %p, ptr->next = %p\n", ptr, ptr->prev, ptr->next);
#endif

	goto destroy_self;

	/*
	free(self);
	memset(self, 0, sizeof(self));
	//if(self->data) free(self->data);
	//if(self->next) free(self->next);
	//memset(self, 0, sizeof(List));
	return LIBLIST_RETVAL_SUCCESS;
	*/

destroy_self:
	free(self);
	memset(self, 0, sizeof(self));
	return LIBLIST_RETVAL_SUCCESS;

err:
#ifdef DEBUG
printf("List_destroy: list should not be NULL.\n");
#endif
	return LIBLIST_RETVAL_FAILED;
}


/*
 * ListHelper Object
 */

//static int ListHelper_destroy_list(ListHelper *self, List *list);
static List *ListHelper_new_linked_list(ListHelper *self, int size);
static List *ListHelper_new_list(ListHelper *self);
static List *ListHelper_head(ListHelper *self, List *list);
static List *ListHelper_last(ListHelper *self, List *list);
static List *ListHelper_find_by_tag(ListHelper *self, List *list, int tag);
static List *ListHelper_reverse(ListHelper *self, List *list);
static int ListHelper_destroy(ListHelper *self);

/*
// TODO: Delete all the list recursively.
static int ListHelper_destroy_list(ListHelper *self, List *list) {
	if (!self || !list) goto err;

	List *ptr = self->last(self, list);
	while (ptr->prev) {
		ptr = ptr->prev;
		ptr->destroy(ptr->next);
	}
	ptr->destroy(ptr);
	return LIBLIST_RETVAL_SUCCESS;

err:
	printf("ListHelper_destroy_list: list should not be NULL.\n");
	return LIBLIST_RETVAL_FAILED;
}
*/

static List *ListHelper_new_linked_list(ListHelper *self, int size) {
	if (!self || size < 1) goto err;

	List *list = NULL;
	List *head = NULL;
	List *buf  = NULL;

	for (int i = 0; i < size; i++) {
		buf = self->new_list(self);
		if (!head) head = buf;
		if (!list) {
			list = buf;
		} else {
			list->join(list, buf);
		}
	}

	return head;

err:
#ifdef DEBUG
printf("ListHelper_new_linked_list: self should not be NULL and size should not lower than 1.\n");
#endif
	return NULL;
}

static List *ListHelper_new_list(ListHelper *self) {
	if (!self) goto err;

	void *buf = malloc(sizeof(List));
	List list = ListElements;
	memcpy(buf, &list, sizeof(list));
	return buf;

err:
#ifdef DEBUG
printf("ListHelper_new_list: self should not be NULL.\n");
#endif
	return NULL;
}

static List *ListHelper_head(ListHelper *self, List *list) {
	if (!self || !list) goto err;

	List *ptr = list;
	while (ptr->prev) ptr = ptr->prev;

	return ptr;

err:
#ifdef DEBUG
printf("ListHelper_head: self or list should not be NULL.\n");
#endif
	return NULL;
}

static List *ListHelper_last(ListHelper *self, List *list) {
	if (!self || !list) goto err;

	List *ptr = list;
	while (ptr->next) {
		ptr = ptr->next;
	}

	return ptr;

err:
#ifdef DEBUG
printf("ListHelper_last: self should not be NULL.\n");
#endif
	return NULL;
}

static List *ListHelper_find_by_tag(ListHelper *self, List *list, int tag) {
	if (!self || !list) goto err;

	List *ptr = list;

	while (ptr->next) {
		if(ptr->tag == tag) break;
		ptr = ptr->next;
		//continue;
	}
	return ptr;

err:
#ifdef DEBUG
printf("ListHelper_find_by_tag: self should not be NULL.\n");
#endif
	return NULL;
}

static List *ListHelper_reverse(ListHelper *self, List *list) {
	if (!self || !list || list->prev) goto err;

	List *list_next = NULL;
	List *list_prev = NULL;

	do {
		list_prev  = list->prev;
		list_next  = list->next;
		list->next = list_prev;
		list->prev = list_next;
		if (list->prev) list = list->prev;
//printf("ListHelper_reverse: list = %p, list->prev = %p, list->next = %p\n", list, list->prev, list->next);
	} while (list->prev);

	return list;

err:
#ifdef DEBUG
printf("ListHelper_reverse: error\n");
#endif
	return NULL;
}

static int ListHelper_destroy(ListHelper *self) {
	if (!self) goto err;

	memset(self, 0, sizeof(ListHelper));
	free(self);
	return LIBLIST_RETVAL_SUCCESS;

err:
#ifdef DEBUG
printf("ListHelper_destroy: self should not be NULL.\n");
#endif
	return LIBLIST_RETVAL_FAILED;
}

ListHelper *newListHelper() {
	void *buf = malloc(sizeof(ListHelper));
	if (!buf) goto err;

	ListHelper list_helper = ListHelperElements;
	memcpy(buf, &list_helper, sizeof(list_helper));
	return buf;

err:
	return NULL;
}

