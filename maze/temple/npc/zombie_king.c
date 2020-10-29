#include <ansi.h>
inherit BOSS;

void do_summon();
void set_from_me(object me);
void create()
{
        set_name( "千年老粽子", ({ "zombie king" }));
        set("vendetta_mark","zombie");
        set("long", "千年红毛老粽子啊，看起来好可怕。。。\n");
        set("title", HIB "(鬼气)" NOR);

        set("str", 50);
        set("con", 120);
        set("dex", 50);
        set("int", 50);
        set("max_qi", 25000000);
        set("eff_qi", 25000000);
        set("max_jing", 15000000);
        set("eff_jing", 15000000);
        set("neili", 550000);
        set("max_neili", 550000);
        set("max_jingli", 80000);
        set("combat_exp", 5000000000);
        set_skill("force", 2000);
        set_skill("unarmed", 2000);
        set_skill("dodge", 2000);
        set_skill("parry", 2000);
        set_skill("blade", 2000);
        set_skill("douzhuan-xingyi", 2000);
        set_skill("guiyuan-tunafa", 2000);
        set_skill("tie-zhang", 1500+random(1500));
        set_skill("wuming-jianfa", 1500+random(1500));
        set_skill("wuhu-duanmendao", 1500+random(1500));
        set_skill("shaolin-shenfa", 2000);
        map_skill("force", "guiyuan-tunafa");
        map_skill("unarmed","tie-zhang");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("blade", "wuhu-duanmendao");
        map_skill("dodge", "shaolin-shenfa");
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: do_summon() :),
        }) );

        set("bellicosity", 5 );
        set("death_msg",RED"\n$N化作了一滩血水。\n\n"NOR);
        set("clear_fuben", 1);

        set("auto_perform", 1);
        set_temp("apply/attack", 15000);
        set_temp("apply/parry", 15000);
        set_temp("apply/unarmed_damage", 8000);
        set_temp("apply/add_weak", 80);
        set_temp("apply/reduce_damage", 90);
        set_temp("apply/reduce_busy", 5);
        set_temp("apply/add_busy", 15);

        set("drops", ([
                "RA&EPIL50"    :       120,   // 中级普通装备
                "RA&EPIL60"    :       100,   // 中级普通装备
                "RA&EPIL60"    :       80,   // 中级普通装备
                "RA&EPIL70"    :       70,   // 中级普通装备
                "FI&/clone/goods/sun" : 40, 
                "FI&/clone/goods/moon" : 40, 
                "FI&/clone/tessera/rune27" : 20, 
                "FI&/clone/tessera/rune28" : 10, 
        ]));
        set("rewards", ([
                "exp"  : 10000,
                "pot"  : 1000,
                "mar"  : 100,  
        ]));
        setup();
        add_money("gold", 100 + random(50));
}

/*
void init()
{
        object me;

        ::init();
        if (! interactive(me = this_player()) ||
            this_object()->is_fighting())
                return;

        set_from_me(me);
        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}
*/
void init()
{
        object ob, me;

        me = this_player();
        ob = this_object();

        ::init();
        if( interactive(me) && visible(me) &&
            !is_fighting()) {
                NPC_D->copy_from_me(ob, me, 120, 1);
                kill_ob(me);
        }
}


void set_from_me(object me)
{
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        set("jiali", query_skill("force") / 2);
}

void do_summon()
{
        object zombie,me,enemy,*enemies;
        object *obs;
        me = this_object();

        obs = all_inventory(environment(me));
        obs=filter_array(obs,(:query("id", $1) == "lord zombie":));
        if( sizeof(obs) > 3 ) return;
        message_vision(HIM "\n$N嗬嗬干嚎，周围的僵尸王应声而来。\n" NOR, me);
        zombie = new(__DIR__"zombie_lord");
        zombie->move(environment(me));
        enemies = me->query_enemy();
        foreach(enemy in enemies) {
                if( !userp(enemy) ) continue;
                zombie->kill_ob(enemy);
                enemy->kill_ob(zombie);
        }
        message_vision( "\n\n$N恶狠狠地扑了上来。\n" , zombie);
        call_out("leave",30+random(10),zombie);
        if( !this_object()->is_busy() )
                this_object()->start_busy(3);
}

void leave(object zombie){
        if( !zombie || zombie->is_fighting() ) return;
        message_vision("\n$N消失了。\n",zombie);
        destruct(zombie);
}

