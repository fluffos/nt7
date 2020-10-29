// tang.c

#include <ansi.h>

inherit ITEM;

void create()
{
        string *colors = ({ HIW, HIR, HIY, HIC, HIM, HIG });
        set_name(colors[random(sizeof(colors))] + "糖果" NOR, ({ "sugar", "tang" }) );
        set_weight(10);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一颗糖，甜甜的。\n" NOR);
                set("value", 0);
                set("unit", "颗");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N吞下一颗$n，舔了舔嘴角，嗯，好甜啊。\n",
                       me, this_object());
        destruct(this_object());
        return 1;
}