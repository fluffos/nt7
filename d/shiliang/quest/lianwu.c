

inherit ROOM;
#include <ansi.h>
#define QUESTJINSHE "skybook/bixue/"

void create()
{
        set("short",HIG "练武场" NOR);
        set("long", @LONG
这是温家堡的练武场，一块空荡荡的场地。
LONG);
        set("exits", ([ 
                "out" : "/d/shiliang/gate",

        ]));
        set("quest", 1);
        setup();
}

void init()
{
        object me,wen1, wen2, wen3, wen4, wen5;
        me = this_player();
        if( query_temp(QUESTJINSHE+"start_kill", me )
            && !me->query_condition("killer")
            && !query(QUESTJINSHE+"pass", me )
            && !query(QUESTJINSHE+"over", me) ) {
                wen1=new(__DIR__"npc/wenfangshan");
                set("kill_id",query("id",  me), wen1);
                wen1->move(environment(me));      
                wen2=new(__DIR__"npc/wenfangwu");
                set("kill_id",query("id",  me), wen2);
                wen2->move(environment(me));        
                wen3=new(__DIR__"npc/wenfangshi");
                set("kill_id",query("id",  me), wen3);
                wen3->move(environment(me));    
                wen4=new(__DIR__"npc/wenfangda");
                set("kill_id",query("id",  me), wen4);
                wen4->move(environment(me));    
                wen5=new(__DIR__"npc/wenfangyi");
                set("kill_id",query("id",  me), wen5);
                wen5->move(environment(me));          
        }      
}

int valid_leave(object me, string dir)
{
        if (me->is_fighting())
                return notify_fail(RED"\n温家五老大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
        if (present("heiyi ren",this_object()))
                return notify_fail(RED"\n温家五老大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
        if(me->query_condition("killer")) 
                return notify_fail(RED"\n怎么进来的？？这里等wiz吧。\n"NOR);
        if( query_temp(QUESTJINSHE+"kill", me )
            && query_temp(QUESTJINSHE+"have_kill", me)){
                delete_temp(QUESTJINSHE+"start_kill", me);
                delete_temp(QUESTJINSHE+"kill", me);
                delete_temp(QUESTJINSHE+"have_kill", me);
    
        }
        return ::valid_leave(me, dir);
}

