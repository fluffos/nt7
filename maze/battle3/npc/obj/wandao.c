// gangdao.c
#include <weapon.h>
inherit BLADE;
#include <ansi.h>
void create()
{
        set_name(HIW"回风刀"NOR, ({ "wan dao","dao","blade" }));   
        set_weight(12000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "这是一柄锋利的回风刀，是宫中侍卫的常备武器。\n");
                set("value", 10000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回刀鞘。\n");
        }
        init_blade(200);
        setup();                   
}