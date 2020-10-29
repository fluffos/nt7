//shufang.c  by Lonely

#include <room.h>
#include <skill.h>

inherit ROOM;

void create()
{        
        seteuid(getuid());
        set("short", "书房");
        set("long",
"这是莲藕小筑里的书房。唐门弟子可以在这里研学诗画。靠墙并排摆\n"
"着几个书架，一本唐诗选集(shi)引起了你的注意，另外墙上还挂了几幅\n"
"字画(hua)，看来在这里可以学到不少东西。\n"
);        
        set("exits", ([        
                "east" : __DIR__"nzlangw3",
        ]));
        set("item_desc", ([
                "shi" : "这是一本很平常的唐诗选集。不少弟子在吟颂(yin)。\n",
                "hua" : "这是一幅临摹郑板桥的字画。不少弟子在看(kan)。\n",
        ]));

        set("no_steal", "1");
        set("no_fight", "1");
        set("area", "tangmen");
        set("objects", ([
                CLASS_D("tangmen") + "/tangyu" : 1,
        ]));

        setup();
}

void init()
{
        add_action("do_look","kan");
        add_action("do_du","yin");
}

int do_look(string arg)
{
        object me;
        int cost;

        me = this_player();
        cost = 10 + ( 20 - (int)me->query_int() ) / 2;

        if ( cost < 1) cost = 0;

        if ( me->is_busy() )
                return notify_fail("你现在正忙着呢。\n");

        if ( arg == "hua")
        {
                if( (int)me->query_skill("literate", 1) > 50 )
                        return notify_fail("你对着字画仔细揣摩了一会儿，发现从中已经学不到什么了。\n");

                if( query("jing", me)>cost && 
                    query("potential", me)-query("learned_points", me) >= 1 )
                {
                        tell_object(me, "你专心地研读墙上的字画，不时还伸出手指临摹一番。\n");
                        me->improve_skill("literate", random( (int)me->query_skill("literate", 1) / 2 ) + 10 );
                        me->receive_damage("jing", cost );
                        addn("potential", -1, me);
                }
                else
                {
                        if( query("jing", me) <= cost )
                                write("你现在过于疲倦，无法专心下来研读新知。\n");

                        if( query("potential", me)-query("learned_points", me) <= 0 )
                                write("你看着字画反复琢磨，竟没有一丝心得。\n");
                }
                return 1;
        }
        else
                return 0;
}

int do_du(string arg)
{
        object me;
        int cost;

        me = this_player();
        cost = 10 + ( 30 - (int)me->query_int() ) / 2;

        if ( cost < 1) cost = 0;

        if ( me->is_busy() )
                return notify_fail("你现在正忙着呢。\n");

        if ( arg == "shi")
        {
                if( (int)me->query_skill("literate", 1) < 51 )
                        return notify_fail("你拿起唐诗选集，翻开一页发现竟什么也看不懂。\n");

                if( (int)me->query_skill("literate", 1) > 101 )
                        return notify_fail("你拿起唐诗选集，翻了翻发现没有什么可学的了。\n");

                if( query("jing", me)>cost && 
                    query("potential", me)-query("learned_points", me) >= 1 )
                {
                        tell_object(me, "你专心地研读书架上的诗集，读到忘情时竟读出了声。\n");
                        me->improve_skill("literate", random( (int)me->query_skill("literate", 1) / 2 ) + 20 );
                        me->receive_damage("jing", cost );
                        addn("potential", -1, me);

                }
                else
                {
                        if( query("jing", me) <= cost )
                                write("你现在过于疲倦，无法专心下来研读新知。\n");

                        if( query("potential", me) <= query("learned_points", me) )
                                write("你看着诗集反复琢磨，竟没有一丝心得。\n");
                }
                return 1;
        }
        else
                return 0;
}