#define _CRT_SECURE_NO_WARNINGS
#include "music_library.h"

Artist* artist_directory[NUM_CHARS];
SNode* index_directory[SIZE_INDEX_TABLE];
int num_index = 0;

void status()
{
	for (int i = 0; i < NUM_CHARS; i++)
	{
		Artist* p = artist_directory[i];
		while (p != NULL)
		{
			print_artist(p);
			p = p->next;
		}
	}
}

void load(FILE* fp)
{
	char buffer[BUFFER_LENGTH];
	char* name, * title, * path;

	while (1) {
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)
			break;

		name = strtok(buffer, "#");
		if (strcmp(name, " ") == 0)
			name = NULL;
		else
			name = _strdup(name);

		title = strtok(NULL, "#");
		if (strcmp(title, " ") == 0)
			title = NULL;
		else
			title = _strdup(title);

		path = strtok(NULL, "#");
		if (strcmp(path, " ") == 0)
			path = NULL;
		else
			path = _strdup(path);

		//printf("%s %s %s\n", name, title, path);
		add_song(name, title, path);
	}
}

void process_command()
{
	char command_line[BUFFER_LENGTH];
	char* command;

	while (1)
	{
		printf("$ ");

		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue;

		command = strtok(command_line, " ");
		if (strcmp(command, "add") == 0)
			handle_add();
		else if (strcmp(command, "search") == 0)
			handle_search();
		else if (strcmp(command, "remove") == 0)
			handle_remove();
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "play") == 0)
			handle_play();
		else if (strcmp(command, "save") == 0) {
			char* tmp = strtok(NULL, " ");
			if (strcmp(tmp, "as") != 0)
				continue;
			handle_save();
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}
}

