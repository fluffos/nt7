// This program is a part of NT MudLIB
// zhangwuji.c

#include <ansi.h>
#include "mingjiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_jiuyang();
mixed ask_qiankun();
mixed ask_ling();

string ask_book();
string ask_qishang();

int ask_hu_quest();
int ask_hu();
int ask_hdg();
void destroy(object ob);
void restart(object me, object ob);

void create()
{
        seteuid(getuid());
        set_name("张无忌", ({ "zhang wuji", "zhang", "wuji" }));
        set("long", @LONG
明教教主张无忌，统领天下十万教众，豪气干云，叱咤千秋，
「九阳神功」、「乾坤大挪移」独步天下，是江湖中不世出的
少年英雄。
LONG );
        set("title",HIG "明教" HIM " 教主" NOR);
        set("gender", "男性");
        set("age", 20);
        set("no_get", 1);
        set("shen_type",1);
        set("attitude", "friendly");
        set("class", "fighter");

        set("str", 33);
        set("int", 35);
        set("con", 38);
        set("dex", 33);

        set("qi", 5800);
        set("max_qi", 5800);
        set("jing", 2700);
        set("max_jing", 2700);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 120);
        set("level", 50);
        set("combat_exp", 2900000);
        set("score", 455000);
        set("book_count", 1);

        set_skill("force", 600);
        set_skill("unarmed", 600);
        set_skill("dodge", 600);
        set_skill("parry", 600);
        set_skill("cuff", 600);
        set_skill("sword", 600);
        set_skill("blade", 600);
        set_skill("strike", 600);
        set_skill("claw", 600);
        set_skill("throwing", 600);
        // set_skill("duoming-jinhua", 450);
        set_skill("jiuyang-shengong", 600);
        set_skill("shenghuo-xinfa", 600);
        set_skill("shenghuo-shengong", 600);
        set_skill("lingxu-bu", 600);
        set_skill("shenghuo-bu", 600);
        set_skill("qingfu-shenfa", 600);
        set_skill("qiankun-danuoyi", 600);
        set_skill("qishang-quan", 600);
        set_skill("taiji-quan", 600);
        set_skill("taiji-jian", 600);
        set_skill("taiji-dao", 600);
        set_skill("lieyan-dao", 600);
        set_skill("liehuo-jian", 600);
        // set_skill("yingzhua-shou", 450);
        // set_skill("hanbing-mianzhang", 450);
        set_skill("shenghuo-ling", 600);
        set_skill("guangming-zhang", 600);
        set_skill("medical", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);
        set_skill("guangming-jing", 600);

        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "qingfu-shenfa");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("strike","guangming-zhang");
        map_skill("cuff", "qishang-quan");
        map_skill("sword","shenghuo-ling");
        map_skill("parry","qiankun-danuoyi");
        map_skill("blade","taiji-dao");
        // map_skill("claw", "yingzhua-shou");
        // map_skill("throwing", "duoming-jinhua");
        // map_skill("strike", "hanbing-mianzhang");

        prepare_skill("cuff", "qishang-quan");

        set("inherit_title",HIG"明教"HIY"光明使者"NOR);
        create_family("明教", 34, "教主");

        set("no_teach", ([
                "jiuyang-shengong"  : "这个我可不能传你。",
                "taiji-jian"        : "你还是找我太师父吧！",
                "taiji-quan"        : "你还是找我太师父吧！",
                "taiji-dao"         : "你还是找我太师父吧！",
                "qishang-quan"      : "想学七伤拳你还是找我义父谢逊吧！",
                "qiankun-danuoyi"   : "乾坤大挪移只有明教教主方能修炼，难道你想做教主？",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform sword.hua") :),
                (: command("perform sword.xi") :),
                (: command("perform sword.lian") :),
                (: command("perform sword.can") :),
                (: command("perform cuff.shang") :),
                (: command("perform cuff.fei") :),
                (: command("yun shield") :),
                (: command("yun powerup") :),
                (: command("yun recover") :),
        }) );

        set("chat_chance", 2);
        set("chat_msg",({
                "张无忌愤然说道“大丈夫当以国为家, 捐躯沙场, 抗元大业未成, 同辈仍需努力!”\n",
                "张无忌叹道“人生失一知己, 生亦何欢, 死亦何忧, 敏儿, 你在哪里?”\n",
                "张无忌道“我教兄弟听了: 生于乱世, 当克己为公, 行侠仗义, 荡寇驱魔!”\n",
        }));

        set("inquiry",([
                "明教"     : "你打听我们明教做什么？。\n",
                "金毛狮王" : "那是我义父谢大侠的职司。\n",
                "谢逊"     : "他就是我义父的大号。\n",
                "张翠山"   : "你想找我父亲有事麽? \n",
                "殷素素"   : "我妈是明尊座下紫微堂主。\n",
                "张三丰"   : "我太师父近来可好? \n",
                "赵敏"     : "人生失一知己, 生亦何欢, 死亦何忧, 敏儿, 你在哪里?\n",
                "小昭"     : "小昭我可一直念着她的好处。\n",
                "周芷若"   : "找她就去峨嵋山, 别来烦我。\n",
                "九阳秘籍" : (: ask_jiuyang :),
                "铁焰令"   : (: ask_ling :),
                "乾坤大挪移" : (: ask_qiankun :),
                "鲜于通"   : (: ask_hu_quest :),
                "胡青牛"   : (: ask_hu :),
                "蝴蝶谷"   : (: ask_hdg :),
                "七伤拳经" : (: ask_qishang :),
                "秘籍"     : (: ask_book :),

        ]));
        set_temp("apply/attack", 180);
        set_temp("apply/damage", 180);
        set_temp("apply/unarmed_damage", 180);
        set_temp("apply/armor", 180);

        set("master_ob",5);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        // carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/book/shenghuo-ling")->wield();
        add_money("silver",70);
}

