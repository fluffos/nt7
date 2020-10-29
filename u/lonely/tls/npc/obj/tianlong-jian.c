// tianlong-jian.c 天龙神剑

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name("天龙剑",({ "tianlong jian", "tianlong", "sword", "jian" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 100000);
                set("treasure",1);
                set("material", "steel");
                set("long", "这是把式样古朴的宝剑，不知道有多少年头了，整个剑身隐藏在一层青气当中，充满杀气。\n");
                set("wield_msg", HIY "只听见「铮」地一声，眼前一道青光冲天而起,$N抽出天龙神剑，剑身如水，流转不定。\n" NOR);
                set("unwield_msg", HIY "一股青芒「唰」地隐入剑鞘,杀气顿然消失。\n" NOR);
                set("unequip_msg", HIY "一股青芒「唰」地隐入剑鞘,杀气顿然消失。\n" NOR);
        }
init_sword(180);
        setup();
}
