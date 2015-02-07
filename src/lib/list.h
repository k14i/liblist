/*
 *
 *  liblist
 *
 *    - Author: Keisuke TAKAHASHI <keithseahus &#64 gmail.com>
 *    - Site: https://github.com/keithseahus/.sandbox
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
 * Member method type definition with standard types in C
 */

typedef int (*Member_int_0)(void*);
typedef int (*Member_int_1_void)(void*, void*);
typedef int (*Member_int_1_int)(void*, int);
typedef int (*Member_int_2_void_int)(void*, void*, int);
typedef int (*Member_int_2_void_void)(void*, void*, void*);


/*
 * List Object
 */

typedef int (*Member_int_1_List)(void*, void*);

typedef struct
{
	void                    *data;
	void                    *next;
	void                    *prev;
	int                     tag;
	Member_int_1_List       append;
	Member_int_1_List       add;
	Member_int_1_int        set_tag;
	Member_int_1_int        add_tag;
	Member_int_2_void_int   add_with_tag;
	Member_int_0            terminate;
	Member_int_1_List       dump;
	Member_int_2_void_void  foreach;
	Member_int_0            length;
	Member_int_0            initialize;
	Member_int_0            destroy;
} List;

#define ListElements {							\
		NULL, NULL, NULL, 0,					\
		(void*)&List_append,					\
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

typedef List *(*Member_List_0)(void*);
typedef List *(*Member_List_2_List_int)(void*, List *list, int number);
typedef List *(*Member_List_1_List)(void*, List *list);

typedef struct
{
	Member_int_1_List       destroy_list;
	Member_List_0           new_list;
	Member_List_2_List_int  find_by_tag;
	Member_List_1_List      reverse;
	Member_List_1_List      last;
	Member_int_0            destroy;
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

typedef void (*Func_0)(void*, void*);
typedef void (*Func_1)(void*, void*, void*);

#endif
