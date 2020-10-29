// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// attack.c

// #pragma save_binary

#include <ansi.h>
#include <origin.h>
#include <skill.h>
#include <action.h>

#define MAX_OPPONENT    4

string *killer = ({ });
string *want_kills = ({ });
nosave object *enemy = ({});
nosave string current_skill = "unarmed";

nosave mixed  next_action = 0;
nosave mixed  default_object = 0;
nosave string default_function =0;
nosave object competitor = 0;
nomask string query_current_skill() { return current_skill; }

// prototypes
object *query_enemy()  { return enemy; }
string *query_killer() { return killer; }
string *query_want()   { return want_kills; }
mapping query_default_action() { return ([ default_object : default_function ]); }
void    apply_killer(string *ik) { if( arrayp(ik) ) killer = filter_array(ik, (: stringp :)); }
void    apply_want(string *ik)   { if( arrayp(ik) ) want_kills = filter_array(ik, (: stringp :)); }

// query_ATTACK() and set_ATTACK()
mapping query_ATTACK()
{
        mapping data = ([]);
        data["killer"] = killer;
        data["want_kills"] = want_kills;
        return data;
}

int set_ATTACK(mapping data)
{
        if( !mapp(data) )
                return 0;

        killer = data["killer"];
        want_kills = data["want_kills"];
        return 1;
}

// This function returns 1 if we are fighting anyone (or with ob)
varargs int is_fighting(object ob)
{
        if( !ob ) return sizeof(enemy) > 0;

        return arrayp(enemy) && member_array(ob, enemy) != -1;
}

// This function returns 1 if we are fighting anyone (or with ob)
varargs int is_killing(string id)
{
        if( !id ) return sizeof(killer) > 0;

        return arrayp(killer) && member_array(id, killer) != -1;
}

// This function returns 1 if I want to kill ob
varargs int is_want_kill(string id)
{
        return arrayp(want_kills) && member_array(id, want_kills) != -1;
}

// This function will update all killer inforamtion
void update_killer()
{
        if( !arrayp(killer) || !arrayp(want_kills) ) {
                killer = ({ });
                want_kills = ({ });
                return;
        }

        // remove all offline char's information
        want_kills = filter_array(want_kills, (: objectp(find_player($1)) :));

        // remove all passive killing action
        killer = filter_array(killer, (: member_array($1, want_kills) == -1 :));
}

// This function starts fight between this_object() and ob
void fight_ob(object ob)
{
        object env;
        object *memb;

        if( !ob || ob == this_object() ) return;
        if( member_array(ob, enemy) != -1 )
                return;

        env = environment();
        if( environment(ob) != env ||
            query("no_fight", env) )
                return;

        if( !living(this_object()) )
                return;

        if( ob->is_ghost() ||
            this_object()->is_ghost() )
                return;

        set_heart_beat(1);
        enemy += ({ ob });

        if( this_object()->in_array() > 1 ) {
                if( this_object()->is_array_member(ob) )
                        this_object()->query_array_master()->release_array(5);
                else {
                        memb = this_object()->query_array_member() - ({ this_object() });
                        foreach( object body in memb ) {
                                body->fight_ob(ob);
                                ob->fight_ob(body);
                        }
                }
        }

        if( this_object()->is_guarder() && is_killing(query("id", ob)) )
                // guarder will look for help
                this_object()->kill_enemy(ob);

        if( this_object()->is_master() && is_killing(query("id", ob)) )
                // family will look for help
                this_object()->master_accept_kill(ob);

        COMBAT_D->reset_combat_cache(this_object());
        ob->fight_ob(this_object());
}

