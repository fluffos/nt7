// user.c

#include <origin.h>
#include <user.h>
#include <ansi.h>
#include <command.h>

inherit CHARACTER;
inherit F_AUTOLOAD;
inherit F_SAVE;
inherit F_SHELL;
inherit F_BUSINESS;

#define DEFAULT_PRISON          "/d/register/prison"
#ifndef PROTECT_AGE
#define PROTECT_AGE     14
#endif

// 死亡保护
protected int die_protect(object ob);
protected void cancle_die_protect(object ob);

// 分站使用
nosave int admin_flag = 0;              // 是否是特殊的管理员？

// 数据是否完整？
nosave int user_cracked = 0;            // RESTORE 时检查数据并设置该标志

nosave int net_dead;                    // 标志：是否断开了连接
nosave int last_age_set = 0;            // 上一次更新AGE的时间
nosave int user_say = 0;                // 一定时间以内玩家做的say-action
nosave int user_command = 0;            // 一定时间以内玩家发送的命令
nosave int attach_flag = 0;             // 是否正在和系统联络
int        at_time = 0;                 // 在什么时间计算的
int        ban_to = 0;                  // 在什么时间解禁玩家
string     ban_say_msg = "";            // 禁止说话的消息

nosave string my_defeater_id;           // 上一次打晕你的人ID
nosave string my_killer_id;             // 上一次杀你的人的ID
nosave int    craze = 0;                // 愤怒

// globals variables
string  prison = 0;
int     time_to_leave = 0;


int     is_stay_in_room()       { return 1; }
int     is_player()             { return clonep(); }
string  query_prison()          { return prison; }
int     query_time_to_leave()   { return time_to_leave; }
int     is_in_prison()          { return stringp(prison); }
int     is_net_dead()           { return net_dead || ! interactive(this_object()); }

varargs string calc_sec_id(int raw);

#define MAX_COMMAND_ONE_SECTION         40
#define MAX_SAY_ONE_SECTION             60
#define BAN_SAY_PERIOD                  60

int query_current_neili_limit();
int query_neili_limit();
int query_current_jingli_limit();
int query_jingli_limit();
int query_potential_limit();
int query_experience_limit();

int is_user() { return 1; }

mapping query_USER()
{
        mapping data = ([]);

        data["at_time"] = at_time;
        data["ban_to"] = ban_to;
        data["ban_say_msg"] = ban_say_msg;
        data["prison"] = prison;
        data["time_to_leave"] = time_to_leave;
        return data;
}

int set_USER(mapping data)
{
        if( !mapp(data) ) return 0;

        at_time = data["at_time"];
        ban_to = data["ban_to"];
        ban_say_msg = data["ban_say_msg"];
        prison = data["prison"];
        time_to_leave = data["time_to_leave"];
        return 1;
}

// 判断是否具有管理权限：如果是版本发布站点或是通过 PASSWD
// 命令设置过，则具有管理权限。具有该权限的巫师可是使用诸如
// clone、call、log、smash、copyskill等命令。
int is_admin()  { return /*VERSION_D->is_release_server() ||*/ admin_flag == 21 || getuid() == "lonely" || getuid() == "redl"; }
int set_admin() { if( is_root(previous_object()) ) admin_flag = 21; }

void create()
{
        ::create();
        set_name("使用者物件", ({ "user object", "user", "object" }) );
}

void terminal_type(string term_type)
{
        set_temp("terminal_type", term_type);
        message("system", "终端机型态设定为 "+term_type+"。\n", this_object());
}

void window_size(int width, int height)
{
        set_temp("window_size", ({width, height}));
        message("system", "终端窗口大小设置为 " + width + " × " + height + "。\n", this_object());
}

void reset()
{
        int lv;

        if( (int)query("thief") > 0 )
                addn("thief", -1);

        if( (int)query("total_hatred") > 0 )
                addn("total_hatred", -1);

        if( (lv = query_skill("xiantian-gong", 1)) >= 60 ||
            (lv = query_skill("quanzhen-xinfa", 1)) >= 60 ) {
                if( can_improve_skill("force") )
                        improve_skill("force", lv * 20);

                if( query_skill("quanzhen-xinfa", 1) >= 60 &&
                    can_improve_skill("quanzhen-xinfa") )
                        improve_skill("quanzhen-xinfa", lv * 10);

                if( query_skill("xiantian-gong", 1) >= 60 &&
                    can_improve_skill("xiantian-gong") &&
                    SKILL_D("xiantian-gong")->valid_learn(this_object()) )
                        improve_skill("xiantian-gong", lv * 10);
        }
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
        string id;

        id = geteuid();
        if( !id ) id = getuid();
        if( !stringp(id) ) return 0;
        return sprintf(DATA_DIR "user/%c/%s", id[0], id);
}
// 服务类
int quest_letter_srv() { return (int)query("srv/quest_letter") > time(); }
int quit_save_srv() { return (int)query("srv/quit_save") > time(); }
int start_room_srv() { return (int)query("srv/start_room") > time(); }
int enter_jtshe_srv() { return (int)query("srv/enter_jtshe") > time(); }
int qiankun_volume_srv() { return (int)query("srv/qiankun_volume"); }

int set_srv(string arg, int t)
{
        if( !stringp(arg) || !intp(t) )
                return 0;

        if( (int)query("srv/"+arg) > time() )
                addn("srv/"+arg, t);
        else
                set("srv/"+arg, time()+t);

        return 1;
}

