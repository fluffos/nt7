#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIM "嫦娥仙子图" NOR, ({ "change tu", "cange", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "嫦娥奔月的图样");
                set("can_tattoo", ({ "脸部"}));
                set("tattoo_type", ({ "容貌" }));
                set("tattoo_per", 5);
                                set("scborn", 1);
        }
}