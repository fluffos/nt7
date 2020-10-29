// This program is a part of NT MudLIB
// lu.c 陆乘风

#include <ansi.h>
#include "taohua.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();

string ask_me();
int    ask_xfsy();

void create()
{
        set_name( "陆乘风" ,({ "lu chengfeng", "lu", "chengfeng" }));
        set("gender", "男性");
        set("nickname", HIC "归云庄主" NOR);
        set("age", 52);
        set("long", "陆乘风是黄药师的第四个徒弟。他的鬓角已微见白发，但\n"
                    "身材魁梧，双眼有神。\n");
        set("attitude", "friendly");
        set("class", "scholar");
        set("str", 24);
        set("int", 30);
        set("con", 25);
        set("dex", 21);

        set("max_qi", 4500);
        set("max_jing", 2500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 120);
        set("combat_exp", 1000000);
        set("bagua_count", 5);
        set("yulu_count", 5);

        set_skill("force", 200);
        set_skill("bibo-shengong", 200);
        set_skill("unarmed", 200);
        set_skill("xuanfeng-tui", 200);
        set_skill("strike", 200);
        set_skill("luoying-shenzhang", 200);
        set_skill("finger", 180);
        set_skill("tanzhi-shentong", 180);
        set_skill("dodge", 180);
        set_skill("luoying-shenfa", 180);
        set_skill("parry", 180);
        set_skill("sword", 200);
        set_skill("luoying-shenjian", 200);
        set_skill("whip", 180);
        set_skill("canglang-bian", 180);
        set_skill("literate", 180);
        set_skill("qimen-wuxing", 160);
        set_skill("calligraphy", 160);
        set_skill("martial-cognize", 160);

        map_skill("force", "luoying-xinfa");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike", "luoying-shenzhang");
        map_skill("finger", "tanzhi-shentong");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "luoying-shenjian");
        map_skill("whip", "canglang-bian");
        map_skill("sword", "luoying-shenjian");

        prepare_skill("unarmed", "xuanfeng-tui");
        prepare_skill("strike", "luoying-shenzhang");

        create_family("桃花岛", 2, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sui" :),
                (: perform_action, "strike.wuxing" :),
                (: perform_action, "unarmed.kuang" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set("inquiry", ([
                "东邪"   : "家师人称东邪！呵呵。",
                "西毒"   : "欧阳锋是与家师并世齐名的高手，人称老毒物。",
                "南帝"   : "听家师说段王爷现在出家当了和尚，法名一灯。",
                "北丐"   : "北丐洪七公是丐帮帮主，现在扬州城外。",
                "黄蓉"   : "她是师父的爱女。",
                "梅超风" :"这贼婆娘害得我好苦。她不要脸偷汉，那也罢了，干吗要偷师父的《九阴真经》？",
                "陈玄风" :"他和梅超风都是师门叛徒，有何好说？这两人害得我好苦！我半身不遂，就是拜受这两人之赐。",
                "曲灵风" :"灵风师兄专于武技，不过育有一女，不知如今下落如何？",
                "冯默风" :"你可持桃花本门信物前往寻找默风，冯师弟天性淡泊，但外和内刚，恐怕需用非常手段才能逼他表露身份．．．",
                "黄药师" : "当年师父一怒之下，将我们师兄弟四人一齐震断脚筋，逐出桃花岛。",
                "桃花岛" : (: ask_me :),
                "巨浪滔天" : (: ask_skill1 :),
                "狂风绝技" : (: ask_skill2 :),
                "风雷四神剑" : (: ask_skill3 :),
                "旋风扫叶腿" : (: ask_xfsy :),
        ]));
        set("master_ob", 4);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian");
}

void init()
{
        ::init();
        add_action("do_recite", "recite");
}

void attempt_apprentice(object ob)
{
        string master;
        if (! permit_recruit(ob))
                return;
        /*
        if( stringp(master=query_temp("taohua/master", ob)) )
        {
                if (master != name())
                {
                        command("say 家师不是让你拜" + master + "的吗？你怎么来"
                                "找我来了？");
                        return;
                }

                command("say 好吧，既然家师有令，我就收下你了，不过要好好遵守桃"
                        "花岛的规矩。");
                command("recruit "+query("id", ob));
                delete_temp("taohua/master", ob);
                return;
        }

        command("shake");
        command("say 我可不敢擅自收徒，你还是找家师黄岛主吧！");
        */
        if( query_temp("pending/recite", ob) )
        {
                command("say 你粗鄙不文，见识浅薄，本庄主怎会收你？");
                return;
        } else
        {
                command("say 一位异人曾在本庄花厅留诗半阙，如果你能补全，也不枉来归云庄一遭");
                message_vision("陆庄主凝视着$N，说道：快把你的下阙大声朗诵(recite)出来吧。\n",
                               this_player());
                set_temp("pending/recite", 1, ob);
        }
}

int do_recite(string arg)
{
        string name, new_name, ttt;

        if( !query_temp("pending/recite", this_player()) )
                return 0;

        if (! arg)
                return notify_fail("你说什么？\n");

        set_temp("pending/recite", 0, this_player());

        message_vision("$N大声说道：" + arg + "\n", this_player());

        if (arg == "无人争晓渡残月下寒沙")
        {
                command("smile");
                if( query("gender", this_player()) == "男性" )
                        ttt = "门生";
                else
                if( query("gender", this_player()) == "女性" )
                        ttt = "青衣";
                else
                {
                        command("sigh");
                        command("say " + "卿本佳人，奈何自宫，本庄与东厂概无关联，你去吧！");
                        return 0;
                }
                command("say " + "好！好！" + RANK_D->query_respect(this_player()) +
                        "果然博闻强记。敝人就收你做个" + ttt +"吧。");

                command("recruit "+query("id", this_player()));
                set("title", "归云庄"+ttt, this_player());
        } else
        {
                command("say 你这白丁，待在这里，没的脏了我的屋子！");
        }
        return 1;
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] !="桃花岛")
                return RANK_D->query_respect(this_player()) +
                       "与敝庄素无来往，不知此话从何谈起？";

        if (query("bagua_count") < 1)
                return "今天我太累了，有什么事明天再说吧。";

        if( present("tie bagua",this_player()) || query_temp("get_bagua", this_player()) )
                return "现在你可以上桃花岛试一试，看有没有福份见到我师傅。";

        if (this_player()->query_skill("qimen-wuxing", 1) < 60 ||
        this_player()->query_skill("bibo-shengong", 1) < 60)
                return "桃花岛上机关重重，你功夫不够，还是不去为妙。";

        addn("bagua_count", -1);
        ob = new("/d/taohua/obj/bagua");
        ob->move(this_player());
        set_temp("get_bagua", 1, this_player());

        message_vision("陆乘风递给$N一块铁八卦。\n", this_player());
        return "上岛之后千万小心，万事靠自己，我也帮不上什么忙了。";
}
/*
mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/pikong-zhang/dai", me) )
                return "这一招我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，问这个干嘛？";

        if (me->query_skill("pikong-zhang", 1) < 1)
                return "你连劈空掌都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<80 )
                return "师父吩咐过，不传功给无功劳的弟子。";

        if (me->query_skill("force") < 120)
                return "你的内功修为不够，还是多锻炼锻炼吧。";

        if (me->query_skill("pikong-zhang", 1) < 80)
                return "你的劈空掌还不够熟练，练高了再来找我。";

        message_sort(HIY "\n$n" HIY "对着$N" HIY "点了点头，说道：“我给你演示"
                     "一遍，可看仔细了！”话音刚落，顿时只见$n" HIY "双掌交叠云"
                     "贯而出，激荡出无数圈劲气，一环环向$N" HIY "斫去，招数当真"
                     "精奇无比。\n\n" NOR, me, this_object());

        command("smile");
        command("say 招式便是如此，你自己下去体会吧。");
        tell_object(me, HIC "你学会了「披星戴月」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("pikong-zhang"))
                me->improve_skill("pikong-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/pikong-zhang/dai", 1, me);
        addn("family/gongji", -80, me);

        return 1;
}
*/

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/canglang-bian/lang", me) )
                return "这一招我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，问这个干嘛？";

        if (me->query_skill("canglang-bian", 1) < 1)
                return "你连沧浪鞭法都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<200 )
                return "师父吩咐过，不传功给无功劳的弟子。";

        if (me->query_skill("force") < 120)
                return "你的内功修为不够，还是多锻炼锻炼吧。";

        if (me->query_skill("canglang-bian", 1) < 80)
                return "你的沧浪鞭法还不够熟练，练高了再来找我。";

        message_sort(HIY "\n$n" HIY "对着$N" HIY "点了点头，说道：“我给你演示"
                     "一遍，可看仔细了！”话音刚落，顿时只见$n" HIY "手中长鞭"
                     "如巨浪连绵无穷无尽攻向虚空，真精奇无比。\n\n" NOR, me,
                     this_object());

        command("smile");
        command("say 招式便是如此，你自己下去体会吧。");
        tell_object(me, HIC "你学会了「巨浪滔天」。\n" NOR);
        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("canglang-bian"))
                me->improve_skill("canglang-bian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/canglang-bian/lang", 1, me);
        addn("family/gongji", -80, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/xuanfeng-tui/kuang", me) )
                return "这一招我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，问这个干嘛？";

        if (me->query_skill("xuanfeng-tui", 1) < 1)
                return "你连旋风扫叶腿都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<300 )
                return "师父吩咐过，不传功给无功劳的弟子。";

        if (me->query_skill("force") < 150)
                return "你的内功修为不够，还是多锻炼锻炼吧。";

        if (me->query_skill("xuanfeng-tui", 1) < 100)
                return "你的旋风扫叶腿还不够熟练，练高了再来。";

        message_sort(HIY "\n$n" HIY "点了点头，喝道：“看好了！”便在$n" HIY
                     "话音落下的一瞬间，早已拔地而起，陡然使出旋风扫叶腿狂风"
                     "绝技，身法变得飘忽不定，足带风尘，掌携万钧。招式连贯气"
                     "势恢弘，劲风只袭得$N" HIY "面庞隐隐生疼。\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 下去后可要勤加练习，莫辜负了恩师的一番栽培。");
        tell_object(me, HIC "你学会了「狂风绝技」。\n" NOR);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("xuanfeng-tui"))
                me->improve_skill("xuanfeng-tui", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuanfeng-tui/kuang", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/luoying-shenjian/fenglei", me) )
                return "这一招我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我们桃花岛的人，问这个干嘛？";

        if (me->query_skill("luoying-shenjian", 1) < 1)
                return "你连落英神剑都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<300 )
                return "师父吩咐过，不传功给无功劳的弟子。";

        if (me->query_skill("force") < 150)
                return "你的内功修为不够，还是多锻炼锻炼吧。";

        if (me->query_skill("luoying-shenjian", 1) < 100)
                return "你的落英神剑还不够熟练，练高了再来。";

        message_sort(HIY "\n$n" HIY "点了点头，喝道：“看好了！”便在$n" HIY
                     "话音落下的一瞬间，早已拔地而起，陡然使出「风雷四神剑」"
                     "绝技，高声长吟：“桃花影里飞神剑”，如风如雷般的发出数剑! "
                     "气势恢弘，劲风只袭得$N" HIY "面庞隐隐生疼。\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 下去后可要勤加练习，莫辜负了恩师的一番栽培。");
        tell_object(me, HIC "你学会了「风雷四神剑」。\n" NOR);
        if (me->can_improve_skill("force")) 
                me->improve_skill("force", 1500000); 
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("luoying-shenjian"))
                me->improve_skill("luoying-shenjian", 1500000);
        if (me->can_improve_skill("bibo-shengong")) 
                me->improve_skill("bibo-shengong", 1500000); 
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/luoying-shenjian/fenglei", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}
int accept_kill(object me)
{
        if( query("family/family_name", me) == "桃花岛" )
        {
                command("say 你我本是同门，如何要加害于我！\n");
                set("th_killer", 1, me);
                kill_ob(me);
                return 1;
        }
      return 1;
}

