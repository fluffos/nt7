// toukui.c 头盔
 
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIM "战神头盔" NOR, ({ "zhanshen toukui", "zhanshen", "toukui" }) );
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "steel");
                set("unit", "顶");
                set("long", HIM "这是一顶铁制的头盔，用以保护头部。\n" NOR);
                set("value", 1500000);
                set("armor_prop/armor", 100);
        }
        setup();
}

int query_autoload()
{
        return 1;
}