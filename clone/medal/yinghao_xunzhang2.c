#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIW "英豪白银勋章" NOR, ({ "yinghao silver medal", "yinghao", "xunzhang" }));
        set("long", HIW "华山论剑英豪组第二获得的勋章，非常珍贵，乃强者的象征。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 150000);
                set("material", "silver");
                set("armor_prop/research_times", 150);
                set("armor_prop/practice_times", 150);
                //set("armor_prop/derive_times", 150);
                
        }
        set("enchase/SN", "yh2");
        set("bindable", 2);
        set("auto_load", 1);
        setup();
}