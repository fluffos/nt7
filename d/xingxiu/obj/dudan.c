// Code of ShenZhou
// wsky 4/7/00

#include <ansi.h>
#include <weapon.h>

inherit ITEM;

void create()
{
        set_name("毒丹", ({ "du dan", "dan"}));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("long", HIR"一块腥红如血的丹丸。\n"NOR);
                set("material", "stone");
        }
        setup();
}