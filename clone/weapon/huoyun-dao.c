#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(NOR + HIR "火云刀" NOR, ({ "huoyun dao", "huoyun", "dao" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一把$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回刀鞘。\n");
        }
        init_blade(1200);
        setup();
}
