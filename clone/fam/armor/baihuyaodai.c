#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIW "白虎腰带" NOR, ({ "baihu belt", "belt", "baihu" }));
        set_weight(4000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIY "一根用神兽白虎之筋做成的腰带，虎虎生威，令人不敢贸然接近。\n" NOR
                            HIC "有效招架修正：+ 10        有效轻功修正：+ 10\n" NOR
                            HIC "抗毒效果修正：+ 5%        防御效果等级：  40\n" NOR
                            HIC "抗毒回避修正：+ 5%\n" NOR);
                set("unit", "根");
                set("value", 500000);
                set("armor_prop/armor", 40);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", HIW "$N" HIW "轻轻地把$n"
                    HIW "系在腰间。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从腰间取了下来。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}