// Written by Lonely@chinamud.cn
// npc.c

// #pragma save_binary

#include <command.h>

inherit CHARACTER;
inherit F_CLEAN_UP;

nosave int keep_beat_flag = 0;
void scan();
void full_self();
int  heal_self();
int  chat();
int  exert_function(string func);

void keep_heart_beat()
{
        set_heart_beat(1);
        keep_beat_flag = 1;
}

void not_keep_heart_beat()
{
        keep_beat_flag = 0;
}

int open_heart_beat()
{
        mapping my;

        if( keep_beat_flag )
                return 1;

        if( is_fighting() )
                return 1;

        if( this_object()->query_condition() )
                return 1;

        if( !living(this_object()) )
                return 1;

        if( this_object()->is_busy() )
                return 1;

        if( this_object()->is_weak() )
                return 1;

        if( query_temp("quest_ob") ||
            this_object()->is_quest_object() ||
            this_object()->is_time_ctl_ob() ) {
                keep_beat_flag = 1;
                return 1;
        }

        my = this_object()->query_entire_dbase();

        if( my["chat_chance"] ) {
                keep_beat_flag = 1;
                return 1;
        }

        if( (my["qi"] < my["max_qi"])
        ||      (my["eff_qi"] < my["max_qi"]) )
        {
                if( this_object()->is_master() ) full_self();
                return 1;
        }

        if( (my["jing"] < my["max_jing"])
        ||      (my["eff_jing"] < my["max_jing"]) )
        {
                if( this_object()->is_master() ) full_self();
                return 1;
        }

        return 0;
}

int init_master()
{
        int exp;
        int i, lvl, level;
        int degree;
        object ob;
        mapping sks;
        string *sk;

        ob = this_object();
        if( !query("master_ob") )
                return 0;

        exp = UPDATE_D->query_max_exp();
        level = to_int(pow(to_float(exp/100), 1.0 / 3)*10) +1;

        lvl = 0;
        degree = query("master_ob");
        switch(degree)
        {
        case 1  :  lvl = level / 5;     exp = exp / 5;     break;
        case 2  :  lvl = level * 2 / 5; exp = exp * 2 / 5; break;
        case 3  :  lvl = level * 3 / 5; exp = exp * 3 / 5; break;
        case 4  :  lvl = level * 4 / 5; exp = exp * 4 / 5; break;
        case 5  :  lvl = level;         exp = exp;         break;
        default :  return 0;
        }

        set("combat_exp", exp, ob);
        sks = ob->query_skills();
        sk = keys(sks);

        if( !sizeof(sk) ) return 0;
        for( i = 0; i < sizeof(sk); i++ ) {
                /*
                if( SKILL_D(sk[i])->type() == "knowledge" )
                        continue;
                */
                if( sks[sk[i]] >= lvl )
                        continue;

                ob->set_skill(sk[i], lvl);
        }
        return 1;
}

void setup()
{
        ::setup();

        if( query("master_ob") > 4 )
                init_master();
}

object carry_object(string file)
{
        object ob, env, *clone;

        ob = new(file);
        if( !objectp(ob) ) {
                clone = filter_array(children( file ), (: clonep :));
                if( sizeof(clone) && objectp(clone[0]) &&
                    objectp(env = environment(clone[0])) && !clonep(env) )
                        ob = clone[0];
        }

        if( ob && ob->violate_unique() )
                ob = ob->create_replica();

        if( ob && ob->is_ctl_ob()     // control ob.
        && (!ob->valid_clone()
        || !clonep()) )
        {
                destruct(ob);
                return 0;
        }

        if( objectp(ob) )
                ob->move(this_object());
        return ob;
}

object add_money(string type, int amount)
{
        object ob;

        ob = carry_object("/clone/money/" + type);
        if( !ob ) return 0;
        ob->set_amount(amount);
}

