#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name( HIY  "日月金轮" NOR,({ "riyue jinlun" ,"lun" ,"jinlun" }));
        set_weight(5000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("unique", 1);
                set("long",HIY"这是一柄金光闪闪的法轮。\n" NOR);
                set("value", 10000);
                set("material", "gold");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg","$N将手中的$n放回腰间。\n");
        }
        init_hammer(200);
        setup();
}