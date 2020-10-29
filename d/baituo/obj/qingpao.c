#include <ansi.h> 
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("青色丝袍", ({ "si pao", "cloth", "pao" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("long", HIG "这是件质地轻柔的青色镂花丝袍，特别受女性青睐。\n" NOR);
                set("material", "cloth");
                set("armor_prop/armor", 8);
                set("value", 100);
        }
        setup();
}