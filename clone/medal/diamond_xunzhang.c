#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; }
inherit MEDAL;

void create()
{
        set_name(HIW "钻石勋章" NOR, ({ "diamond xunzhang", "diamond", "xunzhang", "medal" }));
        set("long", HIW "为泥潭做出重大贡献而获得的勋章，非常珍贵，乃睿者的象征。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/learn_times", 300);
                set("armor_prop/research_times", 500);
                set("armor_prop/practice_times", 500);
                set("armor_prop/derive_times", 500);
        }
        set("enchase/SN", "dm1");
        set("bindable", 1); // 装备绑定
        set("auto_load", 1);
        setup();
}
