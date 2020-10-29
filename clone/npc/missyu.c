// missyu.c
// By haiyan

#include <ansi.h>
inherit NPC;

int over();
int do_end();
int do_stopcai();
void check_time();

int save()
{
        string file;
        file = "/data/npc/missdata";
        return save_object(file);
}

int restore()
{
        string file;
        file = "/data/npc/missdata.o";
        if (file_size(file) > 0)    return restore_object(file);
        else   return 0;
}

void create()
{
        set_name("于小姐", ({ "miss yu", "miss", "yu" }));
        set("gender", "女性");
        set("age", 20);
        set("title", HIG "武林大会" NOR);
        set("nickname", HIY "筹备处秘书" NOR);
        set("str", 25);
        set("con", 25);
        set("spi", 25);
        set("dex", 25);
        set("int", 25);
        set("per", 30);
        set("long", "她是一个很精明能干的人。\n");
        set("combat_exp", 1000000);
        set("class", "fighter");
        set("attitude", "herosim");
        set("shop_id","beijing");

        set("giftyx", 300);
        set("giftwx", 300);

        set("inquiry", ([
                "彩票" : "彩票十两白银一张。",
        ]));

        restore();

        if (clonep(this_object()))
        {
               set("chat_chance", 100);
               set("chat_msg", ({ (: check_time :) }));
               keep_heart_beat();
        }

        setup();
        carry_object("/clone/cloth/female3-cloth")->wear();
        carry_object("/clone/cloth/female-shoe")->wear();
}

void init()
{
        object ob = this_player();

        add_action("do_baoming", "baoming");

        if (ob && wiz_level(ob) > 3)
        {
                add_action("do_start", "start");
                add_action("do_chakan", "chakan");
                add_action("do_finish", "finish");
        }
}

void die()
{       
        return;
}

void unconcious()
{
        die();
}

int do_start()
{
        object me = this_player();
        int times;

        if (query("start_baoming"))
                return notify_fail(HIY "报名进程已经开放了。\n" NOR);

        set("start_baoming", 1);
        set("y_start", 1);
        set("caipiao", 0);
        set("bm_time", time());
        set("c_time", time());
        times = (int)query("bisai_times") + 1;
        set("bisai_times", times);
        set("wizard",query("id", me));
        save();
        tell_object(me, HIY "报名进程启动成功，现在开放报名。\n" NOR);
        message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：好消息！华夏第" + chinese_number(times) + "届武林大会即将召开，" +
                "各路武林高手踊跃报名，竞夺武林五绝！\n" NOR,
                 all_interactive());
        return 1;
}

int do_end()
{
        int n = query("bisai_times");

        set("start_baoming", 0);
        set("caipiao", 1);
        set("cp_time", time());
        save();
        message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：华夏第" + chinese_number(n) + "届武林大会报名已" +
                "经结束，有奖竞猜活动正式开始！发财良机，不容错失！\n" NOR,
                 all_interactive());
        return 1;       
}

int do_stopcai()
{
        int n = query("bisai_times");

        set("caipiao_end", 1);
        set("caipiao", 0);
        delete("bm_time");
        delete("cp_time");
        delete("c_time");
        save();
        message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：华夏第" + chinese_number(n) + "届武林大会正式召开。\n" NOR,
                 all_interactive());
        return 1;
}

