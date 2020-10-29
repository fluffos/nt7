#include <armor.h>
#include <ansi.h>

inherit MEDAL3;

void create()
{
        set_name(HIY "炎黄风雨十年纪念勋章" NOR, ({ "yhhero year10", "yhhero", "year10" }));
        set("long", HIY "为纪念炎黄运营十周年，“风雨十年”活动特别限量发行的纪念勋章！\n" NOR);
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/year10", 1);
                set("armor_prop/damage", 4000);
                set("armor_prop/armor", 4000);
                set("armor_prop/force", 200);
                set("armor_prop/add_yanjiu_times", 100);
                set("special/desc", HIR "佩带后可增加神龙岛杀怪经验及潜能奖励5%\n"
                                        "                  额外提升100次研究次数\n"
                                        "                  有效内功提升200级" NOR);
                set("armor_prop/con", 40);
                set("armor_prop/dex", 40);
                set("armor_prop/str", 40);
                set("armor_prop/int", 40);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}