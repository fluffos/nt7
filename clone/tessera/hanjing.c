#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIW "神之寒晶·冰" NOR, ({"shenzhi hanjing", "shenzhi", "hanjing"}));
        set_weight(300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIW "寒气笼罩在四周，令人不敢接近，乃天界极寒之圣物，拥有着神奇的力量。\n" NOR);
                set("unit", "块");
                set("value", 12000);
                set("can_be_enchased", 1);
                set("enchase/type", "all");
                set("enchase/cur_firm", 100); 
                set("enchase/SN", 1 + random(9));
                set("enchase/weapon_prop", ([
                        "add_cold" : 50,     
                        "add_skill" : 30,     
                ]));
                set("enchase/armor_prop", ([
                        "add_cold" : 50,     
                        "add_skill" : 30,     
                ]));
                set("magic/type", "cold");
                set("magic/power", 90 + random(11));
        }
        setup();
}

int query_autoload()
{
        return 1;
}