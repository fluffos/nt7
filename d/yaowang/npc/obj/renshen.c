#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL"人参"NOR, ({"ren shen", "shen"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "棵");
                set("long", "这是一棵人参，足有七两多重。\n");
                set("yaowang", 1);
                set("dig", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}