// This program is a part of NITAN MudLIB
// Edward.c

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

void create()
{
        ::create();
        set_name(HIM "笑天" NOR, ({ "xiao tian", "edward" }));
        set("gender", "男性" );
        set("age", 30 + random(30));
        set("long", "如梦如幻无法让人看的清楚的一个人。");
        set("attitude", "friendly");
        set_temp("apply/attack", 3000);
        set_temp("apply/dodge", 3000);
        set_temp("apply/parry", 3000);
        set_temp("apply/armor", 3000);
        set_temp("apply/damage", 2000);
        set_temp("apply/unarmed_damage", 2000);
        set("auto_perform", 1);

        if (clonep()) keep_heart_beat();
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
                NPC_D->set_from_me(ob, me, 150);
                kill_ob(me); 
        } 
} 

void set_from_me(object me, int scale)
{
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        exp=query("combat_exp", me)*15/10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);
        
        my = query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];                
        my["jiali"] = query_skill("force") / 2;
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
                
        if( objectp(killer) && query_temp("mibao/to_find", killer) )
        {
                ob = new("/d/reborn/obj/mibao");
                ob->move(killer, 1);
                tell_object(killer, HIR "你获得了一件密宝奇珍。\n" NOR);
                set_temp("mibao/finded", 1, killer);
        }
       
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

varargs void start_busy(mixed new_busy, mixed new_interrupt) 
{
        return;
}
