// questd.c 处理任务的守护进程
// 包括师门任务函数载体和系统注册任务(SYSREG_QUEST)

// 更新的内容：
// mapping mlist           - 发放任务者列表
// int     remote_bonus()  - 远程奖励玩家
// mapping prepare_quest() - 准备远程任务
// int     start_quest()   - 正式开始远程任务

#include <ansi.h>
#include <quest.h>

// #pragma optimize
// #pragma save_binary

inherit F_DBASE;

// 定义提供给外部调用的接口函数
varargs public void bonus(object who, mapping b, int flag);
public void   delay_bonus(object who, mapping b);
public mixed  accept_ask(object me, object who, string topic);
public void   set_information(object qob, mixed key, mixed info);
public mixed  query_information(object qob, string key);
public void   remove_information(object qob, string key);
public void   remove_all_information(object qob);
public string generate_information(object knower, object who, string topic);
public void   start_all_quest();

// 发放任务者列表
mapping mlist = ([
        "丐帮"     : CLASS_D("gaibang")   + "/hong.c",
        "明教"     : CLASS_D("mingjiao")  + "/zhangwuji.c",
        "魔教"     : CLASS_D("mojiao")    + "/tieyan.c",
        "五毒教"   : CLASS_D("wudu")      + "/hetieshou.c",
        "全真教"   : CLASS_D("quanzhen")  + "/ma.c",
        "峨嵋派"   : CLASS_D("emei")      + "/miejue.c",
        "古墓派"   : CLASS_D("gumu")      + "/longnv.c",
        "华山派"   : CLASS_D("huashan")   + "/yue-buqun.c",
        "灵鹫宫"   : CLASS_D("lingjiu")   + "/xuzhu.c",
        "少林派"   : CLASS_D("shaolin")   + "/xuan-ci.c",
        "神龙教"   : CLASS_D("shenlong")  + "/hong.c",
        "桃花岛"   : CLASS_D("taohua")    + "/huang.c",
        "武当派"   : CLASS_D("wudang")    + "/zhang.c",
        "逍遥派"   : CLASS_D("xiaoyao")   + "/suxingh.c",
        "星宿派"   : CLASS_D("xingxiu")   + "/ding.c",
        "凌霄城"   : CLASS_D("lingxiao")  + "/baizizai.c",
        "铁掌帮"   : CLASS_D("tiezhang")  + "/qiuqianren.c",
        "昆仑派"   : CLASS_D("kunlun")    + "/hetaichong.c",
        "青城派"   : CLASS_D("qingcheng") + "/yu.c",
        "嵩山派"   : CLASS_D("songshan")  + "/zuo.c",
        "泰山派"   : CLASS_D("taishan")   + "/tianmen.c",
        "衡山派"   : CLASS_D("henshan")   + "/mo.c",
        "恒山派"   : CLASS_D("hengshan")  + "/xian.c",
        "血刀门"   : CLASS_D("xuedao")    + "/laozu.c",
        "雪山寺"   : CLASS_D("xueshan")   + "/jiumozhi.c",
        "天地会"   : CLASS_D("yunlong")   + "/chen.c",
        "红花会"   : CLASS_D("honghua")   + "/chen-jialuo.c",
        "段氏皇族" : CLASS_D("duan")      + "/duanzc.c",
        "慕容世家" : CLASS_D("murong")    + "/murongbo.c",
        "欧阳世家" : CLASS_D("ouyang")    + "/ouyangfeng.c",
        "关外胡家" : CLASS_D("hu")        + "/hufei.c",
        "华山剑宗" : CLASS_D("huashan")   + "/feng-buping.c",
        "唐门世家" : CLASS_D("tangmen")   + "/tangltt.c",
        "日月神教" : CLASS_D("riyue")     + "/dongfang.c",
]);

void create()
{
        seteuid(getuid());
        set("channel_id", "任务精灵");
        set_heart_beat(900);
        call_out("collect_all_quest_information", 1);
}

#define ONE_DAY                 (86400 / 365)
#define MAX_QUEST_LEVEL         3

private void skill_bonus(object me, object who)
{
        int gongxian;
        string *sk_list = ({
                "wuming-jianfa",
                "wuming-jianfa",
                "wuming-jianfa",
                "wuming-jianfa",
                "wuming-jianfa",
                "liumang-shenquan",
                "liumang-shenquan",
                "liumang-shenquan",
/*
                "qishang-quan",
                "qishang-quan",
                "qishang-quan",
                "qishang-quan",
                "zhuihun-jian",
                "zhuihun-jian",
                "zhuihun-jian",
                "zhuihun-jian",
                "baihua-quan",
                "baihua-quan",
                "baihua-quan",
                "baihua-quan",
                "sougu-yingzhua",
                "sougu-yingzhua",
                "sougu-yingzhua",
                "zhuangzi-wu",
                "shenxing-baibian",
                "hanbing-mianzhang",
                "hanbing-mianzhang",
                "hanbing-mianzhang",
                "xuanming-zhang",
                "xuanming-zhang",
                "xuanming-zhang",
                "shenzhaojing",
                "shenzhaojing",
                "shenzhaojing",
                "mingyu-gong",
                "mingyu-gong",
                "mingyu-gong",
                "shexing-lifan",
                "shexing-lifan",
                "shexing-lifan",
                "baihua-cuoquan",
                "baihua-cuoquan",
*/
        });
        string sk;

        sk = sk_list[random(sizeof(sk_list))];
        if (who->query_skill(sk, 1) > 0)
                return;

        gongxian = 100000;
        if( query("family/gongji", who)<gongxian
        ||  !SKILL_D(sk)->valid_learn(who))
        {
                message_vision("$n赞许的对$N笑了笑，道：“你真是我们" +
                               query("family/family_name", me)+
                               "的佼佼者，我最近研究过" +
                               HIY + to_chinese(sk) + NOR
                               "，\n颇有心得，只可惜你现在尚不足以"
                               "领悟其中奥妙，罢了，罢了。”\n",
                               who, me);
                return;
        }

        message_vision("$n赞许的对$N笑了笑，道：“你真是我们" +
                       query("family/family_name", me)+
                       "的佼佼者，正好我最近研究过" +
                       HIY + to_chinese(sk) + NOR
                       "，\n颇有心得，如果你想学，就传授一些与你吧！”\n",
                       who, me);

        tell_object(who, HIW "\n学习" + to_chinese(sk) + HIW "需要消耗"
                         "你" + chinese_number(gongxian) + "点门派"
                         "贡献，你是否愿意(" HIY "answer Y|N" HIW
                         ")接受？\n\n" NOR);

        // 记录可以领取任务奖励的NPC
        set_temp("quest_gift/npc",query("id",  me), who);

        // 记录任务奖励武功
        set_temp("quest_gift/skill", sk, who);

        // 记录领取该武功所需的门牌贡献
        set_temp("quest_gift/gongxian", gongxian, who);

        return;
}

void special_bonus(object me, object who, mixed arg)
{
        int gongxian;
        // 随机奖励
        string *ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/xuantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
                "/clone/gift/jinkuai",
                "/clone/fam/pill/neili2",
                "/clone/fam/item/bixue",
                "/clone/quarry/item/zhenzhu",
                "/clone/tessera/cruby",
                "/clone/tessera/ctopaz",
                "/clone/tessera/csapphire",
                "/clone/tessera/cemerald",
                "/clone/tessera/cdiamond",
                "/clone/goods/hanxing-yuntie",
                "/clone/tessera/rune11",
                "/clone/tessera/rune12",
                "/clone/tessera/rune13",
                "/clone/tessera/rune14",
                "/clone/tessera/rune15",
                "/clone/tessera/qinglong",
                "/clone/tessera/baihu",
                "/clone/tessera/zhuque",
                "/clone/tessera/xuanwu",
                "/clone/tessera/qilin",
                "/clone/tessera/mcrystal",
        });

        string un, gift;
        object ob;

        /*
        message_vision("$n对$N微微一笑，道：干得不赖，辛苦"
                       "了，正好我这里有点东西，你就拿去吧。\n",
                       who, me);
        */

        if (stringp(arg))
                gift = arg;
        else

        if( query("quest_count", who) == 1000 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 500;
        } else

        if( query("quest_count", who) == 900 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 300;
        } else

        if( query("quest_count", who) == 800 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 400;
        } else

        if( query("quest_count", who) == 700 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 400;
        } else

        if( query("quest_count", who) == 600 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 500;
        } else

        if( query("quest_count", who) == 500 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 300;
        } else

        if( query("quest_count", who) == 400 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 300;
        } else

        if( query("quest_count", who) == 300 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 200;
        } else

        if( query("quest_count", who) == 200 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 150;
        } else

        if( query("quest_count", who) == 100 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 80;
        } else

        if( query("quest_count", who) == 50 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 30;
        } else

        if( query("quest_count", who) == 30 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 10;
        } else
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 1;
        }

        ob = new(gift);
        if( query("base_unit", ob) )
                un=query("base_unit", ob);
        else
                un=query("unit", ob);

        if( query("family/gongji", who) >= gongxian )
        {
                message_vision(CYN "$n" CYN "对$N" CYN "微笑道：我这里有一"
                               + un + ob->name() + CYN "，如果你用得着就拿"
                               "去吧。\n" NOR, who, me);

                tell_object(who, HIW "\n获得" + ob->name() + HIW "需要消耗"
                                 "你" + chinese_number(gongxian) + "点门派"
                                 "贡献，你是否愿意(" HIY "answer Y|N" HIW
                                 ")接受？\n\n" NOR);

                // 记录可以领取任务奖励的NPC
                set_temp("quest_gift/npc",query("id",  me), who);

                // 记录任务奖励物品的路径
                set_temp("quest_gift/obj", gift, who);

                // 记录领取该物品所需的门牌贡献
                set_temp("quest_gift/gongxian", gongxian, who);
        } else
                message_vision(CYN "$n" CYN "对$N" CYN "道：正好我这"
                               "里有…嗯…还是算了，相信你也用不到。"
                               "\n" NOR, who, me);
        destruct(ob);

        return ;
}

