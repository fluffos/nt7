#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIW "文曲降世图" NOR, ({ "wenqu tu", "wenqu", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "文曲星下凡的图样");
                set("can_tattoo", ({ "胸口"}));
                set("tattoo_type", ({ "悟性" }));
                set("tattoo_int", 6);
                                set("addqianneng", 10000);
                                set("scborn", 1);
        }
}