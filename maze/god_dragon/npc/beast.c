#include <ansi.h>

inherit NPC;
string *first_name = ({ "天", "天空"});
string *first_id = ({ "tian", "sky"});
string *name_words = ({ "巨灵", "怪"});
string *id_words = ({ "juling", "guai"});
int combatpower();

void create()
{
        string name;
        int i, j;
        
        i = random(sizeof(first_name));
        name = first_name[i];
        j = random(sizeof(name_words));
        name += name_words[j];

        set_name(name, ({ first_id[i]+" "+id_words[j] }) );
        // random_name_color(this_object());
        
        set("age", 20);
        set("vrm_guard", 1);
        set("attitude", "aggressive");

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);
        
        set("combat_exp", 20000000);
        set("level", 20);
        set("qi", 600000);
        set("max_qi", 600000);
        set("jing", 300000);
        set("max_jing", 300000);
        set("neili", 1200000);
        set("max_neili", 1200000);
        set("jiali", 4000);

        set_skill("unarmed", 2000); 
        set_skill("dodge", 2000); 
        set_skill("parry", 2000); 
        set_skill("force", 2000); 
        

        set_temp("apply/attack", 2000+random(2000));
        set_temp("apply/unarmed_damage",2000+random(2000));
        set_temp("apply/armor", 2000+random(2000));        

        set("drops", ([
                "RA&RANDOM70"                                    :       40,  // 低级普通装备
                "RA&RANDOM80"                                    :       30,  // 中级普通装备
        ]));

        set_weight(500000);
        setup();
}

void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}
        
mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;
        
        damage = 400 + random(400);
        damage-=query_temp("apply/reduce_wind", ob);
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        set("neili",query("max_neili",  me), me);
        return HIC "$N" HIC "“呼”的一声吹出一阵狂风，登时令$n"
               HIC "浑身犹如刀割一般。\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
        ::die();
}


