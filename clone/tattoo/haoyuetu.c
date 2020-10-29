#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(HIY "浩月天尊图" NOR, ({ "tianzun tu", "tianzun", "tu" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 10000000);
                set("material", "paper");
                set("tattoo_long", "浩月天尊的模样");
                set("can_tattoo", ({ "胸口"}));
                set("tattoo_type", ({ "根骨" }));
                set("tattoo_con", 6);
                                set("addtihui", 10000);
                                set("scborn", 1);
        }
}