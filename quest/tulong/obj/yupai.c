#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIG "翠玉牌" NOR, ({ "yupai" }));
        set("long", "\n这是一块翠绿色的玉牌，晶莹光洁，完美无瑕，好一块绝世好玉。\n"+
         "玉身成椭圆状，正中有"+HIR"海枯石烂"NOR+"四个篆体小字。\n");
        set("weight", 300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("value", 50000);
                set("material", "玉");
                set("armor_prop/armor", 2);
                set("female_only", 1);
        }
        setup();
}