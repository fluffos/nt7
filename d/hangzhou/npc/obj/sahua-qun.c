// womancloth
// by ruri

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIR"撒花百褶裙"NOR, ({ "sahua qun", "qun" }) );
        set_weight(3000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("long", "一件鲜艳夺目的百褶裙，式样简单大方。\n");
                set("material", "cloth");
                set("value", 0);
                set("armor_prop/armor", 3);
                set("female_only", 1);
        }
        setup();
}