// fu

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIC"玄女灵符" NOR, ({ "xuannv-lingfu", "lingfu" }));
               set("long", "一张普普通通的符纸，据说是九天玄女开过光的，可以保佑婚姻顺利。\n");
        set("weight", 100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "张");
                set("value", 5000);
                set("material", "纸");
                set("armor_prop/armor", 2);
                }
        setup();
}        