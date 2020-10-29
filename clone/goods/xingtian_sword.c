// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HBGRN "刑天魔剑" NOR, ({ "xingtian sword", "sword" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "柄");
                set("long", HIY "这便是刑天曾经使用的魔剑，剑体血光冲天。\n"
                            HIY + name() + HIY "的等级：上古神品  LV10\n" NOR);
                set("value", 3000); 
                set("no_sell", "这样东西不能卖。\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
                set("no_store", 1); // 不能用干降符文upd
                set("no_save", 1); // quit不保存
        }     

        set("mod_mark", "A2033");
        set("mod_level", "M2030");
        set("mod_name", HBRED "刑天套装" NOR);
        init_sword(50000);
        set("quality_level", 3);
        
        setup();
}

void start_borrowing(int time) 
{
        remove_call_out("return_to_back"); 
        call_out("return_to_back", time); 
} 

void return_to_back() 
{ 
        object me; 

        me = environment(); 
        if( !objectp(me) ) 
                return;

        while( objectp(environment(me)) && !playerp(me) ) 
                me = environment(me); 
        
        if( playerp(me) ) 
        { 
                if( me->is_fighting() ) 
                { 
                        call_out("return_to_back", 1); 
                        return; 
                } 

                tell_object(me, HIR"\n一条人影从你眼前一闪而过：" +
                            "“时间已到，老夫取回" NOR + name() + HIR
                            "，就此谢过，咱们后会有期！”\n\n"NOR);
        } else 
        { 
                message("vision", "忽然一个人走了过来，捡起"+name()+"，叹了口气，摇摇头走了。\n", me); 
        } 

        destruct(this_object());
}

int query_autoload() { return 0; }