int accept_fight(object who)
{
        string att;
        int perqi;
        int perjing;

        if( !query("can_speak") ) {
                kill_ob(who);
                return 1;
        }

        if( this_object()->is_guarder() )
                return this_object()->check_enemy(who, "fight");

        att = query("attitude");
        perqi = (int)query("qi") * 100 / query("max_qi");
        perjing = (int)query("jing") * 100 / query("max_jing");

        if( is_fighting() ) {
                switch(att)
                {
                case "heroism":
                        if( perqi >= 50 ) {
                                command("say 哼！出招吧！");
                                return 1;
                        } else {
                                command("say 哼！我小歇片刻再收拾你不迟。");
                                return 0;
                        }
                        break;
                default:
                        command("say 想倚多为胜，这不是欺人太甚吗！");
                        return 0;
                }
        }

        if( perqi >= 75 && perjing >= 75 ) {
                switch (att)
                {
                case "friendly":
                        command("say " + RANK_D->query_self(this_object())
                                + "怎么可能是" + RANK_D->query_respect(who)
                                + "的对手？");
                        return 0;
                case "aggressive":
                case "killer":
                        command("say 哼！出招吧！");
                        break;
                default:
                        command("say 既然" + RANK_D->query_respect(who)
                                + "赐教，" + RANK_D->query_self(this_object())
                                + "只好奉陪。");
                        break;
                }
                return 1;
        }

        command("say 今天有些疲惫，改日再战也不迟啊。");
        return 0;
}

int accept_hit(object who)
{
        int t;
        string att;
        int perqi;
        int perjing;

        if( !query("can_speak") ) {
                kill_ob(who);
                return 1;
        }

        if( this_object()->is_guarder() )
                return this_object()->check_enemy(who, "hit");

/*
        if( this_object()->is_master() ) {
                command("say 这位" + RANK_D->query_respect(who)
                        + "，还是改日再切磋吧！");
                return -1;
        }
*/

        att = query("attitude");
        perqi = (int)query("qi") * 100 / query("max_qi");
        perjing = (int)query("jing") * 100 / query("max_jing");

        addn_temp("attempt_hit", 1);
        t = query_temp("attempt_hit");

        if( perqi >= 50 && perjing >= 50 ) {
                switch(att)
                {
                case "friendly":
                case "peaceful":
                        command("say 这位" + RANK_D->query_respect(who)
                                + "，且慢！");
                        break;
                case "aggressive":
                        if( random(t) > 8 ) {
                                command("say 他奶奶的，怎么这么烦？就让" +
                                        RANK_D->query_self_rude(this_object()) +
                                        "开开杀戒！");
                                kill_ob(who);
                                return 1;
                        }
                        command("say 好个" + RANK_D->query_rude(who) +
                                "，接招！");
                        break;
                case "killer":
                        if( random(t) > 3 ) {
                                command("say 哼，找死找到这里来了，" +
                                        RANK_D->query_self_rude(this_object()) +
                                        "手正痒呢！");
                                kill_ob(who);
                                return 1;
                        }
                        command("say 接招吧！");
                        break;
                default:
                        if( random(t) > 7 ) {
                                command("say 你要找死啊！");
                                kill_ob(who);
                                return 1;
                        }
                        command("say 这位" + RANK_D->query_respect(who)
                                + "，且慢！");
                        break;
                        switch (random(3))
                        {
                        case 0:
                                command("say 来来来！");
                                break;
                        case 1:
                                command("say 那就较量较量！");
                                break;
                        case 2:
                                command("say 来吧！我还会怕了你不成？");
                                break;
                        }
                        break;
                }
        } else {
                switch(att) {
                case "friendly":
                case "peaceful":
                        command("say 既然" + RANK_D->query_respect(who)
                                + "如此无礼，我只有不容情了！");
                        break;
                case "aggressive":
                case "killer":
                        command("say " + RANK_D->query_rude(who) +
                                "！你找死。");
                        break;
                default:
                        command("say 你不仁，我不义！" + RANK_D->query_rude(who) +
                                "，可不要怪我。");
                        break;
                }
                this_object()->kill_ob(who);
        }
        return 1;
}

int accept_kill(object who)
{
        if( !living(this_object()) )
                return 1;

        if( !query("can_speak") ) {
                kill_ob(who);
                return 1;
        }

        if( this_object()->is_guarder())
                return this_object()->check_enemy(who, "kill");

        switch(query("attitude"))
        {
        case "friendly":
        case "peaceful":
                command("say 既然" + RANK_D->query_respect(who)
                        + "如此逼迫，莫怪在下不留情！");
                break;
        case "aggressive":
        case "killer":
                command("say " + RANK_D->query_rude(who) +
                        "！明年的今天，就是你的忌日！。");
                break;
        default:
                command("say 好！" + RANK_D->query_rude(who)
                        + "，咱们就一决生死！");
                break;
        }
        return 1;
}

int accept_ansuan(object who)
{
        if( !query("can_speak") ) {
                kill_ob(who);
                return 1;
        }

        if( this_object()->is_guarder())
                return this_object()->check_enemy(who, "ansuan");

        command(random(2) ? "say 嗯？怎么…" : "say 啊呀，不好！");
        return 1;
}

