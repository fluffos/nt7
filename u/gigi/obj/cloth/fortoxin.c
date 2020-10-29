// gigiflower.c  ^_^

#include <armor.h>
#include <ansi.h>
inherit HEAD;
void create()
{
        set_name(YEL"一大坨便便"NOR, ({ "shit for toxin", "head" }) );
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "坨");
                 set("long","这是胡子长的"+YEL"一大坨便便"NOR+"。\n"); 
                set("wear_msg", NOR "$N悄悄从身后掏出" YEL "一大坨便便" NOR "顶在头上。\n" NOR); 
                set("remove_msg", NOR "$N轻轻地把头上" YEL "一大坨便便" NOR "又塞进裤裆里。\n" NOR); 
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
