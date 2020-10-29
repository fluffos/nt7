// Room: /huanghe/shamo.c
// Java. Sep 21 1998

#include <room.h>
#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "沙漠");
        set("long", @LONG
这是一片没边际的沙漠，到处是近百米高的巨大沙丘。你一走进来
就仿佛迷了路。
LONG );
        set("exits", ([
                "north" : __FILE__,
                "south" : __DIR__"shamo1",
                "east"  : __FILE__,
                "west"  : __FILE__,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16070);
	set("coor/y", 4240);
	set("coor/z", 0);
	setup();
}
void init()
{
        object ob = this_player();
        if( query("water", ob)>10 )
                set("water",query("water",  ob)-10, ob);
        else
                set("water", 0, ob);
        message_vision(HIY"满天黄沙，$N感到喉咙冒烟，干渴难熬！\n"NOR, ob);
}

int valid_leave(object me, string dir)
{
        int total_steps = random(9)+1;
        if ( dir == "north")
                addn_temp("shamo/steps", 1, me);
        if ( dir == "south")
                addn_temp("shamo/steps", -1, me);
        if( query_temp("shamo/steps", me) == total_steps )
        {
                me->move(__DIR__"jingyuan");
                delete_temp("shamo/steps", me);
                tell_object(me, "你走了半天，终于走出了西夏沙漠。\n");
                return -1;
        }
        if( query_temp("shamo/steps", me) == -total_steps )
        {
                me->move(__DIR__"qingcheng");
                delete_temp("shamo/steps", me);
                tell_object(me, "你走了半天，终于走出了西夏沙漠。\n");
                return -1;
             }
        return ::valid_leave(me,dir);
}