// quest.c

#include <ansi.h>
 
inherit F_CLEAN_UP;
string time_period(int timep);

int main(object me, string arg)
{
        object ob,env;
        mapping q,quest;
        string master,msg,*place;
        int tag_fam = 0;
        int flag_zs = 0;
        int flag_bh = 0;
        int i;

        while (arg)
        {
                if (arg == "cancel")
                {
                        if( !stringp(master=query("quest/master_id", me)) )
                                return notify_fail("有人向你下任务了吗？\n");

                        if (! objectp(ob = present(master, environment(me))))
                                return notify_fail("给你下任务的那个人现在不在这里吧？\n");
                } else
                if (! objectp(ob = present(arg, environment(me))))
                        return notify_fail("这里没有这个人，你怎么领任务？\n");

                if (! living(ob))
                        return notify_fail("你还是等" + ob->name() +
                                           "醒了再说吧！\n");

                if (me->is_fighting())
                        return notify_fail("专心打你的架！\n");

                if (me->is_busy())
                        return notify_fail("你还是有空了再和" + ob->name() +
                                           "谈这些问题吧！\n");

                if (ob->is_fighting())
                        return notify_fail("你还是等" + ob->name() +
                                           "打完架再说吧！\n");

                if (ob->is_busy())
                        return notify_fail(ob->name() +
                                           "正忙着呢，没功夫理你。\n");

                notify_fail(ob->name() + "望着你呵呵的傻笑。\n");
                return (arg == "cancel" ? ob->cancel_quest(me)
                                        : ob->ask_quest(me));
        }
        write(HIR + "帮会任务系统：\n" + NOR);
        if( query_temp("finish_bunch_times", me) )
                write(sprintf("头儿交给你的任务，你已经连续完成了 %d 个。\n",
                       query_temp("finish_bunch_times", me)));

        msg = "";
             if( mapp(quest=query("bunch_quest", me)) )
         {
                flag_bh = 1;
                msg = quest["type"] + "：" + quest["msg"];
                write("你刚才领的任务：\n"+msg+"\n");
                if (quest["id"] == "xc")
                {
                        place = ({});
                        place = quest["place"];
                        if (sizeof(place))
                        {
                                msg = "你还需要巡逻这些地方：";
                                for (i = 0;i < sizeof(place);i++)
                                {
                                        env = get_object(place[i]);
                                        msg += env->short() + " ";
                                }
                                write(msg + "\n");
                        } else write("你可以回去交差了！\n");
                }
         }

        if (!flag_bh) write("你目前没有从帮会那里接任务！\n");

        write(HIR + "\n门派任务系统：\n" + NOR);
        if( query("quest_count", me) )
                write(sprintf("师长交给你的任务，你已经连续完成了 %d 个。\n",
                       query("quest_count", me)));
 
        if( mapp(q=query("quest", me)) )
        {
                 switch (q["type"])
                { 
                  case "kill":
                        write(q["master_name"] + "吩咐你在" + CHINESE_D->chinese_monthday(q["limit"]) +
                      "之前割下" HIR + q["name"] + NOR "的人头，回" + q["family"] + "交差。\n" +
                      "据说此人前不久曾经在" + q["place"] + "出没。\n");
                      tag_fam = 1;
                      break;
                case "letter":
                      write(q["master_name"] + "吩咐你在" + CHINESE_D->chinese_monthday(q["limit"]) +
                      "之前把信件送到" HIC + q["name"] + NOR "手中，取回执交差。\n" +
                      "据闻不久前此人曾经在" + q["place"] + "。\n");
                      tag_fam = 1;
                      break;
                }
        }
        if (!tag_fam) write("你现在没有领任何门派任务！\n");
        
        write(HIR + "\n宗师任务系统：\n" + NOR);

        if( query("questdg_times", me) )
                     write("独孤求败交给你的任务，你已连续完成"+query("questdg_times", me)+"个了。\n");
        if( query("questkh_times", me) )
                     write("葵花太监交给你的任务，你已连续完成"+query("questkh_times", me)+"个了。\n");
        if( query("questsn_times", me) )
                     write("南海神尼交给你的任务，你已连续完成"+query("questsn_times", me)+"个了。\n");;
        if( query("quesths_times", me) )
                 write("黄裳交给你的任务，你已连续完成"+query("quesths_times", me)+"个了。\n");

        msg = "";
        // 独孤求败
         if( mapp(quest=query("quest_dg", me)) )
         {
                flag_zs = 1;
                msg = quest["dgmsg"];
                write("你刚才领的任务：\n"+msg+"\n");
         }

         msg = "";
        // 东方不败
        if( mapp(quest=query("quest_kh", me)) )
         {
                flag_zs = 1;
                        msg = quest["khmsg"];
                if (quest["desc"] == "灭")
                           if(quest["time"] < time())
                                     msg += "\n你已经超过了规定时间了！";
                             else
                                            msg += "\n你还有"+time_period(quest["time"]-time())+"的时间。";
                write("你刚才领的任务：\n"+msg+"\n");
         }

        msg = "";
        // 黄裳
         if( mapp(quest=query("quest_hs", me)) )
         {
                flag_zs = 1;
                msg = quest["msg"];
                if (quest["type"] == "收")
                {
                                     msg += "\n你已经完成了" + quest["ok"] + "个，";
                                            msg += "\n你还需要找" + (quest["want"] - quest["ok"]) + "个。";
                }
                write("你刚才领的任务：\n"+msg+"\n");
         }

        msg = "";
        // 南海神尼
         if( mapp(quest=query("quest_sn", me)) )
         {
                flag_zs = 1;
                msg = quest["msg"];
                if (quest["type"] == "收")
                {
                                     msg += "\n你已经完成了" + quest["ok"] + "个，";
                                            msg += "\n你还需要找" + (quest["want"] - quest["ok"]) + "个。";
                }
                write("你刚才领的任务：\n"+msg+"\n");
         }

        if (!flag_zs) write("你目前没有从任何宗师那里接任务！\n");
        return 1;
}

string time_period(int timep)
{
   int t, d, h, m, s;
   string time;
   t = timep;
   s = t % 60;             t /= 60;
   m = t % 60;             t /= 60;
   h = t % 24;             t /= 24;
   d = t;
 
   if(d) time = chinese_number(d) + "天";
   else time = "";
 
   if(h) time += chinese_number(h) + "小时";
   if(m) time += chinese_number(m) + "分";
   time += chinese_number(s) + "秒";
   return time;
}

int help(object me)
{
        write(@HELP
指令格式 : quest  这个指令可以用来向你的门派的掌门或世家长辈
领取任务，如果不加任何参数则显示出你当前的任务。

从宗师那里领取任务只需要到宗师所在地方输入quest，不需要加任何
参数。

HELP );
        return 1;
}