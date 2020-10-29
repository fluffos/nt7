// Create by BUNCH_D written by Lonely
// center.c

#include <ansi.h>
#include <room.h>
inherit ROOM;
#define PLACE   "yz"
#define TYPE    "bad"

// int is_bunch_room() { return 1; }
int sort_by_id(mapping quest1, mapping quest2);

void create()
{
	set("short", "快乐大本营总坛");
	set("long", "房间的墙上有一块牌子(paizi)。加入帮派快乐大本营的玩家，可以在这里选择任务去完成。\n");
	set("objects", ([
		__DIR__"npc/quester" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"room9", 
	]));

	setup();
}

#include <bang_bad.h>
