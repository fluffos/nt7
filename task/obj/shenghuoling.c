#include <ansi.h> 
inherit TASK; 
void create()  
{ 
    set_name(HIB"圣火令"NOR, ({ "ling", "shenghuo ling" }) );  
    set_weight(1);
    if( clonep() ) 
            destruct(this_object());  
    else { 
          set("unit", "个");  
          set("material", "dagger"); 
            set("long", "明教丢失的圣火令牌。\n"); 
          } 
          set("owner", "接引使");
          setup();
} 
