// tiexiao.c 铁箫
#include <ansi.h>
#include <music.h> 

inherit ITEM;
inherit "/inherit/misc/_xiao";

void create()
{
        set_name(YEL "铁箫" NOR,({ "tie xiao", "xiao" }) );
        set_weight(5000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "支");
                set("value", 300);
                set("material", "steel");
                set("long", "一柄普通铁制洞箫，沉甸甸的有些坠手。\n");
        }
        setup();

}

void init() 
{
        add_action("play_xiao", "play"); 
}