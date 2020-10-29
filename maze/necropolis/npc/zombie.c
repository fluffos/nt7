#include <ansi.h>

inherit "/maze/necropolis/necropolis_npc";
void create()
{
        string *names = ({"僵尸"}); 
        set_name( names[random(sizeof(names))], ({ "zombie"}));
        set("vendetta_mark","zombie");
        set("long", "这是一个腐烂的僵尸。\n");
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

        set("combat_exp", 100000000);
        set("bellicosity", 5 );
        set("death_msg",RED"\n$N化作了一滩血水。\n\n"NOR);
        
        set_skill("force", 30);
        set_skill("dodge", 30);
        set_skill("unarmed", 30);
        set_skill("parry", 30);
        set_temp("apply/attack", 1000);
        set_temp("apply/parry", 500);
        set_temp("apply/unarmed_damage", 6000);
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

int is_zombie() {
        return 1;
}
