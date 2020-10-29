#include <armor.h>
#include <ansi.h>

inherit MEDAL2;


void create()
{
        set_name(HIG "转世勋章（神剑）" NOR, ({ "shenjian xunzhang", "shenjian", "xunzhang" }));
        set("long", HIG "转世后获得的勋章，上绘神剑刺月图，闪闪发亮，甚是精致。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 500);
                set("armor_prop/str", 10);
                set("armor_prop/scborn", 1);
                set("armor_prop/sword", "apply_armor() * 3");
                set("special/desc", HIR "用莫邪圣符升级后可镶嵌提高有效剑法等级。" NOR); 
                set("limit", ([
                        "scborn" : 1, 
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}