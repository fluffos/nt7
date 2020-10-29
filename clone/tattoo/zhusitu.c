#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIR "莹血蛛丝图" NOR, ({ "zhusi tu", "zhusi", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "外形奇特蜘蛛吐着血红色的丝");
                set("can_tattoo", ({ "后背"}));
                set("tattoo_type", ({ "悟性" }));
                set("tattoo_int", 10);
                                set("tattoo_str", -8);
                                set("tattoo_per", -4);
                                set("scborn", 1);
        }
}