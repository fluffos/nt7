// This program is a part of NITAN MudLIB 
// redl 2015

#include <ansi.h>
inherit NPC;

//#define LEV 535
#define COPYNPC "/d/kaifeng/linggt/npc/boss"    //复制来源于
#define BONUS_EXP 6000

int do_copyskill();


void create()
{
        set_name(NOR YEL "金船" HIC "水鬼" NOR, ({ "ghost" }));
        set("str", 1);
        set("con", 1);
        set("dex", 1);
        set("int", 1);
        set("max_qi", 1);
        set("max_jing", 1);
        set("neili", 1);
        set("max_neili", 1);
        set("max_jingli", 1);
        set("jingli", 1);
        set("jiali", 1);
        set("combat_exp", 30000000000);
        set("shen", -1000000);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                        (: exert_function, "shield" :),
                        (: exert_function, "recover" :),
        }));
                set("chat_chance", 5 + random(20));
        set("chat_msg", ({
                (: random_move :),
        }));
                set("auto_perform", 1);

        set("death_msg", NOR "\n$N" + (random(2)? "尖叫" : "嘶吼") + (random(2)? "一声" : "一头") + "栽倒，" + (random(2)? "化作脓血" : "散作青烟") + (random(2)? "。。" : "。。。") + "\n" NOR);

                //set("guarder_level", LEV);
                //do_copyskill();
                
        set_heart_beat(2);
        setup();
}

int check_weapon(int chance)
{
        object me,weapon; 
        string str, wname;

                if (random(100) > chance)
                        return 1;
        me = this_object();
        if (!objectp(me)) return 1;
        wname = query("weaponname");
        if (!wname) return 1;
        
        if (!query_temp("weapon"))
        {
                weapon = new(wname);
                weapon->move(me); 
                str = sprintf("%s" HIY "虚空一抓，突然%s" HIY "出现在他的手中。\n" NOR,
                                       query("name", me),
                                       query("name", weapon));
                        tell_room(environment(me), str, me);
                weapon->wield(); 
        }
        return 1;
}

int do_copyskill()
{
        object ob, me;
        int tlv = query("guarder_level");
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        string *sname;
        string *mname;
        string *pname;
        int i, temp, applytmp;
        object weapon;
        mapping tmp, my_tmp, apply;
        
        if (query("copied")) return 1;
        
        //tlv += 1 + random(11);
        ob = new(COPYNPC);
        ob->setlv(tlv, -1, -1);
        me = this_object();
        if (mapp(skill_status = me->query_skills()))
        {
                skill_status = me->query_skills();
                sname = keys(skill_status);

                temp = sizeof(skill_status);
                for (i = 0; i < temp; i++)
                        me->delete_skill(sname[i]);
        }

        if (mapp(skill_status = ob->query_skills()))
        {
                skill_status = ob->query_skills();
                sname = keys(skill_status);

                for (i = 0; i < sizeof(skill_status); i++)
                        me->set_skill(sname[i], skill_status[sname[i]]);
        }
        
        if (mapp(map_status = me->query_skill_map()))
        {
                mname = keys(map_status);

                temp = sizeof(map_status);
                for (i = 0; i < temp; i++)
                        me->map_skill(mname[i]);
        }

        if (mapp(map_status = ob->query_skill_map()))
        {
                mname = keys(map_status);

                for(i = 0; i < sizeof(map_status); i++)
                        me->map_skill(mname[i], map_status[mname[i]]);
        }

        if (mapp(prepare_status = me->query_skill_prepare()))
        {
                pname = keys(prepare_status);

                temp = sizeof(prepare_status);
                for(i = 0; i < temp; i++)
                        me->prepare_skill(pname[i]);
        }

        if (mapp(prepare_status = ob->query_skill_prepare()))
        {
                pname = keys(prepare_status);

                for(i = 0; i < sizeof(prepare_status); i++)
                        me->prepare_skill(pname[i], prepare_status[pname[i]]);
        }

        hp_status = ob->query_entire_dbase();
        my = me->query_entire_dbase();

        my["str"] = hp_status["str"];
        my["int"] = hp_status["int"];
        my["con"] = hp_status["con"];
        my["dex"] = hp_status["dex"];
        my["per"] = hp_status["per"];
        my["kar"] = hp_status["kar"];

        my["mud_age"]     = hp_status["mud_age"];
        my["age"]     = hp_status["age"];
        my["gender"]     = hp_status["gender"];
        my["max_qi"]     = hp_status["max_qi"];
        my["eff_qi"]     = hp_status["eff_qi"];
        my["qi"]         = hp_status["qi"];
        my["max_jing"]   = hp_status["max_jing"];
        my["eff_jing"]   = hp_status["eff_jing"];
        my["jing"]       = hp_status["jing"];
        my["max_neili"]  = hp_status["max_neili"];
        my["max_jingli"]  = hp_status["max_jingli"];
        my["neili"]      = hp_status["neili"];
        my["jiali"]      = hp_status["jiali"];
        my["score"]      = hp_status["score"];
//        my["shen"]      = hp_status["shen"];
        my["meili"]      = hp_status["meili"];
        my["magic_points"] = hp_status["magic_points"];
        my["potential"] = hp_status["potential"];
        my["learned_points"] = hp_status["learned_points"];
        my["experience"] = hp_status["experience"];
        my["learned_experience"] = hp_status["learned_experience"];
        my["combat_exp"] = hp_status["combat_exp"];
        my["level"] = hp_status["level"];
        my["gift"] = hp_status["gift"];
        my["can_perform"] = hp_status["can_perform"];
        my["special_skill"] = hp_status["special_skill"];
        my["family"] = hp_status["family"];
        my["born_family"] = hp_status["born_family"];
        my["character"] = hp_status["character"];
        //my["reborn"]["times"] = hp_status["reborn"]["times"];
        my["reborn/times"] = hp_status["reborn/times"];
        my["yuanshen"] = hp_status["yuanshen"];
        my["weaponname"] = hp_status["weaponname"];
        
        tmp = ob->query_entire_temp_dbase(); 
        apply = tmp["apply"]; 
        my_tmp = me->query_entire_temp_dbase(); 
        my_tmp["apply"] = apply;
        
        //蝙蝠减弱攻击增强防御
        applytmp = my_tmp["apply/attack"] / 3;
        my_tmp["apply/attack"] /= 2;
        my_tmp["apply/armor"] += applytmp;
        applytmp = my_tmp["apply/unarmed_damage"] * 3 / 4;
        my_tmp["apply/unarmed_damage"] /= 6;
        my_tmp["apply/armor"] += applytmp;
        applytmp = my_tmp["apply/damage"] * 3 / 4;
        my_tmp["apply/damage"] /= 6;
        my_tmp["apply/armor"] += applytmp;
        applytmp = my["str"] * 4 / 5;
        my["str"] = 20;
        my["dex"] += applytmp;
        my["max_qi"] *= 8;
                my["max_jing"] *= 4;
                my["jiali"] = 2;

        if( objectp(weapon=query_temp("weapon", ob)) ) {
                weapon->move(me);
                weapon->wield();
        }
        
        set("level", query("guarder_level") / 3);
        me->full_self();
                me->reset_action();
        
        set("copied", 1);
        destruct(ob);
        check_weapon(50);
}