void init()
{
        object ob;

        ::init();

        if( interactive(this_player()) && query_temp("fighting", this_player()) )
        {
                COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon") );
                addn_temp("beat_count", 1, this_player());
        }
        if( interactive(ob=this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting",1,ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob)!=environment()) return;
        if( query("shen", ob)<-50000 )
        {
                command("wield yitian jian");
                command("hit"+query("id", ob));
                command("unwield yitian jian");
        } else
        if( query("shen", ob)<-5000 )
        {
                command("say 魔从心起，于武学不利，其道必诛，劝君放下屠刀，"
                        "立地成佛。");
        } else
        if( query("shen", ob)<-100 )
        {
                command("say 这位朋友，人行江湖，言行当正，切务走进邪魔歪道。");
        } else
        if( query("shen", ob) >= 0 )
        {
                command("say 光明正道任人走，劝君多加保重。");
        } else
        if( query("shen", ob)>50000 )
        {
                command("say 大侠在上，受无忌一礼，大侠它日必为武林翘楚。");
        }
        return;
}

int accept_fight(object ob)
{
        if( query("combat_exp", ob)<30000 && query("shen", ob)>0 )
        {
                message_vision("武林中人最忌争强斗狠，你不是我的对手，"
                               "回去吧。\n",ob);
                return 0;
        }
        message_vision("张无忌一拱手说道：这位" + RANK_D->query_respect(ob) +
                       "，在下领教了。\n", ob);
        return 1;
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam = query("family", me);

        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "明教" )
        {
                command("say " + RANK_D->query_respect(ob) + "与本教素无来往，不知此话从何谈起？");
                return;
        }

        if ( ob_fam["generation"] > my_fam["generation"] + 2)
        {
                command("say " + RANK_D->query_respect(ob) + "，你先去找教内其他兄弟好好学学武功吧。");
                return;
        }

        if( query("shen", ob)<90000 )
        {
                command("say 你行侠仗义的事做得还不够，还是请回吧。");
                return;
        }

        if( query("combat_exp", ob)<1000000 )
        {
                command("say 你的经验太少，好好再去江湖闯荡闯荡，可别给我明教丢脸啊 !");
                return;
        }

        command("say 恩，好！本教又培养出一位江湖高手，真是可喜可贺 !");

        command("say 恭喜你荣升为明教光明使者！");
        command("recruit "+query("id", ob));

        return;
}

int accept_object(object who, object ob)
{
        int r;
        object me;
        mapping fam;

        me = this_object();
        fam=query("family", who);

        if (playerp(ob))
                return 0;

        if (r = ::accept_object(who, ob))
                return r;

          if( query("id", ob) == "jin mao" )
        {
                tell_object(who, GRN "张无忌激动地说道：你找到我的义父了。\n" NOR);
                if( !query_temp("marks/义父", who) )
                        set_temp("marks/义父", 1, who);
                remove_call_out("destrory");
                call_out("destrory", 1, ob);
                return 1;
        }
          if( query("id", ob) == "shenghuo ling" )
        {
                if (! (fam) || fam["family_name"] != "明教")
                {
                        command("thank"+query("id", who));
                        command("say 多谢你为本教找回了圣物，不知我应该怎么谢谢你？\n");
                        call_out("destroy", 1, ob);
                        return 1;
                }
                if (fam["family_name"] == "明教"
                     && (fam["master_name"] != "张无忌" || query_temp("mj_jiaozhu", who)) )
                {
                        command("nod"+query("id", who));
                        command("say 你为本教找回了圣物，这笔功劳不小啊！\n");
                        call_out("destroy", 1, ob);
                        addn("shen", 2000, who);
                        addn("combat_exp", 100+random(50), who);
                        tell_object(who,HIW"你被奖励了一些正神和经验值。\n"NOR);
                        return 1;
                }
                if( query("mj_jiaozhu", me) )
                {
                        command("pat"+query("id", who));
                        command("say 不错不错，但有人已经比你先找到了。\n");
                        return 0;
                }
                command("ah"+query("id", who));
                command("say 你竟找回了本教圣物，不愧是我的弟子！");
                command("say 上代阳教主有遗命，寻回圣物者当可修习本教神功，你去秘道中试试吧。");
                set_temp("mj_jiaozhu", 1, who);
                set("mj_jiaozhu", 1, me);
                call_out("destroy", 1,  ob);
                remove_call_out("restart");
                call_out("restart", 3600, me, ob);
                return 1;
        } else
                return 0;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "烈火三绝剑" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liehuo-jian/jue",
                           "name"    : "烈火三绝剑",
                           "sk1"     : "liehuo-jian",
                           "lv1"     : 100,
                           "neili"   : 1000,
                           "gongxian": 400,
                           "shen"    : 50000, ]));
                break;

        case "吸焰令" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/xi",
                           "name"    : "吸焰令",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 140,
                           "neili"   : 2000,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        case "敛心令" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/lian",
                           "name"    : "敛心令",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;
        case "光华令" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/hua",
                           "name"    : "光华令",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 160,
                           "neili"   : 2400,
                           "gongxian": 900,
                           "shen"    : 80000, ]));
                break;
        case "残血令" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenghuo-ling/can",
                           "name"    : "残血令",
                           "sk1"     : "shenghuo-ling",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "九曦混阳" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/jiu",
                           "name"    : "九曦混阳",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "混沌一阳" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/hun",
                           "name"    : "混沌一阳",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "骄阳劈天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/pi",
                           "name"    : "骄阳劈天",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "金阳破岭" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/po",
                           "name"    : "金阳破岭",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "魔光日无极" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/ri",
                           "name"    : "魔光日无极",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "极境" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyang-shengong/ji",
                           "name"    : "极境",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 10000,
                           "shen"    : 100000, ]));
                break;
        case "驾御兵器" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_learn/jiuyang-shengong/enable_weapon",
                           "name"    : "驾御兵器",
                           "sk1"     : "jiuyang-shengong",
                           "lv1"     : 220,
                           "neili"   : 5000,
                           "force"   : 350,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "大挪移" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qiankun-danuoyi/yi",
                           "name"    : "大挪移",
                           "sk1"     : "qiankun-danuoyi",
                           "lv1"     : 200,
                           "neili"   : 5000,
                           "force"   : 200,
                           "gongxian": 1000,
                           "shen"    : 100000, ]));
                break;
        case "挪转乾坤" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qiankun-danuoyi/nuozhuan",
                           "name"    : "挪转乾坤",
                           "sk1"     : "qiankun-danuoyi",
                           "lv1"     : 1000,
                           "neili"   : 5000,
                           "force"   : 1000,
                           "gongxian": 3000,
                           "reborn"  : 1,
                           "shen"    : 100000, ]));
                break;
        default:
                return 0;
        }
}