void money_bonus(object me, object who, mixed arg)
{
        string *ob_list = ({
                "/clone/gift/jinkuai",
                "/clone/gift/jintiao",
                "/clone/gift/xiaoyuanbao",
                "/clone/gift/dayuanbao",
                "/clone/gift/jinding",
        });
        object ob;

        /*
        message_vision("$n对$N微微一笑，道：干得不赖，辛苦"
                       "了，行走江湖，总有各类开支应酬，这里有些金子，你就拿去吧。\n",
                       who, me);
        */

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);

        ob->move(who,1);

        tell_object(who, HIM "你获得了一" + query("unit", ob) + ob->name() +
                        HIM "。\n" NOR);
}

varargs public void bonus(object who, mapping b, int flag)
{
        int exp;                // 奖励的经验
        mixed pot;              // 奖励的潜能
        mixed mar;              // 奖励的实战体会
        int shen;               // 奖励的神
        int score;              // 奖励的江湖阅历
        int weiwang;            // 奖励的江湖威望
        int gongxian;           // 奖励的门派贡献
        mixed pot_limit;        // 潜能的界限
        mixed mar_limit;        // 实战体会的界限
        int percent;            // 奖励的有效百分比
        string msg;             // 奖励的描述信息
        int quest_times;

        quest_times = "/adm/daemons/actiond"->query_action("quest_reward");
        // 获得奖励的百分比
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;

        if( query("special_skill/intellect", who) && random(2) )
        {
                exp += exp / 5;
                pot += pot / 5;
        }

        // 八面玲珑增和门派功绩
        if( query("special_skill/cunning", who) && random(2) )
                gongxian += gongxian;

        if (quest_times)
        {
                exp = exp*quest_times;
                pot = pot*quest_times;
                mar = mar*quest_times;
        }

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (! flag)
        {
                pot_limit = who->query_potential_limit() - query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit = who->query_experience_limit() - query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if (who->query_potential_limit() < query("potential", who))
                        pot = 1 + random(2);

                if (who->query_experience_limit() < query("experience", who))
                        mar = 1;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIC + msg + HIG "，你获得了";
        else
                msg = HIC "通过这次锻炼，你获得了";

        if (exp > 0) msg += chinese_number(exp) + "点经验、";
        if (pot > 0) msg += chinese_number(pot) + "点潜能、";
        if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
        if (shen > 0) msg += chinese_number(shen) + "点正神、";
        if (shen < 0) msg += chinese_number(-shen) + "点负神、";
        if (score > 0) msg += chinese_number(score) + "点江湖阅历、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "点威望、";
        if (gongxian > 0) msg += chinese_number(gongxian) + "点门派功绩、";

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        addn("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
}

// 延迟奖励：有时候给出奖励的时候应该是在某些事件发生以后，
// 但是在该事件发生时给与奖励更易于书写程序，所以奖励生成的
// 地方在事件正在发生的时候，但是要让玩家看起来是在事件发生
// 以后。比如杀人，人死亡的时候给与奖励是容易做的，但是我希
// 望玩家在看到NPC 的死亡信息以后才看到奖励的信息，这时候就
// 用delay_bonus了。
public void delay_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "bonus", who, b :), 1);
}

public mixed accept_ask(object me, object who, string topic)
{
        string my_fam;

        my_fam=query("family/family_name", me);

        if (topic == "历练" || topic == "历炼" ||
            topic == "锻炼")
        {
                if( my_fam != query("family/family_name", who) )
                        return "你是谁？找我有什么事情么？";

                if( query("out_family", who) )
                        return "去吧！" + who->name(1) + "，好自为之！";

                if( query("combat_exp", who)<50000 )
                {
                        message_sort(CYN "$N" CYN "叹了一口气，看了看$n"
                                     CYN "道：“你的武功基础还不太好，还是再"
                                     "好好锻炼吧！”\n", me, who);
                        return 1;
                }

                if( query("score", who)<100 )
                {
                        message_sort(CYN "$N" CYN "摆摆手道：“你的江湖"
                                     "阅历太少，现在不可外出独自行走江湖。”\n",
                                     me, who);
                        return 1;
                }

                set("out_family", 1, who);
                if (me->is_good())
                {
                        message_sort(HIY "$N" HIY "对$n" HIY "欣慰的点了"
                                     "点头，道：“看来我们" + my_fam +
                                     "又出了一位人才啊！你记住了！我辈武"
                                     "人，切忌不可好勇争斗，要多做行侠仗"
                                     "义之事！”\n" NOR, me, who);
                } else
                if (me->is_bad())
                {
                        message_sort(HIR "$N" HIR "对$n" HIR "哈哈大笑道"
                                     "：“好！好！你可以出去走走看看了，"
                                     "对那些自认所谓大侠之辈可不要手软，"
                                     "去吧！”\n" NOR, me, who);
                } else
                {
                        message_sort(HIY "$N" HIY "对$n" HIY "叮嘱道：“"
                                     "以后你行走江湖常常是孤身一人，记得"
                                     "要敬重前辈，不可狂妄自大，切记了，"
                                     "去吧！”\n" NOR, me, who);
                }

                message_sort("$N翻出一本小册子来，对$n道：“今后你行走江"
                             "湖，许多山川地理，世间风情你都可以记录在这"
                             "本地图册上，以咨参考，对你多少也会有些帮助"
                             "。”\n", me, who);

                tell_object(me, HIY"你获得了师傅赠给你的地图册，请参见帮"
                            "助(HELP QUEST)以\n获得更详细的信息。\n" NOR);

                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说" + who->name(1) + "已经开始闯荡江湖。");
                return 1;
        }
}

