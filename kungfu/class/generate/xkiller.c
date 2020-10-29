// This program is a part of NT MudLIB

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

#include <slough.h>

void random_move();
int  is_stay_in_room()  { return 1; }

void create()
{
        string *long;

        ::create();
        long = query("from");
        set("gender", "男性");
        set("nickname", HIB "杀人狂魔" NOR);
        set("age", 30 + random(30));
        if (sizeof(long) < 1)
                set("long", "一个神秘的人。\n");
        else
                set("long", long[random(sizeof(long))]);
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("scale", 150);
        set("no_get", 1);

        set_temp("apply/armor", 100);
        set_temp("apply/damage", 15);
        set_temp("born_time", time());
        set_temp("dest_time", 1500 + time());

        add_money("silver", 10 + random(20));

        if (clonep()) keep_heart_beat();
}

void set_from_me(object me)
{
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me) -2);
        my = query_entire_dbase();

        if (my["max_qi"] > 6000)
                my["max_qi"] = 6000;

        if (my["max_jing"] < my["max_qi"] / 2)
                my["max_jing"] = my["max_qi"] / 2;

        if (my["max_jing"] > 3000)
                my["max_jing"] = 3000;

        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        my["quest_count"]=query("quest_count", me);

        exp=query("combat_exp", me)*11/10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);


        if (my["combat_exp"] > 5000000 && random(100) < 21)
        {
                // 经验 > 200K，21%几率出现多个敌人
                set_temp("multi-enemy", 1);
        }

        my["jiali"] = query_skill("force") / 3;
}

void init()
{
        object ob, baixing, env;
        object killer = this_object();

        ob = this_player();

        if( !query_temp("quester", this_object()) )
                return;

        if( query("id", ob) == query_temp("quester") && 
            query("slough/check", ob) )
        {
                killer->fight_ob(ob);
                ob->fight_ob(killer);
                COMBAT_D->do_attack(killer,ob,query_temp("weapon", killer),0);
                ob->remove_all_enemy(0);
                killer->remove_all_enemy(0);

                message_vision(
                        HIB "$n一看到$N, 不由分说，抄出家伙给你一记后，立马溜之大吉！\n" NOR,
                        ob, killer);

                tell_object(ob,"你终于查清杀人狂魔原来是"+query("family/family_name", killer)+"的败类。\n");

                place_npc(killer, ob);
                set("slough/inquiry", 1, ob);
        } else
        if( query("slough/chased", ob) && 
            !query("baixing", killer) && query("id", ob) == query_temp("quester") )
        {
                message_vision(
                        HIB "$n一看到$N，冷笑了一声: “又一个活得不耐烦的家伙，自寻死路！” \n" NOR,
                        ob, killer);

                this_object()->kill_ob(ob);
                ob->kill_ob(this_object());

                remove_call_out("kill_baixing");
                call_out("kill_baixing", 1, ob);
        } else
        if( query("slough/chased", ob) && 
            query("baixing", killer) && query("id", ob) == query_temp("quester") )
        {
                message_sort(
                        HIB "$n不屑地朝$N说道: “原来就是你一直在妨碍老子杀人！人我早杀完了，"
                        "你就来收尸吧，不过就不知道谁能帮你收尸了！” \n" NOR, ob, killer);
                command("heihei"+query("id", ob));

                this_object()->set_leader(ob);
                this_object()->kill_ob(ob);
                ob->kill_ob(this_object());
        }
}

void kill_ob(object ob)
{
        int lvl;

        exert_function("powerup");

        if( query("slough/id", ob) != query("id") )
        {
                ::kill_ob(ob);
                return;
        }

        if (lvl = query_temp("multi-enemy"))
        {
                // 出现多个敌人
                delete_temp("multi-enemy");
                call_out("do_help_me", 1 + random(2), ob);
        }
        ::kill_ob(ob);
}

void do_help_me(object ob)
{
        if (! objectp(ob) || environment(ob) != environment())
                return;

        switch (random(3))
        {
        case 0:
                message_vision(HIW "\n$N" HIW "大声喝道：“好一个" +
                               ob->name(1) +
                               HIW "！各位，不要再等了，快出来帮" +
                               RANK_D->query_self(this_object()) +
                               "一把！”\n" NOR, this_object(), ob);
                break;

        case 1:
                message_vision(HIW "\n$N" HIW "忽然撮舌吹"
                               "哨，你听了不禁微微一愣。\n" NOR,
                               this_object());
                break;

        case 2:
                message_vision(HIW "\n$N" HIW "一声长啸，声音"
                               "绵泊不绝，远远的传了开去。\n" NOR,
                               this_object());
                break;
        }

        call_out("do_continue_help", 1 + random(4), ob);
}