// override set function
varargs mixed set(string idx, mixed para, object ob)
{
        int i, n, s, now_lvl, old_lvl;
        mapping spc_data, my;
        string skill, *files;
        string *spe_skill = ({
                "monster", "nopoison", "demon", "ghost", "wisdom", "stealth",
        });
        string *reborn_skill = ({
                "sophistry", "capture", "kingkong", "immortal", "musha",
                "recover", "astral",
        });

        if( !ob )
                ob = this_object();

        if( idx == "combat_exp" && para && clonep(ob) && geteuid(ob) ) {
                if( para > query("combat_exp") ) {
                        old_lvl = query("level", ob);
                        if( !old_lvl || old_lvl < 1 ) old_lvl = 1;

                        // 等级封印
                        if( !UPDATE_D->can_improve_level(old_lvl) &&
                            para > to_int(pow(old_lvl, 3.0)*10000) ) {
                                //tell_object(ob, HIR "由于你处于等级封印中，你的实战经验无法提升！\n" NOR);
                                return;
                        }

                        for (i = old_lvl; ;i++) {
                                if( to_int(pow(i+1, 3)) > (para / 10000) ) {
                                        now_lvl = i;
                                        break;
                                }
                        }

                        if( now_lvl > old_lvl )
                        {
                                n = now_lvl - old_lvl;
                                ob->set_db("level", now_lvl);

                                if( now_lvl >= 100 && ob->query_skillo("martial-cognize", 1) >= 4500 &&
                                    query("animaout", ob) && !query("yuanshen_level", ob) )
                                {
                                        addn("energy", 1, ob);
                                        set("yuanshen_level", 1, ob);
                                        set("yuanshen/attack", 100, ob);
                                        set("yuanshen/defense", 100, ob);
                                        tell_object(ob, HIR "你冲破了瓶颈，元婴成长为元神，你可以修炼元神了！\n");
                                }

                                addn("ability", 4 * n, ob);
                                addn("experience", 20 * n, ob);
                                addn("potential", 200 * n, ob);
                                addn("magic_points", 20 * n, ob);

                                tell_object(ob, HIY "只见一道红光飞进你的体内，你的人物等级提升了！\n" +
                                        "此次升级，你获得了" + chinese_number(4 * n) +
                                        "点能力点、" + chinese_number(200 * n) +
                                        "点潜能、" + chinese_number(20 * n) +
                                        "点实战体会、" + chinese_number(20 * n) +
                                        "点灵慧！\n" NOR);

                                //UPDATE_D->improve_valid_level(ob, now_lvl);
                        }
                }
                return set_db(idx, para);
        } else
        if( idx == "yuanshen_exp" )
        {
                if( para > query("yuanshen_exp", ob) )
                {
                        old_lvl = query("yuanshen_level", ob);
                        if( !old_lvl || old_lvl < 1 ) old_lvl = 1;

                        for (i = old_lvl; ;i++)
                        {
                                if( to_int(pow(i+1, 3)) > (para / 10000) )
                                {
                                        now_lvl = i;
                                        break;
                                }
                        }

                        if( now_lvl > old_lvl )
                        {
                                n = (now_lvl - old_lvl)*10;
                                ob->set("yuanshen_level", now_lvl);

                                addn("yuanshen/attack", n, ob);
                                addn("yuanshen/defense", n, ob);
                                //addn("yuanshen/damage", n, ob);
                                //addn("yuanshen/armor", n, ob);

                                tell_object(ob, HIY "只见一道红光飞进你的体内，你的元神等级提升了！\n" NOR);

                                if( now_lvl % 10 == 0 )
                                {
                                        message_vision(HIY "突然天空出现一道玄光与$N" HIY "身泛起的红光相接，$N" HIY "全体通红！\n" NOR, ob);
                                        n = now_lvl / 10;
                                        s = old_lvl / 10;
                                        for( i=s+1;i<=n;i++ ) {
                                                switch( i ) {
                                                        //case 0 : tell_object(ob, HIY "你的元神等级提升到真元境界！\n" NOR);break;
                                                        case 1 :
                                                                addn("energy", 1, ob);tell_object(ob, HIY "你的元神等级提升到引魂境界！\n" NOR);break;
                                                        case 2 :
                                                                addn("energy", 2, ob);tell_object(ob, HIY "你的元神等级提升到元罡境界！\n" NOR);break;
                                                        case 3 :
                                                                addn("int", 2, ob);
                                                                addn("str", 2, ob);
                                                                addn("con", 2, ob);
                                                                addn("dex", 2, ob);
                                                                addn("ys/int", 2, ob);
                                                                addn("ys/str", 2, ob);
                                                                addn("ys/con", 2, ob);
                                                                addn("ys/dex", 2, ob);
                                                                addn("energy", 2, ob);
                                                                tell_object(ob, HIY "你的元神等级提升到阴阳境界！\n" NOR);
                                                                tell_object(ob, HIR "你的各项先天天赋都提高了２点！\n" NOR);
                                                                break;
                                                        case 4 :
                                                                addn("energy", 3, ob);tell_object(ob, HIY "你的元神等级提升到神丹境界！\n" NOR);break;
                                                        case 5 :
                                                                addn("energy", 3, ob);tell_object(ob, HIY "你的元神等级提升到神婴境界！\n" NOR);break;
                                                        case 6 :
                                                                addn("energy", 4, ob);
                                                                set("yuanshen/avoid_weak", 10, ob);
                                                                set("yuanshen/research_effect", 100, ob);
                                                                tell_object(ob, HIY "你的元神等级提升到神通境界！\n" NOR);
                                                                tell_object(ob, HIY "你抵抗虚弱的能力提高了１０点！\n" NOR);
                                                                tell_object(ob, HIY "你对武功的研究效率提高了１００％！\n" NOR);
                                                                break;
                                                        case 7 :
                                                                addn("energy", 4, ob);tell_object(ob, HIY "你的元神等级提升到渡虚境界！\n" NOR);break;
                                                        case 8 :
                                                                addn("energy", 5, ob);tell_object(ob, HIY "你的元神等级提升到神劫境界！\n" NOR);break;
                                                        case 9 :
                                                                addn("energy", 5, ob);
                                                                set("yuanshen/immortal", 5, ob);
                                                                //set("yuanshen/reduce_damage", 50, ob);
                                                                tell_object(ob, HIY "你的元神等级提升到不灭境界！\n" NOR);
                                                                tell_object(ob, HIY "你的元神终于修炼成盘古真身神功！\n" NOR);

                                                                my = ob->query_entire_dbase();
                                                                spc_data = ([ "hermit" : 1 ]);
                                                                /*
                                                                skill = spe_skill[random(sizeof(spe_skill))];
                                                                spc_data += ([ skill : 1 ]);
                                                                */
                                                                files = reborn_skill;
                                                                files -= keys(my["special_skill"]); // 去除转世技能重叠的bug
                                                                if( sizeof(files) > 0 )
                                                                {
                                                                        skill = files[random(sizeof(files))];
                                                                        spc_data += ([ skill : 1 ]);
                                                                        files -= ({ skill });

                                                                        if( sizeof(files) > 0 && random(10) == 1 ) {
                                                                                skill = files[random(sizeof(files))];
                                                                                spc_data += ([ skill : 1 ]);
                                                                        }
                                                                }
                                                                my["special_skill"] += spc_data;
                                                                tell_object(ob, HIY "由于元神修炼到不灭境界，你成功的激活了血脉力量及先天技能！\n" NOR);
                                                                break;
                                                        default:
                                                                addn("yuanshen/immortal", 1, ob);
                                                                tell_object(ob, HIY "你的盘古真身神功触发几率提升了１点！\n" NOR);
                                                                break;
                                                }
                                        }
                                }
                        }
                }
        } else
        if( idx == "name" && clonep(ob) && geteuid(ob) ) {
                NAME_D->change_name(ob, para, 1);
                return para;
        } else
                return set_db(idx, para);
}

