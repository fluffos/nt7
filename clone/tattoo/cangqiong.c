#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIG "苍穹月华图" NOR, ({ "cangqiong tu", "cangqiong", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "浩瀚的宇宙月挂高空");
                set("can_tattoo", ({ "胸口"}));
                set("tattoo_type", ({ "身法" }));
                set("tattoo_dex", 6);
                                set("tattoo_special", "agile");
                set("tattoo_spcname", "如鬼似魅");
                                set("scborn", 1);
        }
}