int accept_object(object me, object obj)
{
        call_out("accept_obj", 2, me, obj);
        return 1;
}

int accept_obj(object me, object obj)
{
        if (! me || ! obj) return 0;
        if( query("name", obj) == "旋风扫叶腿" )
        {
                command("ah");
                message_vision(CYN "$N双手颤抖的展开薄纸，仔仔细细的读了起来。\n", this_object());
                message_vision(CYN "$N一边读，一边热泪盈眶！\n", this_object());
                command("cry");
                command("say 多谢"+ RANK_D->query_respect(me) +"了。\n");
                set("xfsy_xinfa_reading", 1);
                set("xfsy_xinfa_accept", 1);
                if( query("family/family_name", me) == "桃花岛" )
                        set("help_chengfeng", 1, me);
        }
        call_out("finish_reading", 100 + random(50), obj);
        return 1;
}

void finish_reading(object obj)
{
        delete("xfsy_xinfa_reading");
        destruct(obj);
}

int ask_xfsy()
{
        object me, obj;

        me = this_player();
        if (query("xfsy_xinfa_reading"))
        {
                command("say 对不住，我还没读完恩师所传心法．");
                return 1;
        }

        if( query("family/family_name", me) == "桃花岛"
        &&  query("xfsy_xinfa_accept"))
        {
                obj = new("/d/taohua/obj/xfsy_xinfa2");
                obj->move(me);
                command("say 这套心法我做了一些注解，"+RANK_D->query_respect(me) +
                        "可拿回去自行参悟。");

                message_vision("$N递给$n一张薄纸。\n",this_object(),me);
                delete("xfsy_xinfa_accept");
        } else
                command("say 旋风扫叶腿心法已不在我这里。");

        return 1;
}
