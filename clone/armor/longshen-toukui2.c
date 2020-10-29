// toukui.c 头盔
 
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIM "龙神头盔" NOR, ({ "longshen toukui", "longshenshen2", "toukui2" }) );
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "steel");
                set("unit", "顶");
                set("long", HIM "这是一顶龙骨铸造的头盔，用以保护头部。\n" NOR);
                set("value", 3500000);
                set("armor_prop/armor", 300);
                set("limit", ([
                        "dex"    :   45,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}