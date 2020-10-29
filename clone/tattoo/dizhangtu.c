#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIM "地藏转世图" NOR, ({ "dizhang tu", "dizhang", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "地藏王的模样");
                set("can_tattoo", ({ "后背"}));
                set("tattoo_type", ({ "根骨" }));
                set("tattoo_con", 10);
                                set("tattoo_int", -7);
                                set("scborn", 1);
        }
}