#include <ansi.h>;

int ask_job()
{
        object me;
        mapping myfam;
        
        me = this_player();
        myfam=query("family", me);
        

        if (! myfam || myfam["family_name"] != "唐门世家")
        {
                command("say 你是我们的人吗？再说我的任务你不一定肯做啊，回去吧！");
                return 1;
        }

        if( query("tangmen/yanli", me) >= 100 )
        {       
                command("gongxi");
                command("say 看你长的一表人才，就知道你是一块料，上山去吧！");
                set("tangmen/upshan", 1, me);
                return 1;
        }

        if( query_temp("started", me) )
        {
                command("say 你有任务，为什么不去做？");
                return 1;
        }
        
        if( query_temp("tmjob_failed", me) )
        {
                delete_temp("tmjob_failed", me);
                me->apply_condition("tmagain", 1);
                command("hmm");
                command("你先下去歇歇吧，过会再来！\n");
                return 1;
        }               
        
        if (me->query_condition("tmagain") > 0)
        {       command("heng");
                command("say 做不了说一下，你等等吧！");
                return 1;
        }        

        if( query_temp("jobok", me) == 1 )
        {
                command("say 好好，干的好，你下去歇歇吧。");
                addn("combat_exp", 3000, me);
                delete_temp("started", me);
                delete_temp("find_wz", me);
                me->apply_condition("tmjob", 0);
                delete_temp("jobok", me);
                addn("tangmen/yanli", 1, me);
                return 1;
        }
        

        command("say 你去给我抓一只蚊子回来吧。");
        command("say 此事不可马虎，关系到你的前程，一定要全力去做。");
        command("say 找不到的话就问问别人，说不定有收获啊");

        set_temp("started", 1, me);
        remove_call_out("putting");
        call_out("putting", 2 , me);
                       
        return 1;
}

int putting(object me)
{
        object ob1,ob2;
        string wh1,wh2;
        string *str = ({"/d/tangmen/kedian","/d/tangmen/edajie",
                        "/d/tangmen/tjpuzi","/d/tangmen/hcfdian",
                        "/d/tangmen/tsqianz","/d/tangmen/xdajie",
                        "/d/tangmen/tmbingqi","/d/tangmen/ndajie",
                        "/d/tangmen/bdajie1","/d/tangmen/bdajie2",
                        "/d/tangmen/jiulou","/d/tangmen/zhongxin",
                       });
        wh1 = str[random(sizeof(str))];
        wh2 = str[random(sizeof(str))];
        ob1 =new("/d/tangmen/npc/askdizi1.c");
        ob2 =new("/d/tangmen/npc/askdizi2.c");
        set("dname",query("id",  me), ob2);
        set("dname",query("id",  me), ob1);
        ob1->apply_condition("tmjob1", 10);
        ob2->apply_condition("tmjob1", 15);
        me->apply_condition("tmjob", 20);
        ob1->move(wh1);
        ob2->move(wh2);        
        tell_object(me, HIC "要快去快回啊！\n" NOR);
        return 1;
}       
        
