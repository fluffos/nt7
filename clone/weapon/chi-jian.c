#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIR "炽剑" NOR, ({ "chi jian" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("long", NOR + HIR "这是一把浑身火红的剑，提在手中感觉炽热无比。\n" NOR);
                set("material", "tian jing");
                set("wield_msg", "$N「唰」的一声抽出一把$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
                set("value", 100000);
        }
        init_sword(800);
        setup();
}