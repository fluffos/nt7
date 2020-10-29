#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIC "蓝蝶宝剑" NOR, ({ "landie jian", "landie", "jian" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", HIC "这是一柄充满传说的宝剑，乃由崆峒仙境的蓝蝶仙子的眼泪所化，由爱生悲，蓝蝶宝剑蕴藏着巨大的威力。\n" NOR);
                set("value", 2000);
                set("limit", ([
                         "exp" : 2088888888,
                         //"thborn" : 1,
                         "str" : 700,
                         "dex" : 700,
                         "int" : 700,
                         "con" : 700,
                ]));
                set("material", "steel");
                set("wield_msg", "一道蓝色的剑芒闪过，只见剑芒化作一直蓝色的蝴蝶，光芒退去$N" HIC "手中却多了一把宝剑。\n");
                set("unwield_msg", HIC "$N" HIC "一声长叹，$n化作一缕蓝色青烟消失了。\n" NOR);
        }
        init_sword(5000);
        setup();
}