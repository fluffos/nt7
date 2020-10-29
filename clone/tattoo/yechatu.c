#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIW "夜叉魑魅图" NOR, ({ "yecha tu", "yecha", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "夜叉和魑魅模样");
                set("can_tattoo", ({ "后背"}));
                set("tattoo_type", ({ "臂力" }));
                set("tattoo_str", 10);
                                set("tattoo_dex", -8);
                                set("scborn", 1);
        }
}