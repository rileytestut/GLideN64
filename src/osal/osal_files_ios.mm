#include "osal_files.h"
#import <Foundation/Foundation.h>
#include <string>
#include <dirent.h>

/* global functions */

#ifdef __cplusplus
extern "C"{
#endif

EXPORT int CALL osal_path_existsA(const char *path)
{
	NSString* nsPath = [NSString stringWithUTF8String:path];
	return [[NSFileManager defaultManager] fileExistsAtPath:nsPath];
}

EXPORT int CALL osal_path_existsW(const wchar_t *_path)
{
	NSString* nsPath = [[NSString alloc] initWithBytes:_path length:wcslen(_path)*sizeof(*_path) encoding:NSUTF32LittleEndianStringEncoding];
	return [[NSFileManager defaultManager] fileExistsAtPath:nsPath];
}

EXPORT int CALL osal_is_absolute_path(const wchar_t* name)
{
	return name[0] == L'/';
}

EXPORT int CALL osal_is_directory(const wchar_t * _name)
{
	NSString* nsPath = [[NSString alloc] initWithBytes:_name length:wcslen(_name)*sizeof(*_name) encoding:NSUTF32LittleEndianStringEncoding];
	BOOL isDirectory;
	if ([[NSFileManager defaultManager] fileExistsAtPath:nsPath isDirectory:&isDirectory] && isDirectory)
	{
		return 1;
	}
	return 0;
}

EXPORT int CALL osal_mkdirp(const wchar_t *_dirpath)
{
	NSString* nsPath = [[NSString alloc] initWithBytes:_dirpath length:wcslen(_dirpath)*sizeof(*_dirpath) encoding:NSUTF32LittleEndianStringEncoding];
	if (![[NSFileManager defaultManager] createDirectoryAtPath:nsPath withIntermediateDirectories:YES attributes:nil error:nil])
	{
		return 1;
	}
	return 0;
}

struct IOSDirSearch
{
	const void *dirNSString;
	const void *enumerator;
	std::wstring currentFilePath;
};

EXPORT void * CALL osal_search_dir_open(const wchar_t *_pathname)
{
    char pathname[PATH_MAX];
    wcstombs(pathname, _pathname, PATH_MAX);
    DIR *dir;
    dir = opendir(pathname);
    return dir;
}

EXPORT const wchar_t * CALL osal_search_dir_read_next(void * dir_handle)
{
    static wchar_t last_filename[PATH_MAX];
    DIR *dir = (DIR *) dir_handle;
    struct dirent *entry;

    entry = readdir(dir);
    if (entry == NULL)
        return NULL;
    mbstowcs(last_filename, entry->d_name, PATH_MAX);
    return last_filename;
}

EXPORT void CALL osal_search_dir_close(void * dir_handle)
{
    closedir((DIR *) dir_handle);
}

#ifdef __cplusplus
}
#endif
