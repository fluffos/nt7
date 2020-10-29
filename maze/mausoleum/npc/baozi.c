#include <ansi.h>
inherit CLASS_D("generate") + "/boss";

void do_swing();
void set_from_me(object me);
void create()
{
        string *names = ({ "青铜豹子" });
        ::create();
        set_name( names[random(sizeof(names))], ({ "bronze leopard", "bronze", "leopard" }));
        set("vendetta_mark", "ghost");
        set("long", "这是一个沉睡在皇陵青铜机关兽。\n");
        set("title", HIR"机关兽" NOR);

        set("str", 150);
        set("con", 120);
        set("dex", 122);
        set("int", 150);
        set("max_qi", 2000000);
        set("max_jing", 1000000);
        set("neili", 2500000);
        set("max_neili", 2500000);
        set("max_jingli", 500000);
        set("attitude", "killer");
        set("auto_perfrom", 1);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: do_swing() :),
        }) );
        set("combat_exp", 100000000);
        set("death_msg",YEL"\n$N散落成一堆青铜。\n\n"NOR);
        set("no_corpse", 1);

        set("rewards", ([
                "exp" : 400,
                "pot" : 70,
                "mar" : 10,
        ]));
        set_temp("apply/attack", 8000);
        set_temp("apply/parry", 8000);
        set_temp("apply/damage", 8000);
        set_temp("apply/unarmed_damage", 8000);
        set_temp("apply/armor", 8000);
        setup();
}

void init()
{
        object me;

        ::init();
        if( !interactive(me = this_player()) ||
            this_object()->is_fighting())
                return;

        set_from_me(me);
        remove_call_out("kill_ob");
        call_out("kill_ob", 0.5, me);
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
void do_swing()
{
        object *enemies,enemy;
        string msg;

        enemies = query_enemy();
        if( !enemies || sizeof(enemies)==0 )
                return;

        msg = RED "$N张开大口，吐一个大火球！！\n" NOR;
        message_vision(msg, this_object());
        foreach( enemy in enemies ) {
                msg = RED"火球在天空炸开,无数小火球飞向$n！"NOR;
                message_vision(msg,this_object(), enemy);
                enemy->receive_damage("qi",5000+random(5000),this_object());
                COMBAT_D->report_status(enemy);
                if( !enemy->is_busy() && !enemy->query_all_buff("daomu") )
                        enemy->start_busy(1);
        }
}
