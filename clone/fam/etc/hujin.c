#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIW "白虎筋" NOR, ({ "tiger vein", "vein" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "一根白虎筋，乃制衣极品，世间罕有。可以将它系(wear)在腰间。\n" NOR
                            HIC "有效招架修正：+ 10        有效轻功修正：+ 10\n" NOR
                            HIC "抗毒效果修正：+ 3%        防御效果等级：  10\n" NOR
                            HIC "抗毒回避修正：+ 2%\n" NOR);
                set("unit", "根");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 2);
                set("armor_prop/reduce_poison", 3);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", HIW "$N" HIW "轻轻地把$n"
                    HIC "系在腰间。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从腰间取了下来。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}