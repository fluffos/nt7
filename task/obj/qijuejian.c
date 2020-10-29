#include <ansi.h>  
inherit TASK;  
void create()  
{ 
        set_name( HIR "七绝剑" NOR, ({ "qijue jian" }) );  
        set_weight(2); 
        if( clonep() )  
                destruct(this_object());  
        else {  
                set("unit", "把"); 
                set("material", "stone"); 
                set("long", "一把绝世宝剑，好像是大理段氏段正明的佩剑。\n");  
             }
             set("owner", "段正明");  
             setup();
}
