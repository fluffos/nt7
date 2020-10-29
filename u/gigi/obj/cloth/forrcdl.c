// gigiflower.c  ^_^

#include <armor.h>
#include <ansi.h>
inherit HEAD;
void create()
{
        set_name(YEL"一大堆便便"NOR, ({ "shit for rcdl", "head" }) );
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "堆");
                 set("long","这是绿莲老猪的"+YEL"一大堆便便"NOR+"。\n"); 
                set("value",0);
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
            set("enchase", ([  
                      "apply_prop" : ([ /* sizeof() == 2 */ 
                              "per" : -25, 
                              "int" : -25, 
                      ]), 
             ])); 

        setup();
}
