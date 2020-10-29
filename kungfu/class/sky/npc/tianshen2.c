// 通天老仙 掌管转世
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

#define MEMBER_D   "/adm/daemons/memberd"

mixed start_thborn();

void create()
{
        set_name(HIY "炎黄天神" NOR, ({ "yanhuang tianshen", "yanhuang", "tianshen" }));
        set("long", HIY "    炎黄天神威风凛凛，在此恭候您多时了，你似乎不想打搅他，希望静\n"
                        "静地听完一守曲子，。\n" NOR);

        set("gender", "男性");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "超脱"   :   (: start_thborn :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/xianpao")->wear();
        carry_object(__DIR__"obj/tianlai-zhiyuan")->hand();
}

mixed start_thborn()
{
        object me = this_player();
        
        mapping job_special;
        string *key_job_special;
        int i, job_add, sk_12t_add, sk_bd_add, sk_lhj_add, total_lhd;
        mapping skills_status;
        string *myskills;
        
        string user, login;
        
        if (me->query("thborn/ok"))
        {
                if (! me->query("thborn/repeat")) // 有repeat标志可再次2转
                        return "你不是已经二转过了吗，快快离开吧，不要打搅我的雅兴！\n";
        }

        // 判断负重，超过30%不能转
        if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() > 30)
                return "为了你物品数据安全，负重不能超过30%，请清理一下背包再来吧！\n";

        // 数据已经清理完毕，职业如果已经选择即可2转
        if (me->query("check_yhjob"))
        {
                if (! me->query("yhjob/job"))
                        return "请选择职业（指令：yhjob <职业>）后再来找我吧！\n";

                if (! me->query("thborn/ok")) // 非重新2转才做提示和设置special
                {
                        CHANNEL_D->do_channel(this_object(), "rumor", HIY + me->name() + "(" + me->query("id") + ")" HIY "借助天神"
                                                                      "之力，超脱意识，完成了第二次转生！\n" NOR);
                        tell_object(me, HIC "\n恭喜你二转成功：你获得了特殊技能「日月齐辉」！\n" NOR);
                        me->set("special_skill/riyue", 1);
                }
                
                me->set("thborn/ok", 1);
                
                command("say 后会有期，祝你好运！");
                me->move("/d/city/wumiao");
                me->delete("thborn/repeat"); // 删除允许重新2转标志
                me->set("thborn/times", time()); // 记录2转时间
                
               // 十周年活动期间，转世成功获得特殊奖励
               me->add("combat_exp", 10000000);
               me->add("potential", 10000000);
               me->add("experience", 2000000);
               me->set_skill("force", 300);
               tell_object(me, HIG "恭喜，炎黄风雨十年活动期间，第二次转世成功，你获得了1000万经验和潜能，200万武学修\n"
                               "养及300级基本内功奖励！\n" NOR);
                       
                me->save();
                return 1;
        }
        else
        {
                // 备份数据
                user =  me->query("id");
                user = "/data/user/" + user[0..0] + "/" + user + ".o";
                login = "/data/login/" + user[0..0] + "/" + user + ".o";
                "/adm/daemons/scbornd"->beifen_thborn(me, user, login);
        }

        // 补偿左右互博10点悟性
        if (! me->query("thborn/ok") && me->query("scborn/ok") && 
            me->query_skill("zuoyou-hubo", 1) >= 385 && ! me->query("buchang-hubo"))
        {
                log_file("buchang-hubo", me->query("id") + " " + ctime(time()) + " 获得10点INT补偿。\n");
                me->add("int", 10);
                me->set("buchang-hubo", 1);
                me->add("int", 10);
                tell_object(me, HIM "\n天道循环，阴阳平衡：你获得了十点先天悟性的补偿！\n");
                me->save();
        }
        
        if (! me->query("thborn/ok")) // 再次2转不返回轮回点
        {
                // 清除LHD使用加成，单指先天悟性，因为技能和SPECIALJOB技能都要DELETE
                // 1、计算12T花费的LHD
                if (me->query_skill("yinyang-shiertian", 1))
                {
                        sk_12t_add += 5;
                        if (me->query("yinyang-shiertian/yinyang"))
                                sk_12t_add += 2;
                        if (me->query("yinyang-shiertian/qiankun"))
                                sk_12t_add += 3;
                        if (me->query("yinyang-shiertian/shier"))
                                sk_12t_add += 4;
                }
                // 2、计算霸刀花费的LHD
                if (me->query_skill("badao", 1))
                {
                        sk_bd_add += 7;
                        if (me->query("can_perform/badao/san"))
                                sk_bd_add += 8;
                }
                // 3、计算轮回剑花费的LHD
                if (me->query_skill("lunhui-sword", 1))
                {
                        sk_lhj_add += 6;
                        if (me->query("can_perform/lunhui-sword/zhen"))
                                sk_lhj_add += 6;
                }
                // 4、清除强化职业special的LHD
                job_special = me->query("lhpoint/special");
                job_add = 0;
                if (sizeof(job_special))
                {
                        key_job_special = keys(job_special);
                        for (i = 0; i < sizeof(key_job_special); i ++)
                        {
                                job_add = job_add + job_special[key_job_special[i]];
                        }        
                }
        
                total_lhd = sk_12t_add + sk_bd_add + sk_lhj_add + job_add;
                
                // 反还轮回点
                if (total_lhd >= 18)
                {
                        total_lhd = 18;
                        log_file("thborn_lhd", me->query("id") + " " + ctime(time()) + " " + sk_12t_add + " " + sk_bd_add + " " + sk_lhj_add + " " + job_add + " \n");
                        //return "轮回点数据出错，请联系游戏管理员！\n";        
                }        
                
                // 清除轮回点使用记录
                me->delete("lhpoint/special");        
                        
                if (total_lhd + me->query("scborn/cur_lunhui_point") >= 18)
                        me->set("scborn/cur_lunhui_point", 18);
                else
                        me->add("scborn/cur_lunhui_point", total_lhd);
                        
                tell_object(me, HIY "\n你总共获得" + chinese_number(total_lhd) + "点轮回点返还。\n" NOR);
                
                // 轮回点总数设置为18，2转后就不会再获得
                me->set("scborn/total_lunhui_point", 18);
        }
        else// 重新2转的单独返回职业技能的轮回点
        {
                // 4、清除强化职业special的LHD
                job_special = me->query("lhpoint/special");
                job_add = 0;
                if (sizeof(job_special))
                {
                        key_job_special = keys(job_special);
                        for (i = 0; i < sizeof(key_job_special); i ++)
                        {
                                job_add = job_add + job_special[key_job_special[i]];
                        }        
                }
        
                total_lhd = job_add;

                // 反还轮回点
                if (total_lhd >= 18)
                {
                        total_lhd = 18;
                        log_file("thborn_lhd", me->query("id") + " " + ctime(time()) + " " + sk_12t_add + " " + sk_bd_add + " " + sk_lhj_add + " " + job_add + " \n");
                        //return "轮回点数据出错，请联系游戏管理员！\n";        
                }

                // 清除轮回点使用记录
                me->delete("lhpoint/special");

                if (total_lhd + me->query("scborn/cur_lunhui_point") >= 18)
                        me->set("scborn/cur_lunhui_point", 18);
                else
                        me->add("scborn/cur_lunhui_point", total_lhd);

                tell_object(me, HIY "\n你总共获得" + chinese_number(total_lhd) + "点轮回点返还。\n" NOR);

                // 轮回点总数设置为18，2转后就不会再获得
                me->set("scborn/total_lunhui_point", 18);                
        }
        
        // 清除相关数据
        skills_status = me->query_skills();
        if (sizeof(skills_status))
        {
                myskills = keys(skills_status);
                for (i = 0; i < sizeof(myskills); i ++)
                {
                        // 如果是2次转世，修养保留
                        if (me->query("thborn/ok") && myskills[i] == "martial-cognize")
                                continue;
                                
                        me->delete_skill(myskills[i]);
                }
        }
        // 清除绝招
        me->delete("can_perform");
        me->delete("yinyang-shiertian");
        me->delte("can_learn");
        
        // 删除自创武功
        me->delete("pmskills");
        
        //清除学习记录
        me->delete("marks");
        
        // 清除tuoli2记录
        me->delete("thborn/tuoli");
        
        // lhj 记录 
        me->delete("lunhui-sword_quest");
        
        // 清除判师，脱离记录
        me->delete("detach");
        me->delete("betrayer");
        
        // 清除经验，潜能，等
        me->set("combat_exp", 0);
        me->set("learned_points", 0);
        me->set("potential", 0);
        me->set("gongxian", 0);
        me->set("weiwang", 0);
        me->set("score", 0);
        me->set("shen", 0);
        me->set("max_neili", 0);
        me->set("neili", 0);
        me->set("experience", 0);  
        me->set("learned_experience", 0);
        me->set("max_jing", 100);     
        me->set("eff_jing", 100); 
        me->set("jing", 100); 
        me->set("max_qi", 100);      
        me->set("eff_qi", 100);  
        me->set("qi", 100);      
        me->set("max_jingli", 0);
        me->set("jingli", 0);
        me->delete("combat");
        me->set("shaqi", 0);
        me->set("age", 5);
        me->set("mud_age", 0);
        me->set("jiali", 0);
        me->delete("family");
        
        if (me->query("gender") == "无性")
                me->set("gender", "男性");
        

        // 清除职业及SPECIAL
        if (me->query("yhjob/job") == "侠客")
        {
                me->delete("special_skill/haoran");
                me->delete("special_skill/xiagu");
                me->delete("special_skill/shewo");
        }
        else if (me->query("yhjob/job") == "魔师")
        {
                me->delete("special_skill/moxin");
                me->delete("special_skill/youran");
                me->delete("special_skill/haoling");
        }
        else // 隐士
        {
                me->delete("special_skill/haina");
                me->delete("special_skill/xianyun");
                me->delete("special_skill/tianxia");
        }        
        me->delete("yhjob");
        
        // 删除独孤无招
        me->delete("can_learn/dugu-jiujian/nothing");
        
        // 提示重新选择职业
        tell_object(me, HIG "\n相关数据清理完毕，请重新选择职业（指令：yhjob <职业>）后再于天神对话！\n" NOR); 
        me->set("check_yhjob", 1);
        me->delete("chose_yhjob");
        
        me->delete("class");
        me->delete("can_learn");
        
        me->save();

        return 1;
}