varargs int delete(string prop, object ob)
{
        object me, pob;

        me = this_player();
        ob = this_object();
        pob= previous_object();

        if( prop == "family" || prop == "family_name" ||
            prop == "betrayer" || prop == "detach" )
                log_file("static/delete",
                        sprintf("%s delete %s %s with %s at %s.\n",
                                me->query_idname(), ob->query_idname(), prop, base_name(pob), ctime(time())) );

        return ob->delete(prop);
}

// override add function by Lonely
mixed add(string prop, mixed data)
{
        string para;
        mixed old;
        int level;

        if( prop == "combat_exp" && clonep(this_object()) &&
            geteuid(this_object()) ) {
                if( !(old = query(prop)) )
                        return set(prop, data);

                if( data < 1 )
                        return set_db(prop, old + data);

                level = query("level");
                if( !level || level < 1 ) level = 1;
                if( !UPDATE_D->can_improve_level(level) &&
                    query("combat_exp") > to_int(pow(level, 3.0)*10000) )
                        return;

                return set(prop, old + data);
        } else
        if( prop == "yuanshen_exp" )
        {
                if( !(old = query(prop)) )
                        return set(prop, data);

                if( data < 1 )
                        return set_db(prop, old + data);

                return set(prop, old + data);
        } else
                return ::add(prop, data);
}

int save()
{
        int res;

        /*
        if( user_cracked )
                // 数据不完整，不能保存
                return 1;
        */

        if( query_temp("user_setup") ) {
                save_autoload();
                set("sec_id", calc_sec_id());   // save sec_id
#ifdef DB_SAVE
                res = DATABASE_D->db_save_all(this_object());
                if( TX_SAVE )
                        res = ::save();
#else
                res = ::save();
#endif
                clean_up_autoload();            // To save memory
        } else {
                set("sec_id", calc_sec_id());   // save sec_id
#ifdef DB_SAVE
                res = DATABASE_D->db_save_all(this_object());
                if( TX_SAVE )
                        res = ::save();
#else
                res = ::save();
#endif
        }

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(me);
#endif
        return res;
}

int restore()
{
        int res;
        string sec_id;

#ifdef DB_SAVE
        res = DATABASE_D->db_restore_all(this_object());

        if( (int)query_temp("restore_mysql") )
                 res = ::restore();

        // if( res && ! DATABASE_D->crc_status())
        if( res )
#else
        res = ::restore();

        if( res )
#endif
        {
                /*
                if( stringp(sec_id = query("sec_id")) ) {
                        if( crypt(calc_sec_id(1), sec_id) != sec_id ) {
                                // 数据不完整
                                log_file("static/user",
                                         sprintf("%s %s's data my be corrupt.\n",
                                                 log_time(), getuid()));
                                user_cracked = 1;
                                return 0;
                        }
                } else {
                        log_file("static/user",
                                 sprintf("%s %s lost assure key.\n",
                                         log_time(), getuid()));
                        user_cracked = 1;
                        return 0;
                }
                */

                // 数据完整
                user_cracked = 0;
        }
        if( !query("on_time") )
                set("on_time", query("mud_age"));

        return res;
}

// This function updates player's age, called by heart_beat()
void update_age()
{
        int age;
        int delta;
        object env;

        env = environment();
        if( !env ) return;

        if( !last_age_set ) {
                last_age_set = time();
                addn("mud_age", 0);
        }

        if( (delta = (time() - last_age_set)) > 100 )
                // time too long
                delta = 100;

        // 离线练功时间
        if( !interactive(this_object()) && query("doing") )
                addn("offline_time", delta);
        else
        if( interactive(this_object()) )
                addn("online_time", delta);

        if( !env->is_chat_room() ||
            !query("env/halt_age") ) {
                // Update age
                addn("mud_age", delta);
                if( query("monfee") < time() ) // 月费控制，非月费用户才在这里扣点
                        addn("on_time", delta);
                if( time_to_leave )
                        time_to_leave -= delta;
        }

        last_age_set = time();
        //age = query("age_modify") + query("mud_age") / 86400;
        age = query("age_modify") + query("mud_age") / 518400;
/*
        if( age > 118 ) age = 46 + (age - 118) / 4; else
        if( age > 28 )  age = 16 + (age - 28) / 3; else
        if( age > 4 )   age = 4  + (age - 4) / 2;
*/
        age -= (int)query_temp("apply/reduce_age");
        if( age < 0 ) age = 0;
        if (query("reborn/times")) age += 5;
        else age += 11;

        set("age", age);
        if( query("age") > 17 ) {
                if( query("newbie") )  delete("newbie");
                if( query("map") ) {
                        delete("map");
                        set("map_all", 1);
                }
        }
        if( query("age") < 18 && !query("no_newbie") ) set("newbie", 1);

        // 八荒六合唯我独尊功
        if( query_skill_mapped("force") == "bahuang-gong" ) {
                if( age >= 60 ) {
                        set("mud_age", 1382400);
                        set("age", 30);
                }
        }

        // 全真先天功
        if( query_skill_mapped("force") == "xiantian-gong" &&
            !query("sex") && query("age") >= 40 ) {
                set("mud_age", 2246400);
                set("age", 40);
                return;
        }

        if( query_skill("fanlao-huantong", 1) >= 500 && query("age") > 25 )
                set("age", 25);

        //设置生日状态
        if( (int)query("mud_age") % 86400 < 240 )
                set("on_birthday", 1);
        else
                set("on_birthday", 0);

}

