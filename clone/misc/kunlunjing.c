#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIW "昆仑镜" NOR, ({ "kunlun jing", "kunlun", "jing" }) );
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "面");
                set("long", HIW "这是一面通体银光的镜子，据说拥有破开太虚的能力。\n" NOR);
        }

        setup();
}