// longsword.c 长剑

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIR "斩天之刃" NOR, ({ "zhantian zhiren", "zhantian", "zhiren" }));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", HIR "传说斩天之刃可以开天辟地，破气穿甲，无所不能。\n" NOR);
                set("value", 2000);
                set("material", "tian jing");
                set("wield_msg", HIR "「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        }
        init_sword(1000);
        setup();
}