void setup()
{
        // We want set age first before new player got initialized with
        // random age.
        last_age_set = 0;
        update_age();

        ::setup();

        // set the enable flag to enable save
        set_temp("user_setup", 1);

        restore_autoload();
        CHANNEL_D->register_channel(this_object(), query("channels"));
        if( query("doing") )
                CLOSE_D->continue_doing(this_object());
}

void user_dump(int type)
{
        switch(type)
        {
        case DUMP_NET_DEAD:
                if( environment() ) {
                            tell_room(environment(this_object()), query("name", this_object()) + "断线超过 " +
                                  NET_DEAD_TIMEOUT / 60 + " 分钟，自动退出这个世界。\n");
                }
                catch(command("quit"));
                if( this_object() && !query("doing") ) {
                        // command quit failed.
                        QUIT_CMD->force_quit(this_object());
                }
                break;

        case DUMP_IDLE:
                if( query_temp("learned_idle_force") ) {
                        message_vision("$N狂笑三声，道：我终于明白了！\n",
                                       this_object());
                        tell_object(this_object(), "你经过长时间的发"
                                    "呆，终于对发呆神功的理解又深了一层！\n");
                        improve_skill("idle-force", 360000);
                        delete_temp("learned_idle_force");
                } else
                        tell_object(this_object(), "对不起，您已经发呆超过 " +
                                    IDLE_TIMEOUT / 60 + " 分钟了，请下次再来。\n");
                if( environment() ) {
                             if (query("env/invisible") < 10) tell_room(environment(), "一阵风吹来，将发呆中的" + query("name") +
                                   "化为一堆飞灰，消失了。\n", ({this_object()}));
                }
                command("quit");
                if( this_object() && !query("doing") ) {
                        // command quit failed.
                        QUIT_CMD->force_quit(this_object());
                }
                break;
        default:
                return;
        }
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.
protected void net_dead()
{
        object link_ob;

        this_object()->remove_interactive();

        if( !query("doing") )
                set_heart_beat(0);

        if( objectp(link_ob = query_temp("link_ob")) ) {
                if( query_temp("ip_number", link_ob)){
                        link_ob->set_db("last_on", time());
                        link_ob->set_db("last_from",
                                   query_temp("ip_number", link_ob));
                        link_ob->save();
                }
                destruct(link_ob);
        }

        net_dead = 1;
        if( userp(this_object()) && !query("doing") ) {
                call_out("user_dump", NET_DEAD_TIMEOUT, DUMP_NET_DEAD);
                tell_room(environment(this_object()), query("name", this_object()) + "断线了。\n", this_object());
                set_temp("net_dead_time", time());
                // CHANNEL_D->do_channel(this_object(), "sys", "断线了。");
                // 副本里断线不取消战斗状态
                if( environment() && base_name(environment())[0..1] != "/f" && !this_object()->query_condition("killer") && !query("no_protect", environment()) )
                remove_all_enemy(1);
        } else {
                if( environment() )
                        message("vision", name() + "离线了。\n",
                                environment(), ({ this_object() }));
        }
}

// reconnect: called by the LOGIN_D when a netdead player reconnects.
void reconnect()
{
        set_heart_beat(1);
        net_dead = 0;
        remove_call_out("user_dump");
        tell_object(this_object(), "重新连线完毕。\n");
}

// skill variable & function
#define MAX_NEILI_IMPROVE       query("con")
#define MAX_JINGLI_IMPROVE      query("con")

int query_neili_limit()
{
        string *skill_names;
        string force;
        mapping skills;
        int neili_limit;
        int base_lvl, lvl;
        int tmp;
        int i;
        string fam;
        int times;

        skills = this_object()->query_skills();
        if( !mapp(skills) )
                return 0;

        force = query_skill_mapped("force");
        skill_names = keys(skills);

        base_lvl = ((int) skills["force"]) / 2;
        neili_limit = base_lvl * 30;
        for (i = 0; i < sizeof(skill_names); i++) {
                if( file_size(SKILL_D(skill_names[i]) + ".c") == -1 ) {
                        continue;
                }

                if( ! SKILL_D(skill_names[i])->valid_enable("force") )
                        continue;

                lvl = (int) skills[skill_names[i]];
                tmp = (base_lvl + lvl) * 30;
                tmp += (int) SKILLS_D->query_neili_improve(skill_names[i], lvl);
                if( tmp > neili_limit ) neili_limit = tmp;
        }

        neili_limit += neili_limit / 100 * query("improve/neili");
        if( query("breakup") )
                neili_limit += neili_limit / 10 * 3;

        if( query("special_skill/mystery") )
        {
                tmp = query_con() * 150;
                if( tmp > 1500000 ) tmp = 1500000;
                neili_limit += tmp;
        }

        fam = query("family/family_name");
        if( query("class") == "bonze" &&
            (fam == "雪山寺" || fam == "少林派" || fam == "峨嵋派" || fam == "血刀门" || fam == "密宗") )
                neili_limit += neili_limit / 10;

        // 天地幽然提高内力上限
        if (query("special_skill/youran"))
        {
                neili_limit = neili_limit + query("lhpoint/special/youran") * 300;
        }
        // 侠骨丹心同样提高内力上限，不过略比天地悠然低，约80%
        if (query("special_skill/xiagu"))
        {
                neili_limit = neili_limit + query("lhpoint/special/youran") * 240;
        }
        // 帝王之星提高20%
        if (query("special_skill/diwang"))
                neili_limit = neili_limit + neili_limit * 2 / 10;

        // 逆转乾坤提升5000点内力
        if (query("special_skill/nizhuan"))
                neili_limit += 5000;

        // 天生奇骨增加5%内力上限
        if (query("special_skill/qigu"))
                neili_limit = neili_limit + neili_limit / 20;

        if( query("special_skill/tianqing") )
                neili_limit = neili_limit + neili_limit / 20;

        if( query("reborn/times") && force == "xiantian-gong" )
                neili_limit = neili_limit + neili_limit * 30 / 100;

        if( times = (int)query("reborn/times") )
                neili_limit = neili_limit + times*neili_limit / 2;

        // 转世技能增加内力上限
        if( query("special_skill/ghost") )
                neili_limit += neili_limit * 50 / 100;

        if( query("drug_addneili") )
                neili_limit += query("drug_addneili");

        neili_limit += this_object()->query_all_buff("max_neili");
        neili_limit += neili_limit * this_object()->query_ability_buff("max_neili")/100;

        return neili_limit;
}

int query_current_neili_limit()
{
        int neili, lvl;
        int times;
        int tmp;
        string force;
        string fam;

        force = query_skill_mapped("force");
        neili = (int)query_skill("force", 1) / 2 * 30;
        if( stringp(force) && force != "" ) {
                lvl = (int)query_skill(force, 1);
                neili += lvl * 30;
                neili += SKILLS_D->query_neili_improve(force, lvl);
        }

        neili += neili / 100 * query("improve/neili");
        if( query("breakup") )
                neili += neili / 10 * 3;

        if( query("special_skill/mystery") )
        {
                tmp = query_con() * 150;
                if( tmp > 1500000 ) tmp = 1500000;
                neili += tmp;
        }

        fam = query("family/family_name");
        if( query("class") == "bonze" &&
            (fam == "雪山寺" || fam == "少林派" || fam == "峨嵋派" || fam == "血刀门" || fam == "密宗") )
                neili += neili / 10;

        // 天地幽然提高内力上限
        if (query("special_skill/youran"))
        {
                neili += query("lhpoint/special/youran") * 300;
        }
        // 侠骨丹心同样提高内力上限，不过略比天地悠然低，约80%
        if (query("special_skill/xiagu"))
        {
                neili = neili + query("lhpoint/special/youran") * 240;
        }

        // 六阴鬼脉提高内力上限30%
        if (query("special_skill/guimai"))
        {
                neili = neili + neili * 3 / 10;
        }

        // 帝王之星提高20%
        if (query("special_skill/diwang"))
                neili = neili + neili * 2 / 10;

        // 逆转乾坤提升500点内力
        if (query("special_skill/nizhuan"))
                neili += 500;

        // 天生奇骨增加5%内力上限
        if (query("special_skill/qigu"))
                neili = neili + neili / 20;

        if( query("special_skill/tianqing") )
                neili = neili + neili / 20;

        if( query("reborn/times") && force == "xiantian-gong" )
                neili += neili * 30 / 100;

        if( times = (int)query("reborn/times") )
                neili += times * neili / 2;

        // 转世技能增加内力上限
        if( query("special_skill/ghost") )
                neili += neili * 50 / 100;

        if( query("drug_addneili") )
                neili += query("drug_addneili");

        neili += this_object()->query_all_buff("max_neili");
        neili += neili * this_object()->query_ability_buff("max_neili")/100;

        return neili;
}

int query_jingli_limit()
{
        int limit;
        int reborn;

        limit = ((int)query("magic_points") / 20) + query("int") * 90;
        limit += limit / 100 * query("improve/jingli");
        if( query("animaout") )
                limit += limit / 10 * 4;

        if( query("reborn/times") && query_skill_mapped("force") == "xiantian-gong" )
                limit += limit * 30 / 100;

        // 侠骨丹心提高精力上限
        if (query("special_skill/xiagu"))
        {
                limit += query("lhpoint/special/xiagu") * 400;
        }
        // 天地悠然同样提高精力上限，只是比侠骨丹心略低，约50%
        if (query("special_skill/youran"))
        {
                limit += query("lhpoint/special/xiagu") * 200;
        }

        // 逆转乾坤提升500点精力
        if (query("special_skill/nizhuan"))
                limit += 500;

        // 帝王之星提高20%
        if (query("special_skill/diwang"))
                limit = limit + limit * 2 / 10;

        if( query("special_skill/tianqing") )
                limit += limit / 20;

        if( reborn = (int)query("reborn/times") )
                limit *= (reborn + 1);

        if( query("special_skill/demon") )
                limit += limit * 50 / 100;

        limit += query("drug_addjingli");

        limit += this_object()->query_all_buff("max_jingli");
        limit += limit * this_object()->query_ability_buff("max_jingli")/100;

        if( limit > query_neili_limit() )
                limit = query_neili_limit();

        return limit;
}

int query_current_jingli_limit()
{
        return query_jingli_limit();
}

int query_potential_limit()
{
        int p;

        p = (int)query("combat_exp") / 20;
        p += (query_int() * p / 100);
        if( ultrap(this_object()) )
                p += 1000000;
        p += 100000;

        p += query("add_pot_limit");
        p += this_object()->query_all_buff("max_potential");
        if( query("special_skill/diwang") )
                p += p / 2;

        return (int)query("learned_points") + p;
}

int query_experience_limit()
{
        int p;

        if( ultrap(this_object()) )
                p = 100000;
        else
        {
                p = query("score");
                if( p < 100 )
                        p = p / 2;
                else
                if( p < 300 )
                        p = p / 4 + 25;
                else
                if( p < 1100 )
                        p = (p - 300) / 8 + 100;
                else
                        p = (p - 1100) / 16 + 200;
                if( p > 80000 )
                        p = 80000;
        }

        p += query("add_mar_limit");
        p += this_object()->query_all_buff("max_experience");

        return query("learned_experience") + p;
}

int improve_potential(int n)
{
        int max;

        max = query_potential_limit() - query("potential");
        if( max <= 0 ) return 0;
        if( max > n ) max = n;

        addn("potential", max);
        return max;
}

int improve_experience(mixed n)
{
        int max;

        max = query_experience_limit() - query("experience");
        if( max <= 0 ) return 0;
        if( n > max ) n = max;

        addn("experience", n);
        return n;
}

int can_improve_neili()
{
        return query("improve/neili") < MAX_NEILI_IMPROVE;
}

int can_improve_jingli()
{
        return query("improve/jingli") < MAX_NEILI_IMPROVE;
}

int improve_neili(int n)
{
        int delta;

        if( (delta = query_neili_limit() - query("max_neili")) <= 0 )
                return 0;

        if( n > delta ) n = delta;
        addn("max_neili", n);
        setup();
        return n;
}

int improve_jingli(int n)
{
        int delta;

        if( (delta = query_jingli_limit() - query("max_jingli")) <= 0 )
                return 0;

        if( n > delta ) n = delta;
        addn("max_jingli", n);
        setup();
        return n;
}

int accept_fight(object ob)
{
        if( query_temp("pending/fight") == ob )
                return 1;

        tell_object(this_object(), YEL "如果你愿意和对方进行比试，请你也对" +
                    ob->name() + "("+ (string)query("id", ob)+")"+
                    "下一次 fight 指令。\n" NOR);

        tell_object(ob, YEL "由于对方是由玩家控制的人物，你必须等对方同意才" +
              "能进行比试。\n" NOR);

        return 0;
}

int accept_hit(object ob)
{
        if( !die_protect(ob) )
                return 0;

        message_vision("$N大喝道：" + ob->name() + "，你要干什么？\n",
                       this_object(), ob);
        return 1;
}

int accept_kill(object ob)
{
        if( is_killing(query("id", ob)) )
                return 1;

        if( !die_protect(ob) )
                return -1;

        tell_object(this_object(), HIR "如果你要和" + ob->name() +
                "性命相搏，请你也对这个人("+query("id", ob)+
                ")下一次 kill 指令。\n" NOR);
        return 1;
}

int accept_ansuan(object who)
{
        if( !die_protect(who) )
                return 0;

        command(random(2) ? "say 嗯！怎么..." : "say 啊！不好！");
        return 1;
}

int accept_touxi(object who)
{
        if( !die_protect(who) )
                return -1;

        switch (random(2))
        {
        case 0:
                message_vision("$N大吃一惊，叫道：“好你个" +
                               RANK_D->query_rude(who) + "！真不要脸！”\n",
                               this_object(), who);
                break;

        default:
                message_vision("$N仓皇之间，不及说话，只得接下$n"
                               "这一招。\n", this_object(), who);
                break;
        }

        return 1;
}

/*
void kill_ob(object ob)
{
        if( userp(ob) && !query_temp("in_pkd") ) {
                if( (query("age", ob) < PROTECT_AGE ) ||
                    (query("age") < PROTECT_AGE) ) {
                        return ::fight_ob(ob);
                }
        }
        return ::kill_ob(ob);
}
*/

int die_protect(object ob)
{
        object env;
        object me = this_object();

        // 只有玩家之间才有死亡保护
        if( !userp(me) || !userp(ob) )
                return 1;

        // 在比武场所不考虑死亡保护
        if( query_temp("in_pkd") )
                return 1;

        env = environment(me);
        if( query("fight_room", env) ||
            query("no_death", env) )
                return 1;

        // 去除攻击者的死亡保护信息
        if( userp(me) )
                cancle_die_protect(ob);

        if( query("NO_PK") )
        {
                message_vision("$N是江湖隐士，$n不能进行攻击。\n",
                               me, ob);
                return 0;
        }

        if( query("NO_PK", ob) )
        {
                message_vision("$n是江湖隐士，不能对$N进行攻击。\n",
                               me, ob);
                return 0;
        }

        if( objectp(WAR_D->query_marshal()) && this_object() == WAR_D->query_marshal() )
        {
                message_vision("$N是王朝战争主帅，$n不能进行攻击。\n",
                               me, ob);
                return 0;
        }

        if( query("newbie") )
        {
                message_vision("$N处于新手保护时期，$n不能进行攻击。\n",
                               me, ob);
                return 0;
        }

        // 被攻击者处于保护时期，本攻击失败
        if( query("die_protect/last_dead") + query("die_protect/duration") > time() ) {
                message_vision("$N处于被保护时期，$n不能进行攻击。\n",
                               me, ob);
                return 0;
        }

        return 1;
}

void cancle_die_protect(object ob)
{
        delete("die_protect", ob);
}

int reject_command()
{
        int t;

        if( wizardp(this_object()) )
                return 0;

        t = time() & 0xFFFFFFFE;
        if( at_time != t ) {
                at_time = t;
                user_command = 1;
                user_say = 0;
        } else
                user_command++;

        if( user_command > MAX_COMMAND_ONE_SECTION ) {
                user_command = 0;
                return 1;
        }

        return 0;
}

void ban_say_until(int ban_period, string msg)
{
        int t;

        t = time();
        if( ban_to > t )
                ban_to += ban_period;
        else
                ban_to = t + ban_period;
        ban_say_msg = msg;
}

int ban_say(int raw)
{
        int t;

        if( wizardp(this_object()) )
                return 0;

        if( is_in_prison() ) {
                notify_fail("你省省吧，好好做你的牢，少折腾。\n");
                return 1;
        }

        t = time() & 0xFFFFFFFE;
        if( ban_to > t ) {
                notify_fail(ban_say_msg + "，请于" +
                            appromix_time(ban_to - t) + "以后再尝试。\n");
                return 1;
        }

        if( !raw )
                return 0;

        if( at_time != t ) {
                at_time = t;
                user_say = 1;
                user_command  = 0;
        } else
                user_say++;

        if( user_say > MAX_SAY_ONE_SECTION ) {
                ban_say_until(BAN_SAY_PERIOD, "系统禁止你送出信息");
                /*
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "因为太罗嗦，被人堵住了嘴。");
                */
                notify_fail(HIR "由于你发布的信息太多，因此系统暂时"
                            "禁止你发出信息。\n" NOR);
                return 1;
        }

        return 0;
}

void permit_say(int n)
{
        if( ban_to <= time() )
                return;

        if( !n )
                ban_to = 0;
        else
                ban_to -= n;

        if( ban_to <= time() )
                tell_object(this_object(), "你可以继续发布信息了！\n");
}

// thow the person into prison
void get_into_prison(object ob, string p, int time)
{
        object me;

        me = this_object();
        if( !p ) p = prison;
        if( !p ) p = DEFAULT_PRISON;

        if( prison && base_name(environment()) == p ) {
                time_to_leave += time * 60;
                if( ob && time )
                        CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                                "听说" + query("name") + "的刑期被" +
                                query("name", ob)+"加长了"+
                                appromix_time(time * 60) + "。");
                return;
        }

        if( prison && prison == p && base_name(environment()) != prison ) {
                p->catch_back(me);
                set("startroom", prison, me);
                me->move(prison);
                message_vision("“啪”的一声，$N狠狠的摔倒了地上。\n", me);
                // if( living(me)) me->unconcious();
                if( living(me) )
                        me->enable_player();

                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "越狱潜逃，结果被抓"
                        "回去了。");

                save();
                return;
        }

        p->catch_ob(me);

        if( ob ) {
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "被" + query("name", ob)+
                        "送进了" + p->short() + HIM "，禁闭" +
                        appromix_time(time * 60) + "。");
        }

        set("startroom", prison, me);
        me->move(p);
        prison = p;
        time_to_leave += time * 60;
        save();

        message_vision("“啪”的一声，$N重重的摔倒了地上。\n", me);
        set("jing", 1, me);
        set("eff_jing", 1, me);
        set("qi", 1, me);
        set("eff_qi", 1, me);
        set("jingli", 0, me);
        set("neili", 0, me);
        me->receive_damage("jing", 0);
        // if( living(me)) me->unconcious();
        if( living(me) )
                me->enable_player();
}

