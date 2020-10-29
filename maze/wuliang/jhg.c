// Room: jhg.c
// By River 98/12
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIY"剑湖宫"NOR);
	set("long", @LONG 
宫内坐着二人，上首是个四十左右的中年道姑，下首是个五十余岁的老者。
西首锦凳上所坐的则是别派人士，其中有的是东西二宗掌门人共同出面邀请的
公证人，其余则是前来观礼的嘉宾。这些人都是云南武林中的知名之士。
LONG
	);
	set("exits", ([ 
	    "south" : __DIR__"wlj",
	    "north" : __DIR__"houyuan",
            "west" : __DIR__"xlgong",
            "east" : __DIR__"dlgong",
        ]));
        set("objects", ([
                __DIR__"npc/zuo_zimu" : 1,
                __DIR__"npc/xin_shuangqing" : 1,
                __DIR__"npc/gong_guangjie" : 1, 
        ]));

	setup();
}

int valid_leave(object me,string dir)
{ 
     if( dir != "south"
      && (present("gong guangjie", environment(me))))
         return notify_fail("龚光杰上前拦住你的去路：无量剑重地，任何人不得擅自入内。\n");
     if( dir != "south"
      && (present("xin shuangqing", environment(me))))
         return notify_fail("辛双清上前拦住你的去路：无量剑重地，任何人不得擅自入内。\n");
     if( dir != "south"
      && (present("zuo zimu", environment(me))))
         return notify_fail("左子穆上前拦住你的去路：无量剑重地，任何人不得擅自入内。\n");
         return ::valid_leave(me, dir);
}