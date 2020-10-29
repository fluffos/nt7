// Written by Lonely@nitan.org (05/21/2009)
// char.c

// #pragma optimize
// #pragma save_binary

#include <action.h>
#include <ansi.h>
#include <command.h>
#include <condition.h>
#include <move.h>
#include <name.h>
#include <skill.h>
#include <team.h>
#include <user.h>

inherit F_ACTION;
inherit F_ALIAS;
inherit F_APPRENTICE;
inherit F_ATTACK;
inherit F_ATTRIBUTE;
inherit F_COMMAND;
inherit F_CONDITION;
inherit F_DAMAGE;
inherit F_DBASE;
inherit F_EDIT;
inherit F_EQUIP_LIV;
inherit F_FINANCE;
inherit F_MESSAGE;
inherit F_MORE;
inherit F_MOVE;
inherit F_NAME;
inherit F_SKILL;
inherit F_TEAM;

#define SCHEME_CMD      "/cmds/usr/scheme"
#define TRIGGER_CMD     "/cmds/usr/trigger"

#define ID      0
#define NAME    1

string *id_name;

// Use a tick with longer period than heart beat to save cpu's work
nosave int tick;
nosave string short_desc = 0;

void create()
{
        seteuid(0); // so LOGIN_D can export uid to us
}

// Use this function to identify if an object is a character.
int is_character() { return 1; }

// check the character is good or bad
int is_not_good() { return query("shen") < 500; }
int is_not_bad()  { return query("shen") > -500; }
int is_good()     { return query("shen") > 500; }
int is_bad()      { return query("shen") < -500; }

// setup: used to configure attributes that aren't known by this_object()
// at create() time such as living_name (and so can't be done in create()).
void setup()
{
        seteuid(getuid(this_object()));

        CHAR_D->setup_char( this_object() );

        if( userp(this_object()) || this_object()->open_heart_beat() )
                set_heart_beat(1);

        tick = 5 + random(10);
        enable_player();
}

