#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIW "天降·狂风靴" NOR, ({ "kuangfeng xue3" }) );
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "双");
                set("long", HIW "这是一双西域银狐之皮制成的靴子，据说穿上后行走如狂风。\n");
                set("value", 2000000);
                
                set("armor_prop/dex", 60); //后天身法+60
                set("armor_prop/dodge", 300);
                set("special/desc", "有效轻功等级提高300级。");
                set("material", "boots");
                set("limit", ([
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}