#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蜀道");
        set("long", @LONG
你走在以险著称天下的蜀道上，往西面再过不远，就到成都了，
向东则开始走入险恶的蜀道。
LONG );
        set("exits", ([
                "west" :  __DIR__"shudao19",
                "eastdown" : __DIR__"shudao17",
        ]));
        
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15150);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}