#ifndef __IDENTIFIERS_H
#define __IDENTIFIERS_H

#define ID_LIST_SIZE 1024

struct lookup_entry
{
	char *name;
	uint16_t def_offset;
	uint16_t use_offset[ID_LIST_SIZE];
	uint16_t cur_use_offset;

	struct lookup_entry *next;
};

extern struct lookup_entry* lookup_entries;

void prep_lookup_entries();
struct lookup_entry* get_lookup_entry(char*);
void add_lookup_entry(char* identifier);
void set_lookup_def_offset(char* identifier);
void resolve_lookups();

#endif // __IDENTIFIERS_H