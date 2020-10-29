#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIW "水晶冠" NOR, ({ "shuijing guan", "shuijing", "guan" }) );
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "steel");
                set("unit", "顶");
                set("long", HIM "这是一顶用水晶雕琢而成的头冠，手工精巧无比，人间罕有。\n" 
                            HIC "佩带后可提高研究及学习次数上限10%。\n" NOR);
                set("value", 3500000);
                set("armor_prop/armor", 100);
                set("armor_prop/yanjiu_times", 10);
                set("special/desc", HIR "佩带后可提高研究及学习次数上限10%。" NOR);
                set("require", ([
                        "int"             :  30,
                        "exp"             :  5000000,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}