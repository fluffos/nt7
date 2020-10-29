#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIW "白袍" NOR, ({"chang pao", "cloth", "pao"}) );
    set_weight(2000);
    /*if( clonep() )
       set_default_object(__FILE__);
    else*/ {
        set("unit", "件");
                set("long", "这是件质量上佳的白色长袍。\n");
        set("material", "cloth");
        set("armor_prop/armor", 10);
        set("value",100);
    }
    setup();
}