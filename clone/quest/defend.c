// 玩家任务：defend.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#include <defend.h>

#define ENEMY_FAM             my["enemy_fam"]      // 攻击者来自的门派
#define DEFEND_FAM            my["defend_fam"]     // 要保卫的门派
#define MASTER_ID             my["master_id"]
#define PLACE                 my["place"]
#define MIN_EXP               30000                // 最小 EXP 要求

nosave object dmaster = 0;

// 下面区分正派和邪派，就是为了防止出现一个门派自己攻击
// 自己的荒唐情况（当然这也不难避免），一般而言，都是正
// 派攻击邪派，或者邪派攻击正派的（诸如“六大门派围攻光
// 明顶”、“日月神教灭五岳剑派”什么的），但是我们知道，
// 有些门派是很难说得清正邪的，比如桃花岛，姑苏慕容等等，
// 这样我们就认为，同时不属于以下两个数组的门派，是“亦
// 正亦邪”或者说是“不正不邪”，也就是说，它在这场纷争
// 中的态度是：既可能攻击正派，也可能攻击邪派，当然，也
// 可能攻击亦正亦邪的门派。

// 正派列表
string *zps = ({
        "武当派", "华山气宗", "全真教", "古墓派",
        "灵鹫宫", "桃花岛", "关外胡家", "段氏皇族",
        "峨嵋派", "丐帮", "少林派", "逍遥派",
        "明教", "华山剑宗","唐门世家",
});

// 邪派列表
string *xps = ({
        "星宿派", "血刀门", "大轮寺", "欧阳世家",
        "神龙教", "慕容世家", "日月神教",
});

void die(object ob);
void npc_destructed();
void move_enemy(object enemy, string family);
void remove_enemy();
int  ask_defend(object ob, object me);
int  ask_finish(object ob, object me);

// 任务对象创建
void create()
{
        seteuid(getuid());
        setup();
}

// 启动一个任务
// 输入生成敌人的数量和被攻击的门派名称，已经向这个门
// 派的掌门要了任务的人可以去杀这些敌人，任务时间到了
// 就可以要奖励。
void init_quest(int num, string family_name)
{
        int i;
        mapping my;
        object enemy;
        string *family;
        string enemy_fam;
        object env;

        my = query_entire_dbase();

        // 生成任务的名字
        set_name("围攻" + family_name);

        // 随机生成攻打者的门派
        family = keys(familys);
        if (member_array(family_name, xps) != -1)
        {
                family = family - xps - ({ family_name });
                enemy_fam = family[random(sizeof(family))];
        }
        // 否则就派正派上场
        else
        {
                family = family - zps - ({ family_name });
                enemy_fam = family[random(sizeof(family))];
        }

        // 记录任务的数据信息
        ENEMY_FAM = enemy_fam;
        DEFEND_FAM = family_name;
        MASTER_ID = familys[family_name]["master_id"];
        PLACE = familys[family_name]["master_place"];

        env = get_object(PLACE);

        if (! objectp(dmaster = present(MASTER_ID, env)) ||
            query("startroom", dmaster) != base_name(env) )
        {
                destruct(this_object());
                return;
        }

        // 设置NPC的对话信息
        set("inquiry/"+name(), "你可以输入指令defend来领取保卫门派任务。", dmaster);
        dmaster->set("inquiry/"+ENEMY_FAM,"这个"+ENEMY_FAM+"真是太可恶了，"
                                            "屡次来我们" + DEFEND_FAM +"挑衅。");
        dmaster->set("inquiry/"+DEFEND_FAM,"在下就是"+DEFEND_FAM+"的掌门呀，"
                                            "你愿不愿意助本门一臂之力，共御外敌？");
        set_temp("override/ask_defend", (:ask_defend:), dmaster);
        set_temp("override/ask_finish", (:ask_finish:), dmaster);

        // 按照指定位置送走敌人
        for (i = 0; i < num; i++)
        {
                enemy = new("/clone/npc/enemy");
                enemy->create_family(enemy_fam, familys[enemy_fam]["generation"]
                                                + (-1 + random(2)), "弟子" );
                enemy->setup_family(enemy_fam);
                set("is_attacking", family_name, enemy);
                set("long", "这人是前来攻打"+family_name+"的一名"+enemy_fam+"弟子。\n", enemy);

                // enemy->set_temp("override/die", (: die :));

                move_enemy(enemy, family_name);
        }

        CHANNEL_D->do_channel(dmaster, "family",
                        sprintf("听说%s的一班弟子大举杀上我派，我派形势不妙。", enemy_fam));

        // 切换到正常状态
        change_status(QUEST_READY);

        // 设置任务最长存活时间：5分钟
        set("live_time", 300);

        // 登记谣言消息
        register_information();
}