// 领取任务
// 如果目前正在协助别人，不能领取任务
public int ask_quest(object me, object who)
{
        string fam;             // ME的门派信息
        object ob;              // 任务重的某些物件或人物
        mapping q;              // WHO的人物
        object aob;             // WHO目前正在协助的对象
        mixed exp;              // WHO的经验
        int t;                  // 用来计算时间的变量
        int level;              // QUEST的等级
        string place;

        message_vision("$n向$N打听有关任务的情况。\n", me, who);

        fam=query("family/family_name", me);
        if( query("family/family_name", who) != fam )
        {
                message_vision("$N瞪大眼睛看着$n，道：“你又不是我们" + fam +
                               "的，来捣什么乱？”\n", me, who);
                return 1;
        }

        if( query_temp("quest_gift", who) )
        {
                if( query_temp("quest_gift/skill", who) )
                        message_vision(CYN "$N" CYN "对$n" CYN "皱眉道：我问你"
                                       "话呢，那武功你到底学(" HIY "answer Y|N"
                                        NOR + CYN ")还是不学？\n" NOR, me, who);
                else
                        message_vision(CYN "$N" CYN "对$n" CYN "皱眉道：我问你"
                                       "话呢，那东西你到底要(" HIY "answer Y|N"
                                        NOR + CYN ")还是不要？\n" NOR, me, who);
                return 1;
        }

        q=query("quest", who);
        if (mapp(q))
        {
                if (q["freequest"] > 0)
                {
                        message_vision(CYN "$N" CYN "对$n" CYN "说道：我这里暂"
                                       "时也没什么事情，你还是自己锻炼一段时间"
                                       "吧。\n" NOR, me, who);
                        tell_object(who, HIY "你突然想到：现在江湖正值动乱，何"
                                         "不四处走访，也许可提高自己的经验阅历"
                                         "。\n" NOR);
                        return 1;
                }

                if( q["master_id"] && q["master_id"] != query("id", me) )
                {
                        message_vision(CYN "$N" CYN "看了看$n" CYN "，"
                                       "哼了一声，没有理会$n" CYN "。\n"
                                       NOR, me, who);
                        return 1;
                }

                switch (q["type"])
                {
                case "kill":
                        message_vision(CYN "$N" CYN "一脸怒容对$n" CYN "道：我不是让"
                                       "你" + CHINESE_D->chinese_monthday(q["limit"]) +
                                       "之前杀了" NOR + HIR + q["name"] + "(" + q["id"] +
                                       ")" + NOR + CYN "的吗？现在是" +
                                       CHINESE_D->chinese_monthday(time()) +
                                       "，他的人头呢？\n" NOR, me, who);
                        return 1;
                        break;

                case "letter":
                        message_vision(CYN "$N" CYN "一脸怒容对$n" CYN "道：我不是让"
                                       "你" + CHINESE_D->chinese_monthday(q["limit"]) +
                                       "之前把信送到" NOR + HIC + q["name"] + "(" + q["id"] +
                                       ")" + NOR + CYN "那里的吗？现在是" +
                                       CHINESE_D->chinese_monthday(time()) +
                                       "，他的回执呢？\n" NOR, me, who);
                        return 1;
                        break;

                }
                        //map_delete("finished", p);
                        delete("quest", who);
                        // return 1;
        }

        if (query("eff_qi", me) * 2 < query("max_qi", me) ||
            query("qi", me) * 2 < query("max_qi", me))
        {
                message_vision(HIC "$N" HIC "捂着胸口，一副非常痛苦的样子，对你的"
                               "话显然没有听进去。\n" NOR, me);
                return 1;
        }

        exp=query("combat_exp", who);
        if (exp < 30000)
        {
                message_vision(CYN "$N" CYN "叹了一口气，对$n" CYN "道：就你那点水平，"
                               "我实在没法给你派任务。\n" NOR, me, who);
                return 1;
        }

        if( objectp(aob=query_temp("quest/assist", who)) )
        {
                message_vision(CYN "$N" CYN "看了看$n" CYN "，道：我听说你不是帮" NOR +
                               HIY + aob->name(1) + NOR + CYN "去了么？先办妥了"
                               "再说吧！\n" NOR, me, who);
                return 1;
        }

        if (exp < 100000)
        {
                object letter;

                if( query("score", who)<20 )
                {
                        message_vision(CYN "$N" CYN "摇摇头，对$n" CYN "道：可惜你"
                                       "的江湖阅历太差，不然我还可以让你帮我送封信"
                                       "。\n" NOR, me, who);
                        return 1;
                }

                ob = new(CLASS_D("generate") + "/receiver.c");
                NPC_D->place_npc(ob, ({ "大理一带", "关外", "星宿海", "天山",
                                        "终南山", "西域" }));
                NPC_D->set_from_me(ob, me, 100);

                NPC_D->random_move(ob);
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);

                place=query("place", ob);

                letter = new("/clone/misc/letter");
                letter->set("long","这是一封"+me->name()+"写给"+ob->name()+
                                    "的亲笔信函。\n");
                set("send_from",query("id",  me), letter);
                set("send_to",query("id",  ob), letter);
                set("send_from_name", me->name(), letter);
                letter->move(me);

                message_vision(CYN "$N" CYN "对$n" CYN "道：这封信你帮我交到" NOR +
                               HIC + ob->name() + "(" + query("id", ob) + ")" + NOR +
                               CYN "手中，他现在应该在" + place + "，然后把回执带回来给我！\n" NOR,
                               me, who);

                me->force_me("give letter to " + query("id", who));
                set("quest/info",query("id",  letter), who);
                set("quest/type", "letter", who);
        } else
        if (exp < 200000)
        {
                message_vision("$N盯着$n看了半天，道：“让你送信委屈了你，"
                               "叫你闯荡江湖我又不放心，你还是好好练练功夫"
                               "吧！”\n", me, who);
                return 1;
        } else
        {
                if( !query("out_family", who) )
                {
                        message_sort(CYN "$N" CYN "摆摆手，对$n" CYN "道：我现在"
                                      "这里倒是有一些事情，不过待你外出历练段时间"
                                      "后再说吧！\n" NOR, me, who);
                        return 1;
                }

                if( query("score", who)<2000 )
                {
                        message_sort(CYN "$N" CYN "叹了一口气，对$n" CYN "道：“你还"
                                     "是在江湖上多历练历练，增进一些阅历再说吧！现在"
                                     "我对你还不够放心！”\n" NOR, me, who);
                        return 1;
                }

                if( query("weiwang", who)<20 )
                {
                        message_sort(CYN "$N" CYN "看了看$n" CYN "，叹气道：你在"
                                     "江湖上一点名头都没有，我没法放心把任务交给"
                                     "你。\n" NOR, me, who);
                        tell_object(who, HIY "看来还是的加强自己的江湖威望才行。\n" NOR);
                        return 1;
                }

                if (who->is_bad() && me->is_good())
                {
                        message_sort(CYN "$N" CYN "大怒道：岂有此理！你居然已经误"
                                     "入歧途，还敢来见我！\n" NOR, me, who);
                        return 1;
                }

                if (who->is_good() && me->is_bad())
                {
                        message_sort(CYN "$N" CYN "大怒道：岂有此理！才几天不见，"
                                     "你居然也学起假仁假义来了，快给我滚！\n"
                                     NOR, me, who);
                        return 1;
                }

                level=query_temp("quest/next_level", who);
                if (level < 0 || level > MAX_QUEST_LEVEL)
                        level = 0;

                ob = new(CLASS_D("generate") + "/killed.c");
                NPC_D->place_npc(ob,query("combat_exp", who)<500000?({"大理一带","终南山","关外","西域"}):
                                     query("combat_exp", who)<800000?({"大理一带","终南山","西域"}):0);
                NPC_D->set_from_me(ob, who, 100);

                addn_temp("apply/attack",ob->query_skill("force")*
                                            (level - 1) / 15, ob);
                addn_temp("apply/dodge",ob->query_skill("force")*
                                            (level - 1) / 15, ob);
                addn_temp("apply/parry",ob->query_skill("force")*
                                            (level - 1) / 15, ob);
                addn_temp("apply/damage", 5+level*7, ob);
                addn_temp("apply/unarmed_damage", 5+level*7, ob);
                addn_temp("apply/armor", 10+level*15, ob);
                set_temp("quester",query("id",  who), ob);

                NPC_D->random_move(ob);
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);

                place=query("place", ob);

                message("vision", WHT + me->name() + WHT "小声的对" + who->name() +
                        WHT "吩咐着什么，" + who->name() +
                        WHT "一边听，一边不住的点头。\n" NOR,
                        environment(who), ({ who }));

                if (me->is_good())
                {
                        set("shen", -20000, ob);
                        if( query("family/family_name", me) == "少林派" )
                                tell_object(who, CYN + me->name() + CYN "对你道：虽"
                                                 "然我们出家人以慈悲为怀，但是对于大"
                                                 "凶大恶之徒也不能放过。\n最近" NOR +
                                                 HIR + ob->name() + "(" + query("id", ob) +
                                                 ")" + NOR + CYN "在" + place + "作恶多端，"
                                                 "你去把他除了，提头来见。\n" NOR);
                        else
                                tell_object(who, CYN + me->name() + CYN"对你道：" NOR
                                                 + HIR + ob->name() + "(" + query("id", ob) +
                                                 ")" + NOR + CYN "这个"
                                                 "败类打家劫舍，无恶不作，听说他最近"
                                                 "在" + place + "，你去除掉他，提头来"
                                                 "见我！\n" NOR);
                } else
                if (me->is_bad())
                {
                        set("shen", 20000, ob);
                        tell_object(who, CYN + me->name() + CYN "对你道：" NOR + HIR
                                         + ob->name() + "(" + query("id", ob) + ")" +
                                         NOR + CYN "这个所谓大侠屡次"
                                         "和我派作对，听说他最近在" + place + "，你"
                                         "去宰了他，提头来见！\n" NOR);
                } else
                {
                        set("shen_type", 0, ob);
                        set("shen", 0, ob);
                        tell_object(who, CYN + me->name() + CYN "对你说道：我早就看"
                                         NOR + HIR + ob->name() + "(" + query("id", ob) +
                                         ")" + NOR + CYN "不顺眼"
                                         "，听说他最近在" + place + "，你去做了他，"
                                         "带他的人头来交差！\n" NOR);
                }
                set("quest/type", "kill", who);
                switch (level)
                {
                case 0:
                        message_vision(CYN "$N" CYN "顿了顿，又对$n" CYN "道：这个"
                                       "事情容易办得很，你要是还办不成那可不象话。"
                                       "\n" NOR, me, who);
                        break;
                case 1:
                        break;
                case 2:
                        message_vision(CYN "$N" CYN "看了看$n" CYN "又道：这个事情"
                                       "很是有些难办，你要是不行我就另找人吧。\n"
                                       NOR, me, who);
                        break;
                case 3:
                        message_vision(CYN "$N" CYN "叹了口气，郑重的对$n" CYN "道"
                                       "：这次任务凶险得紧，你不要勉强自己，不行就"
                                       "算了。\n" NOR, me, who);
                        break;
                }

                if (level > 0 && random(10) == 1)
                {
                        string flee_msg;

                        // 随机重新放置NPC的位置
                        message_sort(CYN "$N" CYN "话音刚落，突然一人"
                                     "急急忙忙的赶了过来，喊道：“不"
                                     "好了，不好了，" HIR + ob->name() +
                                     NOR CYN "在" + place +
                                     "失踪了！现在不知道去了哪里！”"
                                     "$N" CYN "呆了半晌，这才对$n" CYN
                                     "道：“这事麻烦了，看来只有靠你自"
                                     "己努力了！”\n" NOR, me, who);
                        switch (random(3))
                        {
                        case 0:
                                flee_msg = "听说$N听到了江湖上追杀他的风"
                                           "声，已经躲到PLACE去了。";
                                break;
                        case 1:
                                flee_msg = "有人说$N就在咱们这地界呢，"
                                           "但是也有人说他在PLACE，不知道是真是假。";
                                break;
                        default:
                                flee_msg = "不知道...不知道...哦？好像"
                                           "听人说过是在PLACE。";
                                break;
                        }
                        ob->random_place(flee_msg);
                }
        }

        set("quest/family", fam, who);
        set("quest/master_name", me->name(), who);
        set("quest/master_id",query("id",  me), who);
        set("quest/name", ob->name(), who);
        set("quest/id",query("id",  ob), who);
        set("quest/level", level, who);
        set("quest/place", place, who);
        t = time();
        set("quest/time", t, who);
        t = time() / ONE_DAY;
        if( query("place", ob) == "西域" )
                t += 8;
        else
                t += 4;
        t = t * ONE_DAY - 1;
        set("quest/limit", t, who);
        message("vision", WHT + me->name() + WHT "在你耳边悄声说道：你务必要在"
                          NOR + HIY + CHINESE_D->chinese_monthday(t) + NOR + WHT
                         "之前完成！\n" NOR, who);
        who->start_busy(1);
        return 1;
}

public int ask_defend(object me, object who)
{
        function f;
        int r;

        f=query_temp("override/ask_defend", me);
        if (functionp(f))
                r = (*f)(me, who);
        else
                r = 0;
        return r;
}

public int ask_finish(object me, object who)
{
        function f;
        int r;

        f=query_temp("override/ask_finish", me);
        if (functionp(f))
                r = (*f)(me, who);
        else
                r = 0;
        return r;
}

