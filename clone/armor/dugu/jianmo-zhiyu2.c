#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIC "剑魔之羽" NOR, ({ "jianmo zhiyu2", "zhiyu2", "jianmo" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("long", HIC "这是由独孤求败取神雕羽毛精心制作而成的头饰，其中似乎蕴涵了高深的武学真谛。\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 35);
                set("armor_prop/str", 35);
                set("armor_prop/con", 35);
                set("armor_prop/damage", 4000);
                set("armor_prop/sword", 80);
                set("special/desc", "有效剑法等级提高80级。");
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