int accept_touxi(object who)
{
        if( !query("can_speak") )
                return 1;

        if( this_object()->is_guarder() )
                return this_object()->check_enemy(who, "touxi");

        command(random(2) ? "say 嗯！怎么…是谁！" : "say 啊呀…你…");
        return 1;
}

// 为任务提供连接
mixed accept_ask(object who, string topic)
{
        if( this_object()->is_quester() )
                return QUEST_D->accept_ask(this_object(), who, topic);

        // 下面的程序为宗师任务服务
        if( !this_object()->is_knower() ) {
                if( query("ultraquest/id", who) == query("id") )
                        return ULTRA_QUEST_D->ask_information(this_object(), who, topic);
        }
}

// 接收物品
int accept_object(object who, object ob)
{
        string id;

        if( this_object()->is_quester() )
                return QUEST_D->accept_object(this_object(), who, ob);

        // 下面程序为宗师任务服务
        id = query("ultraquest/id", who);

        if( !id ) return 0;

        if( !this_object()->is_knower() &&
            (id == query("id") ||
            query("ultraquest/quest/id", who) == query("id")) )
                return ULTRA_QUEST_D->accept_object(this_object(), who, ob);
}

// 回覆任务人物的应酬
int need_accede(object who)
{
        string id;

        id = query("ultraquest/id", who);

        if( !id ) return 0;

        if( !this_object()->is_knower() &&
            (id == query("id") ||
            query("ultraquest/quest/id", who) == query("id")) )
                return ULTRA_QUEST_D->need_accede(this_object(), who);
}

// This function is called by the reset() of the room that creates this
// npc. When this function is called, it means the room demand the npc
// to return its startroom.
int return_home(object home)
{
        // Are we at home already?
        if( !environment() || environment() == home )
                return 1;

        // Are we able to leave?
        if( !living(this_object()) || is_fighting() ||
            !mapp(query("exits", environment())) )
                return 0;

        // Leave for home now.
        message("vision", this_object()->name() + "急急忙忙地离开了。\n",
                environment(), this_object());

        return move(home);
}

void scan()
{
        object me;

        me = this_object();
        if( !environment() || !living(me) ) return;

        if( me->is_coagent() && me->is_helping() && !me->is_fighting() ) {
                // finish helping
                me->finish_help();
        }

        if( !me->is_fighting() ) {
                // 消除仇恨
                me->remove_hatred();
        }

        if( heal_self() ) return;

        chat();
}

// Here, the NPC will process the heal/recover.
int heal_self()
{
        mapping my;
        int cost;

        if( is_busy() || is_fighting() )
                // 正忙？
                return 0;

        if( query("not_living") )
                // 非生物
                return 0;

        if( !query_skill_mapped("force") )
                // 没有激发内功
                return 0;

        if( query_temp("no_exert") )
                // 特殊情况禁止使用内功
                return 0;

        my = this_object()->query_entire_dbase();
        if( my["neili"] < 50 )
                return 0;

        if( my["jing"] < my["eff_jing"] * 8 / 10 ) {
                // 精气太少
                exert_function("regenerate");
                return 1;
        }

        if( my["qi"] < my["eff_qi"] * 8 / 10 &&
            query_skill("force") >= 150 &&
            my["eff_qi"] > my["max_qi"]/2 ) {
                // 气血不够充沛并且内功等级高
                exert_function("recover");
                return 1;
        }

        if( my["eff_qi"] < my["max_qi"] ) {
                // 受伤了
                exert_function("heal");
                return 1;
        }

        if( my["eff_jing"] < my["max_jing"] &&
            my["eff_qi"] > my["max_qi"]/2 ) {
                // 精受到了损失
                exert_function("jingheal");
                return 1;
        }

        if( my["neili"] < my["max_neili"] - 10 ) {
                // 内力不够充沛，打坐恢复
                cost = my["max_neili"] - my["neili"];
                if( cost > my["qi"] / 2 ) cost = my["qi"] / 2;
                command(sprintf("dazuo %d", cost));
                return 1;
        }

        return 0;
}

// This is the chat function dispatcher. If you use function type chat
// message, you can either define your own functions or use the default
// ones.
int chat()
{
        mixed msg, str;
        int chance, rnd;

        if( is_busy() )
                return 0;
        if( !chance = (int)query(is_fighting() ? "chat_chance_combat" : "chat_chance") )
                return 0;

        if( arrayp(msg = query(is_fighting() ? "chat_msg_combat" : "chat_msg")) && sizeof(msg) ) {
                if( random(120) < chance ) {
                        rnd = random(sizeof(msg));
                        str = msg[rnd];
                        if( stringp(str) )
                                say(str);
                        else if( functionp(str) )
                                return evaluate(str);
                }
                return 1;
        }
}

