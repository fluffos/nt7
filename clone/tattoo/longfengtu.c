#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIR "龙飞凤舞图" NOR, ({ "longfeng tu", "longfeng", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "龙凤双飞的景象");
                set("can_tattoo", ({ "右臂"}));
                set("tattoo_type", ({ "命中等级" }));
                                set("tattoo_attack", 100);
                                set("scborn", 1);
        }
}