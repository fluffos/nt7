
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "闭关符" NOR, ({ "closed charm", "charm" }) );
        set_weight(30);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", YEL "放在行囊中会让人脑袋开窍，加快闭关的速度...。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("autoload", 1);
                set("unit", "张");
        }

        setup();
}


