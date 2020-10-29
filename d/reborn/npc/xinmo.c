// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(HIM "心魔" NOR, ({ "xinmo" }));
        set("gender", "男性" );
        set("age", 30 + random(30));
        set("long", "如梦如幻无法让人看的清楚的一个人。");
        set("attitude", "friendly");
        set_temp("apply/armor", 30);
        set_temp("apply/damage", 20);

        setup();
}

void init() 
{ 
        object ob, me;
        
        me = this_player();  
        ob = this_object();
         
        ::init(); 
        if (interactive(me) && visible(me) &&  
            ! is_fighting())  
        { 
                ob->set_name((query("name", me)+"--魔"),({(query("id", me)+"-xinmo")}));
                NPC_D->copy_from_me(ob, me, 200);
                kill_ob(me); 
        } 
} 

varargs void die(object killer)
{
        object *obs, env;
        object me, ob, owner;
        int exp, pot, mar;

        me = this_object();
        
        if (objectp(ob = previous_object(0)) && 
            sscanf(base_name(ob), "/kungfu/skill/%*s"))
        {
                me->full_self();
                return;
        }
        
        env = environment(me);
        
        if (! killer) 
                killer = me->query_last_damage_from();
                
        if( objectp(killer) && query_temp("xinmo/to_kill", killer) )
                set_temp("xinmo/killed", 1, killer);
       
        return ::die(killer);
}

void unconcious()
{
        object ob;

        if (objectp(ob = previous_object(0)) && 
            sscanf(base_name(ob), "/kungfu/skill/%*s"))
        {
                this_object()->full_self();
                return;
        }
        
        die();
}
