#include <weapon.h>
#include <ansi.h>
inherit F_UNIQUE; 
inherit F_NOCLONE; 
inherit SWORD;

void return_to_back();
void start_borrowing() 
{
        remove_call_out("return_to_back"); 
        call_out("return_to_back", 3600+random(7200)); 
} 

void create()
{
        set_name(CYN "倚天剑" NOR, ({ "yitian sword", "jian", "sword" }) );
        set_weight(1000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", HIY "这便与天下至尊的屠龙宝刀并称的倚天剑。\n相传让刀剑对砍(duikan)可以得到旷世的武林秘籍。\n" NOR);
                set("value", 100000);
                set("no_sell", "这样东西不能卖。\n");
                set("no_store", 1);
                set("rigidity",8000);   
                set("unique", 1); 
                set("replica_ob","/d/city/npc/obj/changjian"); 
                set("enchase/flute", 9);    
                set("material", "steel");
                set("wield_msg", HIW "只听“嗖”的一声破空声响，号称天下第一神兵的倚天剑已被$N握在手中。\n" NOR);
                set("unwield_msg", HIW "$N将倚天剑插回腰间，天地又渐渐放出光芒。\n"NOR);
        }
        set("enchase/apply_prop", ([
                "add_busy"  : 10,
                "add_weak"  : 40,
                "avoid_locked" : 40,
                "add_damage" : 50,
                "add_skill"  : 200,
        ]));

        init_sword(5000);
        setup();
        start_borrowing();
        check_clone(); 
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int pro;
        int dam;
        dam = me->query_dex() * 100;
        addn("neili", -dam*10, victim);

        if( query("neili", victim)<0 )
        set("neili", 0, victim);

        return HIW "倚天剑携着飕飕刺骨风声，直直刺向$n，$n只感到全身的内力竟一丝丝随着剑锋涌出。\n" NOR;
}

void return_to_back() 
{ 
        object me; 

        me = environment(); 
        if (! objectp(me)) 
                return; 

        while (objectp(environment(me)) && ! playerp(me)) 
                me = environment(me); 

        if(base_name(me)=="/d/tulong/yitian/obj/shelf")
        {
                call_out("return_to_back",3600+random(3600));
                return ;
        }
        
        if (playerp(me)) 
        { 
                if (me->is_fighting()) 
                { 
                        call_out("return_to_back", 1); 
                        return; 
                } 
                //是否应该执行unwield
                tell_object(me, HIR"\n一条人影从你眼前一闪而过：" +
                            "“多谢替老夫取回" NOR + name() + HIR
                            "，就此谢过，咱们后会有期！”\n\n"NOR);
        } else 
        { 
                message("vision", "忽然一个人走了过来，捡起"+name()+"，叹了口气，摇摇头走了。\n", me); 
        } 

        move("/clone/misc/void");
        call_out("real_back", random(2));
}

void real_back()
{
        object room, shelf;

        room = get_object("/d/tulong/yitian/was_lou4");
        shelf = present("shelf", room);
        move(shelf);
        start_borrowing();
} 