void send_enemy(int num, string family_name)
{
        object enemy;
        string enemy_fam;
        string *family;
        int i;

        family = keys(familys);
        if (member_array(family_name, xps) != -1)
        {
                family = family - xps - ({ family_name });
                enemy_fam = family[random(sizeof(family))];
        }
        // 否则就派正派上场
        else
        {
                family = family - zps - ({ family_name });
                enemy_fam = family[random(sizeof(family))];
        }

        for (i = 0; i < num; i++)
        {
                enemy = new("/clone/npc/enemy");
                enemy->create_family(enemy_fam, familys[enemy_fam]["generation"]
                                                + (-1 + random(2)), "弟子" );
                enemy->setup_family(enemy_fam);
                set("is_attacking", family_name, enemy);
                set("long", "这人是前来攻打"+family_name+"的一名"+enemy_fam+"弟子。\n", enemy);

                set_temp("override/die", (:die:), enemy);

                move_enemy(enemy, family_name);
        }

        return;
}

// 送走敌人（在 ENEMY 的 chat_msg 中也有呼叫）
void move_enemy(object enemy, string family)
{
        string *places = familys[family]["place"];
        string place = places[random(sizeof(places))];
        object room;

        if (objectp(room = environment(enemy)))
        {
                tell_room(room, enemy->name() + "一闪身就不见了。\n");
        }
#ifdef DEBUG
        CHANNEL_D->do_channel(this_object(), "sys",
                sprintf("%s : %O", enemy->short(), place));
#endif
        enemy->move(place);
        tell_room(place,"只见一名"+query("family/family_name", enemy)+"弟子不知什么时候钻了出来。\n");

        return;
}

// 恢复NPC：任务结束的时候必须恢复正常的NPC
void restore_npc()
{
        mapping my = query_entire_dbase();
        object npc_ob;

        if (! objectp(npc_ob = dmaster))
                return;

        delete_temp("override/ask_defend", npc_ob);
        delete_temp("override/ask_finish", npc_ob);
        delete("inquiry/"+name(), npc_ob);
        delete("inquiry/"+ENEMY_FAM, npc_ob);
        delete("inquiry/"+DEFEND_FAM, npc_ob);
        dmaster = 0;
}

// 结束任务
void cancel_quest()
{
        remove_enemy();
        restore_npc();
        ::cancel_quest();
}

// 到时间了，送走敌人
void remove_enemy()
{
        object *enemys;
        int i;
        mapping my = query_entire_dbase();

        enemys = children("/clone/npc/enemy");
        enemys=filter_array(enemys,(:query("is_attacking", $1) == $(DEFEND_FAM )
                                       && query("family/family_name", $1) == $(ENEMY_FAM):));

        if (sizeof(enemys) > 0)
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "只见" + enemys[i]->name()
                                        + "突然面色一变，迅速攻出几招，跳出战圈转身逃了。\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "只见" + enemys[i]->name()
                                        + "掐值一算，突然脸色大变，急急忙忙地逃走了。\n");
                        }
                        destruct(enemys[i]);
                }
        }
        return;
}