// This function starts killing between this_object() and ob
void kill_ob(object ob)
{
        object *guarded;
        object me;
        object env;
        object gob;
//      int i;

        me = this_object();
        if( !living(me) || !ob )
                return;

        env = environment();
        if( environment(ob) != env ||
            query("no_fight", env) )
                return;

        if( ob->is_ghost() || me->is_ghost() )
                return;

        guarded = query_temp("guarded", ob);
        if( !guarded ) guarded = ({ });
        if( member_array(me, guarded) != -1 ) {
                tell_object(ob, HIR "不能杀你要保护的人！\n" NOR);
                return;
        }

        if( query_temp("owner") == ob || query_temp("owner") == query("id", ob) ) {
                tell_object(me, HIR "不能对你的主人下毒手。\n" NOR);
                return;
        }

        if( !arrayp(killer) ) killer = ({ });
        if( member_array(query("id", ob), killer)==-1 ) {
                killer += ({ query("id", ob) });
                tell_object(ob, HIR "看起来" + this_object()->name() +
                                HIR "想杀死你！\n" NOR);
        }

        foreach( gob in guarded ) {
                if( !gob || gob == me ||
                    environment(gob) != environment() )
                        continue;

                if( !living(gob) )
                        continue;

                if( gob->is_killing(query("id")) )
                        continue;

                tell_object(gob, HIR + ob->name(1) +
                            "受到攻击，你挺身而出，加入战团！\n" NOR);
                switch( random(8) )
                {
                case 0:
                        message_vision(HIW "$N" HIW "一言不发，对$n"
                                       HIW "发动了攻击。\n" NOR, gob, me);
                        break;
                case 1:
                        message_vision(HIW "$N" HIW "一声怒吼，冲上前"
                                       "去，看来是要和$n" HIW "拼命。\n" NOR,
                                       gob, me);
                        break;
                case 2:
                        message_vision(HIW "$N" HIW "冷笑了一声，道："
                                       "“接招吧！”说罢就对$n" HIW
                                       "发动了攻击。\n" NOR, gob, me);
                        break;
                case 3:
                        message_vision(HIW "$N" HIW "迈上一步，挡在前"
                                       "面，开始和$n" HIW "进行殊死搏"
                                       "斗！\n" NOR, gob, me);
                        break;
                case 4:
                        message_vision(HIW "$N" HIW "双臂一振，脸如寒水，"
                                       "已经向$n" HIW "接连发出数招！\n"
                                       NOR, gob, me);
                        break;
                case 5:
                        message_vision(HIW "$N" HIW "深吸一口气，一招"
                                       "直指$n" HIW "的要害，竟然是要"
                                       "取人的性命！\n" NOR, gob, me);
                        break;
                case 6:
                        message_vision(HIW "紧接着$N" HIW "已经攻上！"
                                       "招招进逼$n" HIW "，毫无容情余"
                                       "地！\n" NOR, gob, me);
                        break;
                default:
                        message_vision(HIW "$N" HIW "飞也似的扑上前来"
                                       "，开始进攻$n" HIW "。\n" NOR, gob, me);
                        break;
                }

                if( ob->is_want_kill(query("id")) )
                        gob->want_kill(me);
                else if( ob->can_learn_from() )
                        // For master, kill action cause "want_kill" to guarder
                        me->want_kill(gob);

                gob->kill_ob(me);
        }

        fight_ob(ob);
}

void want_kill(object ob)
{
        string ob_id;
        object me, env;

        if( !userp(ob) ) return;

        if( !arrayp(want_kills) ) want_kills = ({ });

        ob_id = query("id", ob);
        if( is_killing(ob_id) ||
            is_want_kill(ob_id)) return;

        if( ob->is_want_kill(query("id")) ) return;
        if( query_temp("in_pkd", ob) ) return;

        env = environment(ob);
        if( query("fight_room", env) ||
            query("no_death", env) )
                return;

        want_kills += ({ ob_id });
        me = this_object();
        if( userp(ob) && !query("no_newbie", ob) ) {
                set("no_newbie", 1);
                if( query("newbie") ) {
                        delete("newbie");
                        tell_object(me, BLINK + HIR "\n由于你主动攻击其他玩家，所以取消对你的新手保护！\n\n" NOR);
                }
        }
}

void clean_up_enemy()
{
        int i;

        if( i = sizeof(enemy) ) {
                while( i-- ) {
                        if( !objectp(enemy[i]) ||
                            environment(enemy[i]) != environment() ||
                            (!living(enemy[i]) && !is_killing(query("id", enemy[i]))) )
                                enemy[i] = 0;
                }
                enemy -= ({ 0 });
        }
}