// out of prison
void leave_prison(object ob, int time)
{
        object me;

        me = this_object();
        if( time ) {
                time_to_leave -= time * 60;
                if( time_to_leave > 0 ) {
                        CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                                "听说" + query("name") + "的刑期被" +
                                query("name", ob)+"缩短了"+
                                appromix_time(time * 60) + "。");
                        return;
                }
        }

        time_to_leave = 0;

        if( !prison->free_ob(me) )
                return;

        prison = 0;

        if( living(me) )
                me->enable_player();
        else
                me->revive();
        save();

        if( ob )
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "被" + ob->name() +
                        "提前释放了。");
        else
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "已经刑满释放了。");
}

/*
varargs void die(object killer)
{
        if( prison ) {
                set_temp("die_reason", "惨死在监狱中");
                clear_condition(0);
                receive_damage("qi", 0);
                prison = 0;
                if( living(this_object()) )
                        enable_player();
        }

        ::die(killer);
        save();
}
*/

// when the user was in prison, the heart beaten function of
// char will call damage heal_up, then the function will call
// it
void update_in_prison()
{
        object me;

        me = this_object();
        set("qi", 0, me);
        set("jing", 0, me);
        set("neili", 0, me);

        if( !living(me) )
                return;

        if( time_to_leave > 0 ) {
                if( environment() && base_name(environment()) != prison ) {
                        // escape from prison?
                        get_into_prison(0, 0, 0);
                }
                return;
        }

        leave_prison(0, 0);
}

