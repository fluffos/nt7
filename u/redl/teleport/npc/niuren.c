// This program is a part of NITAN MudLIB 
// redl 2013/8

#include <ansi.h>
inherit NPC;

void sp_attack();
int random_move();

int is_niuren() { return 1;}
int in_pkd() { return query("in_pkd");}
int in_zhen() { return query("in_zhen");}
int in_hgg() { return query("in_hgg");}

void create()
{
        set_name(NOR "牛人" NOR, ({ "niu ren", "niu", "ren" }));
        set("long", NOR "这人是top gaoshou榜上有名的著名牛人。\n" NOR);
        set("title", CYN "牛人" NOR);
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
        set("level", 1);
        set("combat_exp", 1);

                set("chat_chance", 20);
        set("chat_msg", ({
                (: random_move :),
        }));
         
//         set("chat_chance_combat", 120);
//         set("chat_msg_combat", ({
//                         (: sp_attack :),
//         }));

                set("auto_perform", 1);

        set("death_msg", NOR "\n$N大叫一声“我错了，我再也不敢牛了”，噗通一头栽倒在地，死了！\n" NOR);
        set("init_msg", NOR "\n$N随着一阵烟雾出现在你面前。。。\n" NOR);
        set("drops", ([
                "RA&EPIL60" : 1, 
                "RA&LEGEND60" : 2, 
                                "FI&/clone/medicine/yuqingwan"   : 50,
        ]));

        setup();
}

int nprotect(int dmg, object who)
{
        object niu = present("qing niu", environment());
        if (niu && objectp(niu)) {
                //niu->kill_ob(who);玩家需要主动去kill青牛，才易杀
                dmg = dmg / 100000;
                if (dmg < 1) dmg = 1;
                if (dmg > 10000 || (!objectp(who))) dmg = 10000;
                niu->receive_damage("qi", dmg, who);
                COMBAT_D->report_status(niu);
                return 1;
        }
        return 0;
}