// This function checks if the current opponent is available or
// select a new one.
// BOSS仇恨系统
object select_opponent()
{
        object *enemy_selected, *enemy_weak, prefered, *enemy;
        object target;
        string target_name;
        //int which;

        enemy = this_object()->query_enemy();

        if( !sizeof(enemy) ) return 0;

        if( !userp(this_object()) )
        {
                // 第一步先选出快死的 --〉make sure you die :D
                // 第二个选择是冒犯你最多的-->max_hatred guy
                // 实在不行就随便选了
                enemy_weak = filter_array(enemy, (: query("qi", $1) < query("max_qi", $1)/10
                                        && userp($1) :));
                if( sizeof(enemy_weak) >= 1 )
                        enemy_selected = enemy_weak;
                else if( !objectp(prefered = this_object()->query_max_hatred()) )
                        enemy_selected = enemy;
                else
                        return prefered;
        } else {
                enemy_selected = enemy;
                if( stringp(target_name = query("env/target")) )
                {
                        if( objectp(target = present(target_name, environment())) )
                        if( member_array(target, enemy) != -1 )
                                return target;
                }
        }

        //which = random(MAX_OPPONENT);
        //return which < sizeof(enemy_selected) ? enemy_selected[which] : enemy_selected[0];

        return enemy_selected[random(sizeof(enemy_selected))];
}

// Stop fighting ob.
int remove_enemy(object ob)
{
        object me;

        me = this_object();

        enemy -= ({ ob });
        // BOSS解除战斗则恢复状态
        if( !sizeof(enemy) && me->is_boss() )
                me->full_self();
        // 解除绝招组合效果
        if( !sizeof(enemy) )
                delete_temp("last_perform", me);

        return 1;
}

// Stop killing ob.
int remove_killer(object ob)
{
        if( playerp(ob) )
                want_kills -= ({ query("id", ob) });

        if( is_killing(query("id", ob)) ) {
                killer -= ({ query("id", ob) });
                remove_enemy(ob);
                return 1;
        }
        return remove_enemy(ob);
}

// Stop all fighting, but killer remains.
// If force set to 1, it will clear all enemy, or it will only
// clear the enemy who doesn't kill you.
void remove_all_enemy(int force)
{
        int i;

        if( !(i = sizeof(enemy)) )
                return;

        while( i-- ) {
                // We ask our enemy to stop fight, but not nessessary to confirm
                // if the fight is succeffully stopped, bcz the fight will start
                // again if our enemy keeping call COMBAT_D->fight() on us.
                if( objectp(enemy[i]) ) {
                        if( force || !enemy[i]->is_killing(query("id")) ) {
                                enemy[i]->remove_enemy(this_object());
                                enemy[i] = 0;;
                        }
                }
        }

        enemy -= ({ 0 });
}

// Not want to kill anyone
void remove_all_want()
{
        want_kills = ({});
}

// Stop all fighting and killing.
void remove_all_killer()
{
        int i;
//      object ob;

        enemy -= ({ 0 });
        remove_all_want();

        for( i=0; i < sizeof(enemy); i++ ) {
                if( enemy[i]->query_leader()==this_object() )
                        enemy[i]->set_leader(0);
                if( enemy[i]->remove_killer(this_object()) )
                        enemy[i] = 0;
        }

        killer = ({ });
        enemy -= ({ 0 });
}

object query_competitor()
{
        return competitor;
}

object set_competitor(object ob)
{
        competitor = ob;
}

// set competition with ob
void competition_with(object ob)
{
        competitor = ob;
        fight_ob(ob);
        ob->set_competitor(this_object());
        ob->fight_ob(this_object());
}

// win a competition
void win()
{
        run_override("win");
        competitor = 0;
}

// lost a competition
void lost()
{
        run_override("lost");
        competitor = 0;
}

// return the next action of this object
mixed query_action(int flag)
{
        if( flag || !functionp(next_action) )
                return next_action;

        return (*next_action)(this_object());
}

// set next action
int set_action(mixed action, string fun)
{
        if( mapp(action) || functionp(action) ) {
                next_action = action;
        } else if (stringp(action) || objectp(action)) {
                next_action = (: call_other, action, fun :);
        } else
                return 0;

        return 1;
}

