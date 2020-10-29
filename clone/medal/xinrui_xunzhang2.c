#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIW "新锐白银勋章" NOR, ({ "xinrui silver medal", "xinrui", "xunzhang" }));
        set("long", HIW "华山论剑新锐组第二获得的勋章，非常珍贵，乃少年强者的象征。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 150000);
                set("material", "silver");
                set("armor_prop/research_times", 100);
                set("armor_prop/practice_times", 100);
                //set("armor_prop/derive_times", 100);
                
        }
        set("enchase/SN", "xr2");
        set("bindable", 2);
        set("auto_load", 1);
        setup();
}