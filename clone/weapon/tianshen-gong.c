// longbow.c

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name(HIY "天神弓" NOR, ({ "tianshen gong", "bow", "tianshen", "gong" }));
        set_weight(5000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "张");
                set("long", "这是一张巨大的弓，命曰：天神，传说乃上天赐予成吉思汗的宝物，据说此弓百发百中，例无虚发。。\n");
                                set("value", 80000);
                set("accuracy", 2000);   // 准确度150%
        }
        setup();
}