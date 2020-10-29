// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;


void create()
{
        set("short", "芝芝的工作室");
        set("long", @LONG
这是没有建造工作室的巫师的临时住处，这里的设备非常简单，只有
一些常用物品。
LONG );

        set("exits", ([ /* sizeof() == 1 */
                "north" : "/d/wizard/wizard_room",
            "east" : "/u/redl/swing",
                "down" : "/d/city/wumiao",
        ]));

        set("valid_startroom", 1);
        set("no_fight", "1");
        set("no_clean_up", 0);
        setup();
             //"/clone/board/gigi_b"->foo();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && ! wizardp(me))
                return notify_fail("那里只有巫师才能进去。\n");

        return ::valid_leave(me, dir);
}

void init()
{
	object me = this_player();
/*
	if ( query("id", me) != "gigi" && query("couple/couple_id", me) != "gigi" )
{		message_vision(YEL "一股微风吹过，把$N吹到了室外。\n" NOR, me);
		me->move("/d/city/wumiao");
		return;}
*/
	add_all_action();
}
