// Create by BUNCH_D written by Lonely
// center.c

#include <ansi.h>
#include <room.h>
inherit ROOM;
#define PLACE   "hz"
#define TYPE    "good"

// int is_bunch_room() { return 1; }
int sort_by_id(mapping quest1, mapping quest2);

void create()
{
	set("short", "峨眉洗象总坛");
	set("long", "房间的墙上有一块牌子(paizi)。加入帮派峨眉洗象的玩家，可以在这里选择任务去完成。\n");
	set("objects", ([
		__DIR__"npc/quester" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"room9", 
	]));

	setup();
}

#include <bang_good.h>
