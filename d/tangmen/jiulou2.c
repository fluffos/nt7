#include <ansi.h>;
inherit ROOM;
//inherit F_DEALER;

void init();
int do_kan(string arg);

void create()
{
        set("name", "唐门酒楼二楼");
        set("short", "唐门酒楼二楼");
        set("long",
"这里是雅座，非常的清静，一般没有人来在这里的，来的都是一些唐\n"
"门中人，好象找唐肥有事的。所以这里虽然是雅座，却是没有生意的。老\n"
"板唐肥正坐在一扇窗子(window)的边上，好象向外在看什么东东。墙上挂\n"
"着一些个没见过的字画。\n"
);
        set("item_desc", ([
                "window" : HIG"一眼看去,早春的点点绿绿，让你只觉得心旷神怡。。\n"NOR,
        ]));
        set("exits", ([
                "down" : __DIR__"jiulou",
        ]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangfei" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        
}

void init()
{
        add_action("do_kan","kan");
}

int do_kan(string arg)
{
        object me;
        
        me = this_player();
        
        if ( !arg || arg!= "zihua")
           return notify_fail(HIR"不要乱看啊！\n"NOR);
           
        if( query("combat_exp", me)<120000 )
        {
                tell_object(me,HIR"心中顿觉气塞，神智不由得迷乱起来。\n"NOR);
                if( query("qi", me)<500 )
                {
                        me->unconcious();
                        return 1;
                }       
                addn("qi", -500, me);
                addn("jingli", -50, me);
                return 1;
        }       
        
        if( query_temp("thua", me) )
           return notify_fail("不要再看了，看多了对你不好的！\n");
            
        if ( (int)me->query_skill("tangmen-jueqi",1) < 120)
           return notify_fail("好一幅风景画，从来都没有看过，真是不枉此生。\n");
        
        if( query_temp("thua1", me) )
        {
                set_temp("thua2", 1, me);
                delete_temp("thua1", me);
           return notify_fail("一声怒吼：贪心的人不会有好下场的！\n");   
        }  
        
        message_vision(HIR"唐花"NOR+HIC"，一朵如此美丽的花，你不由的痴了...... \n"NOR,me);
        set_temp("thua", 1, me);
        return 1;
}