/*void chk_own()
{
        if ( query("is_shadow", this_object()) && !objectp(query("shadow_own", this_object())) ) {
                                unconcious();
                        return;
        }
}*/

void heart_beat()
{
        if (!environment()) return;
        
                if (query("nflee") && time() > query("nflee")) {
                                unconcious();
                        return;
                }
                
        if ( query("is_shadow") ) {
                if  (!query("shadow_own") || !objectp(query("shadow_own")) || !query("shadow_own")->is_fighting() ) 
                                unconcious();
                        return;
        }

/*      if (!is_fighting()) {
                unconcious();
                return;
        }*/

        if (!random(9))
        {
                this_object()->clear_condition("no_perform");
                this_object()->clear_condition("no_exert");
                delete_temp("no_perform");
                delete_temp("no_exert");
                this_object()->stop_busy();
        }
                check_weapon(10);
        return ::heart_beat();
}

void init()
{
        object me, ob, own;
        string basename;

        me = this_object();
        ob = this_player();
        
        if (!ob->is_character()) return;
        if (query("env/invisible", ob)) return;//wiz
        if (query_temp("apply/shade_vision", this_player()) && random(15)) return;
        if (environment() && query("no_fight", environment())) return;
        basename = base_name(ob);
        if (strsrch(basename, __DIR__) != -1) return;
        own = query_temp("owner", ob);
        if (own && strsrch(base_name(own), __DIR__) != -1) return;
        tell_object(ob, query("name", me) + NOR CYN "桀桀怪笑，化为一道黑烟向你扑来...\n" NOR);
        me->kill_ob(ob);
        if (playerp(ob)) set("enemy_player", ob);
}

varargs void die()
{
        object ob;
        object killer;

        if(random(query("guarder_level") / 50) && //x% can call_die
         objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                this_object()->full_self();
                return;
        }
        
        killer = query_last_damage_from();
        if (!killer || !objectp(killer)) {
                killer = query_temp("last_opponent", this_object());
        }
        if (!killer || !objectp(killer)) {
                killer = query("enemy_player", this_object());
        }
        
                message_vision(append_color(query("death_msg"),CYN), this_object());
                        if (!query("is_shadow", this_object())) {
                                if (killer && objectp(killer) && environment(killer)==environment(this_object())) GIFT_D->delay_bonus(killer, 
                                        ([ "exp" : BONUS_EXP, "pot" : BONUS_EXP/3, "mar" : BONUS_EXP/6, "prompt" : "你在广成金船击败" + name() + "之后"]));
                        }
                                        
                destruct(this_object());
                return;
}

void unconcious()
{
        die();
        return;
}