mixed ask_jiuyang()
{
        mapping fam;
        object ob;
        object me = this_player();

        if( !(fam=query("family", this_player())) || fam["family_name"] != "明教" )
                return RANK_D->query_respect(this_player()) + "与本教素无来往，不知此话从何谈起？";

        if( !query_temp("marks/义父", this_player()) )
                return "你如果能帮我找到我的义父谢逊，那还可以考虑！";

        if( query("jiuyang/zhang", me) )
                return "你知道“经在油中”此话的含义了么？";

        set("jiuyang/zhang", 1, me);
        return "想当年太师傅在少林曾听闻昆仑派“昆仑三圣”何足道带话到少林说“经在油中”，\n"+
               "不知道此话有何含义。";
}

/*
mixed ask_ling()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player()) )
                || fam["family_name"] != "明教")
                return RANK_D->query_respect(this_player()) +
                       "与本教素无来往，要这个是何居心？\n";

        if (this_player()->query_skill("shenghuo-ling", 1) < 100)
                return "你的圣火令法造诣太浅，要去也没用的！\n";

        if (this_player()->query_skill("qiankun-danuoyi", 1) < 100)
                return "你的乾坤大挪移心法造诣太浅，圣火令给你我可不太放心！\n";

   ob = new("/d/mingjiao/obj/tieyanling");
        ob->move(this_player());
        message_vision("$N要得一面铁焰令。\n",this_player());

        return "好吧，凭这面铁焰令，你可自由向你的尊长挑战。";
}
*/
mixed ask_ling()
{
        mapping family, skl;
        string *sname;
        object ob;
        int i;

        if( !(family=query("family", this_player())) || family["family_name"] != "明教" )
                return RANK_D->query_respect(this_player()) + "与本教素无来往，不知此话从何谈起？";

        skl = this_player()->query_skills();
        sname  = sort_array( keys(skl), (: strcmp :) );

        for(i=0; i<sizeof(skl); i++)
        {
                if (skl[sname[i]] < 30)
                return RANK_D->query_respect(this_player()) +
                "功力不够，不能领取铁焰令。";
        }

        ob = new("d/mingjiao/obj/tieyanling");
        ob->move(this_player());
        message_vision("$N要得一面铁焰令。\n",this_player());

        return "好吧，凭这面铁焰令，你可自由向你的尊长挑战。";

}

