// metal.c 精金

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "精金" NOR, ({ "jing jin", "metal" }) );
        set_weight(30);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIW "这是一枚精金，由西方庚辛之气凝结而成，色银白，坚不可摧。\n" NOR);
                set("value", 2000);
                set("unit", "枚");
                set("magic/element", "metal");
        }
        setup();
}