void handle_add()
{
	char buffer[BUFFER_LENGTH];
	char* artist = NULL, * title = NULL, * path = NULL;

	printf("    Artist: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
		artist = _strdup(buffer);

	printf("    Title: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
		title = _strdup(buffer);

	printf("    Path: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
		path = _strdup(buffer);

	printf("%s %s %s\n", artist, title, path);

	add_song(artist, title, path);
}

void handle_search()
{
	char name[BUFFER_LENGTH], title[BUFFER_LENGTH];

	printf("    Artist: ");
	if (read_line(stdin, name, BUFFER_LENGTH) <= 0) {
		printf("    Artist name required.\n");
		return;
	}
	printf("    Title: ");
	int title_len = read_line(stdin, title, BUFFER_LENGTH);

	if (title_len <= 0)
		search_song(name);
	else
		search_song(name, title);
}

void handle_remove()
{
	char* id_str = strtok(NULL, " ");
	int index = atoi(id_str);
	remove(index);
}

void handle_play()
{
	char* id_str = strtok(NULL, " ");
	int index = atoi(id_str);
	play(index);
}

void play(int index)
{
	SNode* ptr_snode = find_song(index);
	if (ptr_snode == NULL) {
		printf("No such song exists.\n");
		return;
	}
	printf("Found the song: %s\n", ptr_snode->song->title);
	ShellExecute(GetDesktopWindow(), "open", ptr_snode->song->path, NULL, NULL, SW_SHOW);
}

void handle_save()
{
	char* file_name = strtok(NULL, " ");
	FILE* fp = fopen(file_name, "w");
	save(fp);
	fclose(fp);
}

Artist* find_artist(char* name)
{
	Artist* p = artist_directory[(unsigned char)name[0]];
	while (p != NULL && strcmp(p->name, name) < 0)
		p = p->next;

	if (p != NULL && strcmp(p->name, name) == 0)
		return p;
	else
		return NULL;
}

Artist* add_artist(char* name)
{
	Artist* ptr_artist = create_artist_instance(name);

	Artist* p = artist_directory[(unsigned char)name[0]];
	Artist* q = NULL;

	while (p != NULL && strcmp(p->name, name) < 0) {
		q = p;
		p = p->next;
	}

	if (p == NULL && q == NULL) {
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else if (q == NULL)
	{
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else {
		ptr_artist->next = p;
		q->next = ptr_artist;
	}

	return ptr_artist;
}

Artist* create_artist_instance(char* name)
{
	Artist* ptr_artist = (Artist*)calloc(1, sizeof(Artist));
	ptr_artist->name = name;
	return ptr_artist;
}

Song* create_song_instance(Artist* ptr_artist, char* title, char* path)
{
	Song* ptr_song = (Song*)calloc(1, sizeof(Song));
	ptr_song->artist = ptr_artist;
	ptr_song->title = title;
	ptr_song->path = path;
	ptr_song->index = num_index;
	num_index++;

	return ptr_song;
}

void insert_node(Artist* ptr_artist, SNode* ptr_snode)
{
	SNode* p = ptr_artist->head;
	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0)
		p = p->next;

	if (ptr_artist->head == NULL) {
		ptr_artist->head = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else if (p == ptr_artist->head) {
		ptr_snode->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_snode;
		ptr_artist->head = ptr_snode;
	}
	else if (p == NULL) {
		ptr_snode->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else {
		ptr_snode->next = p;
		ptr_snode->prev = p->prev;
		p->prev->next = ptr_snode;
		p->prev = ptr_snode;
	}
}

void print_artist(Artist* p)
{
	printf("%s\n", p->name);
	SNode* ptr_snode = p->head;
	while (ptr_snode != NULL)
	{
		print_song(ptr_snode->song);
		ptr_snode = ptr_snode->next;
	}
}

void print_song(Song* ptr_song)
{
	printf("    %d: %s, %s\n", ptr_song->index, ptr_song->title, ptr_song->path);
}

void handle_load()
{
	char buffer[BUFFER_LENGTH];

	printf("Data file name ? ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) <= 0)
		return;

	FILE* fp = fopen(buffer, "r");
	if (fp == NULL) {
		printf("No such file exists.\n");
		return;
	}

	load(fp);
	fclose(fp);
}

SNode* find_snode(Artist* ptr_artist, char* title)
{
	SNode* ptr_snode = ptr_artist->head;
	while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0)
		ptr_snode = ptr_snode;
	if (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) == 0)
		return ptr_snode;
	else
		return NULL;
}

void insert_to_index_directory(Song* ptr_song)
{
	SNode* ptr_snode = (SNode*)calloc(1, sizeof(SNode));
	ptr_snode->song = ptr_song;

	int index = ptr_song->index % SIZE_INDEX_TABLE;

	SNode* p = index_directory[index];
	SNode* q = NULL;
	while (p != NULL && strcmp(p->song->title, ptr_song->title) < 0)
	{
		q = p;
		p = p->next;
	}
	if (q == NULL) {
		ptr_snode->next = p;
		index_directory[index] = ptr_snode;
	}
	else
	{
		ptr_snode->next = p;
		q->next = ptr_snode;
	}
}

SNode* find_song(int index)
{
	SNode* ptr_snode = index_directory[index % SIZE_INDEX_TABLE];
	while (ptr_snode != NULL && ptr_snode->song->index != index)
		ptr_snode = ptr_snode->next;

	return ptr_snode;
}

void save(FILE* fp)
{
	for (int i = 0; i < NUM_CHARS; i++)
	{
		Artist* p = artist_directory[i];
		while (p != NULL)
		{
			save_artist(p, fp);
			p = p->next;
		}
	}
}

void save_artist(Artist* p, FILE* fp)
{
	SNode* ptr_snode = p->head;
	while (ptr_snode != NULL)
	{
		save_song(ptr_snode->song, fp);
		ptr_snode = ptr_snode->next;
	}
}

void save_song(Song* ptr_song, FILE* fp)
{
	if (ptr_song->artist != NULL)
		fprintf(fp, "%s#", ptr_song->artist->name);
	else
		fprintf(fp, " #");
	if (ptr_song->title != NULL)
		fprintf(fp, "%s#", ptr_song->title);
	else
		fprintf(fp, " #");
	if (ptr_song->path != NULL)
		fprintf(fp, "%s#\n", ptr_song->path);
	else
		fprintf(fp, " #n");
}

void remove_snode(Artist* ptr_artist, SNode* ptr_snode)
{
	SNode* first = ptr_artist->head;
	SNode* last = ptr_artist->tail;

	if (first == ptr_snode && last == ptr_snode) {  // 유일한 노드
		ptr_artist->head = NULL;
	}
	else if (first == ptr_snode) // 첫노드
		first = ptr_snode->next; // 헤드 변경
	else if (last == ptr_snode) // 마지막노드
		last = ptr_snode->prev; // 테일 변경
	else // 일반
	{
		ptr_snode->prev->next = ptr_snode->next;
		ptr_snode->next->prev = ptr_snode->prev;
	}
	free(ptr_snode);
}

void initialize()
{
	for (int i = 0; i < NUM_CHARS; i++)
		artist_directory[i] = NULL;

	for (int i = 0; i < SIZE_INDEX_TABLE; i++)
		index_directory[i] = NULL;
}

void search_song(char* artist)
{
	Artist* ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		printf("No such artist exists.\n");
		return;
	}
	printf("Found.\n");
	print_artist(ptr_artist);
}

void search_song(char* artist, char* title)
{
	Artist* ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		printf("No such artist exists.\n");
		return;
	}

	SNode* ptr_snode = find_snode(ptr_artist, title);
	if (ptr_snode != NULL) {
		printf("Found.\n");
		print_song(ptr_snode->song);
	}
	else {
		printf("No such song exists.\n");
		return;
	}
}

void add_song(char* artist, char* title, char* path)
{
	Artist* ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		ptr_artist = add_artist(artist);
	}

	Song* ptr_song = create_song_instance(ptr_artist, title, path);
	SNode* ptr_snode = (SNode*)calloc(1, sizeof(SNode));
	ptr_snode->song = ptr_song;

	insert_node(ptr_artist, ptr_snode);
	insert_to_index_directory(ptr_song);
}

void remove(int index)
{
	SNode* q = NULL;
	SNode* p = index_directory[index % SIZE_INDEX_TABLE];
	while (p != NULL && p->song->index != index) {
		q = p;
		p = p->next;
	}

	if (p == NULL)
	{
		printf("No such song exists.\n");
		return;
	}

	Song* ptr_song = p->song;
	if (q == NULL) {
		index_directory[index % SIZE_INDEX_TABLE] = p->next;
	}
	else
	{
		q->next = p->next;
	}
	free(p);

	Artist* ptr_artist = ptr_song->artist;

	SNode* ptr_snode = find_snode(ptr_artist, ptr_song->title);
	if (ptr_snode == NULL)
	{
		printf("Not found snode - something wrong.\n");
		return;
	}
	remove_snode(ptr_artist, ptr_snode);
	destroy_song(ptr_song);
}

void destroy_song(Song* ptr_song)
{
	if (ptr_song->title != NULL)
		free(ptr_song->title);
	if (ptr_song->path != NULL)
		free(ptr_song->path);
	free(ptr_song);
}