void do_continue_help(object ob)
{
        int n;
        object *obs;

        if (! objectp(ob) || environment(ob) != environment())
                return;

        n = random(3) + 1;
        set_temp("slough/help_count", n, ob);
        message("vision", HIR "说时迟，那时快！突然转出" +
                          chinese_number(n) +
                          "个人，一起冲上前来，看来是早"
                          "有防备！\n" NOR, environment());

        // 生成帮手
        obs = allocate(n);
        while (n--)
        {
                obs[n] = new(CLASS_D("generate") + "/slough_killed.c");
                NPC_D->set_from_me(obs[n], ob, 100);
                delete_temp("multi-enemy", obs[n]);
                set_temp("help_who", this_object(), obs[n]);
                set_temp("is_helper", 1, obs[n]);
        }

        // 参与战斗
        set_temp("help_ob", obs);
        set_temp("help_count", sizeof(obs));
        obs->move(environment());
        obs->set_leader(this_object());
        obs->kill_ob(ob);
}

void start_kill(object ob)
{
        int t;
        if(! objectp(ob))
        {
                destruct(this_object());
                return;
        }
        t=query("combat_exp", ob)/10000000;
        if (t < 1) t = 1;
        if (t > 5) t = 5;

        remove_call_out("kill_baixing");
        call_out("kill_baixing", (t * 90 + 30), ob);
}

int kill_baixing(object ob)
{
        object baixing;

        if( !query("baixing", this_object()) )
        {
                baixing = new("/quest/quest3/baixing");
                set("waiting",query("id",  ob), baixing);
                baixing->move(environment(this_object()));

                this_object()->set_leader(baixing);
                baixing->set_leader(this_object());
                kill_ob(baixing);
                set("baixing",query("id", baixing));
        }
        return 1;
}

int filter_to_bonus(object ob, object aob)
{
        if (! playerp(ob) || ! living(ob) ||
            ! ob->is_killing(query("id")))
                // 必须是玩家并且参与屠杀我(NPC)
                return 0;

        // 协助的对象一致
        return (aob == query_temp("quest/assist", ob));
}

