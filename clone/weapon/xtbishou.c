#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(CYN "玄铁" WHT "匕首" NOR,  ({ "bi shou", "sword", "jian" }));

        set_weight(12000);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("no_sell", "这柄烂剑你自个留着吧。\n");
                set("value", 100000);
                set("material", "xuantie");
                set("wield_msg", HIR "$N" HIR "抽出一柄黑黝黝的"
                                 "匕首拿在手中，只感到一阵寒气扑面而来。\n" NOR);
                set("unwield_msg", HIR "$N" HIR "将手中的匕首插回靴中。\n" NOR);
                set("stable", 100);
        }

        init_sword(200);

        setup();
        // move("/d/beijing/aofu_mishi");
}