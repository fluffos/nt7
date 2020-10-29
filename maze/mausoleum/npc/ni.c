#include <ansi.h>
inherit CLASS_D("generate") + "/boss";

void do_swing();
void set_from_me(object me);
void create()
{
        string *names = ({ "青铜狻猊" });

        ::create();
        set_name( names[random(sizeof(names))], ({ "bronze ni", "bronze", "ni" }));
        set("long", @LONG
这是一个沉睡在皇陵青铜机关兽，身长丈许，肋生双翅，爪利牙尖，更有飞天遁地之
能，道法神通均为兽族翘楚。在东方仙术的作用下，它的行动奇快，进退如风，再加
上毛皮刀枪不入，利爪快如刀刃，端的是极难对付。
LONG);
        set("title", HIR"机关兽" NOR);
        set("str", 150);
        set("con", 150);
        set("dex", 150);
        set("int", 150);
        set("max_qi", 2500000);
        set("max_jing", 1500000);
        set("neili", 2500000);
        set("max_neili", 2500000);
        set("max_jingli", 500000);
        set("attitude", "killer");
        set("auto_perfrom", 1);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: do_swing :),
        }) );

        set("combat_exp", 100000000);
        set("death_msg",YEL"\n$N散落成一堆青铜。\n\n"NOR);
        set("no_corpse", 1);

        set("rewards", ([
                "exp" : 500,
                "pot" : 120,
                "mar" : 20,
        ]));
        set_temp("apply/attack", 15000);
        set_temp("apply/parry", 15000);
        set_temp("apply/damage", 15000);
        set_temp("apply/unarmed_damage", 15000);
        set_temp("apply/armor", 20000);
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

        msg = HIW"$N口中突然多了件物事，似是一块透明的布疋，若有若无，不知是什么东西,向众人吐去！\n"NOR;
        message_vision(msg,this_object());
        foreach( enemy in enemies ) {
                msg = HIW"$n突然间脚下一滑，扑地倒了，跟着身子便变成了一团。\n"NOR;
                message_vision(msg,this_object(), enemy);
                enemy->receive_damage("qi",10000+random(10000),this_object());
                COMBAT_D->report_status(enemy);
                if( !enemy->is_busy() && !enemy->query_all_buff("daomu") )
                        enemy->start_busy(2);
        }
}
