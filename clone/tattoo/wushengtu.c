#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIR "武圣奔雷图" NOR, ({ "wusheng tu", "wusheng", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "武圣练功的图样");
                set("can_tattoo", ({ "胸口"}));
                set("tattoo_type", ({ "臂力" }));
                set("tattoo_str", 6);
                                set("addfuzhong", 100000);
                                set("scborn", 1);
        }
}