#ifndef MUSICLIBRARYDATA_H
#define MUSICLIBRARYDATA_H

typedef struct song Song;
typedef struct artist Artist;
typedef struct snode SNode;

struct song {
	int index;
	char* title;
	Artist* artist;
	char* path;
};

struct snode {
	Song* song;
	struct snode* prev, * next;
};

struct artist {
	char* name;
	Artist* next;
	SNode* head, * tail;
};

#endif // !MUSICLIBRARYDATA_H