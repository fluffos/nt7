#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蜀道");
        set("long", @LONG
你走在以险著称天下的蜀道上，走在这样的路上非要格外小心，
用尽全身气力才行。不多一会儿，你就觉得很累了。
LONG );
        set("exits", ([
                "westup" :  __DIR__"shudao16",
                "eastdown" : __DIR__"shudao14",
  
        ]));        
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15120);
	set("coor/y", -1830);
	set("coor/z", -30);
	setup();
}

int init()
{
        object me;
        int i;
        me = this_player();
    i=query("max_qi", me)/50;
        me->receive_damage("qi", i);
        tell_object(me, HIR "你费力的走在蜀道上，累的气喘吁吁。\n" NOR);
}