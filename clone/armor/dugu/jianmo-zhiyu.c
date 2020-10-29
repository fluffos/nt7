#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIM "剑魔之羽" NOR, ({ "jianmo zhiyu", "zhiyu", "jianmo" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("long", HIM "这是由独孤求败取神雕羽毛精心制作而成的头饰，其中似乎蕴涵了高深的武学真谛。\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 30);
                set("armor_prop/str", 30);
                set("armor_prop/con", 30);
                set("armor_prop/damage", 3000);
                set("armor_prop/sword", 50);
                set("special/desc", "有效剑法等级提高50级。");
                set("limit", ([ 
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}