int accept_object(object me, object who, object ob)
{
        mapping q;              // WHO的任务
        string msg;             // 掌门说的消息
        object dob;             // 打晕敌人的人
        int bonus;              // 奖励(正整数，1是正常)
        int t;                  // 用来计算时间的变量
        int exp;                // 获得的经验
        int pot;                // 获得的潜能
        int mar;                // 获得的实战体会
        int weiwang;            // 获得的威望
        int score;              // 获得的江湖阅历
        int gongxian;           // 获得的门派贡献
        int lvl;                // 人物的等级
        int quest_level;        // QUEST的等级
        int quest_count;        // 连续QUEST的数目
        int total_count;        // ......
        int timeover;           // 标志：超时了？
        int added;              // 做任务的时候额外出现的敌人或敌人逃走
        mixed special = 0;      // 是否有特殊奖励

        if( query("family/family_name", me) != query("family/family_name", who) )
                return 0;

        q=query("quest", who);

        if( query("money_id", ob) )
        {
               if( !mapp(q) || q["master_id"] != query("id", me) )
               {
                       tell_object(who,me->name() + "奇怪的看着你说：我没给你什么任务啊？\n");
                       return 0;
               }

               if (ob->value() < 1000000)
               {
                       tell_object(who,me->name() + "不屑一顾的说：这么一点点钱，能用来干什么？你自己留着买鸡腿用吧！\n");
                       tell_object(who,me->name() + "顿了一下又说：如果你给我100两黄金，或许我可以考虑消除了你的任务。\n");
                       return 0;
               }

               delete("quest", who);
               tell_object(who,me->name() + "微微笑了笑，点头道：那你这个任务不做就算了吧。\n");
               destruct(ob);
               return 1;
        }

        if (ob->is_letter())
        {
                if( query("send_from", ob) != query("id", me) )
                {
                        message_vision(CYN "$N" CYN "道：你要干什么？\n" NOR, me);
                        return -1;
                }

                if (! q || q["type"] != "letter" || query("send_to", ob) != q["id"])
                {
                        message_vision(CYN "$N" CYN "深深的叹了一口气，没说什么？\n" NOR, me);
                        destruct(ob);
                        return 1;
                }

                message_vision(CYN "$N" CYN "瞪着$n" CYN "道：干什么？交给你"
                               "的活你不打算干了？\n" NOR, me, who);
                return -1;
        }

        if (ob->is_receipt())
        {
                if( query("reply_to", ob) != query("id", me) )
                {
                        message_vision("$N皱眉道：“给我这玩艺干什么？”\n", me);
                        return 0;
                }

                if( !q || q["type"] != "letter" || q["id"] != query("reply_by", ob) )
                {
                        message_vision("$N点点头道：“多谢了。”\n", me);
                        destruct(ob);
                        return 1;
                }

                message_vision(CYN "$N" CYN "接过" + ob->name() + NOR + CYN"，仔细看了"
                              "看，满意的说：很好。\n" NOR, me, who);

                msg = "";
                t = time();
                if (t > q["limit"])
                {
                        msg += CYN + me->name() + CYN "叹了口气，又道：可惜，不是让你" +
                               CHINESE_D->chinese_monthday(t) + "前做完吗？算"
                               "了，将功补过，你先退下吧。\n" NOR;
                        timeover = 1;
                } else
                {
                        if (t - q["time"] < ONE_DAY)
                        {
                                msg += CYN + me->name() + CYN "点点头道：你很不错，这么"
                                       "快就完成了，好好干！\n" NOR;
                        } else
                                msg += CYN + me->name() + CYN "点点头道：这次不错，辛苦"
                                       "了。\n" NOR;
                        timeover = 0;
                }
                bonus=(query("receive_from", ob) == query("id", who));
                exp = 15 + random(10);
                pot = 5 + random(8);
                mar = 1;
                score = 6 + random(5);
                weiwang = 1;
                gongxian = 1;
                destruct(ob);
        } else
        {
                if (! mapp(q) || ! ob->is_corpse() && ! ob->is_head())
                        return 0;

                if (! stringp(query("owner_id", ob)))
                {
                        message_vision(CYN "$N" CYN "捂着鼻子看了看" + ob->name()
                                       + NOR + CYN "，道：什么臭烘烘的？快给我"
                                       "拿走。\n" NOR, me);
                        return 0;
                }

                if( query("owner_id", ob) != q["id"] )
                        return 0;

                msg = CYN + me->name() + CYN "接过" + ob->name() + NOR + CYN "，呵呵大笑"
                      "，对你道：";

                if (me->is_good())
                        msg += CYN "又除了一害，很好！";
                else
                if (me->is_bad())
                        msg += CYN "好极了！什么大侠，不堪一击！";
                else
                        msg += CYN "干得好，漂亮！";

                msg += "\n" NOR;
                t = time();
                if( query_temp("quest/escape_times", who) )
                {
                        msg += CYN + me->name() + CYN "赞许道：这次没想到敌人这么强悍，实"
                               "在未曾料到，辛苦，辛苦！\n" NOR;
                        timeover = 0;
                } else
                if (t > q["limit"])
                {
                        msg += CYN + me->name() + CYN "摇摇头，又道：可惜，不是让你" +
                               CHINESE_D->chinese_monthday(t) + "前做完吗？算"
                               "了，将功补过，你先退下吧。\n" NOR;
                        timeover = 1;
                } else
                {
                        if (t - q["time"] < ONE_DAY)
                        {
                                msg += CYN + me->name() + CYN "点点头道：干得不错，这么"
                                       "快就完成了，好好干！\n" NOR ;
                        } else
                                msg += CYN + me->name() + CYN "点点头道：这次不错，辛苦"
                                       "了。\n" NOR;
                        timeover = 0;
                }

                // bonus为1表示正常奖励，为2表示扣除一半。
                bonus=(query("killed_by", ob) == query("id", who)) /*&&
                        (query("defeated_by", ob) == who ||
                         !query("defeated_by", ob) &&
                           query("defeated_by_who", ob) == who->name(1))*/;

                if( query("assist", ob) == who )
                {
                        dob=query("defeated_by", ob);
                        msg += CYN + me->name() + CYN "欣慰的对你道：这次你能够"
                               "得到" + (dob ? dob->name(1) : "同门师兄弟") +
                               NOR + CYN "的帮忙，也属不易！以后彼此要多加照"
                               "应！\n" NOR;
                        bonus = 2;
                } else
                if (bonus)
                        bonus = 1;

                destruct(ob);
                lvl = NPC_D->check_level(who);
                exp = 10 + random(5) + lvl;
                pot = 5 + random(3) + lvl;
                mar = 1 + random(2);
                weiwang = 2 + random(3) + lvl / 2;
                score = 2 + random(3) + lvl / 2;
                gongxian = 2;
                quest_count=query("quest_count", who)+1;

                // add temped for keep compactible with old version
                if( query_temp("quest/total_count", who) )
                {
                        quest_count=query_temp("quest/total_count", who)+1;
                        delete_temp("quest/total_count", who);
                }

                // 根据任务完成的次数修正奖励
                if (quest_count >= 1000)
                {
                        exp += 80 + random(50);
                        pot += 45 + random(40);
                        mar = 50 + random(20);
                        weiwang += 8 + random(20);
                        score += 4 + random(15);
                        gongxian += 4 + random(15);
                } else
                if (quest_count >= 500)
                {
                        // 连续完成了超过500次的任务
                        exp += 80 + random(quest_count / 20 + 1);
                        pot += 45 + random(quest_count / 25 + 1);
                        mar = 50 + random(20);
                        weiwang += 8 + random(20);
                        score += 4 + random(15);
                        gongxian += 4 + random(15);
                } else
                if (quest_count >= 200)
                {
                        // 连续完成了超过200次的任务
                        exp += 70 + random(quest_count / 20 + 1);
                        pot += 40 + random(quest_count / 25 + 1);
                        mar = 20 + random(10);
                        weiwang += 5 + random(15);
                        score += 3 + random(10);
                } else
                if (quest_count >= 100)
                {
                        // 连续完成了超过100次的任务
                        exp += 50 + random(quest_count / 20 + 1);
                        pot += 30 + random(quest_count / 25 + 1);
                        weiwang += 3 + random(10);
                        score += 2 + random(10);
                } else
                if (quest_count >= 10)
                {
                        // 连续完成了超过10次的任务
                        exp += 45 + random(quest_count / 20 + 1);
                        pot += 25 + random(quest_count / 25 + 1);
                        weiwang += 1 + random(5);
                        score += 1 + random(5);
                }

                switch (quest_level = q["level"])
                {
                case 0:
                        exp = exp / 2 + 1;
                        pot = pot / 2 + 1;
                        gongxian = gongxian / 2 + 1;
                        weiwang = weiwang / 3 + 1;
                        score = score / 4 + 1;
                        msg += CYN + me->name() + CYN "看着你接着说道：还行吧，下"
                               "次我给你个难点的任务。\n" NOR;
                        break;
                case 1:
                        msg += CYN + me->name() + CYN "对你又道：不错，看来我可以"
                               "托付些重任给你了。\n" NOR;
                        break;
                case 2:
                        exp += exp / 4;
                        pot += pot / 4;
                        mar += mar / 4;
                        weiwang += weiwang / 4;
                        score += score / 4;
                        msg += CYN + me->name() + CYN "对你笑道：真是不错，不愧是"
                               "我们"+query("family/family_name", who)+"的"
                               "矫矫者。\n" NOR;
                        break;
                case 3:
                        exp += exp / 2;
                        pot += pot / 2;
                        mar += mar / 2;
                        gongxian += gongxian / 2;
                        weiwang += weiwang / 2;
                        score += score / 2;
                        msg += CYN + me->name() + CYN "赞许道：非常不错，这次可给我们" +
                               query("family/family_name", who)+"争脸了。\n"
                               NOR;
                        break;
                }
                total_count = quest_count % 1000;
                if (total_count == 100)
                {
                        msg += CYN + me->name() + CYN "哈哈大笑两声道：“真有你的，连着" + chinese_number(quest_count) +
                               "次任务都完成的漂漂亮亮，很好，很好。”\n" NOR;
                        special = 1;
                } else
                if (total_count == 200)
                {

                        msg += CYN + me->name() + CYN "大喜道：“不错不错，真实不错，连着" + chinese_number(quest_count) +
                               "次任务干得很好。”\n NOR";
                        special = "/clone/gift/puti-zi";
                } else
                if (total_count == 300)
                {
                        msg += CYN + me->name() + CYN "叹道：“真是长江后浪推前浪，想不到你接连着" + chinese_number(quest_count) +
                               "次任务都无一疏漏，不易，不易！”\n" NOR;
                        special = "/clone/gift/tianxiang";
                } else
                if (total_count == 500)
                {
                        msg += CYN + me->name() + CYN "深深叹了口气，道：“想不到你连着" + chinese_number(quest_count) +
                               "次任务无一失手，看来我们"+query("family/family_name", me)+
                               "真是后继有人啊！”\n";
                        special = "/clone/gift/jiuzhuan";
                } else
                if (total_count == 0)
                {
                        msg += CYN + me->name() + CYN "深深叹了口气，道：“想不到你连着" + chinese_number(quest_count) +
                               "次任务无一失手，看来我们"+query("family/family_name", me)+
                               "将有宗师出世拉！”\n" NOR;
                        special = "/clone/gift/xuanhuang";
#ifdef DB_SAVE
                        if (MEMBER_D->is_valid_member(query("id", who)))
                        {
                                if( query("special_skill/sophistry", who) )
                                {
                                       if (quest_count >= 5000)
                                                quest_count = 0;
                                } else
                                {
                                       if (quest_count >= 3000)
                                                quest_count = 0;
                                }
                        }
                        else
                        {
#endif
                                if (quest_count >= 1000)
                                        quest_count = 0;
#ifdef DB_SAVE
                        }
#endif
                } else
                if ((total_count % 10) == 0)
                {
                        msg += CYN + me->name() + CYN "喜道：“真是不赖，居然连着" + chinese_number(quest_count) +
                               "次都没有失手，干的好！”\n" NOR ;
                }

                quest_level = q["level"];
                quest_level++;
                if (quest_level > MAX_QUEST_LEVEL)
                        quest_level = 1;

                set("quest_count", quest_count, who);
                addn("all_quest", 1, who);
                if( query("all_quest", who) == 10000000 )
                        HISTORY_D->add_history("QUEST狂人", query("id", who), sprintf("人物等级 %d 级，年龄 %d.\n",
                                               query("level", who), query("age", who)));

                set_temp("quest/next_level", quest_level, who);
        }

        if( (added=query_temp("quest/help_count", who))>0 )
        {
                msg += HIY + me->name() + HIY "又道：这次敌人伏下帮手，而你能随机应变，"
                       "完成任务，可喜，可贺！\n" NOR;
                delete_temp("quest/help_count", who);
        }
        added+=query_temp("quest/escape_times", who)*2;
        delete_temp("quest/escape_times", who);
        // 根据NPC的帮手和逃走的次数调整经验
        if (added)
        {
                exp += exp * added / 2;
                pot += pot * added / 2;
        }

        // message_vision(msg, me, who);
        tell_object(who, msg);

        delete("quest", who);
        if (! bonus) return 1;

        exp /= bonus;
        pot /= bonus;
        mar /= bonus;
        weiwang /= bonus;
        score /= bonus;
        gongxian /= bonus;

        // bouns
        if (timeover)
        {
                exp /= 2;
                pot /= 3;
                mar /= 2;
                weiwang /= 4;
                score /= 4;
                gongxian /= 2;
        } else
        {
                // 百分之一的几率直接赠送物品奖励
                if ((quest_count >= 100 && random(2000) == 1) || special)
                        special_bonus(me, who, special);
                else
                if (random(10000) == 1)
                        skill_bonus(me, who);
        }

        if( query("quest_tuteng/start", who) )
        {
                int n_tt;
                object ob_tt;

                if (random(3000) == 1)
                {
                        n_tt = 1 + random(10);
                        if (n_tt == 6 && random(10) > 1) n_tt = 4;
                        ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                        if (ob_tt)
                        {
                                write(HIG "你获得了一张帝王符图碎片。\n" NOR);
                                ob_tt->move(who, 1);
                        }
                }
        }

        // 八面玲珑增加门派贡献值
        if( query("special_skill/cunning", who) )
                gongxian = gongxian * 2;

	// 拥有真龙天神则奖励提高10%
        if( query("special_skill/tianshen", who) )
	{
	         exp = exp + exp / 10;
		 pot = pot + pot / 10;
		 mar = mar + mar / 10;
		 weiwang = weiwang + weiwang / 10;
		 gongxian = gongxian + gongxian / 10;
	}

        // 慕容世家门派技能可获得多10%POT
        if( who->query_skill("huitong-tianxia", 1) >= 100 &&
            query("family/family_name", who) == "慕容世家" )
                pot = pot + pot / 10;

        exp = exp*9;
        pot = pot*6;
        mar = mar*4;
        gongxian = gongxian;

        GIFT_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score, "gongxian" : gongxian, "percent": 120 ]), 1);

        // 随机停止发送任务，必须等完成一定数量的freequest才能继续。
        if (random(60) == 1 && quest_count >= 50)
                addn("quest/freequest", 1+random(3), who);

        return 1;
}

