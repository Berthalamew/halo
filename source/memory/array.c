/*
ARRAY.C
*/

/* ---------- headers */

#include "cseries.h"
#include "profile.h"
#include "array.h"

/* ---------- globals */

extern struct profile_section data_00308bc0[3];

/* ---------- public code */

void dynamic_array_new(
	struct dynamic_array *array,
	long element_size)
{
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 16, array);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 17, element_size>0);

	array->element_size = element_size;
	array->count = 0;
	array->elements = 0;

	return;
}

boolean dynamic_array_resize(
	struct dynamic_array *array,
	long count)
{
	boolean result = FALSE;

	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 33, array);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 34, array->element_size>0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 35, array->count>=0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 36, (array->count!=0)==(array->elements!=NULL));

	profile_enter(data_00308bc0[0]);

	if (count>=0)
	{
		if (array->count != count)
		{
			void *new_elements = match_realloc("c:\\halo\\SOURCE\\memory\\array.c", 44, array->elements, array->element_size*count);

			if ((count!=0)==(new_elements!=NULL))
			{
				long old_count = array->count;

				if (count>old_count)
				{
					memset((byte*)new_elements + array->element_size*old_count, 0, (count-old_count)*array->element_size);
				}

				array->count = count;
				array->elements = new_elements;

				result = TRUE;
			}
		}
		else
		{
			result = TRUE;
		}
	}

	profile_exit(data_00308bc0[0]);

	return result;
}

void dynamic_array_delete(
	struct dynamic_array *array)
{
	void *elements;

	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 73, array);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 74, array->count>=0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 75, (array->count!=0)==(array->elements!=NULL));

	elements = array->elements;

	array->element_size = -1;
	array->count = -1;

	if (elements!=NULL)
	{
		array->elements = match_realloc("c:\\halo\\SOURCE\\memory\\array.c", 80, elements, 0);
	}

	return;
}

long dynamic_array_add_element(
	struct dynamic_array *array)
{
	long new_index = -1;
	long old_count = -1;

	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 93, array);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 94, array->element_size>0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 95, array->count>=0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 96, (array->count!=0)==(array->elements!=NULL));

	profile_enter(data_00308bc0[1]);

	old_count = array->count;
	
	if (old_count>=0)
	{
		void *new_elements = match_realloc("c:\\halo\\SOURCE\\memory\\array.c", 103, array->elements, array->element_size*(old_count+1));

		if (new_elements!=NULL)
		{
			new_index = old_count;

			memset((byte*)new_elements + array->element_size*array->count, 0, array->element_size);

			array->count = old_count+1;
			array->elements = new_elements;
		}
	}

	profile_exit(data_00308bc0[1]);

	return new_index;
}

void *dynamic_array_get_element(
	struct dynamic_array const *array,
	long index,
	long element_size)
{
	void* element;

	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 125, array);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 126, array->element_size>0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 127, array->element_size==element_size);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 128, array->count>=0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 129, (array->count!=0)==(array->elements!=NULL));
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 130, index>=0 && index<array->count);

	element = (byte*)array->elements + array->element_size*index;
	return element;
}

void dynamic_array_delete_element(
	struct dynamic_array *array,
	long index)
{
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 139, array);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 140, array->element_size>0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 141, array->count>=0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 142, (array->count!=0)==(array->elements!=NULL));
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 143, index>=0 && index<array->count);

	profile_enter(data_00308bc0[2]);

	array->count -= 1;

	if (index<array->count)
	{
		memmove(
			(byte*)array->elements + array->element_size*index,
			(byte*)array->elements + array->element_size*(index+1),
			array->element_size * (array->count-index));
	}

	array->elements = match_realloc("c:\\halo\\SOURCE\\memory\\array.c", 156, array->elements, array->element_size * array->count);

	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 158, (array->count!=0)==(array->elements!=NULL));

	profile_exit(data_00308bc0[2]);

	return;
}

void static_array_new(
	byte *count,
	void *elements,
	short element_size,
	short maximum_count)
{
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 171, count);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 172, elements);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 173, element_size>0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 174, maximum_count<=UNSIGNED_CHAR_MAX);

	*count = 0;
	memset(elements, -1, element_size*maximum_count);

	return;
}

byte static_array_resize(
	byte *count,
	void *elements,
	short element_size,
	short maximum_count,
	short new_count)
{
	boolean result = FALSE;

	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 191, count && *count>=0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 192, elements);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 193, element_size>0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 194, maximum_count<=UNSIGNED_CHAR_MAX);

	if (new_count>=0 && new_count<maximum_count)
	{
		if (*count!=new_count)
		{
			void *new_end = (byte*)elements + new_count*element_size;
			void *old_end = (byte*)elements + *count*element_size;

			if (old_end > new_end)
			{
				csmemset(new_end, 0, (unsigned long)old_end - (unsigned long)new_end);
			}
			else
			{
				csmemset(old_end, -1, (unsigned long)new_end - (unsigned long)old_end);
			}

			*count = new_count;
		}

		result = TRUE;
	}

	return result;
}

short static_array_add_element(
	byte *count,
	void *elements,
	short element_size,
	short maximum_count)
{
	short old_count;
	short new_index;

	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 230, count && *count>=0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 231, elements);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 232, element_size>0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 233, maximum_count<=UNSIGNED_CHAR_MAX);

	old_count = *count;

	if (old_count < maximum_count)
	{
		new_index = old_count;
		*count = *count + 1;
		memset((byte*)elements + old_count*element_size, 0, element_size);
	}
	else
	{
		new_index = -1;
	}

	return new_index;
}

void *static_array_get_element(
	byte count,
	void const *elements,
	short element_size,
	short index)
{
	void* element;

	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 251, count>0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 252, elements);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 253, element_size>0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 254, index>=0 && index<count);

	element = (byte*)elements + element_size*index;
	return element;
}

void static_array_delete_element(
	byte *count,
	void *elements,
	short element_size,
	short index)
{
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 230, count && *count>=0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 231, elements);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 232, element_size>0);
	match_assert("c:\\halo\\SOURCE\\memory\\array.c", 254, index>=0 && index<*count);

	*count -= 1;

	if (index<*count)
	{
		memmove(
			(byte*)elements + element_size*index,
			(byte*)elements + element_size*(index+1),
			element_size * (*count-index));
	}

	memset((byte*)elements + element_size * *count, -1, element_size);

	return;
}