// 要到任务才能去杀人（去掉非要本门的限制）
int ask_defend(object ob, object me)
{
        string *places, place;

        string *msg_now =
        ({
                "最近本门常有人来挑衅", "最近本门似乎不太平安",
                "最近本门时有敌人进攻", "最近本门似乎很不安稳",
                "听说就快要有敌人进攻", "常有人对本门虎视眈眈",
        });
        string *msg_do =
        ({
                "赶快到四处巡查巡查", "注意四周都要去查查",
                "山上山下都仔细看看", "在本门要道好好守着",
                "在险要地方做好防卫", "得防止敌人攻上山来",
        });
        string *msg_place =
        ({
                "虽然说不上山明水秀，但是", "也是一个险要位置，所以",
                "好歹也是个重要关卡，因此", "毕竟算个本门要地，那么",
                "常常有敌人来此攻打，所以", "就怕敌人攻到这里，因此",
        });

        if( !query("family/family_name", me) )
        {
                ob->command("haha"+query("id", me));
                message_sort(HIC "$N" HIC "对$n" HIC "道：“" + RANK_D->query_respect(me)
                                +"无门无派，问我要什么任务呢？”\n" NOR, ob, me);
                tell_object(me, HIW "你还是先拜个师父再要任务吧。\n" NOR);
                return 1;
        }

        if( query("family/family_name", ob) != query("family/family_name", me) )
        {
                ob->command("?"+query("id", me));
                message_sort(HIC "$N" HIC "皱着眉头对$n" HIC "道：“这位"
                        +query("family/family_name", me)+"的"+RANK_D->query_respect(me)+
                        "，你怕是找错人了吧？”\n" NOR, ob, me);
                tell_object(me, HIW "这不是你自己的门派，你不应该问这位师傅要任务呀。\n" NOR);
                return 1;
        }

        if( query("combat_exp", me)<MIN_EXP )
        {
                ob->command("sigh");
                message_sort(HIC "$N" HIC "对$n" HIC "道：“唉，你还是等水平高些"
                                "再来做这个任务不迟。”\n" NOR, ob, me);
                tell_object(me, HIW "这个任务得有 " +MIN_EXP+" 点经验值才能做。\n" NOR);
                return 1;
        }

        if( query_temp("defend_quest", me) && !wizardp(me) )
        {
                ob->command("yi");
                message_sort(HIC "$N" HIC "疑惑地对$n" HIC "道：“你不是已经在做"
                                "这个任务了么？\n怎么还来找我？”\n" NOR, ob, me);
                tell_object(me, HIW "快去做好准备，保卫你的门派吧。\n" NOR);
                return 1;
        }

        else
        {
                places = familys[query("family/family_name", me)]["place"];
                place = places[random(sizeof(places))];
                place=query("short", get_object(place));

                send_enemy(10,query("family/family_name", me));

                command("nod"+query("id", me));
                message_sort(HIC "$N" HIC "赞许地对$n" HIC "道：“好吧，"
                        + msg_now[random(sizeof(msg_now))] +"，你要注意\n"
                        + msg_do[random(sizeof(msg_do))] + "。”\n" NOR, ob, me);

                tell_object(me, HIW + ob->name() + HIW "悄悄告诉你：“"
                        + place + HIW"这个地方" + msg_place[random(sizeof(msg_place))]
                        +"\n你最好多注意注意。”\n" NOR);

                set_temp("defend_quest/start", 1, me);
                me->apply_condition("swjob", 30 + random(30));
                return 1;
        }
}

int ask_finish(object ob, object me)
{
        int killed, exp, pot, gongxian;

        if( !query("family/family_name", me) )
        {
                ob->command("haha"+query("id", me));
                message_vision(HIC "$N" HIC "对$n" HIC "道：“" + RANK_D->query_respect(me)
                                +"无门无派，问我要什么任务呢？”\n\n" NOR,ob,me);
                tell_object(me, HIW "你还是先拜个师父再要任务吧。\n" NOR);
                return 1;
        }

        if( query("family/family_name", ob) != query("family/family_name", me) )
        {
                ob->command("?"+query("id", me));
                message_vision(HIC "$N" HIC "皱着眉头对$n" HIC "道：“这位" +
                               query("family/family_name", me)+"的"+RANK_D->query_respect(me)+
                               "，你怕是找错人了吧？”\n" NOR,ob,me);
                tell_object(me, HIW "这不是你自己的门派，你不应该问这位师傅要任务呀。\n" NOR);
                return 1;
        }

        if( !query_temp("defend_quest/start", me) )
        {
                ob->command("sigh");
                message_vision(HIC "$N" HIC "疑惑地对$n" HIC "道：“你都不是在做这个任务，就想要奖励？”\n" NOR, ob, me);
                tell_object(me, HIW "你总得先要个任务吧。\n" NOR);
                return 1;
        }

        if( !query_temp("defend_quest/finish", me) )
        {
                ob->command("sigh");
                message_vision(HIC "$N" HIC "疑惑地对$n" HIC "道：“你的任务还没有完呢，现在就想要奖励？”\n" NOR, ob, me);
                tell_object(me, HIW "你等做完了再要奖励吧。\n" NOR);
                return 1;
        } else
        {
                if( !query_temp("defend_quest/killed", me) )
                {
                        ob->command("hmm");
                        message_vision(HIC "$N" HIC "点点头对$n" HIC "道：“好吧，这次任务你存功未立，就不给你奖励了。”\n" NOR, ob, me);
                        delete_temp("defend_quest", me);
                        return 1;
                } else
                {
                        killed=query_temp("defend_quest/killed", me);
                        ob->command("nod");

                        exp = killed * 40 + random(200);
                        exp = exp / 2 + random(exp / 2);
                        pot = exp / 3 + random(2);
                        gongxian = killed * 3;

                        message_vision(HIC "$N" HIC "点点头对$n" HIC "道：“好！这次任务你成功截杀了" +
                                       chinese_number(killed) + "个敌人，这里是给你的一点奖励。”\n" NOR, ob, me);
                        /*
                        tell_object(me, HIW "这次任务你得到了" + chinese_number(exp) + "点经验值和" +
                                       chinese_number(pot) + "点潜能值的奖励，你的门派贡献提高了。\n" NOR);
                        */
                        delete_temp("defend_quest", me);

                        QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "gongxian" : gongxian ]), 1);

                        return 1;
                }
        }
}

