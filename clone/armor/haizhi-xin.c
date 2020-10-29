#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIC "海之心" NOR, ({ "haizhi xin", "haizhi", "xin" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "串");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/damage", 100);
                set("armor_prop/con", 10);
        }
        setup();
}        

int query_autoload()
{
        return 1;
}