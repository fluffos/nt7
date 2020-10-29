#include <armor.h>
#include <ansi.h>

inherit MEDAL;

void create()
{
        set_name(HIY "黄金荣誉勋章" NOR, ({ "gold medal" }));
        set("long", HIY "2005年参加炎黄9.18屠杀倭寇并获得冠军的纪念勋章。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/damage", 200);
                set("armor_prop/con", 10);
                set("armor_prop/dex", 10);
                set("armor_prop/str", 10);
                set("armor_prop/int", 10);
                set("armor_prop/medal1", 1);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}