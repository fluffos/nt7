// Room: /d/ruzzhou/yinyuan-tang.c    拜堂之处
// by llm 99/06

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "姻缘堂");
   set("long", @LONG
你简直走进了一片红色的世界，高低左右地垂着各式各样的红绸绫缎
彩纸贴花，细细看去，每一处竟都绣扎着鸳鸯凤凰，透出一股股浓郁的喜
庆气氛，当中一块横匾：
          千里姻缘一线牵
LONG
   );
        set("exits", ([
                "west" : __DIR__"hongniang-zhuang",
   ]) );
   set("objects", ([
   ]) );
   set("no_fight",1);
   set("no_steal",1);
   set("no_beg",1);
   set("no_sleep_room",1);

	set("coor/x", -6720);
	set("coor/y", 1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}