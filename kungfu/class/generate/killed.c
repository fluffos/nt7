// This program is a part of NT MudLIB
// person used in quest
// update by Lonely

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

#define GIFT_DIR        "/clone/gift/"
string  *GF_LIST = ({
        "xiandan", "shenliwan", "unknowdan", "xisuidan",
});

int  accept_object(object who, object ob);
int do_nod(string arg);
void random_move();
int  leave();
int  is_stay_in_room()  { return 1; }

void create()
{
        ::create();
        set("gender", "男性");
        set("age", 30 + random(30));
        set("long", "");
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("scale", 150);
        set("no_get", 1);
        set("auto_perform", 2);

        set_temp("apply/armor", 100);
        set_temp("apply/damage", 15);
        set_temp("born_time", time());
        set_temp("dest_time", 1200 + time());

        add_money("silver", 10 + random(20));

        if (clonep()) keep_heart_beat();
}

void init()
{
        add_action("do_nod", "nod");
}

void set_from_me(object me, int scale)
{
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me) - 2);
        my = query_entire_dbase();

        if (my["max_qi"] > 60000)
                my["max_qi"] = 60000;

        if (my["max_jing"] < my["max_qi"] / 2)
                my["max_jing"] = my["max_qi"] / 2;

        if (my["max_jing"] > 30000)
                my["max_jing"] = 30000;

        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];

        my["quest_count"]=query("quest_count", me);

        // 这里修改
        exp=query("combat_exp", me)*12/10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);


        if (my["combat_exp"] > 200000 && random(100) < 5)
        {
                // 经验 > 200K，5%几率出现多个敌人
                set_temp("multi-enemy", 1);
        }


        my["jiali"] = query_skill("force") / 3;
        if (query("place") == "西域")
                set_temp("dest_time", 900 + time());
        else
                set_temp("dest_time", 600 + time());
}

int do_nod(string arg)
{
        object obj;
        object me = this_player();
        object ob = this_object();
        int amount;

        if( !arg || arg != query("id", ob) || 
            !query_temp("family_quest/waiting", me) )
                return 0;

        me->command("nod");

        if( query_temp("family_quest/ob", me) )
        {
                message_sort(HIW "只见$N" HIW "长笑三声：“哈哈哈，识时务者为俊杰，" +
                        RANK_D->query_respect(me) + "果然是明白人，嘿嘿，这区区仙丹" +
                        "就归你了，哈哈。”\n\n" NOR,
                        ob, me);
                obj = new(GIFT_DIR + GF_LIST[random(sizeof(GF_LIST))]);

                tell_object(me, HIR + ob->name() + "递给了你" + obj->name() +
                        HIR "以后，吐出一口鲜血，扬长而去。\n" NOR);
                if (! obj->move(me))
                        obj->move(environment(me));
                delete_temp("family_quest", me);
                destruct(ob);
                return 1;
        }
        amount=query_temp("family_quest/waiting", me);

        message_sort(HIW "只见$N" HIW "长笑三声：“哈哈哈，识时务者为俊杰，" +
                RANK_D->query_respect(me) + "果然是明白人，嘿嘿，这区区" +
                chinese_number(amount) + "两黄金就归你了，哈哈。”\n\n" NOR,
                ob, me);
        MONEY_D->pay_player(me, amount * 10000);
        tell_object(me, HIR + ob->name() + "递给了你" + chinese_number(amount) +
                "两黄金以后，吐出一口鲜血，扬长而去。\n" NOR );
        delete_temp("family_quest", me);
        destruct(ob);
        return 1;
}

