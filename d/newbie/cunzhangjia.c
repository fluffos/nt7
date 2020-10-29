#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "村长家" NOR);
        set("long", @LONG
这里是古村村长的家，屋内却是颇为朴素，墙边靠着几个农具，
墙角一张竹床，与普通村民家没什么区别。
LONG);

        set("exits", ([
                "north"  :  __DIR__"woshi",
                "west" :  __DIR__"chufang",
                "south"  :  __DIR__"road2",
        ]));
        set("xinshoucun", 1);
        set("outdoors", "newbie");
        
        set("no_fight", 1);
        set("no_pk", 1);
	setup();

        replace_program(ROOM); 
}
