// jiuyang.c
#include <ansi.h>
inherit BOOK;
inherit F_UNIQUE;

void create()
{
        set_name("「独孤九剑残本」", ({ "dugu canben", "canben", "dugu" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long",
                        "这是一本薄薄的布满灰尘的独孤九剑残本，只因长期藏\n"
                        "在空室之中，书页已有些破损残缺。\n",
                        );
                set("value", 1);
                set("no_sell", 1);
                set("material", "paper");
        }
}

void init()
{
        add_action("do_read", "read");
}

int do_read(string arg)
{
        object me = this_player();

        if (! arg || ! id(arg))
                return notify_fail("你要读什么？\n");

        if( query("lonely-sword/nothing", me) )
                return notify_fail("这本残本对你来说没有任何用处了。\n");

        if (me->query_skill("lonely-sword", 1) < 300)
                return notify_fail("你的独孤九剑修为太浅，无法领悟书中奥秘。\n");

        tell_object(me, "你仔细地研读残本上面的讲解......\n"
                        "你开始如痴如狂，沉迷其中........\n"
                        "时间很快的过去..................\n"
                        "突然一日，你毛塞顿开，哈哈大笑起来。\n"
                        "你发现你原先所有对剑法的认识是那么可笑，荒唐。\n"
                        "你通悟了独孤九剑的精髓「" HIR "无招" NOR "」的奥秘。\n");
        tell_object(me, "突然独孤九剑残本变成了一片片碎片，消失了。\n");
        set("lonely-sword/nothing", 1, me);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        destruct(this_object());
        return 1;
}