void kill_ob(object ob)
{
        int lvl;

        if (! is_busy())
                exert_function("powerup");

        if( query("quest/id", ob) != query("id") )
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
        set_temp("quest/help_count", n, ob);
        message("vision", HIR "说时迟，那时快！突然转出" +
                          chinese_number(n) +
                          "个人，一起冲上前来，看来是早"
                          "有防备！\n" NOR, environment());

        // 生成帮手
        obs = allocate(n);
        while (n--)
        {
                obs[n] = new(CLASS_D("generate") + "/killed.c");
                NPC_D->set_from_me(obs[n], ob, 200);
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

int filter_to_bonus(object ob, object aob)
{
        object *obs;

        if (! playerp(ob) || ! living(ob) ||
            ! ob->is_killing(query("id")))
                // 必须是玩家并且参与屠杀我(NPC)
                return 0;

        // 协助的对象一致
        if( aob == query_temp("quest/assist", ob) )
                return 1;

        // 都在一个阵法中
        obs = ob->query_array_member();
        if (sizeof(obs) > 0 && member_array(aob, obs) != -1)
                return 1;

        // 都在一个队伍中
        obs = ob->query_team_member();
        if (sizeof(obs) > 0 && member_array(aob, obs) != -1)
                return 1;
}

// remove
void remove()
{
        object qob;

        if (objectp(qob = query_temp("quest_ob")))
        {
                // 这个人已经消失了，取消相关联的任务
                destruct(qob);
        }

        ::remove();
}

// 随即重新放置
void random_place(string msg)
{
        object old_env;
        object qob;
        string *not_place;
        string new_place;
        int limit;
        int qcount;

        // 如果原先创建了任务，就直接修改信息
        if (objectp(qob = query_temp("quest_ob")))
                set("introduce", msg, qob);
        else
                qob = new("/clone/quest/avoid");

        // 随即选择另外一个地方放置NPC
        old_env = environment();
        not_place = ({ query("place") });

        if (query("combat_exp") < 500000)
                not_place += ({ "大理一带" });

        if (query("combat_exp") < 800000)
                not_place += ({ "西域" });

        NPC_D->place_npc(this_object(), not_place);

        // 根据格式化消息生成结果
        msg = replace_string(msg, "$N", name(1));

        qcount = query("quest_count");
        if ((qcount < 100 || qcount >= 900) && random(10) ||
            (qcount >= 100 && qcount < 900) && random(50))
        {
                new_place = query("place");
                if (new_place == "西域")
                        limit = 1800;
                else
                        limit = 1200;
        } else
        {
                new_place = "很远的地方";
                limit = 1800;

                // 减少打听的价格
                set("ask_cheap", 3);
        }
        set_temp("dest_time", limit + time());
        msg = replace_string(msg, "PLACE",  new_place);

        // 初始化并记录这个任务
        set("introduce", msg, qob);
        qob->init_quest(name(1), old_env);
        set_temp("quest_ob", qob);

        return;
}

// 晕倒的时候有机会逃走
void unconcious()
{
        object *obs;
        object ob;
        object me;
        int amount = 10 + random(10);
        mapping my;
        string msg;
        string quester;
        string *condition = ({
                "气喘吁吁，就要不支", "头重脚轻，马上就倒",
                "呕血成升，眼冒金星", "伤痕累累，无力招架",
        });

        if (! query_temp("is_helper") && ! query_temp("help_ob"))
        {
                if (random(100) < 8)
                {
                        // 10%几率逃走
                        switch (random(8))
                        {
                        case 0:
                                msg = HIC "$N" HIC "狂叫一声，狂吐几"
                                      "口鲜血，眼看就已不支，忽然一"
                                      "道黑影窜出，接连攻出数招，逼"
                                      "退$n" HIC "，只在这么一瞬间，"
                                      "此人已经扶起$N" HIC "，遁逃而"
                                      "走，竟然未留半点痕迹。\n" NOR;
                                break;
                        case 1:
                                msg = HIC "$N" HIC "摇摇欲坠，眼看就"
                                      "要跌倒，忽然口中喷出一口鲜血"
                                      "，$n" HIC "连忙侧身一避，就在"
                                      "此时，$N" HIC "奋然振作精神，"
                                      "提气一纵，竟然飘出十数丈之远"
                                      "，令人目瞪口呆！只见$N" HIC
                                      "刹间变做一个黑影，渐渐消失。"
                                      "\n" NOR;
                                break;
                        case 2:
                                msg = HIC "在$n" HIC "一阵狂攻之下，"
                                      "$N" HIC "只有招架之功，哪里还"
                                      "有还手之力？眼看就要命丧$n" HIC
                                      "之手，$N" HIC "忽然招式一变，"
                                      "精妙无方，竟是世上罕见！$n" HIC
                                      "略一疏神，已被$N" HIC "连环数"
                                      "招逼退，只见$N" HIC "迈开大步"
                                      "，逃遁而走。\n" NOR;
                                break;
                        case 3:
                                msg = HIC "只见$N" HIC "深吸一口气"
                                      "，神色略微好了一些，陡然迸发"
                                      "出惊天动地的一声大吼，直震得"
                                      "$n" HIC "发耳欲聩！仅这一霎"
                                      "，$N" HIC "身形一转，飘然退"
                                      "去，竟让$n" HIC "措手不及，"
                                      "追赶不上！\n" NOR;
                                break;
                        case 4:
                                msg = HIC "$n" HIC "连连进击，眼看"
                                      "便要得手，接连数招，让$N" HIC
                                      "已是避无可避，退无可退！$N"
                                      HIC "神色神色仓皇，急切间猛地"
                                      "咬中舌尖，“噗”的吐出！$n"
                                      HIC "只见眼前一阵红雾，待得雾"
                                      "散去，哪里还有$N" HIC "的影"
                                      "子？\n" NOR;
                                break;
                        case 5:
                                msg = HIC "$N" HIC "再退一步，却慢"
                                      "了小许，腿上早中招！一声惨"
                                      "呼，人已跌倒。$n" HIC "见状"
                                      "赶上前去，忽然眼前星光闪闪"
                                      "，仓皇下急退，只听有人哈哈"
                                      "大笑道：“$N" HIC "莫慌，我"
                                      "来也！”说罢又是一撒手，数"
                                      "十根银针飞出，待得$n" HIC
                                      "抵挡两下，那人早扶起$N" HIC
                                      "遁去了。\n" NOR;
                                break;
                        case 6:
                                msg = HIC "$N" HIC "晃了两下，忽然"
                                      "跌倒。$n" HIC "收住招式，笑道"
                                      "：“$N" HIC "，你……”话音未"
                                      "落，忽见$N" HIC "蓦的窜起，一"
                                      "招直奔$n" HIC "的要害，$n" HIC
                                      "大吃一惊！慌忙招架，只觉得内"
                                      "息紊乱，几欲呕吐！$N" HIC "也"
                                      "不追击，只是急奔而走，$n" HIC
                                      "连运几口气，去了胸前烦闷，却"
                                      "已不见$N" HIC "的踪影。\n" NOR;
                                break;
                        default:
                                msg = HIC "$N身负重伤，已然不敌，悲"
                                      "愤间只放声疾呼，一时震得$n"
                                      HIC "耳鼓欲破，攻势少缓。$N"
                                      HIC "猛然见到有机可乘，哪里肯"
                                      "放过，连出数招，杀出一条血路"
                                      "，就此不见。\n" NOR;
                                break;
                        }

                        clean_up_enemy();
                        obs = query_enemy();
                        if (sizeof(obs) > 0) ob = obs[0]; else ob = 0;
                        if (! objectp(ob))
                                msg = replace_string(msg, "$n", "众人");
                        message_sort("\n" + msg, this_object(), ob);

                        // 解除NPC的中毒状态
                        clear_condition(0);

                        // 恢复NPC的力气
                        my = query_entire_dbase();
                        my["eff_jing"] = my["max_jing"];
                        my["jing"]     = my["max_jing"];
                        my["eff_qi"]   = my["max_qi"] * 2 / 3;
                        my["qi"]       = my["eff_qi"];
                        my["neili"]    = my["max_neili"] * 2;
                        if (! intp(query_temp("escape_times")))
                                set_temp("escape_times", 1);
                        else
                                addn_temp("escape_times", 1);

                        // 登记一个任务，以便玩家可以追踪他的行迹
                        switch (random(9))
                        {
                        case 0:
                                msg = "听说$N被人打伤逃走，据说是躲到PLACE去了。";
                                break;
                        case 1:
                                msg = "听说$N和人动手，差点被打死，不过最"
                                      "后还是侥幸逃走了，好像去了PLACE。";
                                break;
                        case 2:
                                msg = "听说那$N和人一场血战，最后还是全身"
                                      "而退，好像是去了PLACE吧。";
                                break;
                        case 3:
                                msg = "$N听说是在PLACE啊，不过前一阵好像来过这里的。";
                                break;
                        case 4:
                                msg = "听说$N被人打死了吧？咦？不过听人说"
                                      "在PLACE也见过他呀！";
                                break;
                        case 5:
                                msg = "这事我也不太清楚，不过听说他好像在PLACE。";
                                break;
                        case 6:
                                msg = "你找他干啥？他不是在PLACE么？";
                                break;
                        case 7:
                                msg = "前两天他还来过我们这儿呢，现在应该"
                                      "是去了PLACE吧。";
                        default:
                                msg = "$N呀，有人说在PLACE看到过他，好像还受伤了。";
                                break;
                        }

                        random_place(msg);
                        remove_all_enemy(1);
                        return;
                } else
                if (objectp(me = query_last_damage_from()) &&
                    environment() == environment(me) &&
                    !query_temp("family_quest/waiting", me) )
                {
                        switch (random(20))
                        {
                        case 1:
                                message_sort(HIR "\n眼见$N" HIR + condition[random(sizeof(condition))] +
                                        "，突然$N大喝一声，急退几步，\n“扑通”给$n跪了下来。"
                                        "\n" NOR, this_object(), me);
                                tell_object(me, HIW + this_object()->name() + "突然从怀里掏出一堆白花花的银子，小声"
                                        "对你道：“这位" + RANK_D->query_respect(me) + "，\n你"
                                        "就网开一面（nod）如何，这" + chinese_number(amount) +
                                        "两黄金就归你了！”\n" NOR);
                                clean_up_enemy();
                                remove_all_enemy(1);
                                clear_condition(0);
                                set("qi", 1, this_object());
                                set("jing", 1, this_object());
                                set_temp("family_quest/waiting", amount, me);
                                return;
                        case 2:
                                message_sort(HIR "眼见$N" HIR + condition[random(sizeof(condition))] +
                                        "，突然$N大喝一声，急退几步，\n“扑通”给$n跪了下来。"
                                        "\n" NOR, this_object(), me);
                                tell_object(me, HIW + this_object()->name() + "突然从怀里掏出一粒仙丹，小声"
                                        "对你道：“这位" + RANK_D->query_respect(me) + "，\n你"
                                        "就网开一面（nod）如何，这仙丹就归你了！”\n" NOR);
                                clean_up_enemy();
                                remove_all_enemy(1);
                                clear_condition(0);
                                set("qi", 1, this_object());
                                set("jing", 1, this_object());

                                set_temp("family_quest/waiting", amount, me);
                                set_temp("family_quest/ob", 1, me);
                                return;
                        default:
                                break;
                        }
                }
        }

        if (stringp(quester = query_temp("quester")))
        {
                // 如果找到领取该quest的人
                if (objectp(ob = find_player(quester)))
                        set_temp("quest/escape_times", query_temp("escape_times"), ob);
        }
        ::unconcious();
}



// 当任务的NPC死亡的时候，检查是否可以进行奖励某些玩家。奖励
// 的对象：帮助任务者完成这个任务的所有人， 当然首先要求杀的
// 这个人是任务的完成对象，其次就是在这个场景中对该NPC下了杀
// 命令，并且协助了任务的完成者的玩家。
void die(object killer)
{
        mapping quest;          // 任务
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
        object ob;              // NPC暴出的物品
        string *ob_list = ({    // 任务赋予NPC身上的暴出随机物品
                "/clone/gift/puti-zi",
                "/clone/gift/jiuzhuan",
                "/clone/gift/tianxiang",
                "/clone/gift/xuanhuang",
                "/clone/fam/gift/int3",
                "/clone/fam/gift/con3",
                "/clone/fam/gift/dex3",
                "/clone/fam/gift/str3",
                "/clone/fam/item/stone1",
                "/clone/fam/item/stone2",
                "/clone/fam/item/stone3",
                "/clone/fam/item/stone4",
                "/clone/fam/etc/lv5f",
                "/clone/fam/etc/lv5d",
                "/clone/fam/etc/lv7c",
                "/clone/fam/etc/lv7d",
                "/clone/fam/etc/lv7b",
                "/clone/fam/etc/lv7a",
                "/clone/fam/etc/prize5",
                "/clone/fam/item/baxian",
                "/clone/fam/item/kunlun",
                "/clone/fam/item/leihuo",
                "/clone/fam/item/lihuo",
                "/clone/fam/item/zhenlong",
                "/clone/tessera/rune16", 
                "/clone/tessera/rune17", 
                "/clone/tessera/rune18", 
                "/clone/tessera/rune19", 
                "/clone/tessera/rune20", 
                "/clone/herb/blood", 
                "/clone/herb/xuelian2", 
                "/clone/herb/yulu", 
                "/clone/herb/sheli4", 
                "/clone/herb/renshen2", 
                "/clone/herb/puti4", 
                "/clone/herb/lingzhi2", 
                "/clone/herb/dimai", 
        });

        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_defeated_by();

        if (! objectp(dob))
                dob = query_temp("last_damage_from"); 

        if( objectp(dob) && query_temp("owner", dob) )
                dob=query_temp("owner", dob);

        while (1)
        {
                // 记录：此任务已经终止
                if (stringp(quester = query_temp("quester")))
                {
                        qob = UPDATE_D->global_find_player(quester);
                        if( query("quest/id", qob) == query("id") )
                                set("quest/notice", "die", qob);
                        UPDATE_D->global_destruct_player(qob, 1);
                }

                if( dob && query("quest/id", dob) == query("id") )
                        // 我自己打死的
                        break;

                if( dob)aob=query_temp("quest/assist", dob);
                if( aob && query("quest/id", aob) == query("id") )
                        // 我协助别人杀死的
                        break;

                if (dob && dob->in_array() && dob->query_array_status())
                        // 我组阵杀死的
                        break;

                if (dob && dob->in_team())
                        // 我组队杀死的
                        break;

                // 非任务所有者或是任务所有者协助的人杀死，则记录之。
                /*
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("听说%s被人杀死了。", name()));
                log_file("static/killed_die", sprintf("%s %s(%s) died at %s because %s.\n",
                                                      log_time(), name(), query("id"),
                                                      environment()->short(),
                                                      dob?sprintf("%s(%s)",dob->name(1),query("id", dob)):"none"));
                */

                break;
        }

        if (! aob) aob = dob;

        if (! aob)
        {
                // 没有找到 QUEST 的属主
                ::die(killer);
                return;
        }

        // 察看目前正在杀我的人，是否也有值得奖励的
        obs = all_inventory(environment(this_object()));
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
                switch(query("quest/level", aob) )
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
                if ((scale = sizeof(query_temp("help_count") +
                     query_temp("escape_times") * 2)) > 0)
                {
                        exp += exp * scale / 2;
                        pot += pot * scale / 2;
                }
                // 所有人均分经验：为什么除以n + 2？这是因为
                // 打晕我的人分两份经验，所以是n + 1，再加上
                // 领任务的这个人算1，那么就是n + 2。
                if (n > 1)
                {
                        exp *= 1.2;
                        pot *= 1.2;
                        weiwang *= 1.2;
                        score *= 1.2;
                }
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

        // 根据玩家连续完成的任务数量来随机暴出物品
        if ((query_temp("is_helper") || query_temp("help_ob") ||
            query_temp("escape_times")))
        {
                // 有帮手、帮手、或者逃跑过的NPC有九成的机率物品被暴下来
                ob = new(ob_list[random(sizeof(ob_list))]);
                message_vision(HIY"$N"HIY"身子一退，掉下一"+query("unit", ob)+
                        ob->name() + HIY "。\n\n" NOR, this_object());
                ob->move(environment());
        }

        // 无需要完成这个任务的玩家？或者无法生成远程任务，
        // 那么就正常死亡
        // 如果不是自己杀死的，不允许发送远程任务
        if (! qob || !qob->quest_letter_srv() ||
            // 判断是否是领取任务的本人杀死该任务的npc
            // quester != query("id", dob) ||
            ! mapp(quest = QUEST_D->prepare_quest(qob)))
        {
                ::die(killer);
                return;
        }

        // 人物正常完成
        set("quest/finished", 1, qob);

        // 使用书信分配任务
        QUEST_D->remote_assign_quest(qob, quest);

        // 正常死亡
        ::die(killer);

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

                /*
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("听说%s隐居到了深山老泽，从此不再出没在世间。", name()));
                log_file("static/killed_die", sprintf("%s %s(%s) vanished because timeout(%d:%d).\n",
                                                      log_time(), name(), query("id"),
                                                      time() - query_temp("born_time"),
                                                      query_temp("dest_time") - query_temp("born_time")));
                */
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}

