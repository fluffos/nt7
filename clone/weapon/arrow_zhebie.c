// 哲别专用箭
 
#include <weapon.h>
#include <ansi.h>

inherit THROWING;

int is_arrow() { return 1; }
int is_arrow_zhebie() { return 1;} // 来自 /clone/weapon/bow.c 调用

void create()
{
        set_name(HIR "神雕雨箭" NOR, ({ "arrow", "jian" }));
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "一根用神雕羽毛作成的箭，锋利无比，只有蒙古哲别才配拥有。\n" NOR);
                set("unit", "把");
                set("base_unit", "根");
                set("base_weight", 100);
                set("base_value", 200);
                       set("wound_percent", 300);                       
        }

        set_amount(1);
        init_throwing(3000);
        setup();

        set("no_wield", "这不是用来装备的。\n");
}