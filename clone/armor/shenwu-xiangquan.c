// necklace.c 金项链

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIY "神武项圈" NOR, ({ "shenwu xiangquan", "shenwu", "xiangquan" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "串");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/armor", 300);
        }
        setup();
}        

int query_autoload()
{
        return 1;
}