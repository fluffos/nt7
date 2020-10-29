#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIW "开天辟地图" NOR, ({ "kaitian tu", "kaitian", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "盘古开天辟地的景象");
                set("can_tattoo", ({ "右臂"}));
                set("tattoo_type", ({ "伤害等级" }));
                                set("tattoo_damage", 100);
                                set("scborn", 1);
        }
}