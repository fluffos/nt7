#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "王者之心" NOR, ({ "wangzhe zhixin", "wangzhe", "stone" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIR "这是一颗晶莹无瑕的宝石，据说拥有着奇幻的力量，是用来绿化套装的必备材料。\n" NOR); 
                set("unit", "块");
                set("value", 500000);
                set("no_sell", 1);
                set("auto_load", 1);
        }
        setup();
}
