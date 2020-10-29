#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIR "剑魔" HIC "之羽" NOR, ({ "jianmo zhiyu6", "zhiyu6", "jianmo" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("long", HIW "这是由独孤求败取神雕羽毛精心制作而成的头饰，其中似乎蕴涵了高深的武学真谛。\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 50);
                set("armor_prop/str", 50);
                set("armor_prop/con", 50);
                set("armor_prop/damage", 7000);
                set("armor_prop/sword", 300);
                set("special/desc", "有效剑法等级提高300级。");
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