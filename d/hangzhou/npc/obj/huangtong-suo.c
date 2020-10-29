// fu

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(YEL"黄铜锁" NOR, ({ "huangtong suo", "suo" }));
               set("long", "又名同心锁，寓意锁住情人的心。\n");
        set("weight", 1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("value", 5000);
                set("material", "铜");
                set("armor_prop/armor", 2);
                }
        setup();
}        