void init()
{
        add_action("do_yhjob", "yhjob");
        command("hand tianlai zhiyuan");
}

// 选择职业
int do_yhjob(string arg)
{
        object me;
        string msg;

        me = this_player();

        if (me->query("chose_yhjob"))
        {
                return notify_fail("你已经选择好职业了，不能再重新选择！\n");
        }
        
        if (! me->query("check_yhjob"))
                return notify_fail("请先与天神对话，清理相关数据，完成后才能选择职业！\n");
        
        if (me->query("thborn/ok") && ! me->query("thborn/ok"))
                return notify_fail("你已经二转过了，不需要再选择职业！\n");
                
            // 介绍
        if (! arg)
        {
                // 职业介绍
                msg  = HIR "\n您目前可以选择以下职业作为您转世后的职业：\n" NOR;
                msg += HIC "侠客：令江湖中人景仰的职业，拥有正气类攻击特技。\n" NOR;
                msg += HIM "魔师: 令世人畏惧的职业，拥有邪异类攻击特技。\n" NOR;
                msg += HIG "隐士: 被世人所遗忘，隐居世外，拥有多种辅助类特技。\n" NOR;
                msg += HIY "具体职业介绍请参见转世职业帮助文件 help scborn_yhjob\n" NOR;
                msg += HIY "请输入指令" HIR " yhjob 职业 " HIY "来选择您转世后的职业，选择前请认真阅读转世职业帮助文件。\n\n" NOR;

                write(msg);
                return 1;        
        }

        if (arg != "侠客" && arg != "魔师" && arg != "隐士")
                return notify_fail("请选择正确的职业：侠客、魔师、隐士。\n");
        
        if (sizeof(me->query("yhjob/job")))
                return notify_fail("对不起，您现在还不能重新选择职业。\n");

        write(HIG "您选择了 " + arg + " 的职业。\n");
        me->set("chose_yhjob", 1);
        me->set("yhjob/job" , arg);
        
        // 给予相关特技
        // 设置职业技能
        if (arg == "侠客")
        {
                me->set("special_skill/haoran",1);
                me->set("special_skill/xiagu",1);
                me->set("special_skill/shewo",1);
        }
        else if (arg == "魔师")
        {
                me->set("special_skill/moxin",1);
                me->set("special_skill/youran",1);
                me->set("special_skill/haoling",1);
        }
        else // 隐士
        {
                me->set("special_skill/haina",1);
                me->set("special_skill/xianyun",1);
                me->set("special_skill/tianxia",1);
        }
        
        me->save();

        return 1;
}

void unconcious()
{
        die();
}
