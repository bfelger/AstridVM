#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "globals.h"
#include "output.h"
#include "identifiers.h"

struct lookup_entry *lookup_entries;

void prep_lookup_entries()
{
	lookup_entries = (struct lookup_entry*)malloc(sizeof(struct lookup_entry));
	lookup_entries->name = NULL;
	lookup_entries->next = NULL;
	lookup_entries->cur_use_offset = 0;
}

struct lookup_entry* get_lookup_entry(char* identifier)
{
	struct lookup_entry *cursor = lookup_entries;

	while (cursor->name != NULL || cursor->next != NULL)
	{
		if (!strcmp(cursor->name, identifier))
			break;
		cursor = cursor->next;
	}

	if (cursor->name == NULL)
	{
		cursor->name = strdup(identifier);
		cursor->next = (struct lookup_entry*)malloc(sizeof(struct lookup_entry));
		cursor->next->name = NULL;
		cursor->next->next = NULL;
		cursor->next->cur_use_offset = 0;
	}

	return cursor;
}

void add_lookup_entry(char* identifier)
{
	struct lookup_entry* entry = get_lookup_entry(identifier);
	uint16_t offset = out_buf_index + 2;

	entry->use_offset[entry->cur_use_offset++] = offset;
}

void set_lookup_def_offset(char* identifier)
{
	struct lookup_entry* entry = get_lookup_entry(identifier);

	entry->def_offset = out_buf_index;
}

void resolve_lookups()
{
	struct lookup_entry* cursor = lookup_entries;

	while (cursor->name != NULL || cursor->next != NULL)
	{
		for (int i = 0; i < cursor->cur_use_offset; i++)
		{
			print_address(cursor->use_offset[i], cursor->def_offset);
#ifdef DEBUG
			printf("Resolve Lookup(%d, %d)\n", cursor->use_offset[i], cursor->def_offset);
#endif
		}

		cursor = cursor->next;
	}
}