int do_finish()
{
        int n = query("bisai_times");
        int i, yx = 0, wx = 0;
        int *win, sp, x, y, r;
        object ob;
        mapping caipiao, winner;
        string *player;
        string *cpwxwin = ({}), *cpyxwin = ({});
        string *par, msg = "";

        if (! query("y_start"))
               return notify_fail(HIY "比武大会进程并没有启动。\n" NOR);

        if( query("wizard") != query("id", this_player()) )
               return notify_fail(HIY "只能由主持比武大会的巫师才能结束。\n" NOR);

        winner=query("winner", this_player());
        if (! mapp(winner))
              return notify_fail(HIY "你还没有名次数据，不能结束！\n" NOR);

        tell_object(this_player(), HIY "第" + chinese_number(n) +
                    "届比赛宣布结束。\n" NOR);

        caipiao = query("xuancp");
        if (! mapp(caipiao))
        {
              tell_object(this_player(), HIY "没有人参加竞猜活动。\n" NOR);
              message("vision", HIW "【武林盛会】" + this_object()->name() +
                      "：本届比武大会没有人参加彩票竞猜活动。\n" NOR,
                      all_interactive());

              over();
              return 1;
        }

        player = keys(caipiao);
        win = keys(winner);
        par = values(winner);

        for (x = 0; x < sizeof(win); x++)
        {
             for (y = x + 1; y < sizeof(win); y++)
             {
                  if (win[x] > win[y])
                  {
                        r = win[x];
                        win[x] = win[y];
                        win[y] = r;
                  }
             }
        }

        for (i = 0; i < sizeof(player); i++)
        {
            if (caipiao[player[i]][0] == "有序")
            {
                 yx ++;
                 if (caipiao[player[i]][1] == winner[win[0]] &&
                     caipiao[player[i]][2] == winner[win[1]] &&
                     caipiao[player[i]][3] == winner[win[2]] &&
                     caipiao[player[i]][4] == winner[win[3]] &&
                     caipiao[player[i]][5] == winner[win[4]])
                     cpyxwin += ({ player[i] });
            } else
            {
                 wx ++;
                 if (member_array(caipiao[player[i]][1], par) != -1 &&
                     member_array(caipiao[player[i]][2], par) != -1 &&
                     member_array(caipiao[player[i]][3], par) != -1 &&
                     member_array(caipiao[player[i]][4], par) != -1 &&
                     member_array(caipiao[player[i]][5], par) != -1)
                     cpwxwin += ({ player[i] });
            }
        }

        message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：华夏第" + chinese_number(n) + "届武林大会共收到有效彩票" +
                chinese_number(sizeof(player)) + "张。\n" NOR, all_interactive());
        message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：其中，有序玩法" + chinese_number(yx) + "张，无序玩法" +
                chinese_number(wx) + "张。\n" NOR, all_interactive());

        if (sizeof(cpyxwin) == 0 && sizeof(cpwxwin) == 0)
        {
                message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：本届彩票竞猜无人中奖，奖池金共" +
                chinese_number(query("giftyx") + query("giftwx")) +
                "两黄金均滚入下届。\n" NOR, all_interactive());
                addn("giftyx", 300);
                if (query("giftyx") > 2000)   set("giftyx", 2000);
                addn("giftwx", 300);
                if (query("giftwx") > 2000)   set("giftwx", 2000);
                over();
                return 1;
        }

        if (sizeof(cpyxwin) == 0 && sizeof(cpwxwin) != 0)
        {
                message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：有序玩法无人中奖，奖池金" + chinese_number(query("giftyx")) +
                "两黄金滚入下届。\n" NOR, all_interactive());
                addn("giftyx", 300);
                if (query("giftyx") > 2000)   set("giftyx", 2000);

                sp = query("giftwx") / sizeof(cpwxwin);
                if (sp < 1)  sp = 1;

                message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：无序玩法共有" + chinese_number(sizeof(cpwxwin)) +
                "人中奖，单注奖金" + chinese_number(sp) + "两黄金，已存" +
                "入中奖人帐号。\n" NOR, all_interactive());

                for (i = 0; i < sizeof(cpwxwin); i++)
                {
                      ob = find_player(cpwxwin[i]);
                      if (objectp(ob))
                      {
                          addn("balance", sp*10000, ob);
                          command("tell"+query("id", ob)+"恭喜中奖！"+
                                  "您的奖金" + chinese_number(sp) + "两黄金已存入"
                                  "您的帐号了。");
                      }
                }
                over();
                return 1;
        }

        if (sizeof(cpyxwin) != 0 && sizeof(cpwxwin) == 0)
        {
                message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：无序玩法无人中奖，奖池金" + chinese_number(query("giftwx")) +
                "两黄金滚入下届。\n" NOR, all_interactive());
                addn("giftwx", 300);
                if (query("giftwx") > 2000)   set("giftwx", 2000);

                sp = query("giftyx") / sizeof(cpyxwin);
                if (sp < 1)  sp = 1;

                for (i = 0; i < sizeof(cpyxwin); i++)
                {
                      ob = find_player(cpyxwin[i]);
                      if (objectp(ob))
                      {
                           addn("balance", sp*10000, ob);
                           command("tell"+query("id", ob)+"恭喜中奖！"+
                                   "您的奖金" + chinese_number(sp) + "两黄金" +
                                   "已存入您的帐号了。");
                           msg+=query("name", ob)+"("+query("id", ob)+")"+",";
                      }  else   msg += cpyxwin[i] + ",";
                }

                message("vision", HIW "【武林盛会】" + this_object()->name() +
                        "：有序玩法中奖人名单：" + msg[0..strlen(msg)-2] + "。\n" NOR,
                        all_interactive());
                message("vision", HIW "【武林盛会】" + this_object()->name() +
                        "：单注奖金" + chinese_number(sp) + "两黄金，已存入中奖人" +
                        "帐号，恭喜！\n" NOR, all_interactive());
                over();
                return 1;
        }

        sp = query("giftwx") / sizeof(cpwxwin);
        if (sp < 1)  sp = 1;

        message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：无序玩法共有" + chinese_number(sizeof(cpwxwin)) +
                "人中奖，单注奖金" + chinese_number(sp) + "两黄金，已存" +
                "入中奖人帐号。\n" NOR, all_interactive());

        for (i = 0; i < sizeof(cpwxwin); i++)
        {
              ob = find_player(cpwxwin[i]);
              if (objectp(ob))
              {
                   addn("balance", sp*10000, ob);
                   command("tell"+query("id", ob)+"恭喜中奖！"+
                           "您的奖金" + chinese_number(sp) + "两黄金" +
                           "已存入您的帐号了。");
              }
        }

        sp = query("giftyx") / sizeof(cpyxwin);
        if (sp < 1)  sp = 1;

        for (i = 0; i < sizeof(cpyxwin); i++)
        {
              ob = find_player(cpyxwin[i]);
              if (objectp(ob))
              {
                    addn("balance", sp*10000, ob);
                    command("tell"+query("id", ob)+"恭喜中奖！"+
                            "您的奖金" + chinese_number(sp) + "两黄金" +
                            "已存入您的帐号了。");
                    msg+=query("name", ob)+"("+query("id", ob)+")"+",";
              }  else   msg += cpyxwin[i] + ",";
        }

        message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：有序玩法中奖人名单：" + msg[0..strlen(msg)-2] + "。\n" NOR,
                all_interactive());
        message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：单注奖金" + chinese_number(sp) + "两黄金，已存入中奖人" +
                "帐号，恭喜！\n" NOR, all_interactive());
        over();
        return 1;
}

