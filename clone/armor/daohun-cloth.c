#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIW "噬魂战衣" NOR, ({ "shihun zhanyi"}) );
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("long", HIW "一件奇异的战衣，通体透明，飘忽不定，似乎不属于人间。\n" NOR);
                set("material", "steel");
                set("value", 1);
                set("armor_prop/armor", 100);
                set("armor_prop/str", 5);
                set("armor_prop/con", 5);
        }
        setup();
}
