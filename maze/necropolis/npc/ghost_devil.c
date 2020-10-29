#include <ansi.h>

inherit "/maze/necropolis/necropolis_npc";

void do_transfer();

void create()
{
        string *names = ({"幽冥魔"}); 
        // set_name( names[random(sizeof(names))], ({ "ghost devil","ghost"}));
        set_name( names[random(sizeof(names))], ({ "ghost devil" }));
        set("vendetta_mark","ghost");
        set("long", "这是个若隐若现的幽灵。\n");
        set("title", HIB "(鬼气)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 22); 
        set("int", 50);
        set("max_qi", 40000);
        set("max_jing", 45000);
        set("neili", 250000);
        set("max_neili", 250000);
        set("max_jingli", 50000);
        set("attitude", "peaceful");
        //set("shen_type", -1);        
        //set("chat_chance", 2);
        //set("chat_msg", ({
        //               "骷髅空洞的眼眶里闪烁着可怕的荧光。\n"
        //}) ); 
        set("death_msg",BLU"\n$N消失不见了。\n\n"NOR);
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: do_transfer() :),
        }) ); 

        set("combat_exp", 200000000);
        set("bellicosity", 5 );

        set_skill("force", 60);
        set_skill("dodge", 60);
        set_skill("unarmed", 60);
        set_skill("parry", 60);        
        set_temp("apply/attack", 1000);
        set_temp("apply/parry", 500);
        set_temp("apply/unarmed_damage", 500);

        set("drops", ([
                 "RA&RARE40" : 70, 
                 "RA&RARE50" : 30, 
        ]));
        setup();
        carry_object(__DIR__"obj/ghost_fire");
} 

int is_undead() {
        return 1;
}

//int is_ghost() {
//        return 1;
//}


void do_transfer() {
        object *enemies,enemy,env;
        mixed yourexp,myexp,no_busy;
        mapping exits;
        string *keys,direction;
        enemies = query_enemy();

        if(!enemies || sizeof(enemies)==0)
                return;
        
        message_vision(HIM"\n$N仿佛在你的心底里呼唤，来吧...来吧...冥界在召唤你... \n"NOR, this_object(),enemy); 
        myexp = query("combat_exp");
        foreach(enemy in enemies)  {
                if(!enemy)
                        continue;
                if(!present(enemy, environment(this_object())))
                        continue;
                yourexp=query("combat_exp", enemy);
                if( random(myexp*2 + yourexp)>yourexp ) {
                        message_vision(HIM"\n$n像被强大的力量控制，身不由己的向$N走去...... \n"NOR, this_object(),enemy); 
                        enemy->receive_damage("jing",query("max_jing", enemy)/4,this_object());
                        if(!enemy->is_busy())
                                enemy->start_busy(random(4));
                        COMBAT_D->report_status(enemy);
                } else {
                        message_vision(HIG"\n$n恐惧的喊到：这不是真的！ \n"NOR, this_object(),enemy); 
                        message_vision(HIG"\n$n吓得扭头就跑! \n\n"NOR, this_object(),enemy); 
                        env = environment(enemy);
                        if(env) {
                                exits=query("exits", env);
                                if(exits) {
                                        keys = keys(exits);
                                        direction = keys[random(sizeof(keys))];
                                        enemy->move(exits[direction]);
                                }
                        }
                        if(!enemy->is_busy())
                                enemy->start_busy(1);
                        //("/cmds/std/go")->do_flee(enemy);
                }
        }
        start_busy(2);        

}
