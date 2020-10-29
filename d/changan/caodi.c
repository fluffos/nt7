// This program is a part of NT MudLIB
#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "草地");
        set("long",@LONG
这是一片空旷的草地，四周长满了杂草，似乎这里已经很久没有
人来过了，面对这旷野的地方，你的心中不由得升起一丝寒意。再往
东走就是一个深不见底的绝崖了。
LONG
);
        set("outdoors","changan");
        set("exits", ([
                "west" :__DIR__"boshulin10",
                "east" :__DIR__"jueya",
        ]));
        set("item_desc", ([
                "草地" : "在这片草地的中间，你似乎感到一些异样。\n",
        ]));
        set("coor/x", -10620);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
}

void init()
{
        if (interactive(this_player()))
                add_action("do_kill","kill");
}

void check(object me,object ob)
{
        if (!me || !ob)
                return;

        if (!present(me,this_object())
        ||  !present(ob,this_object()))
                return;

        if( query("jiali", ob) != (ob->query_skill("force")/2 )
         || query("jiali", me) != (me->query_skill("force")/2) )
                return;

        if( query("max_neili", me)<100000
         || query("max_neili", ob)<100000 )
                return;

        if( query("max_neili", ob)<query("max_neili", me) )
        {
                message_vision("$n被$N内力一震，往崖边倒飞下去。\n",me,ob);
                ob->move(__DIR__"qinhuang/gudi.c");
                set_temp("killer", 1, ob);
                ob->unconcious();
        }
        else
        {
                message_vision("$N被$n内力一震，往崖边倒飞下去。\n",me,ob);
                me->move(__DIR__"qinhuang/gudi.c");
                set_temp("killer", 1, me);
                me->unconcious();
        }
}

int do_kill(string arg)
{
        object ob, me=this_player();

        if (!arg || arg=="")   return 0;
        if (ob=present(arg, this_object()))
        {
                message_vision( HIY "$N和$n一见面，立即厮杀了起来。\n" NOR ,me,ob);
                if (userp(ob) &&
                    query("jiali", ob) == (ob->query_skill("force")/2) && 
                    query("jiali", me) == (me->query_skill("force")/2) )
                {
                        remove_call_out("check");
                        call_out("check",random(20)+5,me,ob);
                }
        }
        return 0;
}

