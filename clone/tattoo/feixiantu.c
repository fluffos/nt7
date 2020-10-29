#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIY "天外飞仙图" NOR, ({ "feixian tu", "feixian", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "群仙飞舞的情景");
                set("can_tattoo", ({ "臀部"}));
                set("tattoo_type", ({ "根骨", "悟性", "臂力", "身法" }));
                                set("tattoo_con", 2);
                                set("tattoo_dex", 2);
                                set("tattoo_str", 2);
                                set("tattoo_int", 2);
                                set("scborn", 1);
        }
}