// 远程奖励
int remote_bonus(object me)
{
        mapping q;              // WHO的任务
        string msg;             // 掌门说的消息
        object dob;             // 打晕敌人的人
        object who;
        int bonus;              // 奖励(正整数，1是正常)
        int t;                  // 用来计算时间的变量
        int exp;                // 获得的经验
        int pot;                // 获得的潜能
        int mar;                // 获得的实战体会
        int weiwang;            // 获得的威望
        int score;              // 获得的江湖阅历
        int gongxian;
        int lvl;                // 人物的等级
        int quest_level;        // QUEST的等级
        int quest_count;        // 连续QUEST的数目
        int timeover;           // 标志：超时了？
        int added;              // 做任务的时候额外出现的敌人或敌人逃走
        int total_count;
        mixed special = 0;      // 是否有特殊奖励
        string family;

        if( !mapp(q=query("quest", me)) )
                return 0;

        family=query("family/family_name", me);

        // 师傅一般是复制出来的，载入非复制的对象也可
        if (! objectp(who = find_object(mlist[family])))
        {
                who = load_object(mlist[family]);
                if (! objectp(who))
                    log_file("log", sprintf("Can not load master \"%s\".\n",
                                            mlist[family]));
                return 0;
        }

        msg = "你翻开信笺反面，发现师傅另有话说：\n\n又及：为师"
              "得知";
        if (me->is_good())
                msg += "你又除了" HIR + q["name"] + NOR "这一害，很好。";
        else
        if (me->is_bad())
                msg += "你已除掉" HIR + q["name"] + NOR "那不堪一击的所谓"
                       "大侠。";
        else
                msg += "你已完成除掉" HIR + q["name"] + NOR "的任务，不错"
                       "。";
        t = time();
        if( query_temp("quest/escape_times", me) )
        {
                msg += "且不料此次敌人甚为强悍，屡次逃窜，追击可"
                       "谓辛苦，";
                timeover = 0;
        } else
        if (t > q["limit"])
        {
                msg += "但可惜，为师是让你于" +
                       CHINESE_D->chinese_monthday(t) + "前完成，"
                       "将功补过，此次就记下不算。";
                timeover = 1;
        } else
        {
                if (t - q["time"] < ONE_DAY)
                {
                        msg += "你完成的速度如此之快，实在出乎我"
                               "的预料。";
                } else
                        msg += "你这次事情办的不错，辛苦了。";

                timeover = 0;
        }


        // bonus 为 1 表示正常奖励，为 2 表示扣除一半。
        bonus = 1;

        lvl = NPC_D->check_level(me);
        exp = 10 + random(5) + lvl;
        pot = 5 + random(3) + lvl;
        weiwang = 2 + random(3) + lvl / 2;
        score = 2 + random(3) + lvl / 2;
        quest_count=query("quest_count", me)+1;

        // add temped for keep compactible with old version
        if( query_temp("quest/total_count", me) )
        {
                quest_count=query_temp("quest/total_count", me)+1;
                delete_temp("quest/total_count", me);
        }

        // 根据任务完成的次数修正奖励
        if (quest_count >= 1000)
        {
                exp += 80 + random(50);
                pot += 45 + random(40);
                mar = 50 + random(20);
                weiwang += 8 + random(20);
                score += 4 + random(15);
                gongxian += 4 + random(15);
        } else
        // 根据任务完成的次数修正奖励
        if (quest_count >= 500)
        {
                // 连续完成了超过500次的任务
                exp += 80 + random(quest_count / 20 + 1);
                pot += 45 + random(quest_count / 25 + 1);
                mar = 50 + random(20);
                weiwang += 8 + random(20);
                score += 4 + random(15);
                gongxian += 4 + random(15);
        } else
        if (quest_count >= 200)
        {
                // 连续完成了超过200次的任务
                exp += 70 + random(quest_count / 20 + 1);
                pot += 40 + random(quest_count / 25 + 1);
                mar = 20 + random(10);
                weiwang += 5 + random(15);
                score += 3 + random(10);
        } else
        if (quest_count >= 100)
        {
                // 连续完成了超过100次的任务
                exp += 50 + random(quest_count / 20 + 1);
                pot += 30 + random(quest_count / 25 + 1);
                weiwang += 3 + random(10);
                score += 2 + random(10);
        } else
        if (quest_count >= 10)
        {
                // 连续完成了超过10次的任务
                exp += 45 + random(quest_count / 20 + 1);
                pot += 25 + random(quest_count / 25 + 1);
                weiwang += 1 + random(5);
                score += 1 + random(5);
        }

        switch (quest_level = q["level"])
        {
        case 0:
                exp = exp / 2 + 1;
                pot = pot / 2 + 1;
                weiwang = weiwang / 3 + 1;
                gongxian = gongxian / 2 + 1;
                score = score / 4 + 1;
                msg += "下次再给你一个较难的任务吧。";
                break;
        case 1:
                msg += "不错，看来我可以托付些重任给你了。";
                break;
        case 2:
                exp += exp / 4;
                pot += pot / 4;
                weiwang += weiwang / 4;
                score += score / 4;
                msg += "真是不错，不愧是我们" +
                       query("family/family_name", me)+
                       "的矫矫者。";
                break;
        case 3:
                exp += exp / 2;
                pot += pot / 2;
                weiwang += weiwang / 2;
                gongxian += gongxian / 2;
                score += score / 2;
                msg += "非常不错，这次可给我们" +
                       query("family/family_name", me)+
                       "争脸了。";
                break;
        }

        total_count = quest_count % 1000;

        if (total_count == 100)
        {
                msg += "而且连着" + chinese_number(quest_count) + "次任务都完成的漂漂亮亮，"
                       "很好。";
                special = 1;
        } else
        if (total_count == 200)
        {
                msg += "而且竟一连" + chinese_number(quest_count) + "次任务都干得很好。";
                special = "/clone/gift/puti-zi";
        } else
        if (total_count == 300)
        {
                msg += "真是长江后浪推前浪，不想你接连" + chinese_number(quest_count) + "次任务都无一疏漏，不易，不易！";
                special = "/clone/gift/tianxiang";
        } else
        if (total_count == 500)
        {
                msg += "想不到你连着" + chinese_number(quest_count) + "次任务无一失手，看来我们"+query("family/family_name", me)+
                       "真是后继有人啊！”\n";
                special = "/clone/gift/jiuzhuan";
        } else
        if (total_count == 0)
        {
                msg += "想不到你连着" + chinese_number(quest_count) +
                       "次任务无一失手，看来我们"+query("family/family_name", me)+
                       "将有宗师出世拉！”\n" NOR;
                special = "/clone/gift/xuanhuang";

#ifdef DB_SAVE
                if (MEMBER_D->is_valid_member(query("id", me)))
                {
                        if( query("special_skill/sophistry", me) )
                        {
                                if (quest_count >= 8000)
                                        quest_count = 0;
                        } else
                        {
                                if (quest_count >= 5000)
                                        quest_count = 0;
                        }
                }
                else
                {
#endif
                        if (quest_count >= 2000)
                                quest_count = 0;
#ifdef DB_SAVE
                }
#endif
        } else
        if ((total_count % 10) == 0)
        {
                msg += "嗯，况且居然连着" +
                       chinese_number(quest_count) +
                       "次都没有失手。";
        }

        quest_level = q["level"];
        quest_level++;
        if (quest_level > MAX_QUEST_LEVEL)
                quest_level = 1;

        set("quest_count", quest_count, me);
        addn("all_quest", 1, me);
        if( query("all_quest", who) == 10000000 )
                HISTORY_D->add_history("QUEST狂人", query("id", me), sprintf("人物等级 %d 级，年龄 %d.\n",
                                        query("level", me), query("age", me)));

        set_temp("quest/next_level", quest_level, me);

        if( (added=query_temp("quest/help_count", me))>0 )
        {
                msg += HIY "另及：这次敌人伏下帮手，而你能随"
                       "机应变，完成任务，可喜，可贺。\n" NOR;
                delete_temp("quest/help_count", me);
        }
        added+=query_temp("quest/escape_times", me)*2;
        delete_temp("quest/escape_times", me);
        // 根据 NPC 的帮手和逃走的次数调整经验
        if (added)
        {
                exp += exp * added / 2;
                pot += pot * added / 2;
        }
        msg = sort_msg(msg);
        msg += "\n\n";
        tell_object(me, msg);
        delete("quest", me);
        if (! bonus) return 1;

        exp /= bonus;
        pot /= bonus;
        mar /= bonus;
        weiwang /= bonus;
        score /= bonus;
        gongxian /= bonus;

        // bonus
        if (timeover)
        {
                exp /= 2;
                pot /= 3;
                mar /= 2;
                weiwang /= 4;
                score /= 4;
                gongxian /= 2;
        } else
        {
                // 百分之一的几率直接赠送物品奖励
                if ((quest_count >= 100 && random(2000) == 1) || special)
                        special_bonus(who, me, special);
                else
                if (random(10000) == 1)
                        skill_bonus(who, me);
        }

        if( query("quest_tuteng/start", me) )
        {
                int n_tt;
                object ob_tt;

                if (random(3000) == 1)
                {
                        n_tt = 1 + random(10);
                        if (n_tt == 6 && random(10) > 1) n_tt = 4;
                        ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                        if (ob_tt)
                        {
                                write(HIG "你获得了一张帝王符图碎片。\n" NOR);
                                ob_tt->move(me, 1);
                        }
                }
        }

        // 八面玲珑增加门派贡献值
        if( query("special_skill/cunning", me) )
                gongxian = gongxian * 2;

	// 拥有真龙天神则奖励提高10%
        if( query("special_skill/tianshen", me) )
	{
	         exp = exp + exp / 10;
		 pot = pot + pot / 10;
		 mar = mar + mar / 10;
		 weiwang = weiwang + weiwang / 10;
		 gongxian = gongxian + gongxian / 10;
	}

        // 慕容世家门派技能可获得多10%POT
        if( me->query_skill("huitong-tianxia", 1) >= 100 &&
            query("family/family_name", me) == "慕容世家" )
                pot = pot + pot / 10;

        exp = exp*9;
        pot = pot*6;
        mar = mar*4;
        gongxian = gongxian;

        GIFT_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score, "gongxian" : gongxian, "percent": 120 ]), 1);

        // 随机停止发送任务，必须等完成一定数量的freequest才能继续。
        if (random(60) == 1 && quest_count >= 50)
                addn("quest/freequest", 1+random(3), me);

        return 1;
}

