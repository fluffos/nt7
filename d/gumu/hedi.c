// This program is a part of NT MudLIB

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"暗流河底"NOR);
        set("long", @LONG
你没在水中，感觉似乎是到了水底,水势已不似刚才那么迅急，水压却是更甚从前。憋得你就要透不过气来了，你情急
下急急审视四周寻找出路,发觉上方(southup)隐隐透着亮光,不觉
心下一喜,不急细想就欲向上浮去.
LONG
        );

        setup();
}

void init()
{
        object me;

        me = this_player();
        add_action("do_swim","swim");
        me->receive_damage("qi", 500 );
        me->receive_damage("jing", 500 );
        message_vision(HIB"$N的真气正在流失，呼吸十分困难。\n"NOR, me);
        if( query("qi", me)<10 || query("jing", me)<10 )
        {
                set_temp("die_reason", "在潜流中被淹死", me);
                me->unconcious();
                me->die();
                return ;
        }
}

int do_swim(string arg)
{
        object me;
        me=this_player();

        if ( !arg || arg != "southup" )
                return notify_fail("你要游向哪里？\n");

        if ( me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");

        if (arg =="southup")
        {
                if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() >= 40)
                        return notify_fail("你身子沉重，用尽全力也无法浮上去!\n");

                message_vision(YEL"$N两腿用力一蹬，向上面浮去。\n"NOR, me);
                me->receive_damage("jing", 500);
                me->receive_damage("qi", 500);
                me->move(__DIR__"midong");
                tell_room(environment(me), me->name() + "从下面浮了上来。\n", ({ me }));
                message_vision (HIB"$N只觉得头晕晕的，身体浸在冰冷的水中，不住的颤抖。\n"NOR,me);
                return 1;
        }
        return 1;
}
