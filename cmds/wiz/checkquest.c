// checkquest.c
// Smallfish@Huaxia

#include <ansi.h>
 
inherit F_CLEAN_UP;
string time_period(int timep);

int main(object who, string arg)
{
        object me,ob;
        mapping q,quest;
        string master,msg;
        int tag_fam = 0;
        int flag_zs = 0;
        int flag_bh = 0;

        if (! SECURITY_D->valid_grant(who, "(wizard)"))
                return 0;

        if (!arg) return notify_fail("指令格式：checkquest <ID>\n");
        if (!(me = find_player(arg))) return notify_fail(arg + "这个人并不在线啊！\n");

        write(HIY+"检查对象："+HIW+me->name(1)+"("+query("id", me)+")"+NOR+"\n\n");

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

         if( query_temp("questdg_times", me) )
                     write("独孤求败交给你的任务，你已连续完成"+query_temp("questdg_times", me)+"个了。\n");
         if( query_temp("questkh_times", me) )
                     write("葵花太监交给你的任务，你已连续完成"+query_temp("questkh_times", me)+"个了。\n");
        if( query_temp("questsn_times", me) )
                     write("南海神尼交给你的任务，你已连续完成"+query_temp("questsn_times", me)+"个了。\n");;
        if( query_temp("quesths_times", me) )
                 write("黄裳交给你的任务，你已连续完成"+query_temp("quesths_times", me)+"个了。\n");

        msg = "";
        // 独孤求败
         if( mapp(quest=query("quest_dg", me)) )
         {
                flag_zs = 1;
                msg = quest["dgmsg"];
                write("你刚才领的任务："+msg+"\n");
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
                write("你刚才领的任务："+msg+"\n");
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
                write("你刚才领的任务："+msg+"\n");
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
                write("你刚才领的任务："+msg+"\n");
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
指令格式 : checkquest  <ID>
这个指令可以用来查询某个玩家从所在门派的掌门或
世家长辈领取任务以及从宗师那里领取得任务。

HELP );
        return 1;
}