int cancel_quest(object me, object who)
{
        mapping dbase;
        mapping q;
        object ob;
        string msg;
        int n;
        int c;

        dbase = who->query_entire_dbase();
        if (! mapp(q = dbase["quest"]) ||
                q["master_id"] != query("id", me) )
                return notify_fail("我没给你什么任务啊？\n");

        switch (q["type"])
        {
        case "kill":
                if (q["notice"] == "die")
                {
                        message_vision(CYN "$N" CYN "点点头，对$n" CYN "道：算了，听说这人"
                                       "已经被杀了，你不用再辛苦了。\n" NOR, me, who);
                } else
                {
                        message_vision(CYN "$N" CYN "摆摆手，对$n" CYN "道：你干不了就算了"
                                       "，让别人做吧！\n" NOR, me, who);

                        if( !query("special_skill/sophistry", who) )
                                delete("quest_count", who);
                }

                delete_temp("quest/next_level", who);
                if( query("special_skill/sophistry", who) )
                        break;

                n = (40 + random(40) + NPC_D->check_level(who) * 5);
                c = (10 + random(10) + NPC_D->check_level(who));
                // add temped for keep compactible with old version
                switch (q["level"])
                {
                case 0:
                        n *= 2;
                        break;
                case 1:
                        break;
                case 2:
                        n = 0;
                        break;
                case 3:
                        n = 0;
                        break;
                }
                if (! n) break;

                // adjust weiwang
                dbase["weiwang"] -= n;
                if (dbase["weiwang"] < 0)
                        dbase["weiwang"] = 0;
                msg = HIR "你的江湖威望受到了损失";

                // adjust gongxian
                addn("family/gongji", -c, who);
                if( query("family/gongji", who)<0 )
                        set("family/gongji", 0, who);
                msg += HIR "，师门对你的信任降低了";

                // adjust experience
                if (dbase["experience"] > dbase["learned_experience"])
                {
                        dbase["experience"] += (dbase["learned_experience"] - dbase["experience"]) * 2 / 3;
                        msg += "，由于疲于奔命，你的实战体会难以及时消化吸收";
                }

                // notice place
                message("vision", msg + "。\n" NOR, who);
                break;

        case "letter":
                message_vision(CYN "$N" CYN "叹口气，看了看$n" CYN "道：连这点小事都干不了？算了吧。\n" NOR,
                               me, who);

                addn("score", -(15+random(10)), who);
                if( query("score", who)<0 )
                        set("score", 0, who);
                message("vision", HIR "你的江湖阅历受到了损失。\n" NOR, who);
                break;
        }
        who->start_busy(2);

        ob = find_living(q["id"]);
        map_delete(dbase, "quest");
        if( query_temp("quest/help_count", who) )
                delete_temp("quest/help_count", who);
        if( !ob || query_temp("quester", ob) != query("id", who) )
                return 1;

        if (environment(ob))
                message_vision(HIC "$N" HIC "看了看四周，急急忙忙的走掉了。\n" NOR, ob);

        destruct(ob);
        return 1;
}

protected void assign_quest_by_letter(object who, string killed_id, mapping new_quest)
{
        mapping q;
        string  msg;
        string  refuse, accept;
        object  letter;             // 师傅手谕

        if (! objectp(who) || ! living(who))
                return;

        if( !mapp(q=query("quest", who)) )
                return;

        if (! q["finished"])
                return;

        if (q["id"] != killed_id)
                // 任务已经变化了
                return;

        // 师傅发下新的任务，询问是否接受
        switch (random(7))
        {
        case 0:
                // 出现新任务提示
                msg = "只听扑倏扑倏几声，一只白鸽飞了过来，落在"
                      "$N肩头，$N只见白鸽足上红绳系着些什么，连"
                      "忙解下一看，原来竟是师傅手谕。\n";
                // 拒绝信息
                refuse = "$N摇了摇头，将信函随手一撕。\n";
                // 接受信息
                accept = "$N点了点头，将在信函后面写了几个字，绑"
                         "在白鸽足上放走。\n";
                break;
        case 1:
                msg = "$N转身一看，竟见到一只灰点信鸽飞至身旁，"
                      "$N赶紧收住身形，取下信鸽脚上缚着的卷起信"
                      "笺，展看便读。\n";
                refuse = "$N摇了摇头，将信函随手一撕。\n";
                accept = "$N点了点头，将在信函后面写了几个字，绑"
                         "在灰鸽足上放走。\n";
                break;
        case 2:
                msg = "$N一回头，只见一位同门装束的弟子满头大汗"
                      "地跑了过来，边喘气边道：“可叫我好找，这"
                      "是师傅派我送给你的手谕。”\n";
                refuse = "$N皱了皱眉，道：“我还是不去了，你让师"
                         "傅找别的同门去吧。”那位弟子叹了口气，"
                         "转身离开。\n";
                accept = "$N喜道：“请你禀报师傅，我一定准时完成"
                         "。”那位弟子挥了挥手，风尘仆仆的离开了"
                         "。\n";
                break;
        case 3:
                msg = "突然一位" + query("family/family_name", who) +
                      "弟子急急忙忙地跑了上来，拍拍$N的肩膀，把"
                      "一封信递上。\n";
                refuse = "$N皱了皱眉，道：“我还是不去了，你让师"
                         "傅找别的同门去吧。”那位弟子叹了口气，"
                         "转身离开。\n";
                accept = "$N喜道：“请你禀报师傅，我一定准时完成"
                         "。”那位弟子挥了挥手，风尘仆仆的离开了"
                         "。\n";
                break;
        case 4:
                msg = "只见$N刚想离开，一位同门装束的弟子追了上"
                      "来，抹了抹头上的汗珠，说道：“原来你在这"
                      "里啊，快看看师傅派我送来的信。”\n";
                refuse = "$N皱了皱眉，道：“我还是不去了，你让师"
                         "傅找别的同门去吧。”那位弟子叹了口气，"
                         "转身离开。\n";
                accept = "$N喜道：“请你禀报师傅，我一定准时完成"
                         "。”那位弟子挥了挥手，风尘仆仆的离开了"
                         "。\n";
                break;
        case 5:
                msg = "$N正欲离开，忽然发现不远处的地上一块石头"
                      "上刻着些什么，走进一看，正是本门专用的记"
                      "认，原来石头下压着一封书信。\n";
                refuse = "$N摇了摇头，将信函随手一撕。\n";
                accept = "$N点了点头，将在信函后面写了几个字，重"
                         "新压在石头下面。\n";
                break;
        default:
                msg = "忽听“嗖”的一声，一件暗器从$N背后飞来，"
                      "$N不敢疏忽，赶紧接下一看，竟是同门送来的"
                      "一封师傅手谕。\n";
                refuse = "$N摇了摇头，将信函随手一撕。\n";
                accept = "$N点了点头，在信函后面写了几个字，一甩"
                         "手将信函向背后平平送出，那信不知给谁接"
                         "住，竟即刻便消失了。\n";
                break;
        }

        message_sort(HIY + "\n" + msg + NOR, who);

        letter = new("/clone/questob/letter");

        // 这封信是给谁的？
        set("killed_id", killed_id, letter);
        set("quester",query("id",  who), letter);
        set("quest", new_quest, letter);
        set("msg/accept", accept, letter);
        set("msg/refuse", refuse, letter);

        // 要在什么时候之前回答？
        set("dest_time", time()+30, letter);
        letter->move(who);

        // 若 30 秒内不输入 accept 即作拒绝论
        letter->start_auto_cancel(who, 30);
}

