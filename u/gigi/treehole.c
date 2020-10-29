// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;


void create()
{
        set("short", "树洞");
        set("long", @LONG
此处漆黑一片，伸手不见五指，树洞入口曲折，一丝光亮也透不进来。
尽管如此，你却一点也不害怕，且感到自己的思绪前所未有的通透。
LONG );

        set("exits", ([ /* sizeof() == 1 */
                "out" : "/u/gigi/swing",
        ]));

        set("no_fight", "1");
        set("no_rideto", 1);
        set("no_flyto", 1);

             set("sleep_room", 1); 
        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && ! wizardp(me))
                return notify_fail("那里只有巫师才能进去。\n");

        return ::valid_leave(me, dir);
}

void init()
{
        add_all_action();
}
