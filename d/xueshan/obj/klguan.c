// huyao.c

#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name( BLU "骷髅冠" NOR, ({ "kulou guan", "guan" }) );
        set_weight(300);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "顶");
                set("long", "这是一顶骷髅做的宝冠。\n");
                set("value", 500);
                set("material", "head");
                set("armor_prop/armor", 10);
        }
        setup();
}



