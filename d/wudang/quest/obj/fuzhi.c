// Modified by haiyan

#include <ansi.h> 
inherit ITEM; 

void create() 
{ 
     set_name( HIY"符纸"NOR, ({ "fu zhi" })); 
     set_weight(20); 
     /*if( clonep() ) 
         set_default_object(__FILE__); 
     else*/
     { 
         set("unit", "张"); 
         set("no_put", 1);
         set("no_sell", 1);
         set("long", "这是一张道士们用来驱魔捉鬼的符纸，上面画着一些奇怪的红色符号。\n"); 
     } 
     setup(); 
} 