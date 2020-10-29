#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( HIY "烹饪大全" NOR, ({ "pengren book" }) ); 
        set_weight(2); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "本"); 
                set("material", "paper"); 
                set("long", "这是一本摸上去油腻腻的小本子，上面记载了肉，粥，菜共计八大类的各种佳肴做法。\n"); 
        } 
        set("owner", "厨娘"); 
        setup(); 
} 