// return true if the user was attached system, such as
// command sameip will run a much long time, in the period
// the user shouldn't receive message except from the system
int is_attach_system()
{
        return attach_flag;
}

// start attaching
int attach_system()
{
        attach_flag = 1;
}

// stop, deatched
int detach_system()
{
        attach_flag = 0;
}

string command_verb()
{
        return query_verb();
}

#define CRAZE_LIMIT_1   7000    // for 光明磊落
#define CRAZE_LIMIT_2   5000    // for 心狠手辣
#define CRAZE_LIMIT_3   2000

// 愤怒气息
int query_craze() { return craze; }

// 最大的愤怒气息
int query_max_craze()
{
        switch (query("character"))
        {
        case "光明磊落" :
                return CRAZE_LIMIT_1;

        case "心狠手辣" :
                return CRAZE_LIMIT_2;

        default:
                return CRAZE_LIMIT_3;
        }
}

// 现在是否处于最愤怒的状态
int is_most_craze()
{
        return (craze > 0) && (craze >= query_max_craze());
}

// 因为被打倒而震怒
void craze_of_defeated(string defeater_id)
{
        my_defeater_id = defeater_id;
}

// 因为被击毙而震怒
void craze_of_die(string killer_id)
{
        my_killer_id = killer_id;
        craze = query_max_craze();
}

