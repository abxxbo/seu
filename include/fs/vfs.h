#pragma once

#include <libc/stdint.h>


#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08

typedef struct fs_node {
	char name[128];
	uint32_t mask;
	uint32_t uid;
	uint32_t gid;
	uint32_t flags;
	uint32_t inode;
	uint32_t length;
	uint32_t impl;
	read_type_t read;
	write_type_t write;
	open_type_t open;
	close_type_t close;
	readdir_type_t readdir;
	finddir_type_t finddir;
	struct fs_node* ptr;
} fs_node_t;


struct dirent {
	char name[128];
	uint32_t ino;
};

typedef uint32_t (*read_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);
typedef uint32_t (*write_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);
typedef void (*open_type_t)(struct fs_node*);
typedef void (*close_type_t)(struct fs_node*);
typedef struct dirent* (*readdir_type_t)(struct fs_node*,uint32_t);
typedef struct fs_node* (*finddir_type_t)(struct fs_node*,char *name);

fs_node_t* fs_root = 0;

uint32_t read_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer){
    if (node->read != 0) return node->read(node, offset, size, buffer);
    else return 0;
}

uint32_t write_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer){
    if (node->write != 0) return node->write(node, offset, size, buffer);
    else return 0;
}

void open_fs(fs_node_t *node, uint8_t read, uint8_t write){
    if (node->open != 0) return node->open(node);
}

void close_fs(fs_node_t *node){
    if (node->close != 0) return node->close(node);
}

struct dirent *readdir_fs(fs_node_t *node, uint32_t index){
    if ((node->flags&0x7) == FS_DIRECTORY && node->readdir != 0) return node->readdir(node, index);
    else return 0;
}

fs_node_t *finddir_fs(fs_node_t *node, char *name){
    if ((node->flags&0x7) == FS_DIRECTORY && node->finddir != 0)  return node->finddir(node, name);
    else return 0;
}
	
