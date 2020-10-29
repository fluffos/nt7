// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
      set("short", "菩提树下");
        set("long", @LONG
菩提本无树，明镜亦非台；本来无一物，何处惹尘埃。
LONG );

        set("exits", ([ /* sizeof() == 1 */
                 "尘埃":"/d/city/swing",
        ]));

        set("valid_startroom", 1);
        set("no_fight", "1");
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