// 愤怒的攻击对手后调用这个函数清除对象
void craze_defeated(string enemy_id)
{
        if( enemy_id == my_defeater_id )
                my_defeater_id = 0;

        if( enemy_id == my_killer_id )
                my_killer_id = 0;
}

// 是否憎恨某人
int is_hating(string enemy_id)
{
        if( enemy_id == my_defeater_id ||
            enemy_id == my_killer_id )
                return 1;

        return 0;
}

// 提升愤怒，返回提升的有效值
int improve_craze(int amount)
{
        int limit;

        if( amount < 0 )
                error("error: improve_craze amount to be less than 0\n");

        limit = query_max_craze();
        craze += amount;
        if( craze > limit ) {
                amount += limit - craze;
                craze = limit;
        }
        return amount;
}

// 消耗愤怒，返回消耗的有效值
int cost_craze(int n)
{
        if( n < 0 )
                error("error: improve_craze amount to be less than 0\n");

        if( n > craze ) {
                n = craze;
                craze = 0;
        } else
                craze -= n;
        return n;
}

/*
// 编辑文件
void edit_file(string file)
{
        ed(file);
}
*/

// 是否是结拜兄弟？
int is_brother(mixed ob)
{
        string id;

        if( stringp(ob) )
                id = ob;
        else
        if( objectp(ob) )
                id=query("id", ob);
        else
                return 0;

        // 是否是普通结拜兄弟
        if( query("brothers/" + id) )
                return 1;

        // 是否是结盟的兄弟
        return 0;
}

int query_viplevel()
{
        return query("vip/level");
}

int query_vipscore()
{
        return query("vip/score");
}

