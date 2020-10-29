// earth.c 玉髓

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "玉髓" NOR, ({ "yu sui", "earth" }) );
        set_weight(30);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", YEL "这是一块玉髓，受中央戊己土气所钟而生玉魄，色黄，入手温润。\n" NOR);
                set("value", 2000);
                set("unit", "块");
                set("magic/element", "earth");
        }
        setup();
}