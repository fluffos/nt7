#include <armor.h>
#include <ansi.h>

inherit MEDAL2;

void create()
{
        set_name(HIW "转世勋章（无极）" NOR, ({ "wuji xunzhang", "wuji", "xunzhang" }));
        set("long", HIW "转世后获得的勋章，上绘天地无极图，闪闪发亮，甚是精致。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 500);
                set("armor_prop/dex", 10);
                set("armor_prop/int", 10);
                set("armor_prop/scborn", 1);
                set("armor_prop/dodge", "apply_armor() * 2");
                set("armor_prop/parry", "apply_armor() * 2");
                set("special/desc", HIR "用莫邪圣符升级后可镶嵌提高有效轻功及有效招架等级。" NOR); 
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