// Default chat
// Default chat function: Let the npc random move to another room.
int random_move()
{
        mapping exits;
        string *dirs;

        if( !environment() || !living(this_object()) ) return 0;
        if( !mapp(exits = query("exits", environment())) || !sizeof(exits) ) return 0;

        dirs = keys(exits);
        dirs -= ({ "dongtian" });
        if( !sizeof(dirs) ) return 0;
        command("go " + dirs[random(sizeof(dirs))]);
        return 1;
}

// Default chat function: Let the npc cast his/her enabled spells
void cast_spell(string spell)
{
        string spell_skill;

        if( !environment() || !living(this_object()) ) return;
        if( stringp(spell_skill = query_skill_mapped("spells")))
                SKILL_D(spell_skill)->cast_spell(this_object(), spell);
}

// Default chat function: Let the npc exert his/her enabled force
int exert_function(string func)
{
        string force_skill;

        if( !environment() || !living(this_object()) ) return 0;
        if( !stringp(force_skill = query_skill_mapped("force")) )
                return 0;
        if( this_object()->query_condition("no_exert") )
                return 0;

        if( SKILL_D(force_skill)->exert_function(this_object(), func) )
                return 1;

        return SKILL_D("force")->exert_function(this_object(), func);
}
// Default chat function: Let the npc perform special action with
// his/her enabled martial art
int perform_action(string action)
{
        string martial_skill, act;

        if( !environment() || !living(this_object()) ) return 0;
        if( this_object()->query_condition("no_perform") )
                return 0;
        if( !stringp(action))   return 0;
        if( sscanf(action, "%s.%s", martial_skill, act) != 2 )
                return 0;
        martial_skill = query_skill_mapped(martial_skill);
        if( stringp(martial_skill) )
                return SKILL_D(martial_skill)->perform_action(this_object(), act);
}

// Check the player wether is belong a family
int check_family(object ob, string fam)
{
        if( query("family/family_name", ob) == fam )
                return 1;

        if( !query("family/family_name", ob) &&
            query("born_name", ob) == fam )
                return 1;

        return 0;
}

// when remove
void remove()
{
        mixed fun;

        if( functionp(fun = query_temp("override/destruct")) )
                catch(evaluate(fun, this_object()));

        ::remove();
}

// environment destruct
void move_or_destruct()
{
        remove();
}
/*
void relay_emote(object me, string verb)
{
        string player_id, att, relay_msg;
        string *emote;
        string cmd_emote;
        object ob = this_object();
        int    i;

        if( !userp(me) )
                return;

        if( !query("can_speak", ob) )
                return;

        player_id = query("id", me);

        att = query( "attitude" );

        // 如果这个npc身上设了emote这个mapping
        // 对一些emote有特殊的反应，
        // 这个反应可以是个string，也可以是个function

        if( relay_msg = query("emote/" + verb) ) {
                if( stringp(relay_msg) )
                        message_vision(relay_msg + "\n", ob, me);
                else if( functionp(relay_msg) )
                        return evaluate(relay_msg);

                return;
        }

        if( random(2) != 1 )
                return ;

        emote = sort_array(EMOTE_D->query_all_emote(), 1);
        i = 0;
        i = sizeof(emote);

        if( !i ) return ;

        cmd_emote = emote[random(i)];
        command(cmd_emote + " " + player_id);
}
*/

void full_self()
{
        mapping my;

        clear_condition(0);
        clear_weak();
        this_object()->interrupt_me(this_object());

        my = this_object()->query_entire_dbase();

        my["eff_qi"] = my["max_qi"];
        my["qi" ] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["jing" ] = my["max_jing"];
        if( /*undefinedp*/(my["init_max_neili"]) )
                my["max_neili"] = my["init_max_neili"];
        if( /*!undefinedp*/(my["init_max_jingli"]) )
                my["max_jingli"] = my["init_max_jingli"];
        my["neili" ] = my["max_neili"];
        my["jingli" ] = my["max_jingli"];
        return;
}

void attempt_apprentice(object ob)
{
        command("sigh "+query("id", ob));
        command("say "+RANK_D->query_self(this_object())+"才疏学浅，不敢误人子弟，这位"+
                       RANK_D->query_respect(ob)+"另谋高就吧！");
        return;
}