// 传书分配新任务
void remote_assign_quest(object who, mapping new_quest)
{
        assign_quest_by_letter(who,query("quest/id", who),new_quest);
}

// 准备给玩家发送远程任务
mapping prepare_quest(object me)
{
        mapping q;      // 任务数据
        string place;   // npc 放置的地点
        mapping name;   // npc 的姓名
        int exp;        // 完成任务玩家的经验值
        int t;          // 时间
        string family;  // 玩家门派
        object master;  // 师傅

        exp=query("combat_exp", me);
        t = time();
        name = NPC_D->get_cn_name();
        family=query("family/family_name", me);

        // 师傅一般是复制出来的，载入非复制的对象也可
        if (! objectp(master = find_object(mlist[family])))
        {
                master = load_object(mlist[family]);
                if (! objectp(master))
                    log_file("log", sprintf("Can not load master \"%s\".\n",
                                            mlist[family]));
                return 0;
        }

        q = ([ ]);
        q["place"] = NPC_D->random_place(exp < 500000  ? ({ "大理一带", "终南山", "关外", "西域" }) :
                                         exp < 800000 ? ({ "大理一带", "终南山", "西域" }) : 0);
        q["name"] = name["name"];
        q["id"] = name["id"][0];
        q["full_id"] = name["id"];
        q["level"]=query_temp("quest/next_level", me);
        q["time"] = t;
        q["count"]=query("quest_count", me)+1;
        q["family"] = family;
        q["master_name"] = master->name();
        q["master_id"]=query("id", master);
        q["type"] = "kill";

        t = time() / ONE_DAY;
        if (place == "西域")
                t += 8;
        else
                t += 4;
        t = t * ONE_DAY - 1;
        q["limit"] = t;

        return q;
}

// 正式开始远程 quest
int start_quest(object me, mapping quest)
{
        object ob;
        int level;
        string place;

        level = quest["level"];
        ob = new(CLASS_D("generate") + "/killed.c");

        // 换上预置的姓名
        ob->set_name(quest["name"], quest["full_id"]);
        // 更换了姓名，需要重新 set_living_name，否则
        // 无法 find_living()
        ob->enable_player();

        // 到预先生成的指定地方去
        NPC_D->place_npc(ob, 0, ({ quest["place"] }));
        NPC_D->set_from_me(ob, me, 100);

        ob->add_temp("apply/attack",ob->query_skill("force")*
                                     (level - 1) / 15);
        ob->add_temp("apply/dodge",ob->query_skill("force")*
                                    (level - 1) / 15);
        ob->add_temp("apply/parry",ob->query_skill("force")*
                                    (level - 1) / 15);
        addn_temp("apply/damage", 5+level*7, ob);
        addn_temp("apply/unarmed_damage", 5+level*7, ob);
        addn_temp("apply/armor", 10+level*15, ob);
        set_temp("quester",query("id",  me), ob);
        NPC_D->random_move(ob);
        NPC_D->random_move(ob);
        NPC_D->random_move(ob);
        place=query("place", ob);

        if (me->is_good())
        {
                ob->set("shen", -query("combat_exp", ob) / 2000);
        } else
        if (me->is_bad())
        {
                set("shen",query("combat_exp",  ob)/2000, ob);
        } else
        {
                set("shen_type", 0, ob);
                set("shen", 0, ob);
        }

        // 1 级以上的任务有 10% 机会重新分布
        if (level > 0 && random(10) == 1)
        {
                string flee_msg;

                // 随机重新放置NPC的位置
                message_sort(CYN "$N" CYN  "刚想离开，突然一个"
                             "同门装束的弟子急急忙忙的赶了过来"
                             "，喊道：“不好了，不好了，" HIR +
                             ob->name() + NOR CYN "在" + place +
                             "失踪了！现在不知道去了哪里！”弟"
                             "子叹了口气，续道：“这事麻烦了，"
                             "看来只有靠你自己努力了。”\n" NOR, me);
                switch (random(3))
                {
                case 0:
                        flee_msg = "听说$N听到了江湖上追杀他的风"
                                   "声，已经躲到PLACE去了。";
                        break;
                case 1:
                        flee_msg = "有人说$N就在咱们这地界呢，"
                                   "但是也有人说他在PLACE，不知道是真是假。";
                        break;
                default:
                        flee_msg = "不知道...不知道...哦？好像"
                                   "听人说过是在PLACE。";
                        break;
                }
                ob->random_place(flee_msg);
        }

        set("quest", quest, me);
        return 1;
}

/***********************************************************
  系统注册任务概念

    HELL采用任务对象来管理众多各式各样的任务，而任务守护进程
就是他们的管理者。为什么需要任务对象？这是因为大部分任务都具
有类似的处理过程：收集情报，根据线索完成某些要求，实现最终任
务，获得奖励。为了能够快速的编写和实现多种任务，共享重复的实
现代码，系统规定了任务对象的格式，只要遵循任务对象的格式，就
可以快速的生成玩家任务。

    让我们首先看一下任务的结构：一个任务实际上就是一个自动机，
然后由玩家不断的触发这个自动机最后达到一个稳定状态，一般来说
就是任务成功或是终止。系统可以为任务对象制定一些标准事件，然
后由任务的设计者自己制定一些事件，这就组合成了一个任务的输入
事件，然后系统为任务维护一个状态，这样就构成了一个完整的自动
机。

    看一个简单的“杀人”任务。

    杀一个人主要需要三个要素：时间、地点、人物。在某一个时间，
某个地点出现一个人物，杀掉它就算完成，可以获得奖励。那么我们
设计的流程预期是这样的：一个人打听到了这个任务，就去相应的地
点，杀人，杀掉以后获得奖励。

    任务对象的自动机器：

                                      消息收集完全
            <原生态> -> 人物生成态 -----------+
                           /                  |
                 <Timeout>/    <Timeout>      |
                   -------<---------------\   |
                 /                         \  v
            <结束态>   <--------------- 人物出现态
                            杀死该人

<原生态>和<结束态>是系统规定的状态，<Timeout> 是系统原先保留
的事件。而人物生成态和人物出现态是该任务特有的状态，另外消息
收集完全和杀死该人则是该任务对象特有的事件。

<原生态>阶段系统初始化任务对象，完成一些必要的操作，并将控制
权传递给任务对象以进行后续的操作。这时该任务就自动生成一个人
物，制定它的等级，正邪，预期出现的地点，打听的难度等等。然后
就进入到人物生成态，同时表明自己需要接受超时事件。

此时，玩家如果打听消息，有可能打听到这个任务，并经过反复打听，
获得了该人出现的地点信息，则该人物对象认为消息收集完全，就真
正的生成这个人物，等候玩家将它消灭。

如果该人物被消灭，则通知任务对象，人物对象转移到<结束态>。另
外一个进入结束态的可能是超时了。

进入<结束态>，系统自动清除该任务对象。

任务产生：这可以是游戏中的机关产生，故事产生，和系统随机产生
等等。只要调入一个对象，就可以产生任务。

任务消息：除了通常的消息，有一种消息即通过电脑控制的人物产生，
包括店小二和特殊的传递消息的人物，这些消息可以反映出当前任务
的一些信息，这些功能已经由系统封装。任务产生以后，系统调用接
口函数：register_information()来登记和任务相关的消息 -- 为什
么不在任务产生的同时由任务自己登记？这是因为任务守护进程有可
能析构后重新创建，这样将遗失所有登记的数据，此时任务守护进程
就会遍历系统中所有的任务，调用register_information()接口来重
新组织这些消息。

消息数据结构：

---+-- scheme(1) -*
   |
   +-- scheme(2) -*
   |
   +-- scheme(3) --+-- 关键字：消息1
                   |
                   +-- 关键字：消息2
                   |
                   .........

打听需要一定的江湖阅历，当random(江湖阅历) > 消息的时候， 就
有可能打听到这个消息。消息可能是一个函数，如果是这样的话，在
打听消息的时候系统把打听的对象和打听消息的人，关键字传递给该
函数，取它的返回结果。

QUEST_D提供的消息API：

QUEST_D->add_quest(QUEST_OBJECT);
QUEST_D->set_information(QUEST_OBJECT, key, information);
QUEST_D->query_information(QUEST_OBJECT, key);
QUEST_D->remove_information(QUEST_OBJECT, key);
QUEST_D->remove_all_information(QUEST_OBJECT);

QUEST_OB必须提供的消息接口：

QUEST_OB->register_information();
QUEST_OB->name();
QUEST_OB->can_know_by(object knower);
QUEST_OB->can_rumor_by(object knower);
QUEST_OB->query_introduce(object knower, object who);

***********************************************************/

