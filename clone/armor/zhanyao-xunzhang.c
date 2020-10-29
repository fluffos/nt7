#include <armor.h>
#include <ansi.h>

int is_xunzhang() { return 1; } 
inherit MEDAL;

void create()
{
        set_name(HIG "斩妖勋章" NOR, ({ "zhanyao xunzhang", "zhanyao", "xunzhang" }));
        set("long", HIG "斩杀千年九头蛇精后获得的勋章，非常珍贵，乃勇者的象征。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 200);
                set("armor_prop/zhanyao", 1);
                set("special/desc", HIR "佩带后可增加神龙岛杀怪经验及潜能奖励10%。" NOR);
                set("armor_prop/con", 6);
                set("armor_prop/dex", 6);
                set("armor_prop/str", 6);
                set("armor_prop/int", 6);

        }
        set("enchase/SN", "zyxz");
        setup();
}        

int query_autoload()
{
        return 1;
}
