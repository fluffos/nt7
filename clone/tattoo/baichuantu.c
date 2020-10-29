#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIG "百川经络图" NOR, ({ "baichuan tu", "baichuan", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "俯瞰百川的情景");
                set("can_tattoo", ({ "左臂"}));
                set("tattoo_type", ({ "内力上限" }));
                                set("tattoo_addneili", 2000);
                                set("tattoo_addjingli", -500);
                                set("scborn", 1);
        }
}