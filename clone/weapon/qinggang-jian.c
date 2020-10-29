#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(NOR + CYN "青罡剑" NOR, ({ "qinggang jian", "qinggang", "jian" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", NOR + CYN "这是一柄生铁和青铜铸造成的宝剑，颇为锋利。\n" NOR);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
                set("value", 100000);
        }
        init_sword(300);
        setup();
}

int query_autoload()
{
        return 1;
}