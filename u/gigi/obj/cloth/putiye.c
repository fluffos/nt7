// gigiflower.c  ^_^

#include <armor.h>
#include <ansi.h>
inherit HEAD;
void create()
{
        set_name(HIG"菩提叶"NOR, ({ "bodhi leaf", "head" }) );
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "片");
                 set("long","这是一片碧绿色的"+HIG"菩提叶"NOR+"，叶片色泽鲜亮且圆润饱满，\n似有清雅香气传来，令人忘却烦忧。\n"); 
                set("value",0);
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
            set("enchase", ([  
                      "apply_prop" : ([ /* sizeof() == 2 */ 
                              "per" : 25, 
                              "int" : 25, 
                      ]), 
             ])); 

        setup();
}
