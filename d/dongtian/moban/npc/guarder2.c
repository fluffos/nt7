// This program is a part of NITAN MudLIB 
// redl 2013/8

#include <ansi.h>
inherit NPC;

#define COPYNPC "/d/kaifeng/linggt/npc/boss"    //复制来源于
#define BONUS_EXP 10000

void sp_attack();
int random_move();
int do_copyskill();

// int fight_ob(object who)
// {
//        return -1; 
// }
// 
// int accept_kill(object who)
// {
//        return -1; 
// }
// 
// int accept_fight(object who)
// {
//        return -1; 
// }
// 
// int accept_ansuan(object who)
// {
//        return -1; 
// }

void create()
{
        set_name(YEL "傀儡将" NOR, ({ "kuilei jiang", "kui lei", "kuilei", "jiang" }));
        set("long", NOR "这货生前像是个武林高手，不知道被谁制作成了傀儡僵尸。\n" NOR);
        set("attitude", "aggressive");
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

         set("chat_chance", 30);
         set("chat_msg", ({
                (: random_move :),
         }));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                        (: sp_attack :),
                        (: sp_attack :),
                        (: sp_attack :),
                        //(: exert_function, "powerup" :),
                        //(: exert_function, "shield" :),
                        //(: exert_function, "recover" :),
                        //(: exert_function, "dispel" :),
        }));

                set("auto_perform", 1);

        set("death_msg", NOR "\n$N" + (random(2)? "咔嚓" : "噗通") + (random(2)? "一声" : "一头") + "栽倒，" + (random(2)? "散成碎片" : "摔得粉碎") + (random(2)? "。。" : "。。。") + "\n" NOR);
        //set_heart_beat(3);
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
        int i, temp;
        object weapon;
        mapping tmp, my_tmp, apply;
        
        if (query("copied")) return 1;
        
        tlv += 70 + random(11);//灵感塔50层以下水准的大米休想参与争夺洞天
        ob = new(COPYNPC);//复制灵感塔囚徒
        ob->setlv(tlv, -1, -1);
        set("title", CYN + chinese_number(tlv - 39) + "级" + NOR);
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
        my["max_qi"]     = hp_status["max_qi"] * 3;
        my["eff_qi"]     = hp_status["eff_qi"] * 3;
        my["qi"]         = hp_status["qi"] * 3;
        my["max_jing"]   = hp_status["max_jing"] * 3;
        my["eff_jing"]   = hp_status["eff_jing"] * 3;
        my["jing"]       = hp_status["jing"] * 3;
        my["max_neili"]  = hp_status["max_neili"];
        my["max_jingli"]  = hp_status["max_jingli"];
        my["neili"]      = hp_status["neili"];
        my["jiali"]      = hp_status["jiali"] * 3;
        my["score"]      = hp_status["score"];
        my["shen"]      = hp_status["shen"];
        my["meili"]      = hp_status["meili"];
        my["magic_points"] = hp_status["magic_points"];
        my["potential"] = hp_status["potential"];
        my["learned_points"] = hp_status["learned_points"];
        my["experience"] = hp_status["experience"];
        my["learned_experience"] = hp_status["learned_experience"];
        my["combat_exp"] = hp_status["combat_exp"] * 3;
        my["level"] = hp_status["level"];
        my["gift"] = hp_status["gift"];
        my["can_perform"] = hp_status["can_perform"];
        my["special_skill"] = hp_status["special_skill"];
        my["family"] = hp_status["family"];
        my["born_family"] = hp_status["born_family"];
        my["character"] = hp_status["character"];
        //my["reborn"]["times"] = hp_status["reborn"]["times"];
        my["yuanshen"] = hp_status["yuanshen"];
        my["weaponname"] = hp_status["weaponname"];
        
        tmp = ob->query_entire_temp_dbase(); 
        apply = copy(tmp["apply"]); 
        my_tmp = me->query_entire_temp_dbase(); 
        my_tmp["apply"] = apply;

        if( objectp(weapon=query_temp("weapon", ob)) ) {
                weapon->move(me);
                weapon->wield();
        }
        
        me->full_self();
                me->reset_action();
        
        set("copied", 1);
        destruct(ob);
        check_weapon(100);
}

void heart_beat()
{
        object croom;
        
        if (!environment()) return;
        
        if (strsrch(base_name(environment()), "/d/pk/") != -1) {
                croom = query("croom");
                if (croom) {
                        croom->add_qy();
                }
        }
        
                if (query("nflee") && time() > query("nflee")) {
                                unconcious();
                        return;
                }
                
        // 解除不能perform yun的限制
        if (!random(3))
        {
                this_object()->clear_condition("no_perform");
                this_object()->clear_condition("no_exert");
                delete_temp("no_perform");
                delete_temp("no_exert");
                this_object()->stop_busy();
        }
                check_weapon(20);
        return ::heart_beat();
}

