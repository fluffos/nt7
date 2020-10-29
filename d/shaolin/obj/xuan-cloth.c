#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name("护法袈裟", ({ "jia sha", "jia", "sha" }));
        set_weight(8000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 30);
        }
        setup();
}