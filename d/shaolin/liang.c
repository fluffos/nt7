#include <room.h>

inherit ROOM;

void create()
{ 
       set("short","藏经阁房梁");
        set("long", @LONG
你现在在藏经阁的房梁上四下观瞧，周围都是一些高大的书架(s
hujia)。
LONG );
        set("exits", ([
                "down" : __DIR__"cjlou1",
        ]));       
        set("item_desc", ([
                "shujia" : "书架顶上积满了厚厚的灰尘。\n",
                "书架"   : "书架顶上积满了厚厚的灰尘。\n",
        ]) ); 
        set("objects", ([
                "/d/shaolin/obj/muban" : 1,
         ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" )
                return 0;
        if( arg == "shujia" )
        {
                if( query_temp("marks/跳1", me) )
                {
                        if (me->query_skill("dodge",1)<100)
                                write("你试图跳上书架的顶端，但老是跳不上去。\n");
                        else 
                        {
                                write("你纵身跃上了书架顶端。\n");
                                message("vision",
                                        me->name() + "一纵身跃上了书架顶端。\n",
                                        environment(me), ({me}) );
                                me->move("/d/shaolin/shujiad");

                        }

                        return 1;
                }
        }
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/跳1", me);
        return ::valid_leave(me, dir);
}

