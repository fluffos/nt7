// Code of ShenZhou
// wuchang-dan.c 无常丹

#include <ansi.h>

inherit ITEM;

int cure_ob(string);

void create()
{
        set_name(HIR "无常丹" NOR, ({"wuchang dan", "dan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("long", "这是桃花岛疗伤圣药无常丹。\n");
                set("value", 5000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        if ( (int)this_player()->query_condition("bonze_drug" ) > 0 )
        {
                addn("neili", -100, this_player());
                message_vision(HIR "$N吃下一棵无常丹，只觉得头重脚轻，火气翻腾，
原来服食太多，药效适得其反！\n" NOR, this_player());
                this_player()->apply_condition("bonze_drug",
                this_player()->query_condition("bonze_drug")+10);
                destruct(this_object());
        }
        set("eff_qi",query("max_qi",  me), me);

        message_vision(HIG 
"$N吃下一粒无常丹，顿时神完气足，精神焕发\n" NOR, me);
        this_player()->apply_condition("bonze_drug",
                this_player()->query_condition("bonze_drug")+10);

        destruct(this_object());
        return 1;
}