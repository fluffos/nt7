// huqingyu.c
#include <ansi.h>
#include <command.h>
inherit BUNCHER; 

void create()
{
        set_name("胡庆余",({ "hu qingyu","hu" }));
        set("gender", "男性" );
        set("age", 63);
        set("long",
"胡庆余是当世一大巫医，他的本事神奇无比。真有生死肉骨之功。\n");
        set("combat_exp", 200000);
        set("attitude", "friendly");
/*
        set("inquiry", ([
                "改名": "五百两黄金，给你改头换面，江湖上没人会知道你的！",
        ]) );
        set("chat_chance", 30);
        set("chat_msg",({
                "胡庆余淡淡说道：“改个名，就是新人了。”\n",
        }));
*/
        setup();
}
/*
void init()
{
        object ob,me;
        //add_action("do_name","name");
//        add_action("do_betrayer","betrayer");
//        add_action("do_age","age");
}
int accept_object(object me, object ob)
{
        if (userp(me))
        {
                if( query("money_id", ob) && ob->value() >= 5000000 )
                {
                        if( query("class", me) == "bonze" || query("class", me) == "quanzhen" )
                        {
                                say("胡庆余掩口暗笑：出家人是不能改名字的。我还怕你们掌门师尊派人砸我的小店呢。\n");
                                return 0;
                        }
                        command("nod");
                        command("say好吧，"+query("name", me)+"，你说个章程！\n");
                        set_temp("marks/huqingyu", 1, me);
                        return 1;
                }
        } else return 1;
}
int do_name(string arg,object me)
{
        string *banned_name = ({
                "你", "操", "我", "他", "她", "它", "妈", "爸", "　",
                "翔少爷", "方舟子", "草鱼", "时空", "丁",
                "木人", "赫连铁树", "单正", "韦小宝",
                "仙子", "天马行空", "迪阳", "风儿", "演若达多", "凡狗",
                "寒江雪", "天星", "紫志龙","虾咪碗糕"
        });
        int i;

        me = this_player();
        if( query("class", me) == "bonze" || query("class", me) == "quanzhen" )
                return notify_fail("胡庆余掩口暗笑：出家人是不能改名字的。我还怕你们掌门师尊派人砸我的小店呢。\n");
        if( !query_temp("marks/huqingyu", me) )
        {
                return notify_fail("胡庆余翻着黑白眼：钱呢？没给钱想占便宜？\n");
        }
        if( !arg ) return notify_fail("胡庆余笑道：名字总该写全吧。\n");
        if( strlen(arg) > 10 )
        return notify_fail("胡庆余惊呼起来：哪有这么长的名字？\n");
        if( strlen(arg) < 4 )
        return notify_fail("胡庆余哼了一声：这么短算啥名字？\n");
        i=strlen(arg);
        while(i--)
        {
                if( arg[i]<=' ' ) {
                        write("对不起，你的中文名字不能用控制字元。\n");
                        return 1;
                }
                if( (strsrch(arg, "　") >= 0) ||
                    (strsrch(arg, "爸") >= 0)) {
                        write("对不起，你的中文名字不能用引起误会的单字。\n");
                        return 1;
                }
                if( i%2==0 && !is_chinese(arg[i..<0]) ) {
                        write("对不起，请您用「中文」取名字。\n");
                        return 1;
                }
        }
        if( member_array(arg, banned_name)!=-1 ) {
                write("对不起，这种名字会造成其他人的困扰。\n");
                return 1;
        }
        if( (strlen(arg) < 2) || (strlen(arg) > 10 ) ) {
                write("对不起，你的中文名字必须是 1 到 5 个中文字。\n");
                return 1;
        }

        delete_temp("marks/huqingyu", me);
        if( query("gender", me) == "女性" )
                message_vision(CYN"胡大夫大笔一挥就改了$N的芳名！真爽呆了....\n"NOR,me);
        else message_vision(CYN"胡大夫大笔一挥就改了$N的大名...真神！\n"NOR,me);
        set("name", arg, me);

        return 1;
}

int do_betrayer(object me)
{
        me = this_player();
        if( !query_temp("marks/huqingyu", me) )
        {
                return notify_fail("胡庆余翻着黑白眼：钱呢？没给钱想占便宜？\n");
        }

        delete_temp("marks/huqingyu", me);
        if( query("combat_exp", me)<10000 )
                return notify_fail("真冤枉！你的经验还可以随便叛师的！\n");

        set("betrayer",query("betrayer",  me)+1, me);
        set("title", "普通百姓", me);
        set("class", "0", me);
        delete("family", me);
        message_vision(CYN"胡大夫笑道：江湖上海阔天空，都是$N的天地了！不过，你的叛师记录也多了一次！\n"NOR,me);
        command("sigh");
        return 1;
}

int do_age(object me)
{
        object obj;
        me = this_player();

        return notify_fail("胡庆余翻着黑白眼：死生有命，你也别太在意了！\n");
        if( !query_temp("marks/huqingyu", me) )
        {
                return notify_fail("胡庆余翻着黑白眼：钱呢？没给钱想占便宜？\n");
        }
        delete_temp("marks/huqingyu", me);

        if( query("age", me)<21 )
        {
//                obj=new("/clone/money/gold");
//                obj->set_amount(100);
//                obj->move(me);
                return notify_fail("胡大夫道：你还很年轻的，这一百两黄金就送老夫白花了！\n");
        }

        addn("mud_age", -86400, me);
        addn("age", -1, me);
        delete("last_slp", me);
        delete("jingzuo_time", me);
        log_file("CHANGEAGE",sprintf("%sat%s:%d\n",query("id", me),ctime(time()),query("age", me)));
        message_vision(CYN"胡大夫道：果然有钱能使鬼推磨，$N现在看是年轻多了！\n"NOR,me);
        return 1;
}
*/
