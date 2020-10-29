// shitou.c

#include <weapon.h>
#include <ansi.h>
inherit HAMMER;

void create()
{
        set_name(HIW"大石头"NOR, ({ "shi tou"}));
        set_weight(5000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
        set("unit", "块");
        set("long", "这是一平平常常的大石头。\n");
        set("value", 0);
        set("material", "stone");
                set("wield_msg", "$N搬起一块$n准备战斗。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_hammer(1);
        setup();
}

/*
void init()
{
        add_action("do_break", "break");
}

int do_break(string arg)
{
        object obj, me;

        if (!arg || (arg != "stone" && arg != "shi tou"))
                return notify_fail("什么？\n");

        me = this_player();
        if( query("neili", me)<500 )
                return notify_fail("你功力不足，不能击石成粉！\n");
        message_vision(HIW"$N气沉丹田，运足真气，向石头击去！\n"NOR,me); 
        write(HIW"只听得“嘭”的一声，石头被击成碎块！\n"NOR);
        obj = new("/d/taohua/obj/shizi2");
        obj->move(me);
        addn("neili", -(100+random(100)), me);
        destruct(this_object());
        return 1;
}
*/