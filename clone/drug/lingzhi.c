// Code of ShenZhou
//lingzhi.c

#include <ansi.h>

inherit ITEM;

int cure_ob(string);
void init();

void create()
{
        set_name(HIW "灵芝" NOR, ({"ling zhi", "zhi"}));
        set_weight(20);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "枚");
                set("long", HIW"这是一枚灵芝，长约四寸，如伞状，通体晶白。\n"NOR);
                set("value", 20000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("cool_drug") > 0){
        addn("max_jingli", -1, me);
        addn("eff_jingli", -1, me);
        message_vision(HIR "$N吃下一枚灵芝，只觉得头重脚轻，摇摇欲倒，原来服食太急太多，药效适得其反！\n" NOR, me);
        destruct(this_object());
        return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("jingli",query("max_jingli",  me), me);
        set("qi",query("max_qi",  me), me);
        set("neili",query("max_neili",  me), me);
        
        message_vision(HIG "$N吃下一枚灵芝，只觉得精神健旺，气血充盈，体内真力源源滋生，甚至不再感到饥饿干渴! \n" NOR, me);

        me->apply_condition("cool_drug", 30);
        destruct(this_object());
        return 1;
}