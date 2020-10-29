#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_NOCLONE;

void start_borrowing() 
{
     remove_call_out("return_to_aobai"); 
     call_out("return_to_aobai", 3600+random(7200)); 
} 

void create()
{
        set_name(CYN "真丝" HIY "宝甲" NOR,  ({ "bao jia", "jia", "armor" }));
        set_weight(6000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("long", "一见黑黝黝的甲，毫不起眼。\n");
                set("no_sell", "这样东西能值钱么。\n");
                set("value", 100000);
                set("material", "silk");
                set("armor_prop/armor", 200);
                set("stable", 100);
        }

        setup();
        move("/d/beijing/aofu_mishi");
        start_borrowing();
        check_clone();
}

int query_unique() { return 1; } // add by shure@tomud.com

void return_to_aobai() 
{ 
     object me; 

     me = environment(); 
     if (! objectp(me)) 
             return; 

     while (objectp(environment(me)) && ! playerp(me)) 
             me = environment(me); 

        if(base_name(me)=="/d/beijing/aofu_mishi")
        {
                call_out("return_to_aobai",3600+random(3600));
                return ;
        }
        
     if (playerp(me)) 
     { 
             if (me->is_fight()) 
             { 
                     call_out("return_to_aobai", 1); 
                     return; 
             } 
             //是否应该执行unwield
             message_vision("忽然$N觉得身上少了件什么东西似的。\n", me); 
     } else 
     { 
             message("vision", "忽然一个人走了过来，捡起"+name()+"，叹了口气，摇摇头走了。\n", me); 
     } 

        move("/clone/misc/void");
        call_out("real_back",random(600));
}

void real_back()
{
     move("/d/beijing/aofu_mishi");
     start_borrowing();
} 