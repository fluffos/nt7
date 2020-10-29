// Room: wljmen.c
// By River 98/12
inherit ROOM;
#include <ansi.h>
#include <wanted.h>
void create()
{
        set("short",HIY"无量剑宗"NOR);
	set("long", @LONG
「无量剑」于五代后唐年间在南诏无量山创派，掌门人居住无量山剑湖宫。
自大宋仁过年间分为东、北、西三宗，每隔五年，三宗门下弟子便在剑湖宫中
比武斗剑，获胜者入住剑湖宫。
LONG
	);
	set("exits", ([ 
	    "southdown" : __DIR__"xiaolu5",
	    "enter" : __DIR__"wlj",
        ]));

        set("objects", ([
              __DIR__"npc/yu_guangbiao" : 1,
              __DIR__"npc/wu_guangsheng" : 1,
        ]));

        set("outdoors", "大理");

	setup();
}

int valid_leave(object me,string dir)
{ 
	if (dir == "enter" && is_wanted(me))
		return 0;
     if( dir == "enter"
      && (present("yu guangbiao", environment(me))))
         return notify_fail("郁光标上前拦住你的去路：无量剑重地，任何人不得擅自入内。\n");
     if( dir == "enter"
      && (present("wu guangsheng", environment(me))))
         return notify_fail("吴光胜上前拦住你的去路：无量剑重地，任何人不得擅自入内。\n");
         return ::valid_leave(me, dir);
}