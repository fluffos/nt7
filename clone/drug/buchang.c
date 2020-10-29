// Code of ShenZhou

#include <ansi.h>

inherit ITEM;

void init();

void create()
{
        set_name(HIW "幸福散" NOR, ({"xingfu san", "san"}));
        set_weight(20);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "粒");
                set("value", 50);
                set("medicine", 1);
                set("no_sell", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_drop", 1);
                set("no_sell", 1);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        addn("shenzhou/pts", 40, me);
        message_vision(HIG "$N服下了一些幸福散，所有忿怨顷刻一笔勾销! \n" NOR, me); 

        destruct(this_object());
        return 1;
}