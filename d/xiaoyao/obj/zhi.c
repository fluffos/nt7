#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG"七宝指环"NOR, ({"zhihuan"}));
        set("unit", "个");
        set("long", "逍遥派掌门信物。\n");
        set("value", 0);
        setup();
}