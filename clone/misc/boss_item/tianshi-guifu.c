inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + YEL "天师鬼符" NOR, ({"tianshi guifu", "tianshi", "guifu"}));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "张");
                set("long", NOR + YEL "这是一张道符，乃张天师为了降伏鬼怪而制。\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}