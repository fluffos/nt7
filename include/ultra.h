// ultra.h 宗师评价玩家的公共代码

int query_auto_perform() { return 1; }
int calc_level(object me, string skill);
void check_ultra(object me);

// check level
// level is calculate as:
// level = (skill effect level) + (action["force"] - 200) / 5
mapping opinions_rank = ([
        500 : "宗师",
        450 : "登峰造极",
        410 : "超凡脱俗",
        380 : "臻至化境",
        350 : "炉火纯青",
        320 : "已有大成",
        290 : "非同凡响",
        260 : "出类拔萃",
        230 : "身手不凡",
        200 : "已有小成",
]);

// generate opinion
void check_opinion(object me)
{
        string msg;
        string rank;
        int *ks;
        int lvl;
        int next_lvl;
        int opinion;
        int i;

        delete_temp("opinion");
        if (! me || environment(me) != environment())
        {
                command("sigh");
                return;
        }

        // rank: 原有的评价称号
        // ks:   不同评价需要的等级按照升序排列
        // lvl:  原有评价所在的等级
        // next_lvl: 在原有的评价下下一等级需要的lvl
        // opinion : 此次的评价等级，如果为-1就没有变化
        rank = query("opinion/" + MY_OPINION, me);
        ks  = sort_array(keys(opinions_rank), 1);
        if (! stringp(rank))
        {
                // 以前没有评价，设置最小评价需要的等级
                next_lvl = ks[0];
        } else
        {
                // 以前有评价，看这一次如果提升的话需要
                // 到多少级
                for (i = 0; i < sizeof(ks) - 1; i++)
                        if (opinions_rank[ks[i]] == rank)
                        {
                                next_lvl = ks[i + 1];
                                break;
                        }
                if (i >= sizeof(ks))
                {
                        // 无法找到原先的等级，设置最小评价
                        next_lvl = ks[0];
                }
        }
        opinion = -1;
        for (i = 0; i < sizeof(my_opinions); i++)
        {
                lvl = calc_level(me, my_opinions[i]);
                if (lvl >= next_lvl && lvl > opinion)
                        // 记录：第i项武学有更好的评价
                        opinion = lvl;
        }

        if (opinion == -1)
        {
                if (next_lvl == ks[0])
                {
                        message_vision("\n$N淡淡一笑，对$n道："
                                       "“你的" OPINION_TYPE "不行啊！好好"
                                       "努力吧！”\n", this_object(), me);
                        return;
                }
                message_vision("\n$N对$n摇摇头道：“不怎么样，我"
                               "发现你的" OPINION_TYPE
                               "比上次没什么太大的进步。”\n",
                               this_object(), me);
                return;
        }

        for (i = sizeof(ks) - 1; i > 0; i--)
                if (opinion >= ks[i]) break;

        set("opinion/" + MY_OPINION, opinions_rank[ks[i]], me);
        if (i == sizeof(ks) -1)
        {
                // 到了终极
                message_vision("\n$N对$n笑道：“恭喜！" +
                               RANK_D->query_respect(me) +
                               "的" OPINION_TYPE "已然到了宗师境界！"
                               "武道无穷，阁下自重！”\n",
                               this_object(), me);
                set("opinions/master", 1, me);
                check_ultra(me);
                return;
        }

        message_vision("\n$N沉思片刻，对$n道：“就目前来看，你的"
                       OPINION_TYPE "已经可以算得上是" +
                       opinions_rank[ks[i]] + "了。”\n",
                       this_object(), me);
}

void check_ultra(object me)
{
        object *ultra;

        if (query("opinion/unarmed", me) != "宗师" ||
            query("opinion/weapon", me) != "宗师"  ||
            query("opinion/force", me) != "宗师"  ||
            query("opinion/dodge", me) != "宗师" )
                return;

        set("opinion/ultra", 1, me);
        ultra = NPC_D->query_ultra_master();
        ultra -= ({ this_object() });
        command("chat 真是长江后浪推前浪，想不到今日又有" + query("name", me) +
                "跻身武林大宗师的行列！");
        ultra->do_congration(me);
        CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                              "听说" + query("name", me) + "成为武学大宗师。");
}
