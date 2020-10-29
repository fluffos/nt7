// l襄阳保卫战，哲别专用弓

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name(HIW "大漠之鹰" NOR, ({ "damo bow", "bow", "damo", "gong" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "张");
                set("long", HIW "一张用黄金打造的长弓，上面雕刻着一只飞翔的鹰，此弓产自大漠，乃神弓。\n");
                set("value", 80000);
                set("accuracy", 100000);   // 准确度，几乎100%命中
        }
        setup();
}
