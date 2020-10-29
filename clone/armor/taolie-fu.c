#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(HIY "饕餮符" NOR, ({ "taolie fu", "taolie", "fu" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "张");
                set("long", HIY "这是一张道符，上面画着一个古怪的巨兽。\n" NOR);
                set("value", 10000);
                set("armor_prop/greedy", 1);
                set("special/desc", "5%几率打中对手降低对方食物及饮水量。");
        }
        setup();
}

int query_autoload()
{
        return 1;
}