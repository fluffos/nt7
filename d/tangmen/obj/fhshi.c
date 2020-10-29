#include <weapon.h>
#include <ansi.h>
inherit THROWING;
void create()
{
        set_name("飞蝗石", ({ "feihuang shi", "shi" }) );
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("value", 500);
                set("base_unit", "粒");
                set("base_weight", 100);
                set("base_value", 25);
                set("material", "stone");
                set("long", "一块有棱有角的石头。\n");
                
        }
       set_amount(20);
       init_throwing(5);
       setup();
}