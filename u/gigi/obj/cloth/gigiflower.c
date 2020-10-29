// gigiflower.c  ^_^

#include <armor.h>
#include <ansi.h>
inherit HEAD;
void create()
{
        set_name(HIW"月朦胧"NOR, ({ "pear flower", "head" }) );
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "朵");
                 set("long","这是一朵洁白的梨花，花瓣皎洁如月，\n正如诗中所吟:“月胧胧，一树梨花细雨中。”\n"); 
                set("value",0);
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
        setup();
}
