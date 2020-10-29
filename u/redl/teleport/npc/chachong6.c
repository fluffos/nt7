      // This program is a part of NITAN MudLIB 
// redl 2015/11
// /u/redl/teleport/qroom.c

#include <ansi.h>
inherit NPC;

int wieldweapon()
{
        string weaponstr;
        object weapon;

        weaponstr = query("weapon_A");
        //DEBUG_CHANNEL("weaponstr:" + weaponstr);
        if (strlen(weaponstr) && file_size(weaponstr + ".c")) {
                        weapon = new(weaponstr);
                        weapon->move(this_object());
                        weapon->wield();
        }
        weaponstr = query("weapon_B");
        if (strlen(weaponstr) && file_size(weaponstr + ".c")) {
                        weapon = new(weaponstr);
                        weapon->move(this_object());
                        weapon->wield();
        }
        return 1;
}

string query_save_file()
{
        object env;
        return sprintf("/temp/qroom/%s/cc%d.o", query("owner_id"), query("idx"));
}
int restore()
{
                object own;
        string ownid, file;
        if( !stringp(file = this_object()->query_save_file()) || file_size(file) < 1 ) return 0;
        ownid = query("owner_id");
        own = find_player(ownid);
        if (!own) {
                return 0;
        }
                restore_object(file);
        set("owner", own);
        set_temp("owner", own);
                wieldweapon();
        return 1;
}

int do_store()
{
        string s = sprintf("/temp/qroom/%s", query("owner_id"));
        if (!sizeof(get_dir(s))) mkdir(s);
        save_object(query_save_file());//mapping没法save
        return 1;
}

void create()
{
        set_name(NOR "茶宠" NOR, ({ "cha chong", "cha", "chong", "cc" }));
        set("title", CYN "茶宠" NOR);
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
        set("auto_perform", 1);
        set("death_msg", NOR "\n$N化作一道水蒸气不见了。\n" NOR);
        set("init_msg", NOR "\n$N随着一片水雾出现在你面前...\n" NOR);
        setup();
}

int do_copy(object ob, object own, int idx)
{
        object me,weapon;
        string wname, widname, wlong, weaponstr;
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        string *sname;
        string *mname;
        string *pname;
        int i, temp, itmpsk, scale = 99;
        mapping tmp, my_tmp, apply, buff2, buff_cache;

                if (!ob) return 0;
        //if (query("copied")) return 0;
        me = this_object();
        set("owner", own);
        set("owner_id", query("id", own));
        set_temp("owner", own);
        set("idx", idx);
        scale += -( idx * 2 );
        //set("title", CYN +own->name()+"的"+chinese_number(idx)+"号茶宠" + NOR);
        set("title", NOR CYN +chinese_number(idx)+"号茶宠" + NOR);
        set_name(NOR + ob->name()+ NOR, ({ "cha chong", "cha", "chong", "cc" }));
        tmp = ob->query_entire_temp_dbase(); 
        apply = tmp["apply"]; 
        buff2 = tmp["buff"]; 
        buff_cache = tmp["buff_cache"]; 
        my_tmp = me->query_entire_temp_dbase(); 
        
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

                for (i = 0; i < sizeof(skill_status); i++) {
                        itmpsk = skill_status[sname[i]] / 100 * scale;
                        if (itmpsk > 100000) itmpsk /= 2;
                        if (itmpsk > 1000000) itmpsk /= 3;
                        if (itmpsk > 10000000) itmpsk /= 4;
                        if (itmpsk > 100000000) itmpsk /= 5;
                        if (itmpsk > 1000000000) itmpsk /= 6;
                    me->set_skill(sname[i], itmpsk);
                }
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
        my["age"] = hp_status["age"];
        my["gender"] = hp_status["gender"];
        my["level"] = hp_status["level"];
        
        my["max_qi"]     = hp_status["max_qi"] / 1000 * scale;
        my["eff_qi"]     = hp_status["eff_qi"] / 1000 * scale;
        my["qi"]         = hp_status["qi"] / 1000 * scale;
        my["max_jing"]   = hp_status["max_jing"] / 1000 * scale;
        my["eff_jing"]   = hp_status["eff_jing"] / 1000 * scale;
        my["jing"]       = hp_status["jing"] / 1000 * scale;
        my["max_neili"]  = hp_status["max_neili"] / 1000 * scale;
        my["max_jingli"]  = hp_status["max_jingli"] / 1000 * scale;
        my["neili"]      = hp_status["neili"] / 1000 * scale;
        my["jiali"]      = hp_status["jiali"] / 100 * scale;
        my["combat_exp"] = hp_status["combat_exp"] / 1000 * scale;
        my["family"] = hp_status["family"];
        my["born_family"] = hp_status["born_family"];
        my["ability2"] = hp_status["ability2"];
        my["ability_count"] = hp_status["ability_count"];
        my["character"] = hp_status["character"];
        my["can_perform"] = hp_status["can_perform"];

        my_tmp["apply"] = apply;
        my_tmp["buff"] = buff2;
        my_tmp["buff_cache"] = buff_cache;
        
        weapon = query_temp("weapon", ob);
        if (weapon) {
                weaponstr = query("skill_type", weapon);
                if (weaponstr =="pin") weaponstr ="sword";
                weaponstr = "/clone/weapon/" + weaponstr;
                set("weapon_A", weaponstr);
                //DEBUG_CHANNEL("weapon:" + weaponstr);
        }
        weapon = query_temp("secondary_weapon", ob);
        if (weapon) {
                weaponstr = query("skill_type", weapon);
                if (weaponstr =="pin") weaponstr ="sword";
                weaponstr = "/clone/weapon/" + weaponstr;
                set("weapon_B", weaponstr);
                //DEBUG_CHANNEL("weapon:" + weaponstr);
        }
        
        //set("copied", 1);
        do_store();
        return 1;
}

