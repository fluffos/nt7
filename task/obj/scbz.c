#include <ansi.h>  
inherit TASK;
void create()
{
    set_name(HIC"生辰八字"NOR, ({ "scbz", "shengchen bazi" }) );  
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object());  
    else { 
            set("unit", "张");  
            set("material", "paper");
            set("long", "生辰八字。。。。。。！\n"); 
        }
        set("owner", "红娘");  
        setup(); 
}
