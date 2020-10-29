#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; } 
inherit MEDAL;

void create()
{
        set_name(HIR "盗墓"HIY"勋章" NOR, ({ "daomu xunzhang", "daomu", "xunzhang" }));
        set("long", HIG "盗墓勋章，非常珍贵，可免疫秦皇陵墓里怪物的busy特技。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 200);
                set("armor_prop/daomu", 1);
                set("special/desc", HIR "佩带后可免疫秦皇陵墓里怪物的busy特技。" NOR);
                set("armor_prop/con", 6);
                set("armor_prop/dex", 6);
                set("armor_prop/str", 6);
                set("armor_prop/int", 6);

        }
        set("enchase/SN", "dmxz");
        setup();
}        

int query_autoload()
{
        return 1;
}
