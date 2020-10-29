// ruanwei jia
#include <armor.h>
#include <ansi.h>
inherit ARMOR;
void create()
{
    set_name(WHT "软甲" NOR,({ "ruan jia","jia", }) );
    set_weight(1000);
    /*if( clonep() )
        set_default_object(__FILE__);
    else*/
    {
        set("unit", "件");
            set("long", "一件轻飘飘的、生满尖锐倒刺的护甲。\n");
            set("material", "copper");
            set("value",2000);
            set("armor_prop/armor", 75);
            set("armor_prop/dodge", -5);
    }
    setup();
}