void init()
{
        object me, ob, croom;
        string there, basename;

        me = this_object();
        ob = this_player();
        
        if (!ob->is_character()) return;
        if (query("env/invisible", ob)) return;
        if (query_temp("apply/shade_vision", ob)) return;
        
        croom = query("croom");
        if (!croom) return;
        if (croom->owner_level(ob)) return;
        basename = base_name(ob);
        if (strsrch(basename, __DIR__) != -1) return;
        
        there = base_name(environment());
        if (strsrch(there, "/d/pk/") != -1) {
                if (playerp(ob)) return;//屠人场时不主动kill玩家
                if (!me->is_fighting()) {
                        me->set_leader(ob);
                        message_vision(append_color(NOR + CYN + "$N对$n怒喝道：气运之争不是儿戏，乖乖领死吧。\n" + NOR, CYN), me, ob);
                }
        } else {
                if (strsrch(basename, "data/warcraft/") != -1) return;
                if (ob->is_baby()) return;
//              if (basename=="/kungfu/class/misc/haigui") return;
//              if (basename=="/kungfu/class/misc/shendiao") return;
                if (!me->is_fighting()) {
                        me->set_leader(ob);
                        message_vision(append_color(NOR + CYN + "$N对$n怒喝道：大胆，竟敢擅闯" + query("dtname") + "，乖乖领死吧。\n" + NOR, CYN), me, ob);
                }
        }
        if (playerp(ob)) set("enemy_player", ob);
        me->kill_ob(ob);
}

void sp_attack()
{
        object *enemies, enemy, ob;
        string msg;
        object *obs;

        enemies = query_enemy();
        if( !enemies || sizeof(enemies) == 0 )
                return;
                
        enemy = enemies[random(sizeof(enemies))];
        if( !random(10) && (strsrch(base_name(environment()), "/d/pk/") == -1) ) {
                        obs = filter_array(all_inventory(environment(this_object())),
                           (: $1->is_character() &&
                           query("is_shadow", $1)
                           :));
                        if (sizeof(obs)<12) {
                msg = NOR + HIK + "\n$N" + NOR + HIK + (random(2)? "大声" : "一阵") + (random(2)? "尖啸" : "疾呼") + "，" + (random(2)? "身后" : "旁边") + "跑来个傀儡扑向$n" + NOR + HIK + "。\n\n" NOR;
                message_vision(append_color(msg, HIK),this_object(),enemy);
                                ob = new(__DIR__"guarder");
                                set("shadow_own", this_object(), ob);
                                set("is_shadow", 1, ob);
                                set("guarder_level", query("guarder_level") - 30, ob);
                                set("nflee", time() + 120 + random(30) , ob);
                                ob->do_copyskill();
                                ob->move(environment(this_object())); 
                                set("name", query("dtname") + query("name", ob), ob);
                                set("enemy_player", enemy, ob);
                                ob->stop_busy();
                        ob->command("exert powerup");
                        ob->stop_busy();
                        ob->command("exert shield");
                        ob->stop_busy();
                        ob->command("exert zu");
                        ob->stop_busy();
                                ob->set_leader(enemy);
                                ob->kill_ob(enemy);
                        }
        }
        
        return;
}

varargs void die()
{
        object ob;
        object killer;
        int perc = 1;

        if(random(8) && 
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
                if (strsrch(base_name(environment()), "/d/pk/") != -1) perc = 350;
                message_vision(append_color(query("death_msg"),CYN), this_object());
                                if (killer && objectp(killer) && environment(killer)==environment(this_object())) GIFT_D->delay_bonus(killer, 
                                        ([ "exp" : BONUS_EXP * perc, "pot" : BONUS_EXP * perc /3, "mar" : BONUS_EXP * perc /6, "prompt" : "你在击退" + name() + "之后"]));
                                        
                                if (environment() && strsrch(base_name(environment()), "/d/pk/") != -1 && query("croom")){
                                        CHANNEL_D->channel_broadcast("dt", NOR + WHT + query("name") + NOR + WHT + "携带( " + (string)(query("croom")->query_dt_qy()) + " )点气运黯然离场。\n" + NOR);
                                }
                destruct(this_object());
                return;
}

void unconcious()
{
        die();
        return;
}

int can_getall(string where)
{
        if (strsrch(where, "caidi") != -1
                || strsrch(where, "chufang") != -1
                || strsrch(where, "yaopu") != -1
                || strsrch(where, "liandanfang") != -1
                ) return 0;
        return 1;
}

int is_home(string where)
{
        if (strsrch(base_name(environment()), "/d/pk/") != -1)
                return 1;
        if (strsrch(where, "dongtian") == -1)
                return 0;
        if (strsrch(where, "guangchang") != -1)
                return 0;
        if (strsrch(where, "enter") != -1)
                return 0;
        if (strsrch(where, "houshan") != -1)
                return 0;
        if (strsrch(where, "dadian") != -1)
                return 0;
        if (strsrch(where, "shuilao") != -1)
                return 0;
        if (strsrch(where, "shuifang") != -1)
                return 0;
        return 1;
}

int random_move()
{
        mapping exits;
        string *dirs, direction, to_go_place;
        object env; 
        if (can_getall(base_name(environment()))) command("get all");
        if( !mapp(exits=query("exits", environment())))return 0;
        dirs = keys (exits);
        direction = dirs[random(sizeof(dirs))];
        env = environment(this_object());
        to_go_place=query("exits/"+direction, env);
                if (!is_home(to_go_place)) return 0;
        command("go " + direction);
        return 1;
}   