int do_copy(object ob)
{
        object me,weapon;
        string wname, widname, wlong, weaponstr;
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        string *sname;
        string *mname;
        string *pname;
        string titl;
        int i, temp, scale = 100;
        mapping tmp, my_tmp, apply, buff2, buff_cache;

                if (!ob) return 0;
        me = this_object();
        titl = query("family/family_name", ob) + "牛人";
        set("title", CYN +titl+ NOR);
        titl = query("nickname", ob);
        set("nickname", titl);
        //set_name( query("surname", ob) + query("purename", ob) , ({ query("id", ob), "niu ren", "niu", "ren" }));
        set_name( ob->name(1) , ({ query("id", ob), "niu ren", "niu", "ren" }));
        tmp = ob->query_entire_temp_dbase(); 
        apply = tmp["apply"]; 
        buff2 = tmp["buff"]; 
        buff_cache = tmp["buff_cache"]; 
        my_tmp = me->query_entire_temp_dbase(); 
        
        if (query("copied")) return 0;
        
        if (mapp(skill_status = me->query_skills()))
        {
                skill_status = me->query_skills();
                sname = keys(skill_status);

                temp = sizeof(skill_status);
                for (i = 0; i < temp; i++)
                        me->delete_skill(sname[i]);
        }
        
        if (in_hgg()) scale = 120;
        if (in_zhen()) scale = 180;
        if (in_pkd()) scale = 260;

        if (mapp(skill_status = ob->query_skills()))
        {
                skill_status = ob->query_skills();
                sname = keys(skill_status);

                for (i = 0; i < sizeof(skill_status); i++)
                        me->set_skill(sname[i], skill_status[sname[i]] / 100 * scale);
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

        my["level"] = hp_status["level"];
        my["max_qi"]     = hp_status["max_qi"] * scale;
        my["eff_qi"]     = hp_status["eff_qi"] * scale;
        my["qi"]         = hp_status["qi"] * scale;
        my["max_jing"]   = hp_status["max_jing"] * scale;
        my["eff_jing"]   = hp_status["eff_jing"] * scale;
        my["jing"]       = hp_status["jing"] * scale;
        my["max_neili"]  = hp_status["max_neili"] / 8 * 15;
        my["max_jingli"]  = hp_status["max_jingli"] / 8 * 15;
        my["neili"]      = hp_status["neili"] * 10;
        my["jiali"]      = hp_status["jiali"] * 5;
        my["combat_exp"] = hp_status["combat_exp"] * 10;
        my["family"] = hp_status["family"];
        my["born_family"] = hp_status["born_family"];
        my["character"] = hp_status["character"];
        my["can_perform"] = hp_status["can_perform"];

        my_tmp["apply"] = apply;
        my_tmp["buff"] = buff2;
        my_tmp["buff_cache"] = buff_cache;
        
        weapon = query_temp("weapon", ob);
        if (weapon) {
                wname = query("name", weapon);
                widname = query("id", weapon);
                wlong = query("long", weapon);
//              hp_status = weapon->query_entire_dbase();
                weaponstr = "/clone/weapon/" + query("skill_type", weapon) + ".c";
                if (file_size(weaponstr) > 0) {
                        weapon = new(weaponstr);
                        weapon->move(me);
                        set("name", wname, weapon);
                        weapon->set_name(wname, ({ widname })); 
                        set("long", wlong, weapon);
                        // my = weapon->query_entire_dbase();
//                      my["insert"] = hp_status["insert"];
//                      my["magic"] = hp_status["magic"];
//                      my["qianghua"] = hp_status["qianghua"];
//                      my["qiling"] = hp_status["qiling"];
//                      my["weapon_prop"] = hp_status["weapon_prop"];
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                set("maze_item", 1);
                set("unique", 1);
                set("no_pawn", 1);
                        weapon->wield();
                }
        }
        weapon = query_temp("secondary_weapon", ob);
        if (weapon) {
                wname = query("name", weapon);
                widname = query("id", weapon);
                wlong = query("long", weapon);
                weaponstr = "/clone/weapon/" + query("skill_type", weapon) + ".c";
                if (file_size(weaponstr) > 0) {
                        weapon = new(weaponstr);
                        weapon->move(me);
                        set("name", wname, weapon);
                        weapon->set_name(wname, ({ widname })); 
                        set("long", wlong, weapon);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                set("maze_item", 1);
                set("unique", 1);
                set("no_pawn", 1);
                        weapon->wield();
                }
        }
        if (!random(10)) {
                weapon = new("/kungfu/class/tangmen/obj/hua");
        } else {
                if (random(2)) weapon = new("/d/chengdu/npc/obj/flower-leaf");
                else weapon = new("/d/chengdu/npc/obj/tielianzi");
                weapon->set_amount(999);
        }
        
        weapon->move(me);
        command("hand " + query("id", weapon));
        
        full_self();
                me->reset_action();
        set("copied", 1);
        return 1;
}

int accept_kill(object who)
{
        object *t;
        set("enemy_player", who);
        this_object()->kill_ob(who);
        who->kill_ob(this_object());
        t = this_object()->query_team(); 
        if (t && sizeof(t)) {
                t -= ({ 0 }); 
                foreach (object tob in t) 
                        tob->kill_ob(who);
        }
    return 1;//::accept_kill(who); 
}

int accept_fight(object who)
{
        return accept_kill(who); 
}

int accept_ansuan(object who)
{
        return 0; 
}

int accept_hit(object who)
{
        return accept_kill(who); 
}

void killplayer(object who)
{
        if (!who) return;
        if (!environment()) return;
        if (environment() != environment(who)) return;
        this_object()->kill_ob(who);
}

void init()
{
        object me, ob;
                me = this_player();
                ob = this_object();
                if (!query("init_room") || query("init_room")!=environment())
                {
                        //message_vision(append_color(query("init_msg"), CYN), ob);
                        set("init_room", environment());
                        ob->stop_busy();
                        command("exert shield");
                        ob->stop_busy();
                        command("exert powerup");
                        ob->stop_busy();
                        command("exert zu");
                        ob->stop_busy();
                        command("exert huaxue");
                        ob->stop_busy();
                        command("exert freeze");
                        ob->stop_busy();
                        command("exert nizhuan");
                        ob->stop_busy();
                        command("exert reserve");
                        ob->stop_busy();
                        command("exert niepan");
                        ob->stop_busy();
                        command("exert fengyun");
                        ob->stop_busy();
                        command("perform dodge.fei");
                                        ob->full_self();
                                                ob->stop_busy();
                }
                
                if (me->is_character() && !me->is_niuren() && living(me) && !query("env/invisible", me))
                {
                                if ((in_pkd() && random(10) < 4) || (in_zhen())) {
                                        this_object()->kill_ob(this_player());
                                        set("enemy_player", me);
                                } else if (in_hgg()) {
                                        // if (random(2)) tell_object(me, HIG + name() + NOR + HIG + "严厉警告道：吾护道出关，尔等速速回避。\n" NOR);   
//                                      call_out("killplayer", 8 + random(2), me);
                                }
                }
}

// void sp_attack()
// {
//         object *enemies, enemy;
//         string msg;
//         object weapon;
//         int i, dmg;
// 
//         enemies = query_enemy();
//         if( !enemies || sizeof(enemies) == 0 )
//                 return;
//         enemy = enemies[random(sizeof(enemies))];
//         if( !enemy->is_busy() && !random(50) ) {
//                 msg = HIK "\n$N往前疾冲，突然一个踉跄摔倒在地上，却恰好滑出去抱住了$n的双脚。\n" NOR;
//                 message_vision(append_color(msg, HIK),this_object(),enemy);
//                 enemy->start_busy(4+random(3));
//                 return;
//         }
//                 
//         return;
// }


int receive_damage(string type, int n, object who) 
{ 
        if (!who) return 0;
        if (nprotect(n, who)) return 0;
        return ::receive_damage(type, n / 10);
} 
      
int receive_wound(string type, int n) 
{ 
     return;
} 
      
varargs void die(object killer)
{
        object ob;
        mapping drops;

                if (nprotect(1, killer)) return;
                
        if(!random(8 - (in_pkd()? 3 : 0)) && 
         objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                return;
        }
        
        if(!objectp(killer)) {
                killer = query("enemy_player");
        }

                if( objectp(killer) && mapp(drops = query("drops")) ) {
                        EQUIPMENT_D->killer_reward(killer,this_object(),drops);
                        if (!random(2)) EQUIPMENT_D->killer_reward(killer,this_object(),drops);
                        if (!random(4)) EQUIPMENT_D->killer_reward(killer,this_object(),drops);
                        if (!random(8)) EQUIPMENT_D->killer_reward(killer,this_object(),drops);
                }
                
                message_vision(append_color(query("death_msg"),CYN), this_object());
                destruct(this_object());
                return;
}

void unconcious()
{
        object ob;
        
        ob = query_last_damage_from();
        if (ob) {
                die(ob);
                return;
        }
        ob = query_temp("last_opponent", this_object());
        if (ob) {
                die(ob);
                return;
        }
        ob = query("enemy_player");
        if (ob) {
                die(ob);
                return;
        }
        die();
        return;
}

int is_home(string where)
{
//         if (strsrch(base_name(environment()), "/d/pk/") != -1)
//                 return 1;
//         if (strsrch(where, "dongtian") == -1)
//                 return 0;
                if (in_pkd()) return 1;
                if (in_zhen()) return 0;
                if (in_hgg()) return 0;
//         if (strsrch(where, "/u/redl/") != -1)
//                 return 0;
        return 1;
}

int random_move()
{
        mapping exits;
        string *dirs, direction, to_go_place;
        object env; 
        if (query("lifetime") && query("lifetime") < time()) {
                command("wave");
                destruct(this_object());
                return 1;
        }
                if (query("combat_exp")<100000) return 0;
        if( !mapp(exits=query("exits", environment())))return 0;
        dirs = keys (exits);
        direction = dirs[random(sizeof(dirs))];
        env = environment(this_object());
        to_go_place=query("exits/"+direction, env);
                if (!is_home(to_go_place)) return 0;
        command("go " + direction);
        return 1;
}   

void test(string arg)
{
        do_copy(find_player(arg));
}