// 当任务的NPC死亡的时候，检查是否可以进行奖励某些玩家。奖励
// 的对象：帮助任务者完成这个任务的所有人， 当然首先要求杀的
// 这个人是任务的完成对象，其次就是在这个场景中对该NPC下了杀
// 命令，并且协助了任务的完成者的玩家。
void die(object killer)
{
        object *obs;            // 场景中所有可以奖励的
        object dob;             // 打晕这个NPC的人
        object hob;             // 协助者
        object aob;             // 被协助者
        int qlevel;             // 本次任务的等级
        int lvl;                // NPC的等级
        int scale;              // NPC呼叫的帮手和逃跑的次数
        int n;                  // 可以奖励的人的数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        int weiwang;            // 需要瓜分的威望
        int score;              // 需要瓜分的阅历
        int extra_exp;          // 打晕的人的额外经验
        int extra_pot;          // 打晕的人的额外潜能
        string quester;         // 需要完成这个任务的玩家ID
        object qob;             // 需要完成这个任务的玩家对象
        object baixing;

        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_defeated_by();

        if( objectp(dob) && query_temp("owner", dob) )
                dob=query_temp("owner", dob);

        while (1)
        {
                // 记录：此任务已经终止
                if (stringp(quester = query_temp("quester")))
                {
                        qob = UPDATE_D->global_find_player(quester);
                        if( query("slough/id", qob) == query("id") )
                                set("slough/notice", "die", qob);
                        UPDATE_D->global_destruct_player(qob, 1);
                }

                if( dob && query("slough/id", dob) == query("id") )
                        // 我自己打死的
                        break;

                if( dob)aob=query_temp("quest/assist", dob);
                if( aob && query("slough/id", aob) == query("id") )
                        // 我协助别人杀死的
                        break;

                // 非任务所有者或是任务所有者协助的人杀死，则记录之。
                CHANNEL_D->do_channel(this_object(), "info",
                                      sprintf("听说%s被人杀死了。", name()));

                break;
        }

        if (! aob) aob = dob;

        if (! aob)
        {
                remove_call_out("kill_baixing");
                // 没有找到 QUEST 的属主
                ::die();
                return;
        }

        if (query("baixing") &&
             objectp(baixing = present(query("baixing", environment(this_object())))))
        {
                message_vision(CYN "$N对$n表示衷心的感谢！\n" NOR, baixing, dob);
                baixing->command("bye"+query("id", dob));
                destruct(baixing);
        }

        if (! query_temp("baixing_killed"))
        {
                set("slough/succeed", 1, dob);
                tell_object(dob,
                        HIY "由于你的卓越表现，成功的解救了当地的百姓！\n" NOR);
        }

        if( query("id", dob) == query_temp("quester") && 
            query("slough/succeed", dob) != 1 )
        {
                tell_object(dob,
                        HIW "由于你的失误，未能成功解救受害百姓！\n" NOR);
        }

        // 察看目前正在杀我的人，是否也有值得奖励的
        obs = all_inventory(environment());
        obs = filter_array(obs, (: filter_to_bonus :), aob);

        if ((n = sizeof(obs)) > 0)
        {
                // 查找打晕我的人：不是杀死我的人
                dob = query_defeated_by();

                // 奖励多少呢？总共奖励供所有的人分，最后每
                // 人加上一点随机量，其中打晕这个人的玩家获
                // 得额外的一些奖励。
                lvl = NPC_D->check_level(this_object());
                exp = 15 + random(10) + lvl;
                pot = 9 + random(5) + lvl;
                weiwang = 8 + random(6) + lvl / 2;
                score = 9 + random(6) + lvl / 2;

                // 根据这个任务的等级进行奖励调整
                switch(query("slough/level", aob) )
                {
                case 1:
                        break;
                case 2:
                        exp += exp / 2;
                        pot += pot / 2;
                        weiwang += weiwang / 2;
                        score += score / 2;
                        break;
                case 3:
                        exp += exp;
                        pot += pot;
                        weiwang += weiwang;
                        score += score;
                        break;
                default:
                        exp = exp / 2 + 1;
                        pot = pot / 2 + 1;
                        weiwang = weiwang / 2 + 1;
                        score = score / 2 + 1;
                        break;
                }
                // 如果NPC呼叫了帮手，则可以获得额外经验
                if (scale = sizeof(query_temp("help_count")) > 0)
                {
                        exp += exp * scale;
                        pot += pot * scale;
                }
                // 所有人均分经验：为什么除以n + 2？这是因为
                // 打晕我的人分两份经验，所以是n + 1，再加上
                // 领任务的这个人算1，那么就是n + 2。
                exp = exp / (n + 2) + 1;
                pot = pot / (n + 2) + 1;
                weiwang = weiwang / (n + 2) + 1;
                score = score / (n + 2) + 1;

                // 计算打晕我的额外奖励
                if (objectp(dob) && member_array(dob, obs) != -1)
                {
                        extra_exp = 1 + random(exp);
                        extra_pot = 1 + random(pot);
                        if( query("combat_exp", dob)<query("combat_exp")/2 )
                        {
                                // 出手的人武功比较低，获得的额外奖励多
                                extra_exp *= 2;
                                extra_pot *= 2;
                        } else
                        if( query("combat_exp", dob)>query("combat_exp")*2 )
                        {
                                // 出手的人武功太高，获得的额外奖励少
                                extra_exp /= 2;
                                extra_pot /= 2;
                        }
                }

                // 进行奖励
                foreach (hob in obs)
                {
                        // 调用延迟奖励，为什么这么调用？很简单，
                        // 因为我希望玩家在看到NPC死了以后才能够
                        // 看到奖励。
                        GIFT_D->delay_bonus(hob, ([ "exp"     : exp + random(4) +
                                                    ((hob == dob) ? extra_exp : 0),
                                                    "pot"     : pot + random(3) +
                                                    ((hob == dob) ? extra_pot : 0),
                                                    "weiwang" : weiwang + random(3),
                                                    "score"   : score + random(3),
                                                    "prompt"  : "击毙" + name() + "之后" ]));
                }
        }

        remove_call_out("kill_baixing");
        // 正常死亡
        ::die();

        return ;
}

int accept_fight(object ob)
{
        command("say 好！咱们就比划比划！");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say 你死去吧！");
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        command("say 哼！找死！");
        return 1;
}

void random_move()
{
        if (query_temp("is_helper"))
        {
                // is a helper
                if (! environment())
                {
                        // not in environment? unavaliable npc.
                        destruct(this_object());
                        return;
                }

                if (! query_temp("help_who"))
                {
                        // owner is killed. destruct this helper
                        if (! living(this_object()))
                                message_vision("$N缓缓的醒了过来。\n",
                                               this_object());

                        message_vision("$N看看四周，急匆匆的逃走了。\n",
                                       this_object());
                        destruct(this_object());
                        return;
                }

                // move with owner
                return;
        }

        if (time() > query_temp("dest_time"))
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->do_channel(this_object(), "info",
                                      sprintf("听说%s隐居到了深山老泽，从此不再出没在世间。", name()));
                log_file("static/killed_die", sprintf("%s %s(%s) vanished because timeout(%d:%d).\n",
                                                      log_time(), name(), query("id"),
                                                      time() - query_temp("born_time"),
                                                      query_temp("dest_time") - query_temp("born_time")));
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}