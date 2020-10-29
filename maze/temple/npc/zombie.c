#include <ansi.h>
inherit BOSS;

void do_bite();
void create()
{
        set_name("僵尸", ({ "zombie" }));
        set("vendetta_mark","zombie");
        set("long", "这是一个腐烂的僵尸。\n");
        set("title", HIB "(鬼气)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 22); 
        set("int", 50);
        set("max_qi", 200000);
        set("eff_qi", 200000);
        set("max_jing", 100000);
        set("eff_jing", 100000);
        set("neili", 250000);
        set("max_neili", 250000);
        set("max_jingli", 50000);
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: do_bite() :),
        }) ); 
        set("combat_exp", 100000000);
        set("bellicosity", 5 );
        set("death_msg", RED"\n$N化作了一滩血水。\n\n"NOR);
        
        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("unarmed", 300);
        set_skill("parry", 300);
        set_temp("apply/attack", 5000);
        set_temp("apply/parry", 5000);
        set_temp("apply/unarmed_damage", 6000);
        set_temp("apply/add_weak", 60);
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 20);
        
        set("rewards", ([ 
                "exp"  : 30,  
                "pot"  : 10,  
        ]));
        setup();
        add_money("gold", 10 + random(10));
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

void do_bite() 
{
        object *enemies,enemy;
        string msg;

        clean_up_enemy();
        enemies = query_enemy();

        if( !enemies || sizeof(enemies)==0 )
                return;
        enemy = enemies[random(sizeof(enemies))];
        if( !userp(enemy) ) return;
        message_vision(RED"$N露出森森的白牙，扑向$n！\n"NOR,this_object(), enemy);
        message_vision(HIR"$N咬住$n脖子猛吸血！\n"NOR,this_object(),enemy);
        enemy->receive_damage("qi",5000+random(5000),this_object());
        msg = "( $n" + 
              COMBAT_D->status_msg(enemy->query("qi") * 100 / 
              (enemy->query("max_qi") ? enemy->query("max_qi") : 100)) + ")\n"; 
        message_vision(msg, this_object(), enemy);
        this_object()->receive_heal("qi",5000+random(5000));
        this_object()->receive_curing("qi",2500+random(2500));
        if( !enemy->is_busy() && !random(3) )
                enemy->start_busy(1);

/*
        if( !this_object()->is_busy() )
                this_object()->start_busy(2);
*/
}

