// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "魔鬼滩");
        set("long", @LONG
这是蛇谷中最荒凉恐怖的地带，地上连一粒石子都没有。民间传
说这里发生过一些奇怪的事情。滩头四周的树木都向一边歪长着，中
心是一块巨大的凹陷处，似乎有一股巨大的旋风要把你卷进滩坑里。
LONG );

        set("exits", ([ 
            "west" : __DIR__"shegu_maze3",
        ]));

        if(random(2) == 0)
                set("objects", ([
                    "/clone/money/gold" : 1+random(3),
                ]));

        set("cost", 2);
        set("hide_snake", 1);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49950);
        set("coor/y", 20160);
        set("coor/z", 20);
        setup();
}

void init()
{
        object me = this_player();

        if( query("race", me) == "蛇类")return ;

        set("enter_shegu", 1, me);
        addn("jingli", -7, me);

        me->affect_by("snake_poison",
                    ([ "level" : 300,
                       "id":query("id", me),
                       "duration" :  20 ]));

        if( query("hide_snake") ) {
                remove_call_out("snake_attack");
                call_out("snake_attack", 3+random(3), me); 
                tell_object(me, HIB"你一走进魔鬼滩，登时觉得四面八方传来极为浓冽的毒气，异乎寻常……\n"NOR,);
        }
}

void snake_attack(object me)
{
        object snake, here;
        int i;

        here = this_object();
        i = random(12);

        if ( environment(me) != here) return;

        if( time()-query("last_enter", here)>300 )
                addn("hide_snake", 1);

        if ( query("hide_snake") < 1 ) return;

        addn("hide_snake", -1);
        set("last_enter", time());
        
        if( i == 0 ) snake = new(__DIR__"npc/lt_snake");
        else if( i == 11 ) snake = new(__DIR__"npc/cy_snake");
        else snake = new(__DIR__"npc/pu_snake");

        snake->move(here);

        message("vision", HIR"你突然听见沙沙异声，一条"+snake->name()+HIR"从魔鬼滩中心土底窜出，伴随一阵腥风，向"+me->name()+"张口咬去！\n"NOR, environment(me), me);
        tell_object(me, HIR"你耳中忽闻沙沙异声，猛然警觉，但见一条"+snake->name()+HIR"从魔鬼滩中心土坑窜出，张口向你咬来！\n"NOR);
        COMBAT_D->do_attack(snake,me,query_temp("weapon", snake));
        snake->kill_ob(me);
}
