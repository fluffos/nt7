#include <armor.h>
#include <ansi.h>
inherit TASK;

void create()
{
        set_name( HIB "八卦道袍" NOR, ({ "daopao" }) );
        set_weight(3000);
        if( clonep() )
            destruct(this_object());
        else {
                set("unit", "件");
                set("long", "这是一件画有八卦的袍\n");
                set("value", 1000);
                set("material", "cloth");
                set("armor_prop/armor", 2);
        }
        set("owner", "胖头陀");
        setup();
}
