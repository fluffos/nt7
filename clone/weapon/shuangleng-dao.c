#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(NOR + CYN "霜冷宝刀" NOR, ({ "shuangleng dao", "shuangleng", "dao" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", NOR + CYN "刀柄上的小篆写着：亮如霜雪，挥洒之间漫天银雨。出鞘之时，无血不归，十步之内，谁与争锋！。\n"
                                                      "此刀为炎黄非自造兵器宝刀排名第三位。\n" NOR);
                set("material", "steel");
                set("wield_msg", NOR + CYN "$n寒光一闪，已然出鞘。\n" NOR);
                set("unwield_msg", NOR + CYN "$n回鞘，天地顿时暗淡。\n" NOR);
                                set("value", 100000);
        }
        init_blade(800);
        setup();
}

int query_autoload()
{
        return 1;
}