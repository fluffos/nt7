#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "柴房");
        set("long", @LONG
这是一间矮小的瓦房，平时作为堆放杂物所用。房屋里布
满了蛛网，地面满是灰尘。看样子已经很久没有人打扫了。柴
房的一角斜放着几捆干柴。
LONG);
        set("exits", ([
                "west" : __DIR__"ma_dayuan",
        ]));
        set("region", "yangzhou");
        set("no_clean_up", 0);
        set("objects", ([
                "/d/wudu/obj/ganchai" : 2,
        ]));
	set("coor/x", 40);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();

        if( query("family/family_name", me) == "五毒教" )
        {
                tell_object(me, HIR "\n你突然发现一只色彩斑斓的蜘蛛，竟"
                                "似五毒教的独门密信。\n" NOR);
                set_temp("want_back_wudu", 1, me);

                remove_call_out("letter");
                call_out("letter", 3, me);
        }
        add_action("do_back", "back");
}

void letter(object me)
{
        if( !objectp(me) ) return;
        if (environment(me) != this_object())
                return;

        if( !query_temp("want_back_wudu", me) )
                return;

        tell_object(me, WHT "  ┏------------┓\n"
                            "  ┃柴房水缸下有┃\n"
                            "  ┃本教密道能够┃\n"
                            "  ┃直通(" HIY "back" NOR + WHT ")五┃\n"
                            "  ┃毒教  齐云傲┃\n"
                            "  ┗------------┛\n" NOR);
}

int do_back()
{
        object me = this_player();

        if( query_temp("want_back_wudu", me) )
        {
                message("vision", HIC "忽然间只见" + me->name() +
                                  HIC "身形一晃，竟没了踪影。\n" NOR,
                                  environment(me), ({me}));
                me->move("/d/wudu/midao5");
                tell_object(me, HIC "\n你钻进了柴房水缸下的密道。\n\n" NOR);
        }
        return 1;
}
