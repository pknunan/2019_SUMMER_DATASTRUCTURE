#include "music_library_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_tools.h"
#include <Windows.h>

#define BUFFER_LENGTH 200
#define NUM_CHARS 256
#define SIZE_INDEX_TABLE 100

void handle_search();
void search_song(char* artist);
void search_song(char* artist, char* title);
SNode* find_snode(Artist* ptr_artist, char* title);
SNode* find_song(int index);
Artist* find_artist(char* name);

void handle_add();
void add_song(char* artist, char* title, char* path);
Artist* add_artist(char* name);

void handle_remove();
void remove(int index);
void remove_snode(Artist* ptr_artist, SNode* ptr_snode);
void destroy_song(Song* ptr_song);

void handle_play();
void play(int index);

void handle_load();
void load(FILE* fp);

void initialize();
void process_command();
void status();

void handle_save();
void save(FILE* fp);
void save_artist(Artist* p, FILE* fp);
void save_song(Song* ptr_song, FILE* fp);

Artist* create_artist_instance(char* name);
Song* create_song_instance(Artist* ptr_artist, char* title, char* path);

void insert_node(Artist* ptr_artist, SNode* ptr_snode);
void insert_to_index_directory(Song* ptr_song);

void print_artist(Artist* p);
void print_song(Song* ptr_song);