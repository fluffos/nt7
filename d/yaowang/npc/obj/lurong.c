#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( YEL "鹿茸" NOR , ({"lu rong", "rong"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一支梅花鹿茸。\n");
                set("unit", "支");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
}