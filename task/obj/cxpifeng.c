#include <ansi.h>
#include <armor.h>
inherit TASK;
void create()
{
        set_name(HIR"彩霞披风"NOR, ({ "cxpifeng" }) );
        set_weight(3000);
        if( clonep() )
            destruct(this_object());
        else {
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 2);
                set("armor_prop/spells", 3);
        }
        set("owner", "任盈盈");
        setup();
}