mixed ask_qiankun()
{
        object obj,me;
        me = this_player();

        if (this_player()->query_skill("shenghuo-shengong", 1)<100)
        {
                command("say " + RANK_D->query_respect(me) + "似乎圣火神功修为还不够。");
                return 1;
        }
        if( query("combat_exp", this_player())<800000 )
        {
                command("say " + RANK_D->query_respect(me) + "似乎实战经验还不够。");
                return 1;
        }
        if (this_player()->query_skill("force", 1) < 100)
        {
                command("say " + RANK_D->query_respect(me) + "似乎基本内功修为还不够。");
                return 1;
        }
              if( query_temp("marks/挪移", this_player()) )
              {
                command("say 你不是刚刚才问过吗？");
                return 1;
        }
        else
        {
                command("say 好吧，我就准许你进入秘室修炼乾坤大挪移。以后你要发扬光大明教。");
                // command("say 你到张中前辈那里去就说是我准许的。");
                command("pat"+query("id", me));
                command("addoil"+query("id", me));
                set_temp("marks/挪移", 1, this_player());
                return 1;
        }

}

int ask_hu_quest()
{
        object me = this_player();
        if( query_temp("hu/quest1", me) != 2 )
        {
                command("say 怎么突然提起他做什么？");
                return 1;
        } else
        {
                command("say 原来胡先生还健在？");
                command("jump");
                command("say 我帮胡先生狠狠的骂了这个家伙一顿，而且他也自己中了自己的毒死了。");
                command("say 胡先生若是能亲自看到，想必会很高兴。");
                set_temp("hu/quest1", 3, me);
                return 1;
        }
}

