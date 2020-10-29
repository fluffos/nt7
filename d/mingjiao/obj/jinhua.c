#include <ansi.h>
#include <weapon.h>
inherit THROWING;

void create()
{
       set_name(HIY "金花" NOR, ({"jin hua", "jin", "hua" }));
       /*if( clonep() )
               set_default_object(__FILE__);
       else*/ {
                set("long", "一串金光灿烂，闪闪发光的，黄金铸成的梅花。\n");               
               set("unit", "串");
               set("base_value", 10000);
               set("base_unit", "颗");
               set("base_weight", 10);
       }
       set_amount(81);
       init_throwing(20);
}
