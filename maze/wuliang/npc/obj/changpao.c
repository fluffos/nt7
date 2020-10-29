// changpao.c 长袍

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name("长袍", ({ "chang pao", "pao" ,"cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                set("long","一件有普通布料制成的长袍。\n");
                set("value", 100);
                set("armor_prop/armor", 5);
        }
        setup();
}