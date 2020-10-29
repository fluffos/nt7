#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIY "炎龙腰带" NOR, ({ "yanlong belt", "belt", "yanlong" }));
        set_weight(4000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIY "一根用北海神龙之筋做成的腰带，透射着令人敬畏的光芒。\n" NOR
                            HIC "有效招架修正：+  5        有效轻功修正：+ 15\n" NOR
                            HIC "抗毒效果修正：+ 5%        防御效果等级：  10\n" NOR
                            HIC "抗毒回避修正：+ 5%\n" NOR);
                set("unit", "根");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 15);
                set("armor_prop/parry", 5);
                set("wear_msg", HIY "$N" HIY "轻轻地把$n"
                    HIY "系在腰间。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从腰间取了下来。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}