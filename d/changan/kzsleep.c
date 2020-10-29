//Room: kzsleep.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "客店睡房");
        set("long", @LONG
客栈的一间睡房，房间里打扫得干干净净，不时的可以听到从隔
壁客房里传出呼呼的打鼾声，墙角有一张榻（ｂｅｄ），是供客人们
休息睡觉用的。
LONG );
        set("item_desc", ([ /* sizeof() == 1 */
                "bed" : "一张白色的软榻，看上去极为精致(bed)。",
        ]));
        set("exits", ([
                "down" : "/d/changan/kezhan",
        ]));

        set("no_fight", 1);
        set("coor/x", -10750);
	set("coor/y", 1950);
	set("coor/z", 10);
	setup();
}
void init()
{
        add_action("do_bed", "bed");
}
int do_bed()
{       object me;
        me=this_player();
        message_vision(HIY "$N掀开纱帐，准备上床了。\n\n" NOR, me);
        me->move("/d/changan/bed");
        message_vision(HIY "\n沙帐轻轻一动，$N钻了进来。\n" NOR, me);
        return 1;
}

int valid_leave(object me, string dir)
{
        delete_temp("rent_paid", me);
        return ::valid_leave(me, dir);
}