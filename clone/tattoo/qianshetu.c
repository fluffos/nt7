#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIG "千蛇缠身图" NOR, ({ "qianshe tu", "qianshe", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "无数只毒蛇缠绕的图样");
                set("can_tattoo", ({ "后背"}));
                set("tattoo_type", ({ "身法" }));
                set("tattoo_dex", 10);
                                set("tattoo_con", -6);
                                set("scborn", 1);
        }
}