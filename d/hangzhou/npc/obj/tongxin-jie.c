// fu

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIR"同心结" NOR, ({ "tongxin jie", "jie" }));
               set("long", "一个鲜红色的中国结，象征着有情人永结同心。\n");
        set("weight", 100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "个");
                set("value", 5000);
                set("material", "丝");
                set("armor_prop/armor", 2);
                }
        setup();
}        