#include <ansi.h>

inherit "/maze/necropolis/necropolis_npc";

void create()
{
        string *names = ({ "幽灵" }); 
        set_name( names[random(sizeof(names))], ({ "ghost"}));
        set("vendetta_mark", "ghost");
        set("long", "这是个若隐若现的幽灵。\n");
        set("title", HIB "(鬼气)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 22); 
        set("int", 50);
        set("max_qi", 20000);
        set("max_jing", 25000);
        set("neili", 250000);
        set("max_neili", 250000);
        set("max_jingli", 50000);
        set("attitude", "peaceful");
        //set("shen_type", -1);        
        //set("chat_chance", 2);
        //set("chat_msg", ({
        //      "骷髅空洞的眼眶里闪烁着可怕的荧光。\n"
        //}) ); 

        //set("chat_chance_combat", 50);
        //set("chat_msg_combat", ({
        //      (: do_stun() :),
        //}) ); 
        set("self_go_msg",1);
        set("arrive_msg","幽灵飘了过来。");
        set("leave_msg","幽灵飘走了。");
        set("chat_chance", 1);
        set("chat_msg", ({
                (: random_move :)
        }) );  
        set("combat_exp", 100000000);
        set("bellicosity", 5 );
        set("death_msg",BLU"\n$N消失不见了。\n\n"NOR);
        set_skill("force", 30);
        set_skill("dodge", 30);
        set_skill("unarmed", 30);
        set_skill("parry", 30);

        set_temp("apply/attack", 1000);
        set_temp("apply/parry", 1000);
        set_temp("apply/unarmed_damage", 500);
/*
        set("drops", ([
                 "RA&RARE40" : 70, 
                 "RA&RARE50" : 30, 
        ]));
*/
        setup();
} 

int is_undead() {
        return 1;
}

/*
int is_ghost() {
        return 1;
}
*/
