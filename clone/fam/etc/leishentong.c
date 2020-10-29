inherit ITEM;
#include <ansi.h>

int is_enchase_ob() { return 1; } 
void create()
{
        set_name(HIM "雷神之瞳·电" NOR, ({"leishen tong", "leishen", "tong"}));
        set_weight(300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIM "顷刻间，七彩之光透射天地，此乃天界之圣物，拥有着神一般的力量。\n" NOR);
                set("unit", "颗");
                set("value", 12000);
                set("can_be_enchased", 1);
                set("enchase/cur_firm", 100); 
                set("enchase/type", "all");
                set("enchase/SN", 1 + random(9));
                set("enchase/wspe_data", ([
                        "add_lighting" : 50,     
                        "add_skilllevel" : 30,     
                ]));
                set("enchase/aspe_data", ([
                        "add_lighting" : 50,     
                        "add_skilllevel" : 30,     
                ]));
                set("magic/type", "lighting");
                set("magic/power", 90 + random(11));
        }
        setup();
}

int query_autoload()
{
        return 1;
}