// set default action
// this action may be a simple mapping or a file & function to called
int set_default_action(mixed ob, string fun)
{
        default_object = ob;
        default_function = fun;
        return 1;
}

// reset_action()
//
// This function serves as a interface of F_ATTACK and wielded, worn objects.
// When the living's fighting action need update, call this function.
//
void reset_action()
{
        object me,ob;
        mapping prepare;
        string type, skill;

        me = this_object();
        prepare = query_skill_prepare();

        if( objectp(ob=query_temp("weapon")) ) {
                type = query("skill_type", ob);
                if( type == "pin" ) type = "sword";
        }

        if( !type ) {
                if( !prepare || sizeof(prepare) == 0 ) type = "unarmed";
                else if( sizeof(prepare) == 1 ) type = (keys(prepare))[0];
                else if( sizeof(prepare) == 2 )
                        type = (keys(prepare))[query_temp("action_flag")];
        }

        if( stringp(skill = query_skill_mapped(type)) &&
            (int)query_skill(skill, 1) > 0) {
                // If using a mapped skill, call the skill daemon.
                if( ob )
                        set_action((: call_other, SKILL_D(skill), "query_action", me, ob :), 0);
                else
                        set_action((: call_other, SKILL_D(skill), "query_action" :), 0);

                if( current_skill != skill ) {
                        current_skill = skill;
                        this_object()->change_skill_status(skill);
                        COMBAT_D->reset_combat_cache(this_object());
                }
        } else {
                // Else, let weapon handle it.
                if( ob )
                {
                        set_action(query("actions", ob), 0);
                }
                else
                        set_action(default_object, default_function);

                if( current_skill != skill ) {
                        current_skill = skill;
                        this_object()->change_skill_status(skill);
                        COMBAT_D->reset_combat_cache(this_object());
                }
        }
}

// this is called in heart_beat() to perform attack action.-- move to damage.c
int attack()
{
        object opponent;

        clean_up_enemy();

        opponent = select_opponent();
        if( objectp(opponent) )
        {
                set_temp("last_opponent", opponent);
                COMBAT_D->fight(this_object(), opponent);
                return 1;
        }

        else
                return 0;
}

//
// init() - called by MudOS when another object is moved to us.
//
void init()
{
        object me;
        object ob;
        mapping my, its;
//      string bunch_name;
//      string vendetta_mark;

        // We check these conditions here prior to handle auto fights. Although
        // most of these conditions are checked again in COMBAT_D's auto_fight()
        // function, these check reduces lots of possible failure in the call_out
        // launched by auto_fight() and saves some overhead.
        me = this_object();

        if( !living(me) ||
            !(ob = this_player()) ||
            !living(ob) ||
            sizeof(enemy) ||
            (!interactive(ob) && !interactive(me)) )
                return;

        if( query_temp("owner") ||
            query_temp("owner", ob) == me )
                return;

        my = me->query_entire_dbase();
        its = ob->query_entire_dbase();

        // Now start check the auto fight cases.
        if( interactive(ob) && is_killing(its["id"]) ) {
                if( interactive(me) ) {
                        // I don't wish two user kill ecah other
                        // when meeting. Because one player can
                        // kill another player & quit, then relogin,
                        // so nobody know that the player is willing
                        // to kill another player but another player
                        // may lost his life because auto fight.
                        // Here, I will check weather the player is
                        // really want to kill the other player,
                        // If want, then start auto fight.
                        if( !is_want_kill(its["id"]) ) {
                                remove_killer(ob);
                                return;
                        }
                }
                COMBAT_D->auto_fight(me, ob, "hatred");
                return;
        /*
        } else if( stringp(vendetta_mark = my["vendetta_mark"]) && query("vendetta/" + vendetta_mark, ob) ) {
                COMBAT_D->auto_fight(me, ob, "vendetta");
                return;
        */
        } else if( !playerp(ob) && my["attitude"] == "aggressive" ) {
                COMBAT_D->auto_fight(me, ob, "aggressive");
                return;
        }
        return;
}