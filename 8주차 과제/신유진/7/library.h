#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <string.h>
typedef struct song Song;
typedef struct snode SNode;
typedef struct artist Artist;
struct song {
	Artist* artist;
	char* title;
	char* path;
	int index;
};

struct snode {
	SNode* next, * prev;
	Song* song;
};

struct artist {
	char* name;
	Artist* next;					//�ܹ��� ���Ḯ��Ʈ�� �����ϱ� ���� �ʵ�
	SNode* head, * tail;

};
void initiailze();
void add_song(char* artist, char* title, char* path);
void status();
void load(FILE* fp);
void search_song(char* artist, char* title);
void search_song(char* artist);
void play(int index);
void save(FILE* fp);
void remove(int index);
#endif