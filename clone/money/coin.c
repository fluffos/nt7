// coin.c

#include <weapon.h>
#include <ansi.h>

inherit MONEY;
inherit F_EQUIP;

void create()
{
        set_name(HIY "铜板" NOR, ({"coin", "coins", "coin_money" }));
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("money_id", "coin");
                set("long", "这是流通中单位最小的货币，约要一百个铜板才值得一两银子。\n");
                set("unit", "串");
                set("base_value", 1);
                set("base_unit", "个");
                set("base_weight", 30);
                set("consistence", 100);

                set("weapon_prop/damage", 10);
                set("flag", 2);
                set("wield_msg", "$N从袖口取出一串$n抛了抛，握在手中。\n");
                set("unwield_msg", "$N将手中的$n放回兜里。\n");
                set("skill_type", "throwing");
                if( !query("actions") ) {
                    set("actions", (: call_other,WEAPON_D, "query_action" :));
                    set("verbs", ({ "throw" }) );
                }
        }
        set_amount(1);
}