#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(NOR + YEL "黄符纸" NOR, ({ "huangfu zhi", "huangfu", "zhi" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "张");
                set("long", NOR + YEL "一张泛黄的符纸，上面用红色的颜料绘着各种奇怪的符号。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/qy", 5);

        }
        setup();
}

int query_autoload()
{
        return 1;
}