void heart_beat()
{
        int wimpy_ratio, cnd_flag;
        mapping my;
        object me, ob;
        string prompt;
        int is_player;
        object room;
        object killer;

        if( !objectp(room = environment()) ) return;

        me = this_object();
        my = me->query_entire_dbase();

        // update prompt
        if( userp(me) && living(me) && mapp(my["env"]) ) {
                prompt = my["env"]["prompt"];
                if( (prompt == "time" || prompt == "mud" || prompt == "hp") &&
                    is_waiting_command() && ! me->is_attach_system() ) {
                        write_prompt();
                }
        }

        if( my["eff_qi"] < 0 || my["eff_jing"] < 0 || my["qi"] < -my["max_qi"]/5  ||
            my["jing"] < -my["max_jing"]/5 ) {
                killer = me->query_last_damage_from();
                if( !living(me) || (objectp(killer) && killer->is_killing(query("id", me)) &&
                     same_environment(me, killer) && !killer->is_punisher()) )
                        die();
                else
                        unconcious();
                return;
        }

        // If we're dying or falling unconcious?
        if( my["qi"] < 0 || my["jing"] < 0 ) {

                if( !living(me) ) die();
                else unconcious();
                // Why does the living test? Because
                // The wizard may set immortal but his
                // qi was -1, so I don't want return,
                // or the continue_action will never be
                // called in such case.
                if( !me || !living(me) )
                        return;
        }

        if( weak > 1 ) weak--;
        else if( weak == 1 ) set_weak(0);
        if( freeze > 1 ) freeze--;
        else if( freeze == 1 ) set_freeze(0);

        // Do attack if we are fighting.
        if( is_busy() ) {
                if( is_fighting() )
                        tell_object(me, "\n--->>你上一个动作没有完成，失去一次进攻机会。\n");
                continue_action();
        } else if( living(me) ) {
                // Is it time to flee?
                if( is_fighting()
                &&      intp(wimpy_ratio = (int)query("env/wimpy"))
                &&      wimpy_ratio > 0
                &&      (       my["qi"] * 100 / my["max_qi"] <= wimpy_ratio
                        ||      my["jing"] * 100 / my["max_jing"] <= wimpy_ratio) )
                        GO_CMD->do_flee(me);

                if( query("auto_perform") || me->query_auto_perform() ) {
                        if( my["eff_jing"] > 0 && my["jing"] * 100 / my["eff_jing"] <= 50 )
                                SKILL_D("force/regenerate")->exert(me, me);
                        if( my["eff_qi"] > 0 && my["qi"] * 100 / my["eff_qi"] <= 50 )
                                SKILL_D("force/recover")->exert(me, me);

                        // 如果不在打架而且处于受伤状态，则自行疗伤
                        if( !is_fighting() ) {
                                if( my["eff_jing"] < my["max_jing"] )
                                        SKILL_D("force/inspire")->exert(me, me);
                                if( my["eff_qi"] < my["max_qi"] )
                                        SKILL_D("force/heal")->exert(me, me);
                        }
                }
                // Do attack or clean up enemy if we have fleed.
                if( is_busy() )
                        continue_action();
                else    attack();
        }

        // 检测辅助任务
        MYGIFT_D->check_curgift(me);

        if (my["doing"] == "trigger")
                TRIGGER_CMD->execute_trigger(me);

        if( my["doing"] == "scheme" )
                // executing schedule now
                SCHEME_CMD->execute_schedule(me);

        if( !me ) return;

        is_player = playerp(me);
        if( !is_player ) {
                me->scan();
                // scan() may do anything -- include destruct(this_object())
                if( !me) return;
        } else {
                // 杀戮值随时间而减少
                if( query("pk_score") > 0 ) {
                        if( time() - query("pk_score_time") >= 3600 ) {
                                addn("pk_score", -1, me);
                                set("pk_score_time", time(), me);
                        }
                }

                // 道具时间奖励
                if( mapp(my["time_reward"]) ) {
                        if( !undefinedp(my["time_reward"]["study"]) ) {
                                my["time_reward"]["study"] -= 1;
                                if( my["time_reward"]["study"] < 1 )
                                        map_delete(my["time_reward"], "study");
                        }
                        if( !undefinedp(my["time_reward"]["quest"]) ) {
                                my["time_reward"]["quest"] -= 1;
                                if( my["time_reward"]["quest"] < 1 )
                                        map_delete(my["time_reward"], "quest");
                        }
                }
        }

        if( tick-- ) return;
        else tick = 5 + random(10);

        if( !my["not_living"] ) // 木人不调用update condition
                cnd_flag = update_condition();
        if( !me ) return;

        /*
        // 极其不合理，在玩家较多的游戏
        // CPU 浪费极大，用另外的方法处理。
        // Find.
        if( !(cnd_flag & CND_NO_HEAL_UP) )
                cnd_flag = heal_up();

        // If we are compeletely in peace, turn off heart beat.
        // heal_up() must be called prior to other two to make sure it is called
        // because the && operator is lazy :P
        if( !cnd_flag
        &&      !is_player
        &&      !is_fighting()
        &&      !is_busy()
        &&      !interactive(this_object()) ) {
                if( environment() && query("chat_msg") ) {
                        ob = first_inventory(environment());
                        while( ob && !interactive(ob) )
                                ob = next_inventory(ob);
                } else
                        ob = 0;
                if( !ob ) set_heart_beat(0);
        }
        */
        heal_up();

        update_all_limb_damage();

        if( !me || !is_player ) return;

        // Make us a bit older. Only player's update_age is defined.
        // Note: update_age() is no need to be called every heart_beat, it
        //       remember how much time has passed since last call.
        me->update_age();

#ifdef AUTO_SAVE
        if( living(me) ) {
                int period, t = time();
                period = t - ((int) my["last_save"]);
                if( period < 0 || period > 15 * 60 ) {
                        string msg;
                        // msg = HIG "【档案存储】您的档案已经自动存盘。\n" NOR;
                        if( !me->save() )
                                msg = HIR "【数据保护】由于数据异常，您的档"
                                          "案本次存盘失败。\n" NOR;
                        set("last_save", t);
                        if( msg )
                                tell_object(me, msg);
                }
        }
#endif

        if( !interactive(me) )
                return;

        if( query_idle(me) > IDLE_TIMEOUT && !wizardp(me) &&
            (!mapp(my["env"]) || !my["env"]["keep_idle"]) )
                me->user_dump(DUMP_IDLE);
}

