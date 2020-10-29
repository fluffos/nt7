#include <ansi.h>
#include <armor.h>
inherit CLOTH;
void create()
{
        set_name(BLK"重钢战甲"NOR, ({ "zhonggang zhanjia","jia" }) );   
        set_weight(20000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("material", "gold");
                set("value", 1000000);
                set("armor_prop/armor", 500);
                set("no_steal",1);
                set("no_get",1);
                set("no_put",1);    
        }
        setup();
}