int do_baoming(string arg)
{
        object me = this_player();
        int mca, mcb;
        string ipn, msg;
        mapping baoming_list;

        if( query("combat_exp", me)<500000 )
             return notify_fail("于小姐白了你一眼：就你这两下子，去搬个凳子坐在擂台下看看算了。\n");

        if (! query("start_baoming"))
        {
             if (query("caipiao"))
             {
                   command("say 这位" + RANK_D->query_respect(me) +
                           "你来晚了，报名时间已过，不如买张彩票玩玩吧。");
                   return 1;
             }
             if (query("caipiao_end"))
             {
                   command("say 比武大会已经开始，你只有等下次再来了。");
                   return 1;
             }
             command("say 这位" + RANK_D->query_respect(me) +
                     "别着急呀，还没有到武林大会召开的时间呢。");
             return 1;
        }

        if (! arg || sscanf(arg, "%d %d", mca, mcb) != 2)
        {
             msg = "指令格式：baoming <欲参赛的名次一> <欲参赛的名次二>\n";
             msg += "说明：每个ID可以参加两个名次的角逐。\n例如：你想参加";
             msg += "第一名和第三名的比赛，则打入 baoming 1 3\n";
             me->start_more(msg);
             return 1;
        }

        if (mca < 1 || mca > 5 || mcb < 1 || mcb > 5)
        {
             command("?"+query("id", me));
             command("say 你到底要参加第几名的比赛呀？");
             return 1;
        }

        if (query("baoming") &&
            member_array(query("id", me),keys(query("baoming"))) != -1 )
        {
             command("say 这位" + RANK_D->query_respect(me) +
                     "，你已经报过名了，快去准备准备吧。");
             return 1;
        }

        ipn = query_ip_number(me);
        if (!query("baoming"))  baoming_list = ([]);
        else baoming_list = query("baoming");
        baoming_list+=([query("id", me):({mca,mcb,ipn})]);
        set("baoming", baoming_list);
        save();
        tell_object(me, HIY "您报名参加第" + chinese_number(mca) +
                    "名和第" + chinese_number(mcb) + "名的比赛，祝你成功！\n"NOR);
        return 1;
}

