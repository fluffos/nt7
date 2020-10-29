#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIR "凤凰头冠" NOR, ({ "fenghuang touguan", "touguan", "fenghuang" }));
        set_weight(4000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "一顶用火凤凰羽毛和凤凰角做成的头冠，透射出一道摄人心魄的光芒。\n" NOR
                            HIC "有效招架修正：+ 10        有效轻功修正： + 5\n" NOR
                            HIC "抗毒效果修正：+ 5%       防御效果等级：  10\n" NOR
                            HIC "抗毒回避修正：+ 5%\n" NOR);
                set("unit", "顶");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 5);
                set("armor_prop/parry", 10);
                set("wear_msg", HIR "$N" HIR "轻轻地把$n"
                    HIR "戴在头上，刹那间光华四射。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从腰间取了下来。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}