#include <armor.h>
#include <ansi.h>

inherit MEDAL2;

void create()
{
        set_name(HIM "转世勋章（空明）" NOR, ({ "kongming xunzhang", "kongming", "xunzhang" }));
        set("long", HIM "转世后获得的勋章，上绘千手观音空明静思图，闪闪发亮，甚是精致。\n" NOR);
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
                set("armor_prop/unarmed", "apply_armor() * 3");
                set("armor_prop/finger", "apply_armor() * 3");
                set("armor_prop/strike", "apply_armor() * 3");
                set("armor_prop/hand", "apply_armor() * 3");
                set("armor_prop/cuff", "apply_armor() * 3");
                set("armor_prop/claw", "apply_armor() * 3");
                set("special/desc", HIR "用莫邪圣符升级后可镶嵌提高所有空手技能有效等级。" NOR); 
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