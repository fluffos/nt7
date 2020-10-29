// Code of JHSH
// mingjiao job file

#include <ansi.h>
#define OBJ_PATH "/d/mingjiao/obj"
#define MINGJIAO "/d/mingjiao/"
#include "/d/mingjiao/obj/time_all.h"
#define BASE 80

string judge_jobmsg(object player,int flg)
{
        string s_msg,job_msg,job_flg;
        s_msg=query("mingjiao/job", player);

        switch (s_msg)
        {
                case "jin_caikuang":
                        job_flg="采集铁矿";break;

                case "huo_zaoqiang":
                        job_flg="打造火枪";break;

                case "shui_tiaoshui":
                        job_flg="挑水";break;

                case "mu_kanshu":
                        job_flg="砍树";        break;

                case "tu_didao":
                        job_flg="挖地道"; break;

//                default:
//                        job_msg="这位"+RANK_D->query_respect(player)+"现在好象没有任务在身。";
//                        return job_msg;
//                        write("judge_jobmsg reached default! please report.\n");
        }

        if(flg)
        return job_flg;

        job_msg="这位"+RANK_D->query_respect(player)+"现在不是"+job_flg+"吗？等完成了再来领取其它任务吧。";
        return job_msg;
}

int cut_abandon_jl(string job_kind)
{
        int cut_cc;

        switch (job_kind)
        {
                case "采集铁矿":
                        cut_cc=BASE+random(BASE*2)/2; break;
                case "打造火枪":
                        cut_cc=BASE+random(BASE*3)/2; break;
                case "挑水":
                        cut_cc=BASE+random(BASE*3)/2; break;
                case "砍树":
                        cut_cc=BASE+random(BASE*2)/2; break;
                case "挖地道":
                        cut_cc=BASE+random(BASE*2)/2; break;
        }

        if( query("family/gongji", this_player()) )
                addn("family/gongji", -cut_cc, this_player());
        if( query("family/gongji", this_player())<0 )
                delete("family/gongji", this_player());
        tell_object(this_player(),RED"你的明教功绩下降了"+cut_cc+"点。\n"NOR);

        delete("mingjiao/job", this_player());

        return 1;
}




string ask_abandon()
{
        object player;
        string job_flg, id, name;
        player=this_player();

        if( !query("mingjiao/job", player) )
                return "这位"+RANK_D->query_respect(player)+"现在好像没有任务在身。";

        job_flg=judge_jobmsg(player,1);

        switch (job_flg)
        {
                case "采集铁矿":
                        id = "zhuang zheng"; name = "庄铮"; break;
                case "打造火枪":
                        id = "xin ran"; name = "辛然"; break;
                case "挑水":
                        id = "tang yang"; name = "唐洋"; break;
                case "砍树":
                        id = "wen cangsong"; name = "闻苍松"; break;
                case "挖地道":
                        delete_temp("didao_done", player);
                        id = "yan yuan"; name = "颜垣"; break;
        }

        if( query("id", this_object()) == id && query("name", this_object()) == name )
        {
                if(cut_abandon_jl(job_flg))
                        return "阁下连这种事情都办不好，将来如何光大我光明圣火教。";
                else
                        return "阁下尽力完成这次任务吧。";
        }
        else
                return "既然这位"+RANK_D->query_respect(player)+"想放弃"+job_flg+"的任务，请去跟"+name+"旗主说一声。";

        return "ask_abandon() has error!";
}



void reward(object me, string job_flg)
{
        int old_cc,add_cc/*,max_pot*/, add_exp,add_pot;
        mixed old_pot;

        if (!me) return;

        old_cc=query("family/gongji", me);
        old_pot=query("potential", me);

        switch(job_flg)
        {
                case "采集铁矿":
                        add_cc=BASE+random(BASE*2)/2;                // BASE = 100
                        add_exp=BASE+random(add_cc);
                        add_pot=add_exp/3+random(add_exp/4);
                        break;
                case "打造火枪":
                        add_cc=BASE+random(BASE*3)/2;
                        add_exp=BASE+random(add_cc);
                        add_pot=add_exp/3+random(add_exp/4);
                        break;
                case "挑水":
                        add_cc=BASE+random(BASE*3)/2;
                        add_exp=BASE+random(add_cc);
                        add_pot=add_exp/3+random(add_exp/4);
                        break;
                case "砍树":
                        add_cc=BASE+random(BASE*2)/2;
                        add_exp=BASE+random(add_cc);
                        add_pot=add_exp/3+random(add_exp/4);
                        break;
                case "挖地道":
                        add_cc=BASE+random(BASE*2)/2;
                        add_exp=BASE+random(add_cc);
                        add_pot=add_exp/3+random(add_exp/4);
                        break;
        }

        delete("mingjiao/job", me);

        add_cc /= 10;
        addn("family/gongji", add_cc, me);
        addn("combat_exp", add_exp, me);
        addn("potential", add_pot, me);
        //if (me->query("potential") > me->query_potential_limit())
        //        me->set("potential",me->query_potential_limit());
        tell_object(me,HIG"恭喜！你的明教功绩上升了"+add_cc+"点。\n"NOR);
        tell_object(me,HIG"你的经验上升了"+add_exp+"点。\n"NOR);
        tell_object(me,HIG"你的潜能上升了"+add_pot+"点。\n"NOR);

}