int accept_object(object me, object ob)
{
        object piao;
        mapping cai, bm;
        string *xs;
        int i;

        if( query("money_id", ob) )
        {
              if (query("caipiao"))
              {
                   if (ob->value() >= 1000 )
                   {
                         bm = query("baoming");
                         xs = keys(bm);
                         for (i = 0; i < sizeof(xs); i++)
                         {
                              if (bm[xs[i]][2] == query_ip_number(me))
                              {
                                   tell_object(me, "于小姐对你道：你的IP" +
                                       "有人参加比赛，你不能参与竞猜。\n");
                                   return 0;
                              }
                         }
                         piao = new(__DIR__"obj/piao");
                         set("baoming", query("baoming"), piao);
                         piao->move(me);
                         message_vision("于小姐撕下一张彩票递给$N。\n", me);
                         destruct(ob);
                         return 1;
                   } else
                   {
                         command("say 才给这么点钱？你也太穷酸了吧。");
                         return 0;
                   }
              }

              if (query("start_baoming"))
              {
                   command("say 现在正在报名中，等报名结束才能卖彩票。");
                   return 0;
              }

              if (query("caipiao_end"))
              {
                   command("say 比武大会已经开始了，你等下次吧。");
                   return 0;
              }

              command("say 现在不出售彩票，等比武大会开始报完名后再来买吧。");
              return 0;
        }

        if( query("id", ob) == "caipiao" )
        {
              if( !query("done", ob) )
              {
                    command("say 这张彩票什么也没填，填好了再给我吧。");
                    return 0;
              }

              if (query("caipiao_end"))
              {
                    command("say 比武大会已经开始，你这张彩票作废了。");
                    message_vision("$N接过$n的彩票几下撕成了碎片。\n", this_object(), me);
                    destruct(ob);
                    return 1;
              }

              if (! query("caipiao"))
              {
                    command("say 你这张彩票已经过期作废了。");
                    message_vision("$N接过$n的彩票几下撕成了碎片。\n", this_object(), me);
                    destruct(ob);
                    return 1;
              }

              bm = query("baoming");
              xs = keys(bm);
              for (i = 0; i < sizeof(xs); i++)
              {
                   if (bm[xs[i]][2] == query_ip_number(me))
                   {
                        tell_object(me, "于小姐对你道：你的IP" +
                                    "有人参加比赛，你不能参与竞猜。\n");
                        return 0;
                   }
              }

              if (!query("xuancp"))  cai = ([]);
              else
              {
                   cai = query("xuancp");
                   if( member_array(query("id", me),keys(cai)) != -1 )
                   {
                         tell_object(me, "你已经投过注了。\n");
                         return 0;
                   }
              }
              cai+=query("array", ob);
              set("xuancp", cai);
              save();
              destruct(ob);
              command("say 祝你好运！");
              return 1;
        }
        return 0;
}

