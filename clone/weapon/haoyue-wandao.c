#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(HIY "浩月弯刀" NOR, ({ "haoyue wandao" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", NOR + WHT "这是一柄亮晃晃的弯刀，到柄上雕刻着一个月亮。\n" NOR);
                set("material", "tian jing");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回刀鞘。\n");
                set("value", 100000);
        }
        init_blade(600);
        setup();
}