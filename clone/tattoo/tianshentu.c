#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIY "真龙天神图" NOR, ({ "tianshen tu", "tianshen", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "真龙天神的模样");
                set("can_tattoo", ({ "脸部"}));
                set("tattoo_type", ({ "容貌" }));
                set("tattoo_per", 5);
                                set("scborn", 1);
        }
}