inherit COMBINED_ITEM;
#include <ansi.h>                                                                                                                                     
string query_autoload()
{                                     
        return query_amount() + "";
}
                                                                                         
void create()                                                                            
{                                                                                        
        set_name(HIW "消慧丹" NOR, ({ "xiaohui dan" }));              
        /*if (clonep())                                                                    
                set_default_object(__FILE__);                                            
        else*/ {                                                                           
                set("long", YEL "此丹吃下后可以消除一次悟性类吃丹失败记录。\n" NOR);   
                set("base_unit", "颗");                                                  
                set("base_value", 400000);                                               
                set("base_weight", 50);                                                  
                set("only_do_effect", 1);                                                                                                                                       
                set("gift_msg", HIM "突然间你觉得自己身上好象少了点什么。\n" NOR);
        }                                                                                
        setup();                                                                         
}               

int do_effect(object me)
{
                                                               
        message_vision(WHT "$N" WHT "一仰脖，吞下了一" +                                                                      
                       query("base_unit") + name() + WHT
                       "。\n" NOR, me);    
                       
        if( query("gift/clearcount", me) >= 3 )
        {                                                           
                tell_object(me, "你觉得这药好象没什么效果。\n");
        }
        else
        {                                                           
                if( query("gift/int/fail", me) )
                {
                       addn("gift/int/fail", -1, me);
                       addn("gift/int/all", -1, me);
                       addn("gift/clearcount", 1, me);
                       tell_object(me, query("gift_msg"));
                       tell_object(me, HIC "OK.\n" NOR);
                }
                else 
                {
                        tell_object(me, HIC "你觉得这药好象没什么效果。\n" NOR);
                }
                
        }             
        add_amount(-1);                    
        if (query_amount() < 1)
                destruct(this_object());
        
        return 1;
}

void autoload(string param)
{                                                                         
        int amt;

        if (sscanf(param, "%d", amt) == 1)    
                set_amount(amt);
}                                             
                                              
void setup()
{                                             
        set_amount(1);
        ::setup();
}

                               
                               