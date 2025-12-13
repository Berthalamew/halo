/*
FILES.H

header included in hcex build.
*/

#ifndef __FILES_H
#define __FILES_H
#pragma once

/* ---------- constants */

enum
{
	FILE_REFERENCE_SIZE= 268,
	MAXIMUM_FILENAME_LENGTH= 255
};

enum
{
	_file_reference_application_relative= 0,
#ifndef xbox
	_file_reference_cd_relative,
#endif
	_file_reference_absolute,

	NUMBER_OF_FILE_REFERENCE_LOCATIONS
};

enum
{
	FILE_REFERENCE_SIGNATURE= 'filo'
};
//
//enum
//{
//	_has_filename_bit= 0,
//
//	NUMBER_OF_REFERENCE_INFO_FLAGS
//};
//
//struct datastore
//{
//    datastore_entry entry[200]; // 0x0
//};
//static_assert(sizeof(datastore) == 102000, "Invalid datastore size");
//
//struct datastore_entry
//{
//    char name[255]; // 0x0
//    char data[255]; // 0xFF
//};
//static_assert(sizeof(datastore_entry) == 510, "Invalid datastore_entry size");
//
//struct file_reference_info
//{
//    unsigned long signature; // 0x0
//    unsigned short flags; // 0x4
//    short location; // 0x6
//    char path[256]; // 0x8
//};
//static_assert(sizeof(file_reference_info) == 264, "Invalid file_reference_info size");
//
//enum
//{
//    _find_files_recursive_bit = 0,
//    _find_files_enumerate_directories_bit,
//    NUMBER_OF_FIND_FILES_FLAGS,
//};
//
//enum
//{
//    FIRST_DRIVE_LETTER = 65, // 0x0041 'A'
//    LAST_DRIVE_LETTER = 90, // 0x005A 'Z'
//    DRIVE_NAME_LENGTH = 4, // 0x0004
//    DIRECTORY_SEPARATOR = 92, // 0x005C '\'
//    EXTENSION_SEPARATOR = 46, // 0x002E '.'
//    BAD_FILE = -1, // 0xFF
//    MAXIMUM_SEARCH_DEPTH = 8, // 0x0008
//};
//
//enum
//{
//    has_filename_bit = 0,
//    NUMBER_OF_REFERENCE_INFO_FLAGS,
//};
//
//struct find_files_state
//{
//    unsigned long flags; // 0x0
//    short depth; // 0x4
//    short location; // 0x6
//    char path[256]; // 0x8
//    void *handles[8]; // 0x108
//    _WIN32_FIND_DATAA data; // 0x128
//};
//static_assert(sizeof(find_files_state) == 616, "Invalid find_files_state size");
//
struct file_reference_info
{
	unsigned long signature;
	word flags;
	short location;
	char path[256];
	void *file_handle;
};
//static_assert(sizeof(file_reference_info) == 268, "Invalid file_reference_info size");

/* ---------- macros */

/* ---------- structures */

struct file_reference
{
	char data[FILE_REFERENCE_SIZE];
};

/* ---------- prototypes/FILES.C */

void file_location_set_volume(short location, const char *volume_name);
struct file_reference *file_reference_create(struct file_reference *reference, short location);
long find_files(unsigned long flags, struct file_reference const *directory, long maximum_count, struct file_reference *references);
void *file_read_into_memory(struct file_reference *reference, unsigned long *size);
void file_printf(struct file_reference *file, char *format, ...);
struct file_reference_info *file_reference_get_info(struct file_reference *reference);
struct file_reference *file_reference_copy(struct file_reference *destination, const struct file_reference *source);
struct file_reference *file_reference_add_directory(struct file_reference *reference, const char *directory);
struct file_reference *file_reference_set_name(struct file_reference *reference, const char *name);
boolean file_references_equal(const struct file_reference *reference0, const struct file_reference *reference1);
struct file_reference *file_reference_create_from_path(struct file_reference *reference, const char *path, boolean directory);
void directory_create_or_delete_contents(const char *directory_name);
boolean datastore_read(const char *file_name, const char *field_name, long length, void *data);
boolean datastore_write(const char *file_name, const char *field_name, long length, const void *data);

/* ---------- prototypes/FILES_WINDOWS.C */

/* ---------- globals */

/* comm */
char file_location_volume_names[NUMBER_OF_FILE_REFERENCE_LOCATIONS-1][256];

/* ---------- public code */

#endif // __FILES_H
