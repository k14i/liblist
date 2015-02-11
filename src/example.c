#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib/list.h"

#define TIMES 1

int test_set_prev() {
	int ret = 0;

	ListHelper *list_helper = newListHelper();
	List *list0 = list_helper->new_list(list_helper);
	List *list1 = list_helper->new_list(list_helper);
	list1->set_prev(list1, list0);

	if (list0->next != list1 || list1->prev != list0) goto err;

	goto clean_up_and_return;

err:
	ret = 1;
	goto clean_up_and_return;

clean_up_and_return:
	list_helper->destroy_list(list_helper, list0);
	(void)list_helper->destroy(list_helper);
	return ret;
}

int test_set_next() {
	int ret = 0;

	ListHelper *list_helper = newListHelper();
	List *list0 = list_helper->new_list(list_helper);
	List *list1 = list_helper->new_list(list_helper);
	list0->set_next(list0, list1);

	if (list0->next != list1 || list1->prev != list0) goto err;

	goto clean_up_and_return;

err:
	ret = 1;
	goto clean_up_and_return;

clean_up_and_return:
	list_helper->destroy_list(list_helper, list0);
	(void)list_helper->destroy(list_helper);
	return ret;
}

int test_new_linked_list() {
	int ret = 0;

	ListHelper *list_helper = newListHelper();
	List *ptr = NULL;
	List *list = list_helper->new_linked_list(list_helper, 5);
	ptr = list;
	if (!list) goto err;
	printf("list = %p, ptr = %p, ptr->prev = %p, ptr->next = %p\n", list, ptr, ptr->prev, ptr->next);
	ptr = ptr->next;
	printf("list = %p, ptr = %p, ptr->prev = %p, ptr->next = %p\n", list, ptr, ptr->prev, ptr->next);
	ptr = ptr->next;
	printf("list = %p, ptr = %p, ptr->prev = %p, ptr->next = %p\n", list, ptr, ptr->prev, ptr->next);
	ptr = ptr->next;
	printf("list = %p, ptr = %p, ptr->prev = %p, ptr->next = %p\n", list, ptr, ptr->prev, ptr->next);
	ptr = ptr->next;
	printf("list = %p, ptr = %p, ptr->prev = %p, ptr->next = %p\n", list, ptr, ptr->prev, ptr->next);
	if (ptr->next) goto err;

	goto clean_up_and_return;

err:
	ret = 1;
	goto clean_up_and_return;

clean_up_and_return:
	list_helper->destroy_list(list_helper, list);
	(void)list_helper->destroy(list_helper);
	return ret;
}

int test_join() {
	int ret = 0;

	ListHelper *list_helper = newListHelper();
	List *list0 = list_helper->new_list(list_helper);
	List *list1 = list_helper->new_list(list_helper);
	list0->join(list0, list1);

	List *last = list_helper->last(list_helper, list0);

	if (!list0) {
		printf("ERROR: !list0\n");
		goto err;
	}
	if (!list1) {
		printf("ERROR: !list1\n");
		goto err;
	}
	if (!last) {
		printf("ERROR: !last\n");
		goto err;
	}
	if (list0 == list1) {
		printf("ERROR: list0 == list1\n");
		goto err;
	}
	if (last == list0) {
		printf("ERROR: last == list0\n");
		goto err;
	}
	if (last != list1) {
		printf("ERROR: last != list1\n");
		printf("  last  = %p\n", last);
		printf("  list1 = %p\n", list1);
		goto err;
	}
	if (last->prev != list0) {
		printf("ERROR: last->prev != list0\n");
		goto err;
	}

	goto clean_up_and_return;

err:
	ret = 1;
	goto clean_up_and_return;

clean_up_and_return:
	list_helper->destroy_list(list_helper, list0);
	//list_helper->destroy_list(list_helper, list1);
	(void)list_helper->destroy(list_helper);
	return ret;
}

int test_head() {
	int ret = 0;

	ListHelper *list_helper = newListHelper();
	List *list0 = list_helper->new_list(list_helper);
	List *list1 = list_helper->new_list(list_helper);
	List *list2 = list_helper->new_list(list_helper);
	list0->next = list1;
	list1->prev = list0;
	list1->next = list2;
	list2->prev = list1;

	List *head = list_helper->head(list_helper, list2);
	if (head != list0) goto err;

	goto clean_up_and_return;

err:
	ret = 1;
	goto clean_up_and_return;

clean_up_and_return:
	list_helper->destroy_list(list_helper, list0);
	(void)list_helper->destroy(list_helper);
	return ret;
}

int test_last() {
	int ret = 0;

	ListHelper *list_helper = newListHelper();
	List *list = list_helper->new_list(list_helper);
	List *last = list_helper->last(list_helper, list);
	if (list != last) {
		printf("list != last\n");
		goto err;
	}

	goto clean_up_and_return;

err:
	ret = 1;
	goto clean_up_and_return;

clean_up_and_return:
	list_helper->destroy_list(list_helper, list);
	(void)list_helper->destroy(list_helper);
	return ret;
}

