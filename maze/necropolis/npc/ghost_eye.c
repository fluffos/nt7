#include <ansi.h>

inherit "/maze/necropolis/necropolis_npc";
void do_eye();
void create()
{
        string *names = ({"幽冥之眼"}); 
        // set_name( names[random(sizeof(names))], ({ "ghost eye","ghost"}));
        set_name( names[random(sizeof(names))], ({ "ghost eye" }));
        set("vendetta_mark","ghost");
        set("long", "这是个若隐若现的幽灵。\n");
        set("title", HIB "(鬼气)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 50); 
        set("int", 50);
        set("max_qi", 80000);
        set("max_jing", 85000);
        set("neili", 450000);
        set("max_neili", 450000);
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
                (: do_eye() :),
        }) ); 

        set("combat_exp", 150000000);
        set("bellicosity", 5 );
        
        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("unarmed", 120);
        set_skill("parry", 120);                
        set_temp("apply/attack", 1000);
        set_temp("apply/parry", 500);
        set_temp("apply/unarmed_damage", 500);
/*
        set("drops", ([
                 "RA&RARE40" : 70, 
                 "RA&RARE50" : 30, 
        ]));
*/
        setup();
        //carry_object(__DIR__"obj/bone_finger");
} 

int is_undead() {
        return 1;
}

//int is_ghost() {
//        return 1;
//}


void do_eye() {
        object *enemies,enemy;
        mixed yourexp,myexp;
        enemies = query_enemy();

        if(!enemies || sizeof(enemies)==0)
                return;
        enemy = enemies[random(sizeof(enemies))];
                if(!present(enemy, environment(this_object())))
                return;
        
        message_vision(HIR"\n$N中现出了$n的影子，$n不由得凝视着自己的影子...... \n"NOR, this_object(),enemy); 
        yourexp=query("combat_exp", enemy);
        myexp = query("combat_exp");
        if( random(myexp + yourexp)> yourexp ) {
                message_vision(HIR"\n影子突然四分五裂，$N觉得自己的灵魂也分裂了！ \n"NOR, enemy); 
                enemy->receive_damage("jing",query("jing", enemy)/2,this_object());
                COMBAT_D->report_status(enemy);
        } else 
                message_vision(HIC"\n但是$N迅速收回了目光！ \n"NOR, enemy); 
        
        if (!this_object()->is_busy())
                this_object()->start_busy(2);
}
