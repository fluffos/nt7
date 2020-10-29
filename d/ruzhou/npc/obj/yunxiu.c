// yunxiu.c

#include <ansi.h>
#include <armor.h>
inherit CLOTH;

void create()
{
        set_name(CYN"青边"NOR HIR"戴花"NOR HIM"水云袖"NOR, ({ "yunxiu" }));
        set("long", "这是一件崭新的新娘出阁时穿的礼服。\n");
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("material", "cloth");
                set("unit", "件");
set("armor_prop/armor", 100);
    set("female_only", 1);
        }
        setup();
}