int test_foreach() {
	int ret = 0;
	ListHelper *list_helper = newListHelper();
	List *list0 = list_helper->new_list(list_helper);
	List *list1 = list_helper->new_list(list_helper);
	List *list2 = list_helper->new_list(list_helper);
	list0->join(list0, list1);
	list0->join(list0, list2);

	list0->foreach(list0, &(list0->dump), NULL);

	list_helper->destroy_list(list_helper, list0);
	(void)list_helper->destroy(list_helper);
	return ret;
}

int test_destroy_list() {
	for (int i=0; i<TIMES; i++) {
		ListHelper *list_helper = newListHelper();
		List *list = list_helper->new_list(list_helper);
		list_helper->destroy_list(list_helper, list);
		// NOTE: 'warning: expression result unused [-Wunused-value]' without cast.
		(void)list_helper->destroy(list_helper);
	}
	return 0;
}

int test_set_tag() {
	int ret = 0;
	ListHelper *list_helper = newListHelper();
	List *list = list_helper->new_list(list_helper);

	if (list->tag != 0) {
		printf("list->tag != 0\n");
		goto err;
	}

	list->set_tag(list, 255);

	if (list->tag != 255) {
		printf("list->tag != 255\n");
		goto err;
	}

	goto clean_up_and_return;

err:
	ret = 1;
	goto clean_up_and_return;

clean_up_and_return:
	list_helper->destroy_list(list_helper, list);
	(void)list_helper->destroy(list_helper);
	return ret;
}

int test_length() {
	int ret = 0;
	int len = 0;

	ListHelper *list_helper = newListHelper();
	List *list0 = list_helper->new_list(list_helper);
	List *list1 = list_helper->new_list(list_helper);
	List *list2 = list_helper->new_list(list_helper);
	List *list3 = list_helper->new_list(list_helper);
	list0->join(list0, list1);
	list0->join(list0, list2);
	list0->join(list0, list3);
	len = list0->length(list0);
	if (len != 4) goto err;

	goto clean_up_and_return;

err:
	ret = 1;
	goto clean_up_and_return;

clean_up_and_return:
	list_helper->destroy_list(list_helper, list0);
	(void)list_helper->destroy(list_helper);
	return ret;
}

int test_reverse() {
	int ret = 0;
	List *list;

	ListHelper *list_helper = newListHelper();
	List *list0 = list_helper->new_list(list_helper);
	List *list1 = list_helper->new_list(list_helper);
	List *list2 = list_helper->new_list(list_helper);
	list0->join(list0, list1);
	list0->join(list0, list2);
printf("list0 = %p, list0->prev = %p, list0->next = %p\n", list0, list0->prev, list0->next);
printf("list1 = %p, list1->prev = %p, list1->next = %p\n", list1, list1->prev, list1->next);
printf("list2 = %p, list2->prev = %p, list2->next = %p\n", list2, list2->prev, list2->next);
	list = list_helper->reverse(list_helper, list0);
printf("list = %p, list->prev = %p, list->next = %p\n", list, list->prev, list->next);
	if (ret != 0) goto err;

	goto clean_up_and_return;

err:
	ret = 1;
	goto clean_up_and_return;

clean_up_and_return:
	list_helper->destroy_list(list_helper, list0);
	//list_helper->destroy_list(list_helper, list);
printf("list_helper->destroy_list(list_helper, list), list = %p\n", list);
	(void)list_helper->destroy(list_helper);
	return ret;
}

int main(int argc, char *argv[]) {
	int ret = 0;
	int exit_status = 0;

	printf("---- BEGIN main() ----\n");
	ret = test_set_prev();
	if (ret != 0) {
		printf("ERROR in test_prev()\n");
		goto err;
	}
	ret = test_set_next();
	if (ret != 0) {
		printf("ERROR in test_next()\n");
		goto err;
	}
	ret = test_new_linked_list();
	if (ret != 0) {
		printf("ERROR in test_new_linked_list()\n");
		goto err;
	}
	ret = test_destroy_list();
	if (ret != 0) {
		printf("ERROR in test_destroy_list()\n");
		goto err;
	}
	ret = test_head();
	if (ret != 0) {
		printf("ERROR in test_head()\n");
		goto err;
	}
	ret = test_last();
	if (ret != 0) {
		printf("ERROR in test_last()\n");
		goto err;
	}
	ret = test_foreach();
	if (ret != 0) {
		printf("ERROR in test_foreach()\n");
		goto err;
	}
	ret = test_join();
	if (ret != 0) {
		printf("ERROR in test_join()\n");
		goto err;
	}
	ret = test_set_tag();
	if (ret != 0) {
		printf("ERROR in test_set_tag()\n");
		goto err;
	}
	ret = test_length();
	if (ret != 0) {
		printf("ERROR in test_length()\n");
		goto err;
	}
	ret = test_reverse();
	if (ret != 0) {
		printf("ERROR in test_reverse()\n");
		goto err;
	}
	printf("---- END main() ----\n");
	goto clean_up_and_exit;

err:
	exit_status = 1;
	goto clean_up_and_exit;

clean_up_and_exit:
	printf("Exit with exit_status(%d)\n", exit_status);
	return exit_status;
}