int ask_hu()
{
        object me = this_player();

        if( !query_temp("hu/quest2", me) )
        {
                command("say 胡青牛先生号称蝶谷医仙，医术一流，不过脾气有点怪。");
                return 1;
        } else
        {
                command("ah");
                command("say 真是对不住，最近明教将要起事，我实在抽不出身。");
                command("say 麻烦了你三番两此帮忙胡先生送口信。");
                command("say 请告诉他，无忌安好，并且请他小心身子。");
                command("say 这个铁炎令你拿去，让胡先生看看吧。");
                me->apply_condition("hu_quest", 5);
                new("/d/mingjiao/obj/tieyan")->move(me);
                return 1;
        }
}

int ask_hdg()
{
        object me = this_player();
        command("say 蝴蝶谷是胡青牛神医的居所。");
        command("say 那在长江南岸附近，跟着蝴蝶就能找到了。");
        set_temp("hdg", 1, me);
        return 1;
}

string ask_qishang()
{
        mapping fam;
        object me = this_player();

        fam=query("family", me);
        if (! fam || fam["family_name"] != "明教" || fam["master_name"] != "张无忌")
                return "嗯....这我可不清楚，你最好问问别人吧。";

        if( query("can_perform/xiexun/qishang", me) )
                return "咦，义父不是已经把七伤拳的拳理教了你吗？\n";

        if( query_temp("marks/七伤", me) )
                return "咦，我不是叫你出海去拜访我义父谢狮王了吗？\n";

        // me->set("luopan/bhd");
        set_temp("marks/七伤", 1, me);

        command("hmm");
        command("whisper"+query("id", me)+"我义父在极北冰火岛上，大概位于黄道带以北九百五十、以东二百个距离的地方。");
        // new("/d/mingjiao/obj/luopan")->move(this_object());
        // command("give luo pan to " + me->query("id"));
        return "这七伤拳，是当年我义父亲自传我的绝技，你如果真有信心和毅力，就出海去拜访我义父吧！\n";
}

string ask_book()
{
        mapping fam;
        object me = this_player();

        fam=query("family", me);
        if (! fam || fam["family_name"] != "明教" || fam["master_name"] != "张无忌")
                return "我有一本太极拳经，是当年我武当的太师父送给我的。";

        set_temp("marks/秘1", 1, me);
        return "我有一本太极拳经，是当年我武当的太师父送给我的，现我交张散人了。";
}

void destroy(object ob)
{
        if (ob) destruct(ob);
}

void restart(object me, object ob)
{
        if( query("mj_jiaozhu", me) )
                delete("mj_jiaozhu", me);

        if (ob) destruct(ob);
}

/*
void unconcious()
{
        die();
}
*/
