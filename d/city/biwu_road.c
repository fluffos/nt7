#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"演武走廊"NOR);
        set("long", @LONG
这是一个很短的走廊，侧门通向演武休息室，从大门进来直走，
就是著名的演武大厅。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);
    set("biwu_room",1);

    set("exits", ([
        "west"  : "/d/city/biwu_restroom",
        "south" : "/d/city/biwu_gate",
        "north" : "/d/city/biwu_dating",
        "east"  : "/d/city/xinrui_dating",
    ]));

    set("no_clean_up", 0);
	set("coor/x", -60);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}
 int valid_leave(object me, string dir)
{
        mapping conditions; 
        if (dir != "south") return 1;
//        if (wizardp(me)) return 1;

/*
        if (mapp(conditions = me->query_condition()))
               me->clear_condition();
*/
 
        if( query("eff_qi", me)<query("max_qi", me) )
               set("eff_qi",query("max_qi",  me), me);

        if( query("eff_jing", me)<query("max_jing", me) )
               set("eff_jing",query("max_jing",  me), me);

        return 1;
}