#ifndef DIJK_H
#define DIJK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pn.h"

struct link* add_link(char from, char to, int distance,struct link* last);

struct link* add_link1(struct link* this, struct link* list);

struct link* move_to_trash(struct link *lk,struct link *trash);

struct point* init_map();

struct link* init_link(struct link* link,struct point* p);

struct link* remove_from_list(struct link* this,struct link* list);

struct link* move_to_wl(struct link* curr,struct link* lk,struct link* wl);

struct link* remove_from_wl(struct link* next,struct link* wl);

struct link* select_next(struct link* waiting_list);

struct link* store_selected(struct link* new,struct link* collection);

struct trac* get_path(struct link* collection,char startp,char endp);

void deallocate_link(struct link *list);

void deallocate_trac(struct trac *list);

struct trac* calculate(char startp,char endp,struct link* lk);

#endif

