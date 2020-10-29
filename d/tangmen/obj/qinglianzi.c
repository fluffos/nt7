#include <weapon.h>
#include <ansi.h>
inherit THROWING;
void create()
{
        set_name("青莲子", ({ "qing lianzi", "lianzi" }) );
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("value",2000);
                set("base_unit", "粒");
                set("base_weight",20);
                set("base_value", 80);
                set("material", "stone");
                set("long", "一粒长的象莲子一样的圆石头。\n");
                
        }
       set_amount(25);
       init_throwing(20);
       setup();
}