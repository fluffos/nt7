#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIR "凤凰腰带" NOR, ({ "fenghuang belt", "belt", "fenghuang" }));
        set_weight(4000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "一根用火凤凰之筋做成的腰带，透射出一道摄人心魄的光芒。\n" NOR
                            HIC "有效招架修正：+ 10        有效轻功修正：+ 20\n" NOR
                            HIC "抗毒效果修正：+ 5%        防御效果等级：  30\n" NOR
                            HIC "抗毒回避修正：+ 5%\n" NOR);
                set("unit", "根");
                set("value", 500000);
                set("armor_prop/armor", 40);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 20);
                set("armor_prop/parry", 10);
                set("wear_msg", HIR "$N" HIR "轻轻地把$n"
                    HIR "系在腰间。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从腰间取了下来。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}