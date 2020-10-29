#include <ansi.h>
inherit NPC;


void create()
{
        set_name("布娃娃", ({ "buwawa", "bu", "wawa" }) );
        set("gender", "男性" );
        set("age", 22);
        set("combat_exp", 100);
        set("attitude", "friendly");

        setup();
}

void init()
{
        add_action("do_lianxi", "lianxi");
}

int do_lianxi(string arg)
{
        object me;
        int i;
        me=this_player();
        i=(int)me->query_skill("zhenjiu-shu",1);

        if( query("family/family_name", me) != "药王谷" || me->query_skill("zhenjiu-shu",1) >= 100 )
        {       
                return notify_fail("你不能使用布娃娃！\n");
        }

        if (!id(arg))
                return notify_fail("指令格式：lianxi <ID> \n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着呢！\n");

        if( query("jing", me) <= i )
                return notify_fail("你太累了，休息一会儿吧！\n");

        message_vision ("$N拿起一支银针，在布娃娃身上照着经络图，比划着！\n", me);
        me->improve_skill("zhenjiu-shu", (i/3));
        addn("jing", -i, me);
        me->start_busy(1);

        return 1;
}
