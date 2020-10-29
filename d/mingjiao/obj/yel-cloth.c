// yel-cloth.c 黄色圣衣
#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(YEL"黄色圣衣"NOR, ({ "cloth" }) );
        set_weight(3000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long","这是一件绣着红色火焰的黄色圣衣。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 30);
        }
        setup();
}