// check the poison attack
mixed hit_ob(object me, object victim, int damage_bonus)
{
        object unarmed_weapon;

        if( unarmed_weapon = query_temp("armor/hands") )
                return unarmed_weapon->hit_ob(me, victim, damage_bonus);

        if( !mapp(query_temp("daub")) )
                return;

        return COMBAT_D->hit_with_poison(me, victim, this_object());
}

int visible(object ob)
{
        int lvl;

        if( !ob->is_character() )
                return 1;

        if( !wizardp(ob) ) {
                if( wizardp(this_object()) ||
                    query("env/invisible") ||
                    is_ghost() ) return 1;

                if( query_temp("apply/astral_vision") )
                        return 1;

                if( query("env/invisible", ob) ||
                    ob->is_ghost() ) return 0;

                if( query_temp("apply/shade_vision", ob) ||
                    query_temp("shade_vision", ob) ) {
                        if( !userp(this_object()) )
                                return 1;
                        else    return 0;
                }
        }

        lvl = wiz_level(this_object());
        if( lvl &&
            lvl >= wiz_level(ob) )
                return 1;
        if( query("env/invisible", ob) == "YES" )
                return 0;
        if( lvl &&
            lvl >= (int)query("env/invisible", ob) )
                return 1;

        if( wizardp(ob) &&
            query("env/invisible", ob) )
                return 0;

        return 1;
}

// 这里应该区分是否带面具名字，而不是大小写
varargs string query_idname(int raw)
{
        if( !raw ) return query("name") + "(" + query("id") + ")";
        if( !arrayp(id_name) || sizeof(id_name) < 1 )
        {
                //return query("name",this_object()) + "(" + (raw ? capitalize(query("id",this_object())) : query("id",this_object())) + ")";
                if( raw > 1 ) return query("name") + "(" + capitalize(query("id")) + ")";
                return query("name") + "(" + query("id") + ")";
        }

        return (id_name[NAME] ? id_name[NAME] : query("name")) + "(" +
               (raw > 1 ? color_capitalize(id_name[ID] ? id_name[ID] : query("id")) :
               (id_name[ID] ? id_name[ID] : query("id"))) + ")";
}

mixed query_IDNAME()
{
        if( !arrayp(id_name) || sizeof(id_name) < 1 )
                return 0;

        return id_name;
}

void set_IDNAME(mixed m)
{
        if( !arrayp(m) || sizeof(m) < 1 )
                return;

        id_name = m;
}

void remove_idname()
{
        id_name = ({});
}

varargs string *set_idname(string id, string name)
{
        string text;

        if( !stringp(id) && ! stringp(name) ) return 0;

        if( !arrayp(id_name) || sizeof(id_name) < 1 )
                id_name = allocate(2);

        if( stringp(id) ) {
                text = lower_case(filter_color(trans_color(id, 3), 1));
                id = lower_case(trans_color(id, 3));

                if( !id(text) ) return 0;

                id_name[ID] = id;
        }

        if( stringp(name) ) {
                name = trans_color(name, 3);

                if( filter_color(name, 1) != query("name") ) return 0;

                id_name[NAME] = name;
        }

        return copy(id_name);
}

nomask varargs string query_id(int raw)
{
        if( !arrayp(id_name) || sizeof(id_name) < 1 )
                return raw ? filter_color(query("id"), 1) : query("id");

        return id_name ? (undefinedp(raw) ? (id_name[ID] ? id_name[ID] : query("id")) : filter_color((id_name[ID] ? id_name[ID] : query("id")),1)) : 0;
}

