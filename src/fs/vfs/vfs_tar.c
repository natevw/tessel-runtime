#include "vfs.h"
#include <stdio.h>

typedef struct {         // byte offset
  char name[100];        //   0
  char mode[8];          // 100
  char uid[8];           // 108
  char gid[8];           // 116
  char size[12];         // 124
  char mtime[12];        // 136
  char chksum[8];        // 148
  char typeflag;         // 156
  char linkname[100];    // 157
  char magic[6];         // 257
  char version[2];       // 263
  char uname[32];        // 265
  char gname[32];        // 297
  char devmajor[8];      // 329
  char devminor[8];      // 337
  char prefix[155];      // 345
                         // 500
} tar_header;

const unsigned tar_block = 512;

int tm_fs_mount_tar(tm_fs_ent* /*&mut*/ root, char* /* & */ path, uint8_t* /* &'fs */ tar, unsigned size) {
	tm_fs_ent* dir;
	int r = 0;
	
	r = tm_fs_lookup(root, path, &dir);
	if (r) return r;

	const uint8_t *ptr = tar;

	while (ptr < tar+size) {
		tar_header* header = (tar_header*) ptr;

		if (memcmp(header->magic, "\0\0\0\0\0\0", 6) == 0) {
			return 0;
		}

		if (memcmp(header->magic, "ustar", 5) != 0) {
			printf("Invalid header at %lx\n", ptr-tar);
			return -1;
		}

		unsigned size = strtoul(header->size, 0, 8);

		switch (header->typeflag) {
			case '5': {
				printf("dir:  %s \n", header->name);
				r = tm_fs_mkdir(dir, header->name);

				if (r != 0) {
					return r;
				}

				break;
			}
			case 0:
			case '0':
			case '7': {
				unsigned mtime = strtoul(header->mtime, 0, 8);
				printf("file: %s %u %u\n", header->name, size, mtime);
				const uint8_t* data = ptr + tar_block;

				tm_fs_ent* ent = tm_fs_raw_file_from_buf(data, size, mtime);
				r = tm_fs_insert(dir, header->name, ent);

				if (r != 0) {
					tm_fs_destroy(ent);
					return r;
				}

				break;
			}
			default: {
				printf("Ignoring unknown type %u\n", header->typeflag);
				break;
			}
		}

		ptr += tar_block + ((size+tar_block-1)/tar_block) * tar_block;
	}

	return r;
}