int accept_ansuan(object who)
{
        return 0; 
}

// int callout_exert(string file, object me)
// {
//      call_other(file, "exert", me, me);
//      me->stop_busy();
//      return 1;
// }

int auto_exert(object me)
{
        int l;
        string dir;
        string file;
        mixed *all_file;
        string skill;

                skill = me->query_skill_mapped("force");
                if (!skill || !strlen(skill)) return 0;

        if( !stringp(dir = SKILL_D(skill) + "/") ||
            file_size(dir) != -2 )
                return 0;

        if( file_size(dir + "exert/") == -2 ) {
                all_file = get_dir(dir + "exert/");
                if( !sizeof(all_file) )
                        all_file = get_dir(dir);
                else
                        dir += "exert/";
        } else
                all_file = get_dir(dir);

        if( !sizeof(all_file) )
                return 0;

        all_file = filter_array(all_file, (: is_c_file($1) :));
        if( !sizeof(all_file) )
                return 0;

                foreach (file in all_file) {
                l = strlen(file);
                file = dir + file[0..l-3];
                //DEBUG_CHANNEL("exert:"+file+"\n");
                if (sscanf(file,"%*s/roar") || sscanf(file,"%*s/youming")) continue;
                //DEBUG_CHANNEL("exert ok\n");
                call_other(file, "exert", me, me);
                        me->stop_busy();
        }
        return 1;
}


int init()
{
                int idx;
                string ownid;
        object me, ob;
                me = this_player();
                ob = this_object();
                if (!environment(ob)) return 1;
                if (!query("idx"))
                {
                        if (!sscanf(base_name(ob),"%*s/npc/chachong%d", idx)) idx = 1;
                        if (!sscanf(base_name(environment(ob)),"%*s/qroom/%s", ownid)) {
                                destruct(this_object());
                                return 1;
                        }
                set("idx", idx);
                set("owner_id", ownid);
                        if (restore()) {
                                set("startroom", base_name(environment(ob)));
                                message_vision(append_color(query("init_msg"),CYN), this_object());
                                ob->not_keep_heart_beat();
                                set_heart_beat(3);
                                ob->reset_action();
                                return 1;
                        }
                        destruct(this_object());
                        return 1;       
                }
                return 1;       
}

     
int receive_wound(string type, int n) 
{ 
     return;
} 
      
varargs void die(object killer)
{
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

void jointeam()
{
        object own, me = this_object();
        own = query("owner");
        if (!own) return;
        own->add_team_member(me); 
}

int do_backhome()
{
        object ob = find_object(query("startroom"));
        
        if( ob ) this_object()->return_home(ob);
        else {
                tell_object(environment(), this_object()->name()+"匆匆忙忙的走了。\n");
                destruct(this_object());
                return 1;
        }
        return 1;
}

int do_helpkill(object own, object me)
{
        object room, ene, *enemies;
        room = environment(own);
        if (!room) return 1;
        tell_room(room, NOR YEL "地上突然冒出枚黑棋子，慢慢涨大，" + name() + NOR YEL  "从里面走出来后，黑棋子又沉入地下。\n" NOR);
        me->move(room);
        me->full_self();
        me->auto_exert(me);
        me->jointeam();
        me->set_leader(own);
        set("helpkill_time", time() + 300, me);
        set_temp("guardfor", own, me);
        set_temp("guarding", 1, me);
        me->reset_action();
        me->stop_busy();
        enemies = own->query_enemy();
        foreach (ene in enemies) {
                if (!ene) continue;
                me->kill_ob(ene);
        }
        me->full_self();
        return 1;
}

int heart_beat()
{
        object own, *enemies;
        int htime = query("helpkill_time");
        if (!environment()) return 1;
        own = query("owner");
        if (!own) {
                tell_object(environment(), this_object()->name()+"匆匆忙忙的走了。\n");
                destruct(this_object());
                return 1;
        }
        if (htime > 0 && htime < time())
        {
                delete("helpkill_time");
                do_backhome();
        }
//      command("say " + (string)time());
        return ::heart_beat();
}

