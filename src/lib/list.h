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

#ifndef LIBLIST_H
#define LIBLIST_H

#define LIBLIST_RETVAL_SUCCESS 0
#define LIBLIST_RETVAL_FAILED  1

/*
 * Method type definition with standard types in C
 */

typedef int (*LibListMethod_int_0)(void*);
typedef int (*LibListMethod_int_1_void)(void*, void*);
typedef int (*LibListMethod_int_1_int)(void*, int);
typedef int (*LibListMethod_int_2_void_int)(void*, void*, int);
typedef int (*LibListMethod_int_2_void_void)(void*, void*, void*);


/*
 * List Object
 */

typedef int (*LibListMethod_int_1_List)(void*, void*);

typedef struct
{
	void                           *data;
	void                           *next;
	void                           *prev;
	int                            tag;
	LibListMethod_int_1_List       join;
	LibListMethod_int_1_List       add;
	LibListMethod_int_1_int        set_tag;
	LibListMethod_int_1_int        add_tag;
	LibListMethod_int_2_void_int   add_with_tag;
	LibListMethod_int_0            terminate;
	LibListMethod_int_1_List       dump;
	LibListMethod_int_2_void_void  foreach;
	LibListMethod_int_0            length;
	LibListMethod_int_0            initialize;
	LibListMethod_int_0            destroy;
} List;

#define ListElements {							\
		NULL, NULL, NULL, 0,					\
		(void*)&List_join,					\
			(void*)&List_add,					\
			(void*)&List_set_tag,				\
			(void*)&List_add_tag,				\
			(void*)&List_add_with_tag,			\
			(void*)&List_terminate,				\
			(void*)&List_dump,					\
			(void*)&List_foreach,				\
			(void*)&List_length,				\
			(void*)&List_initialize,			\
			(void*)&List_destroy,				\
}


/*
 * ListHelper Object
 */

typedef List *(*LibListMethod_List_0)(void*);
typedef List *(*LibListMethod_List_2_List_int)(void*, List *list, int number);
typedef List *(*LibListMethod_List_1_List)(void*, List *list);

typedef struct
{
	LibListMethod_int_1_List       destroy_list;
	LibListMethod_List_0           new_list;
	LibListMethod_List_2_List_int  find_by_tag;
	LibListMethod_List_1_List      reverse;
	LibListMethod_List_1_List      last;
	LibListMethod_int_0            destroy;
} ListHelper;

#define ListHelperElements {					\
		(void*)&ListHelper_destroy_list,		\
		(void*)&ListHelper_new_list,			\
			(void*)&ListHelper_find_by_tag,		\
			(void*)&ListHelper_reverse,			\
			(void*)&ListHelper_last,			\
			(void*)&ListHelper_destroy,			\
}

ListHelper *newListHelper();

#endif


/*
 * Function Type Definition
 */

#ifndef LIBLIST_FUNC_TYPE
#define LIBLIST_FUNC_TYPE

typedef void (*LibListFunc_0)(void*, void*);
typedef void (*LibListFunc_1)(void*, void*, void*);

#endif
