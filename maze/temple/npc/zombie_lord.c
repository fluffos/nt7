#include <ansi.h>
inherit BOSS;

void do_summon();
void create()
{
        set_name( "僵尸王", ({ "lord zombie" }));
        set("vendetta_mark","zombie");
        set("long", "这是一个腐烂的僵尸王，看起来好可怕。。\n");
        set("title", HIB "(鬼气)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 50); 
        set("int", 50);
        set("max_qi", 2500000);
        set("eff_qi", 2500000);
        set("max_jing", 1500000);
        set("eff_jing", 1500000);
        set("neili", 550000);
        set("max_neili", 550000);
        set("max_jingli", 80000);

        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: do_summon() :),
        }) ); 

        set("combat_exp", 200000000);
        set("bellicosity", 5 );
        set("death_msg",RED"\n$N化作了一滩血水。\n\n"NOR);

        set_skill("force", 1200);
        set_skill("dodge", 1200);
        set_skill("unarmed", 1200);
        set_skill("parry", 1200);      
        set_temp("apply/attack", 15000);
        set_temp("apply/parry", 15000);
        set_temp("apply/unarmed_damage", 18000);
        set_temp("apply/add_weak", 80);
        set_temp("apply/reduce_damage", 90);
        set_temp("apply/add_busy", 15);

        set("rewards", ([ 
                "exp"  : 200,  
                "pot"  : 70,  
                "mar"  : 10,  
        ]));

/*
        set("drops", ([
                "RA&EPIL60"    :       70,    // 中级普通装备
                "RA&EPIL70"    :       30,    // 中级普通装备
        ]));
*/
        
        setup();
        add_money("gold", 100 + random(200));
} 

void init()
{
        object me;

        ::init();
        if (! interactive(me = this_player()) || 
            this_object()->is_fighting())
                return;

        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

void do_summon() 
{
        object zombie,me,enemy,*enemies;
        object *obs;
        me = this_object();
        
        obs = all_inventory(environment(me));
        obs=filter_array(obs,(:query("id", $1) == "zombie":));
        if( sizeof(obs) > 10 ) return;
        message_vision(HIM "\n$N嗬嗬干嚎，周围的僵尸应声而来。\n" NOR, me); 
        zombie = new(__DIR__"zombie");
        zombie->move(environment(me));
        enemies = me->query_enemy();
        foreach(enemy in enemies) {
                if( !userp(enemy) ) continue;
                zombie->kill_ob(enemy);
                enemy->kill_ob(zombie);
        } 
        message_vision( "\n\n$N恶狠狠地扑了上来。\n" , zombie);
        call_out("leave",20+random(10),zombie);
        if( !this_object()->is_busy() )
                this_object()->start_busy(3);
}

void leave(object zombie){
        if( !zombie || zombie->is_fighting() ) return;
        message_vision("\n$N消失了。\n",zombie);
        destruct(zombie);
}
