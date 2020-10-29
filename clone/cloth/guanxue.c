// /clone/armor/guanxue.c   官靴 -3

#include <armor.h>
#include <ansi.h>

inherit BOOTS;
void create()
{
        set_name(HIW"官靴"NOR, ({ "guan xue", "xue","shoes" }));
        set_weight(150);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long","这是一双朝廷官员惯用的官靴。\n");
                set("unit", "双");
                set("no_transfer",1);
                set("material", "cloth");
                set("armor_type", "feet");
                set("armor_prop/dodge", 2);
        }
        setup(); 
}