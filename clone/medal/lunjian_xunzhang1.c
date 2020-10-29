#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIY "论剑黄金勋章" NOR, ({ "lunjian gold medal", "lunjian", "xunzhang" }));
        set("long", HIY "华山论剑天下第一获得的勋章，非常珍贵，乃强者的象征。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/research_times", 300);
                set("armor_prop/practice_times", 300);
                set("armor_prop/derive_times", 300);
        }
        set("enchase/SN", "lj1");
        set("bindable", 2);
        set("auto_load", 1);
        setup();
}