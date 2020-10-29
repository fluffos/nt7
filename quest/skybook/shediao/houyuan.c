//Created by Redhat@Sjmud 2009/4/7
//updated by Zhuifeng@SJFY 2010/7/27

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/射雕英雄传/风雪惊变/"

void create()
{
	set("short", GRN "后院" NOR);
	set("long",@long
这里就是大侠杨铁心家的后院，院子由篱笆和竹子编成的栅栏，
院子里有一小块地种了好几种蔬菜，菜地旁边篱笆上靠着一把锄头。
long);
  set("indoors", "牛家村");
	set("exits",([
		"south" : __DIR__"yangjia",
		"north" : __DIR__"mafang",
]));
            set("quest",1);
            	            set("objects",([
               __DIR__"npc/yang": 1,
               __DIR__"npc/bao": 1,
            ]));
	//set("no_fight", 1);
	setup();
}


