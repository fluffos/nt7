// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","石阶");

        set("long",@LONG
这後山石阶蜿蜒於战场中，也不知通往何处。只见浓荫蔽天，越
走越是阴森，不时还有野兽吼声传来，令人心中发毛。
LONG);

        set("exits",([
                "up" : __DIR__"wtower5",
                "down" : __DIR__"wtower3",
        ]));
        set("outdoors", "battle");

        set("objects", ([
                __DIR__"npc/guarder" : 1,
        ]));
        
        setup();
}

void init()
{
        string team_name;
        object ob;
        
        team_name = query("team_name", get_object(__DIR__"wtang"));
        ob = present("guarder", this_object());
        if( objectp(ob) && !query_temp("battle/team_name", ob) )
                set_temp("battle/team_name", team_name, ob);
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        object ob, wp, *inv;
        int i, j=0;

        if( dir == "up" )
        {
                if( objectp(ob = present("guarder", this_object())) )
                {
                        if( query_temp("battle/team_name", me) != query_temp("battle/team_name", ob) )
                        {
                                if( objectp(wp=query_temp("weapon", ob)) )
                                        message_vision("$N对$n喝道：尔等邪魔歪道人物，要想过此路，得先问问我手中的"
                                                +query("name", wp)+"答应不答应！\n",ob,me);
                                else
                                        message_vision("$N对$n喝道：只要我在，尔等邪魔歪道人物，便休想过此路！\n", ob, me);
                                return notify_fail("\n");
                        }
                }
        }

        return ::valid_leave(me, dir);
}
