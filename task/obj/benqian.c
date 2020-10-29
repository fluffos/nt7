#include <ansi.h> 
inherit TASK; 
void create() 
{
    set_name(HIR"翻本的本钱"NOR, ({ "benqian" }) ); 
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "张"); 
            set("material", "paper"); 
            set("long", "一张赌客翻本的本钱。\n"); 
          } 
          set("owner", "赌客"); 
          setup();
}