// 计算完整性数据和
string calc_sec_id(int raw)
{
        mapping my;
        string *list;
        string key;
        int sum;
        string str;
        int i;

        sum = 0;

        // 累计所有的数据
        if( mapp(my = query_entire_dbase()) ) {
                foreach (key in keys(my) - ({ "sec_id" })) {
                        sum += sizeof(key);
                        if( intp(my[key]) )
                                sum += my[key];
                        else
                                sum += sizeof(my[key]);
                }
        }

        // 累计所有的武功技能
        // if( mapp(my = query_skills()))
        if( mapp(my = query_skillc()) ) {
                foreach (key in keys(my) ) {
                        sum += sizeof(key);
                        if( intp(my[key]) )
                                sum += my[key];
                        else
                                sum += sizeof(my[key]);
                }
        }

        // 因动态装备在载入前后涉及到字符转换的问题，累计结果会不一样
        // 故取消累计所有携带的物品
        /*
        // 累计所有携带的物品
        if( arrayp(list = query_autoload_info()) ) {
                foreach (key in list) {
                        sum += sizeof(key);
                        if( stringp(key) )
                                for (i = 0; i < strlen(key); i++) sum += key[i];
                }
        }
        */

        // 转化成字符串
        str = sprintf("%d", sum);
        // str[0] = (sum % 26) + 'a';

        if( !raw ) str = crypt(str, 0);
        return str;
}

string query_info()
{
        string msg;
        int dexp, dpot, dmar, dage, dquest, dt;

        msg = "";
        if( wiz_level(this_object()) > 0 )
                return msg;

        if( query("chblk_on") ) {
                if( stringp(query("chblk_by")) )
                        msg += "频道已经被 " + query("chblk_by") + " 关闭。\n";
                else
                        msg += "频道被关闭中。\n";
        }

        dexp = query("combat_exp") - query("last_examine/combat_exp");
        dpot = query("potential") - query("last_examine/potential");
        dmar = query("experience") - query("last_examine/experience");
        dage = query("mud_age") - query("last_examine/mud_age");
        dquest = query("all_quest") - query("last_examine/all_quest");
        dt = time() - query("last_examine/time");
        if( dquest < 0 ) dquest += 1000;

        if( dt > 60 ) {
                msg += sprintf("自上次检查 %s 以来：\n"
                               "连线时间增加了 %s。\n"
                               "师门任务完成了 %d 个。\n"
                               "平均每分钟获得经验速度：%d\n"
                               "平均每分钟获得潜能速度：%d\n"
                               "平均每分钟获得体会速度：%d\n",
                               appromix_time(dt),
                               appromix_time(dage),
                               dquest,
                               dexp * 60 / dt, dpot * 60 / dt, dmar * 60 /dt);
        }

        return msg;
}

void guest_count()
{
        if( !previous_object() || (geteuid(previous_object()) != ROOT_UID) )
                return;

        call_out("do_guest_leave", 600);
}

protected void do_guest_leave()
{
        tell_object(this_object(), "\n您参观时间已到，如您需要注册正式账号，请使用其它 ID 进入游戏。\n\n");
        command("quit");
}

int analyse_trigger(string msg, string tg_msg, string tg_cmd)
{
        string *lines, str1, str2, str3;
        int sz;
        object me = this_object();

        if( !msg || !tg_msg || ! tg_cmd ) return 0;
        msg = replace_string(msg, "(*)", "");
        tg_msg = replace_string(tg_msg, "~", "");
        lines = explode(tg_msg, "(*)");

        sz = sizeof(lines);
        if( sz == 4 ) {
                if( sscanf(msg, "%*s"+lines[0]+"%s"+lines[1]+"%s"+lines[2]+"%s"+lines[3]+"%*s", str1, str2, str3) ) {
                        tg_cmd = replace_string(tg_cmd, "%1", str1);
                        tg_cmd = replace_string(tg_cmd, "%2", str2);
                        tg_cmd = replace_string(tg_cmd, "%3", str3);
                        set_temp("trigger", tg_cmd, me);
                        return 1;
                } else return 0;
        }
        else if( sz == 3 ) {
                if( sscanf(msg, "%*s"+lines[0]+"%s"+lines[1]+"%s"+lines[2]+"%*s", str1, str2) ) {
                        tg_cmd = replace_string(tg_cmd, "%1", str1);
                        tg_cmd = replace_string(tg_cmd, "%2", str2);
                        set_temp("trigger", tg_cmd, me);
                        return 1;
                } else return 0;
        }
        else if( sz == 2 ) {
                if( sscanf(msg, "%*s"+lines[0]+"%s"+lines[1]+"%*s", str1) ) {
                        tg_cmd = replace_string(tg_cmd, "%1", str1);
                        set_temp("trigger", tg_cmd, me);
                        return 1;
                } else return 0;
        } else return 0;
}

void do_trigger(string msg)
{
        string file, *lines, tg_msg, tg_cmd;
        int i, n;
        object me = this_object();

        if( !stringp(file = query("trigger")) )
                return;

        if( query("doing") != "trigger" )
                return;

        if( query_temp("trigger") )
                return;

        if( file_size(DATA_DIR + "trigger/" + query("id") + __SAVE_EXTENSION__) < 0 )
                return;

        if( !file ) return;
        lines = explode(file, "\n");
        n = sizeof(lines);

        msg = filter_color(msg, 1);

        for( i = 0; i < n; i++ ) {
                if( sscanf(lines[i], "%s:%s", tg_msg, tg_cmd) == 2 ) {
                        if( strlen(msg) >= strlen(tg_msg) && sscanf(msg, "%*s"+tg_msg+"%*s") ) {
                                set_temp("trigger", tg_cmd, me);
                                break;
                        }

                        if( analyse_trigger(msg, tg_msg, tg_cmd) > 0 )
                               break;
                }
        }

        return;
}

int id(string str)
{
        string *applied_id;

        if( geteuid(this_object()) != str )
                return 0;

        if( pointerp(applied_id = query_temp("apply/id")) && sizeof(applied_id) )
        {
                if ( this_player() && !wizardp(this_player()) )
                        return 0;
        }

        if( this_player() && !this_player()->visible(this_object()) )
                return 0;

        return 1;
}
