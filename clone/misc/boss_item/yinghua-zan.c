inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "《樱花赞》" NOR, ({"yinghua zan", "yinghu", "zan"}));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
                set("long", HIM "这是一本写有《樱花赞》的曲谱。\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}