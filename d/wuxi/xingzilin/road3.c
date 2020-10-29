// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "杏林小道");
        set("long", @LONG
这是林中小路，高大的杏树密布。浓雾飘绕五丈外不可见人，周围
杀喊的声音不时传来。
LONG);
        set("no_magic", 1);
	set("no_sleep_room",1);
        set("exits", ([
                        "north"  : __DIR__"xxlin1",
                        "west" : __DIR__"road2",
        ]));

           set("objects", ([ 
                     "/clone/npc/walker"  : 3, 
           ])); 

setup();


}

int valid_leave(object me, string dir)
{
          if (dir == "west" && ! playerp(me)) return 0; //阻挡npc逃出区域
        return ::valid_leave(me, dir);
}

