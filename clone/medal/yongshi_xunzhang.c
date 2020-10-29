#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIY "勇士勋章" NOR, ({ "yongshi xunzhang", "yongshi", "xunzhang", "medal" }));
        set("long", HIR "勇士勋章，非常珍贵，乃勇者的象征。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 100000);
                set("material", "gold");
                set("armor_prop/learn_times", 300);
                set("armor_prop/research_times", 300);
                set("armor_prop/practice_times", 300);
                set("armor_prop/derive_times", 300);
        }
        set("enchase/SN", "ys1");
        set("bindable", 1); // 装备绑定
        set("auto_load", 1);
        setup();
}
