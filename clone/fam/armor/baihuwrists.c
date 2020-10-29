#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
        set_name(HIW "神虎护腕" NOR, ({ "baihu huwan", "huwan", "baihu" }));
        set_weight(800);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "一双用白虎骨和白虎皮做成的护腕。\n" NOR
                            HIC "有效招架修正：+ 10       有效轻功修正：  + 5\n" NOR
                            HIC "抗毒效果修正：+ 5%       防御效果等级：   10\n" NOR
                            HIC "抗毒回避修正：+ 5%\n" NOR);
                set("unit", "双");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", HIW "$N" HIW "轻轻地把$n"
                    HIW "戴在手腕上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从手腕上取了下来。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}