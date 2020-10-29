// longpao.c

#include <ansi.h>
#include <armor.h>
inherit CLOTH;

void create()
{
        set_name(HIR"大红"NOR HIY"金边"NOR HIR"滚龙袍"NOR, ({ "longpao" }));
        set("long", "这是一件崭新大红金边滚龙袍，是新郎的专用礼服。\n");
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("material", "cloth");
                set("unit", "件");
    set("armor_prop/armor", 100);
    set("male_only", 1);
        }
        setup();
}