int do_chakan()
{
        mapping bm;
        string *rs, msg = "\n";
        int i, j;

        bm = query("baoming");
        if (! mapp(bm))
             return notify_fail(HIY "现在没有人报名。\n" NOR);

        rs = keys(bm);
        for (i = 1; i <= 5; i++)
        {
             msg += "参加第" + chinese_number(i) + "名比赛的有：\n";
             for (j = 0; j < sizeof(rs); j++)
             {
                  if (bm[rs[j]][0] == i || bm[rs[j]][1] == i)
                       msg += rs[j] + " ";
             }
             msg += "\n\n";
        }
        this_player()->start_more(HIY + msg + NOR);
        return 1;
}

int over()
{
        int n = query("bisai_times");
        message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：下届有序玩法奖池金为：" + chinese_number(query("giftyx")) +
                "两黄金；无序玩法奖池金为：" + chinese_number(query("giftwx")) +
                "两黄金。\n" NOR, all_interactive());
        message("vision", HIW "【武林盛会】" + this_object()->name() +
                "：热烈祝贺华夏第" + chinese_number(n) + "届武林大会圆满结束"
                "。\n" NOR, all_interactive());
        set("caipiao", 0);
        set("y_start", 0);
        delete("xuancp");
        delete("winner");
        delete("baoming");
        delete("wizard");
        delete("caipiao_end");
        save();
        delete("winner", this_player());
        return 1;
}

void check_time()
{
        int n, tm;

        n = query("bisai_times");
        if (query("c_time") && (time() - query("c_time") >= 300))
        {
              if (query("start_baoming"))
              {
                    if (query("bm_time") && (time() - query("bm_time") < 82800))
                    {
                        message("vision", HIW "【武林盛会】" + this_object()->name() +
                        "：华夏第" + chinese_number(n) + "届武林大会即将召开，" +
                        "各路武林高手已开始踊跃报名，竞夺武林五绝！\n" NOR,
                        all_interactive());
                    }  else
                    if (query("bm_time") && (time() - query("bm_time") >= 82800) &&
                       (time() - query("bm_time") < 86400))
                    {
                        tm = 86400 - (time() - query("bm_time"));
                        if (tm >= 300)  tm /= 60;
                        else tm = 5;

                        message("vision", HIW "【武林盛会】" +
                                this_object()->name() + "：距第" +
                                chinese_number(n) + "届武林大会报" +
                                "名结束时间还剩" + chinese_number(tm) +
                                "分钟！\n" NOR, all_interactive());
                    }  else   do_end();

                    set("c_time", time());
                    save();
                    return;
              }

              if (query("caipiao"))
              {
                    if (query("cp_time") && (time() - query("cp_time") < 5400))
                    {
                        if (random(3) > 0)
                            message("vision", HIW "【武林盛会】" + this_object()->name() +
                            "：华夏第" + chinese_number(n) + "届武林大会报名已" +
                            "经结束，有奖竞猜活动正在举行！发财良机，不容错失！\n" NOR,
                            all_interactive());
                        else
                            message("vision", HIW "【武林盛会】" + this_object()->name() +
                                    "：本届武林大会奖池金额为：有序玩法" +
                                    chinese_number(query("giftyx")) +
                                    "两黄金；无序玩法" + chinese_number(query("giftyx")) +
                                    "两黄金。\n" NOR, all_interactive());
                    }  else
                    if (query("cp_time") && (time() - query("cp_time") >= 5400) &&
                       (time() - query("cp_time") < 7200))
                    {
                        tm = 7200 - (time() - query("cp_time"));
                        if (tm >= 300)   tm /= 60;
                        else  tm = 5;

                        message("vision", HIW "【武林盛会】" +
                                this_object()->name() + "：还有" +
                                chinese_number(tm) + "分钟，第" +
                                chinese_number(n) + "届武林大会将" +
                                "正式召开！\n" NOR, all_interactive());
                    }  else   do_stopcai();

                    set("c_time", time());
                    save();
                    return;
              }
        }
        return;
}

void reset()
{
        restore();
}
