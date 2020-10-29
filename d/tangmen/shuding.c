//shuding.c  by Lonely

#include <room.h>
#include <skill.h>
#include <ansi.h>

inherit ROOM;

void create()
{        
        seteuid(getuid());
        set("short", "树顶");
        set("long",
"这是万年古松的树顶。当年祖师爷？？？曾在这里日观云动，夜观星\n"
"变，最终悟出了？？？？的唐门绝学，因此很多弟子常常在这里日夜静坐。\n"
);        
        set("item_desc", ([
                "down" : "一眼望去只见白云片片，犹如棉絮般轻柔，随着山风飘来飘去。\n",
        ]));

        set("area", "tangmen");
        setup();
}

void init()
{
        add_action("do_wu","lingwu");
        add_action("do_climb","climb");
        add_action("do_climb","pa");
}

int do_wu(string arg)
{
        object me;
        int cost;
        int c_exp;
        int d_skill, f_skill;

        me = this_player();
        cost=20+(30-query("int", me))/2;//原始值为15+。加大点难度
        c_exp=query("combat_exp", me);
        d_skill = (int)me->query_skill("dodge",1); 
        f_skill = (int)me->query_skill("finger",1); 

        if ( cost < 1)
                cost = 0;

        if ( 25 - (int)me->query_int() > 0 )
             return notify_fail("以你目前的悟性，恐怕不会领悟到什么。\n");

        if( !me->query_skill("literate", 1) )
                return notify_fail("你是个文盲，先学点文化(literate)吧。\n");

        if ( me->is_busy() )
                return notify_fail("你现在正忙着呢。\n");

        if( me->is_fighting() )
                return notify_fail("你无法在战斗中静心领悟！\n");
        if ( arg == "yun")
        {
                if( (int)me->query_skill("dodge", 1) < 51 )
                        return notify_fail("你日观云变，但是却无法从中领悟什么。\n");

                if( (int)me->query_skill("dodge", 1) > 201 )
                        return notify_fail("你日观云变，自觉一切变化都已熟记于心。\n");

                if( d_skill*d_skill*d_skill/10 > c_exp )
                                      return notify_fail("你静观天变，但由于实战经验不足没有领悟到什么。\n"); 

                if( query("jingli", me)>cost )
                {
                        tell_object(me, "你盘膝坐下静观头顶浮云随风飘动，毫无踪迹可寻。\n你对基本身法有了进一步认识。\n");
                        me->improve_skill("dodge", random( (int)me->query_skill("literate", 1) / 2 ) + 20 );
                        addn("jingli", -cost, me);
                }
                else
                {
                        if( query("jingli", me) <= cost )
                                write("你现在过于疲倦，无法静下心来领悟。\n");
                }
                return 1;
        }
        else
                if ( arg == "xing")
                {
                        if( (int)me->query_skill("finger", 1) < 51 )
                                return notify_fail("你夜观星变，但是却无法从中领悟什么。\n");
        
                        if( (int)me->query_skill("finger", 1) > 201 )
                                return notify_fail("你夜观星变，自觉一切变化都已熟记于心。\n");

                        if( f_skill*d_skill*d_skill/10 > c_exp )
                                      return notify_fail("你静观天变，但由于实战经验不足没有领悟到什么。\n"); 
        
                        if( query("jingli", me)>cost )
                        {
                                tell_object(me, "你盘膝坐下静观头顶明星闪烁，忽静忽动。\n你对基本手法有了进一步认识。\n");
                                me->improve_skill("finger", random( (int)me->query_skill("literate", 1) / 2 ) + 20 );
                                addn("jingli", -cost, me);
                        }
                        else
                        {
                                if( query("jingli", me) <= cost )
                                        write("你现在过于疲倦，无法静下心来领悟。\n");
                        }
                        return 1;
                }
                else
                        return 0;
}

int do_climb(string arg)
{
        object ob;
        ob = this_player();

        if ( arg && arg == "down" )
        {
                message_vision(HIC "$N攀着繁茂的树枝一步步爬了下去。\n" NOR, ob);
                ob->move(__DIR__"shugan3");
                return 1;
        }
        else
                return notify_fail("你要向哪里爬？\n");
}