#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"乾坤一气袋"NOR, ({"yiqi dai", "dai" }) );
        set_weight(1000);
        set_max_encumbrance(5000);
        
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/{
                set("unit", "个");
                set("long", "这是一个布袋样的袋子。非绸非革，坚韧异常，摸上去\n"
                        "布纹宛然，显是粗布所制，但撕上去却坚韧无比。\n");
                set("value", 10000);
                set("material","silk");
                set("treasure",1);
        }        
        setup();
}