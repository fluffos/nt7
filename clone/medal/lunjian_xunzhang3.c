#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIC "论剑青铜勋章" NOR, ({ "lunjian bronze medal", "lunjian", "xunzhang" }));
        set("long", HIC "华山论剑天下第三获得的勋章，非常珍贵，乃强者的象征。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 100000);
                set("material", "bronze");
                set("armor_prop/research_times", 300);
                //set("armor_prop/practice_times", 300);
                //set("armor_prop/derive_times", 300);
        }
        set("enchase/SN", "lj3");
        set("bindable", 2);
        set("auto_load", 1);
        setup();
}