// 系统增加一个任务
public void add_quest(object qob)
{
        mapping total;

        if (! mapp(total = query("information")))
        {
                // 原先没有任何任务
                total = ([ qob : 1 ]);
                set("information", total);
        } else
        {
                // 查看这个任务是否已经有定义
                if (undefinedp(total[qob]))
                        // 增加一个任务，因为这时候刚刚将任
                        // 务加入，还没有任何相关的具体信息，
                        // 所以这个条目对应的就只是一个简单
                        // 整数标识。
                        total[qob] = 1;
        }
}

// 设置消息
public void set_information(object qob, mixed key, mixed info)
{
        mixed total;
        mixed all_info;

        if (! stringp(key) || (! stringp(info) && ! functionp(info)))
        {
                log_file("static/quest",
                         sprintf("%s Quest:%O(%s) set illegal info:%s:%O.\n",
                                 log_time(), qob, qob->name(), key, info));
                return;
        }

        if (! mapp(total = query("information")))
                total = ([ ]);

        if (! mapp(all_info = total[qob]))
        {
                // 原先没有该任务对象的消息信息
                all_info = ([ ]);
                total += ([ qob : all_info ]);
        }

        all_info[key] = info;
        set("information", total);
}

// 查询消息
public mixed query_information(object qob, string key)
{
        mapping total;
        mapping all_info;

        if (! mapp(total = query("information")))
                return 0;

        if (! mapp(all_info = total[qob]))
                return 0;

        return all_info[key];
}

// 删除消息
public void remove_information(object qob, string key)
{
        mapping total;
        mapping all_info;

        if (! mapp(total = query("information")))
                return;

        if (! mapp(all_info = total[qob]))
                return;

        map_delete(all_info, key);
        if (! sizeof(all_info))
        {
                // 该任务对象已经没有消息了
                map_delete(total, qob);
                return;
        }
}

// 删除某一个对象的所有消息
public void remove_all_information(object qob)
{
        mapping total;

        if (! mapp(total = query("information")))
                return;

        // 在删除所有消息的同时，任务本身也去掉了 -- 为什么
        // 这样做，这是因为如果是一个没有任何消息的任务（仅
        // 靠任务介绍提供信息）调用这个函数的含义就是清除任
        // 务本身，而一个提供消息的任务清除所有消息也具有相
        // 同的含义。
        map_delete(total, qob);
}

// QUEST系统重新启动的时候收集所有任务对象的消息
protected void collect_all_quest_information()
{
        mapping total;
        object qob;
        object *obs;

        CHANNEL_D->do_channel(this_object(), "sys",
                              "任务精灵开始收集所有的任务信息。");

        if (! mapp(total = query("information")))
        {
                total = ([ ]);
                set("information", total);
        }

        obs = filter_array(objects(), (: $1->is_quest() :));

        // 扫描所有的QUEST对象，登记信息
        foreach (qob in obs)
        {
                reset_eval_cost();
                total[qob] = 0;
                catch(qob->register_information());
        }

        // 唤醒几个子任务守护进程
        start_all_quest();
}

public void start_all_quest()
{
        string quest;
        string *qlist;
        string name;
        int pos;

        /*
        if (! VERSION_D->is_version_ok())
                // 正在同步版本？那么不启动任务守护进程
                return;
        */

        quest = read_file(CONFIG_DIR "quest");
        if (! stringp(quest))
                // 配置文件中没有任务
                return;

        qlist = explode(quest, "\n");
        foreach (name in qlist)
        {
                // 防止运行超时
                reset_eval_cost();

                if (strlen(name) < 1 || name[0] == '#')
                        // 空行或者是注释行
                        continue;

                // 去掉行尾的注释和空格
                pos = strsrch(name, '#');
                if (pos > 1) name = name[0..pos - 1];
                name = replace_string(name, " ", "");

                // 生成文件名字
                name = QUEST_DIR + name + ".c";
                if (file_size(name) < 0)
                {
                        // 没有这个任务
                        log_file("static/quest",
                                 sprintf("%s invalid quest: %s\n",
                                         log_time(), name));
                        continue;
                }

                // 启动这个任务
                catch(call_other(name, "startup"));
        }
}

// 整理所有的任务
protected void heart_beat()
{
        mapping total;
        mixed key;
        int live_time;
        int t;

        // 重新启动所有的任务进程：如果因为某种故障停止运行，
        // 此时可以将它们重新启动，如果他们原本没有出故障，
        // 那么此时重新启动会修改它们的心跳时间。
        start_all_quest();

        if (! mapp(total = query("information")))
                return;

        // 计算当前时间
        t = time();

        // 扫描所有的任务，只保留有效的任务
        foreach (key in keys(total))
        {
                reset_eval_cost();
                if (! objectp(key))
                        map_delete(total, key);
                else
                switch (key->query_status())
                {
                case QUEST_CREATE:
                        if( t-query("start_time", key)>QUEST_CREATE_PERIOD )
                        {
                                // 创建任务超过有效时间了，结束之
                                log_file("static/quest", sprintf("%s quest: %s create timeout\n%O",
                                                                 log_time(), base_name(key),
                                                                 key->query_entire_dbase()));
                                catch(key->change_status(QUEST_FINISH));
                                map_delete(total, key);
                        }
                        break;

                case QUEST_FINISH:
                        if( t - query("finish_time", key)>QUEST_FINISH_PERIOD )
                                // 结束任务超过有效时间了
                                key->change_status(QUEST_ERROR);
                        break;

                case QUEST_ERROR:
                        // 任务在运行错误状态中
                        break;

                default:
                        // 任务在通常运行状态中
                        if( (live_time=query("live_time", key))>0 &&
                            live_time < t - query("start_time", key))
                        {
                                // 生存超过了时间
                                catch(key->change_status(QUEST_FINISH));
                                map_delete(total, key);
                        }
                        break;
                }
        }
}

// 供消息灵通人士调用使用
public string generate_information(object knower, object who, string topic)
{
        mapping total;
        object *obs;
        object *dest;
        string name, title;
        object last_ob;
        mixed answer;

        total = query("information");

        switch (random(30))
        {
        case 0:
                return "阿嚏！有点感冒，不好意思。";
        case 1:
                return "等...等等，你说什么？没听清楚。";
        case 2:
                return "嗯，稍等啊，就好... 好了，你刚才说啥？";
        case 3:
                return "这个... 这个... 哦，好了，啊？你问我呢？";
        case 4:
                return "唉呦！... 不好意思，是你问我么？";
        case 5:
                return "就好... 就好... 好了，你说啥？";
        case 7:
                return "!@#$%^&*";
        }

        if (topic == "rumor" || topic == "消息")
        {
                // 生成传闻
                if (! mapp(total) ||
                    ! sizeof(obs = filter_array(keys(total), (: objectp($1) :))))
                {
                        // 目前没有任何任务
                        switch (random(3))
                        {
                        case 0:
                                return "最近没啥消息。";
                        case 1:
                                return "好像最近挺太平的。";
                        default:
                                return "不知道...你去问问别人吧。";
                        }
                }

                // 过滤该小二可以散布的消息
                obs = filter_array(obs, (: objectp($1) && $1->can_rumor_by($(knower)) :));
                if (! sizeof(obs))
                {
                        // 该人士不能散布信息
                        switch (random(3))
                        {
                        case 0:
                                return "我倒是听说最近江湖上出了不少事儿。";
                        case 1:
                                return "哎呀呀！你也知道了一些秘密？快给我说说！";
                        default:
                                return "这年头，是越来越乱了。";
                        }
                }

                // 随机选择一个可以散布的任务消息
                last_ob = obs[random(sizeof(obs))];
                set_temp("last_asked_quest", last_ob, knower);
                if (answer = last_ob->query_prompt(knower, who))
                        return answer;

                switch (random(3))
                {
                case 0:
                        return "你可曾听过最近有关『" HIY +
                               last_ob->name() + NOR CYN "』的传闻？";
                case 1:
                        return "最近正在盛传『" HIY +
                               last_ob->name() + NOR CYN "』这件事情呢！";
                default:
                        return "你没有听到大家都在议论『" HIY +
                               last_ob->name() + NOR CYN "』吗？";
                }
        }

        if (! mapp(total))
                return 0;

        // 获得该人知道的所有任务信息
        obs = filter_array(keys(total), (: objectp($1) :));
        obs = filter_array(obs, (: $1->can_know_by($(knower)) :));

        // 查看是否问某一个任务的某一个条目
        if (sscanf(topic, "%s.%s", name, title) == 2)
        {
                dest = filter_array(obs, (: $1->name() == $(name) :));
                if (! sizeof(dest))
                        return 0;

                last_ob = dest[0];
        } else
        {
                // 查看是否问某一个任务
                dest = filter_array(obs, (: $1->name() == $(topic) :));
                if (sizeof(dest) > 0)
                {
                        last_ob = dest[0];
                        set_temp("last_asked_quest", last_ob, knower);
                        answer = last_ob->query_introduce(knower, who);
                        if (stringp(answer))
                                return answer;
                        return "你说的是" HIY + knower->name() +
                               HIY "那件事情吗？你问我算是问对人了。" NOR;
                } else
                // 查看最后一次被询问的任务消息中是否有该条目
                {
                        last_ob=query_temp("last_asked_quest", knower);
                        if (! objectp(last_ob) || ! mapp(total[last_ob]))
                                return 0;

                        title = topic;
                }
        }

        // 返回有关某个任务的某个条目的消息
        set_temp("last_asked_quest", last_ob, knower);
        answer = total[last_ob];

        if (! mapp(answer))
                return 0;

        // 这个任务登记了具体的信息
        answer = answer[title];
        if (functionp(answer))
                return evaluate(answer, knower, who, topic);

        if (stringp(answer))
                return answer;

        return 0;
}
