
#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; } 
inherit MEDAL;

void create()
{
        set_name(HIM "幸运勋章" NOR, ({ "lucky xunzhang", "lucky", "xunzhang" }));
        set("long", HIM "祝福您在2016年幸运通达、吉祥如意的勋章，非常珍贵，乃幸运吉祥的象征。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/armor", 21000);
                set("armor_prop/magic_find", 100);
                set("armor_prop/lucky2016", 1);
                set("special/desc", HIR "佩带后可增加突破每次技能升级上限的机会。" NOR);

        }
        set("enchase/SN", "jxxz");
        setup();
}        

int query_autoload()
{
        return 1;
}