nomask varargs string query_name(int raw)
{
        if( !arrayp(id_name) || sizeof(id_name) < 1 )
                return raw ? filter_color(query("name"), 1) : query("name");

        return id_name ? (undefinedp(raw) ? (id_name[NAME] ? id_name[NAME] : query("name")) : filter_color((id_name[NAME] ? id_name[NAME] : query("name")),1)) : 0;
}

string set_short_desc(string desc)
{
        short_desc = desc;
}

varargs string short(int raw)
{
        string title, nick, str, str1, *mask;
        string party_title;
        string bname;
        object me, obj;
        int pk_score;

        me = this_object();

        pk_score = (int)query("pk_score");
        if( !raw && sizeof(mask = query_temp("apply/short")) )
                str = (string)mask[sizeof(mask) - 1];
        else {
                if( pk_score >= 5 )
                        str = HIM + filter_color(query_idname(), 1) + NOR;
                else if( pk_score >= 3 )
                        str = MAG + filter_color(query_idname(), 1) + NOR;
                else if( pk_score >= 2 )
                        str = HIR + filter_color(query_idname(), 1) + NOR;
                else if( pk_score >= 1 )
                        str = RED + filter_color(query_idname(), 1) + NOR;
                else
                        str = query_idname(1);

                if( !stringp(title = query_temp("title")) )
                        title = query("title");
                if( nick = query("nickname") ) {
                        str = "「" + nick + "」" + str;
                        if( title ) str = title + str;
                } else if( title ) str = title + " " + str;

                if( stringp(query("party/rank")) ) {
                        party_title = query("party/party_name") + query("party/rank");
                        str = sprintf("%s %s",party_title, str);
                }

                if( stringp(bname = query("bunch/bunch_name")) )
                        str = sprintf("%s%s%s" NOR " %s",
                                query(bname + "/color", get_object(BUNCH_D)) ? query(bname + "/color", find_object(BUNCH_D)) : NOR,
                                bname, (string)query("bunch/title") ? query("bunch/title") : "帮众", str);

                if( stringp(title = query("viremploy/job")) )
                        str = sprintf(HIY "%s" NOR " %s", title, str);
        }

        if( !raw ) {
                if( short_desc )
                        str = name() + short_desc;
        } else
                return str;

        if( objectp(obj = query_temp("is_riding")) )
                str += HIY "{" + obj->name(1) + NOR + HIY "}" NOR;

        if( me->is_ghost() )
                str = HIB "(鬼气) " NOR + str;

        if( me->is_weak() )
                str += HIB " <虚弱>" NOR;

        if( me->is_freeze() )
                str += HIW " <冰冻>" NOR;

        if( me->query_condition("killer") )
                str += HIR " <通缉犯>" NOR;

        if( me->is_fighting() )
                str += HIR " <战斗中>" NOR;

        if( me->is_net_dead() ) {
                switch( query("doing") )
                {
                case "breakup":
                case "animaout":
                case "invent":
                        str += HIY " <闭关中>" NOR;
                        break;

                case "closed":
                case "xiulian":
                        str += HIY " <修炼中>" NOR;
                        break;

                case "scheme":
                        str += HIW " <计划中>" NOR;
                        break;

                case "trigger":
                        str += HIW " <触发中>" NOR;
                        break;

                default:
                        str += HIG " <断线中>" NOR;
                }
        }

        if( query_temp("on_bantan") )
                str += HIG " <摆摊中> " NOR;

        if( in_input() )
                str += HIC " <输入文字中>" NOR;

        if( !living(me) && query("disable_type") )
                str += HIR + query("disable_type") + NOR;

        if( in_edit() )
                str += HIY " <编辑档案中>" NOR;

        if( interactive(this_object()) &&
            !query("doing") &&
            query_idle(this_object()) > 120 )
                if( wizardp(this_object())) str += HIM " <思考中>" NOR;
                else str += HIM " <发呆中>" NOR;

        return str;
}

int command( string str )
{
        //reset_eval_cost();
        return efun::command(str);
}