void die(object ob)
{
        int percent;
        object me;
        string *pills, pill;
        int amount = 300 + random(300);
        string *condition = ({
                "气喘吁吁，就要不支", "头重脚轻，马上就倒",
                "呕血成升，眼冒金星", "伤痕累累，无力招架",
        });

        if (objectp(me = ob->query_last_damage_from())
        &&  environment(ob) == environment(me)
         && query_temp("defend_quest/start", me )
         && !query_temp("defend_quest/finish", me )
         && !query_temp("defend_quest/waiting", me) )
        {
                switch (random(15))
                {
                        case 1: {
                                message_sort(HIR "眼见$N" HIR + condition[random(sizeof(condition))]
                                                +"，突然$N大喝一声，急退几步，\n“扑通”给$n跪了下来。"
                                                "\n" NOR, ob, me);
                                tell_object(me, HIW + ob->name()+"突然从怀里掏出一堆白花花的银子，小声"
                                                "对你道：“这位" + RANK_D->query_respect(me) + "，\n你"
                                                "就网开一面（nod）如何，这" + chinese_number(amount) +
                                                "两白银就归你了！”\n" NOR);
                                ob->clean_up_enemy();
                                ob->remove_all_enemy(0);
                                ob->clear_condition(0);
                                set("jing", 1, ob);
                                set("qi", 1, ob);
                                set_temp("defend_quest/waiting", amount, me);
                                return;
                        }
                        default: {
                                // 奖励
                                if( query("family/family_name", me) == query("is_attacking", ob) )
                                        addn_temp("defend_quest/killed", 1, me);

                                set_temp("die", 1, ob);

                                QUEST_D->bonus(me, ([ "exp" : 10 + random(30),
                                                      "pot" : 3 + random(20),
                                                      "score" : 3 + random(20) ]));
                                ob->die(me);
                        }
                }
                return;
        }
        if( objectp(me) && query("family/family_name", me) == query("is_attacking", ob) )
        {
                addn_temp("defend_quest/killed", 1, me);

                QUEST_D->bonus(me, ([ "exp" : 10 + random(30),
                                      "pot" : 3 + random(20),
                                      "score" : 3 + random(20) ]));
        }
        ob->die();
}

// 询问DEFENDER - 正在被攻打的门派
string ask_defender(object knower, object me)
{
        mapping my = query_entire_dbase();

        return CYN "这个" HIY + DEFEND_FAM + NOR CYN
               "听说名声倒是很大，不会这次就会给" HIY
               + DEFEND_FAM + NOR CYN "灭了吧。";
}

// 询问ENEMY - 攻打者的门派
string ask_enemy(object knower, object me)
{
        mapping my = query_entire_dbase();

        return CYN "这个" HIY + ENEMY_FAM + NOR CYN
               "的弟子一向凶霸霸的，一看就不是什么好东西。" NOR;
}

// 任务介绍
string query_introduce(object knower)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC))
        {
                remove_call_out("do_say");
                call_out("do_say", 1);
        }

        return CYN "据说那个" + HIY + ENEMY_FAM + NOR CYN "的弟子们正在攻打" +
               HIY + DEFEND_FAM + NOR CYN "呢，也不知道结下了什么梁子。" NOR;
}

void do_say(object knower)
{
        if (! objectp(knower) || ! living(knower))
                return 0;

        message_sort("$N嘟囔道：“我跟你都说了，这些门派呀，没一个好"
                       "东西，这不？打起来了吧？”\n", knower);
}

// 任务提示
string query_prompt()
{
        switch (random(3))
        {
        case 0:
                return CYN "倒是最近听有些客人说起" HIY + name() +
                       NOR CYN "来。";
        case 1:
                return "也没什么大事，只是听说过" HIY + name() +
                       NOR CYN "罢了。";
        default:
                return "前两天还听人家说过" HIY + name() +
                       NOR CYN "呢。";
        }
}

// 登记该任务的消息
void register_information()
{
        mapping my = query_entire_dbase();

        if (! clonep() || ! mapp(my))
                // 不是任务，所以不登记
                return;

        set_information(ENEMY_FAM, (: ask_enemy :));
        set_information(DEFEND_FAM,(: ask_defender :));
}

// 这个任务可以被某人知晓吗？
int can_know_by(object knower)
{
        return 1;
}

void check_all_place()
{
        int i, j;
        string *the_place;
        string *family;
        object env;

        family = keys(familys);
        for (i = 0;i < sizeof(family);i++)
        {
                the_place = familys[family[i]]["place"];
                for (j = 0;j<sizeof(the_place);j++)
                        if (!objectp(env = get_object(the_place[j])))
                                log_file("static/defend_quest",sprintf("门派任务错误记录：%s\n",the_place[j]));
        }
}
