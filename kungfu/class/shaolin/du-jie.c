// dujie.c

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#define HEISUO          "/clone/lonely/heisuo3"
#define JINLAN          "/clone/lonely/jinlan"

mixed ask_me();
mixed ask_jia();

void create()
{
        object ob1, ob2;
        set_name("渡劫", ({ "du jie", "jie" }) );
        set("title", "少林长老");
        set("gender", "男性");
        set("age", 90);
        set("long",
                "这是一个面颊深陷，瘦骨零丁的老僧，他脸色惨白，象一张纸一样。\n");

        set("attitude", "peaceful");
        set("class", "bonze");
        set("combat_exp", 2300000);

        set("str", 32);
        set("int", 30);
        set("con", 33);
        set("dex", 31);

        set("qi", 5000);
        set("max_qi", 2500);
        set("neili", 6700);
        set("max_neili", 6700);
        set("level", 40);
        set("jiali", 90);

        create_family("少林派", 35, "弟子");
        assign_apprentice("弟子", 0);

        set_skill("buddhism", 250);
        set_skill("force", 255);
        set_skill("whip", 255);
        set_skill("parry", 250);
        set_skill("dodge", 240);

        set_skill("hunyuan-yiqi", 255);
        set_skill("shaolin-xinfa", 255);
        set_skill("riyue-bian", 255);
        set_skill("shaolin-shenfa", 240);

        map_skill("force", "hunyuan-yiqi");
        map_skill("whip",  "riyue-bian");
        map_skill("parry", "riyue-bian");
        map_skill("dodge", "shaolin-shenfa");

        set_skill("finger", 250);
        set_skill("jingang-zhi", 250);
        set_skill("martial-cognize", 220);

        map_skill("finger", "jinggang-zhi");

        prepare_skill("finger", "jingang-zhi");

        set_skill("medical", 200);
        set_skill("shaolin-yishu", 200);

        set("inquiry", ([
                "金刚罩"     : (: ask_me :),
                "锦襕袈裟"   : (: ask_jia :),
                "袈裟"       : (: ask_jia :),
        ]));

        set("master_ob",4);
        setup();

        if (clonep())
        {
                ob1 = find_object(HEISUO);
                if (! ob1) ob1 = load_object(HEISUO);
                if (! environment(ob1))
                {
                        ob1->move(this_object());
                        ob1->wield();
                } else
                {
                        ob1 = new("/d/shaolin/obj/changbian");
                        ob1->move(this_object());
                        ob1->wield();
                }

                ob2 = find_object(JINLAN);
                if (! ob2) ob2 = load_object(JINLAN);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wear();
                } else
                {
                        ob2 = new("/d/shaolin/obj/xuan-cloth");
                        ob2->move(this_object());
                        ob2->wear();
                }
        }
}

mixed ask_me()
{
        mapping fam;
        object ob;

        if( !query_temp("valid_in_fumoquan", this_player()) )
        {
                command("say 大胆鼠辈，乳臭未干，竟敢偷入金刚伏魔圈，且让老衲来超度与你！");
                kill_ob(this_player());
                return 1;
        }

        if( query_temp("valid_in_fumoquan", this_player()) != 1 )
        {
                command("heng");
                return 1;
        }

        if (present("jingang zhao", this_player()))
                return RANK_D->query_respect(this_player()) +
                "宝罩只有一件，而且就在你身上，真是贪得无餍！";

        if (present("jingang zhao", environment()))
                return RANK_D->query_respect(this_player()) +
                "宝罩只有一件，而且就在这里任你取走，真是贪得无餍！";

        ob = get_object("/d/shaolin/obj/jingang-zhao");
        if (! ob || environment(ob) && environment(ob) != this_object())
                return "抱歉，你来晚了，金刚罩已经给人取走了。";

        ob->move(this_player());

        message_vision("\n渡劫一声不吭地瞧了$N半饷，扭过身，从树洞里取出金刚罩递给$N。\n\n", this_player());

        return "你能挨我们三个老不死的三招日月神鞭不死，确实是命大，这件金刚罩就是你的了！";
}

mixed ask_jia()
{
        object ob;
        object me;
        object owner;

        me = this_player();

        if( !query_temp("valid_in_fumoquan", me) )
        {
                command("say 大胆鼠辈，竟敢偷入金刚伏魔圈，且让老衲来超度与你！");
                kill_ob(me);
                return 1;
        }

        if( query_temp("valid_in_fumoquan", me) != 1 )
        {
                command("heng");
                return 1;
        }

        if( query("combat_exp", me)<1000000 )
                return "你这点微末本事，打听达摩祖师留下的利器作甚？";

        ob = find_object(JINLAN);
        if (! ob) ob = load_object(JINLAN);

        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "东西不已经给你了么？你还打算怎的？";

        if (owner == environment(me))
        {
                command("sneer");
                command("get"+query("id", ob));
                return "百年来还没人敢愚弄老衲，滚开！";
        }

        if (objectp(owner) && owner != this_object())
                return "此时锦襕袈裟并不在老衲手中。";

        ob->move(this_object());

        command("disapp1");
        command("give jinlan jiasha to "+query("id", me));

        if (! query_temp("armor/cloth"))
        {
                ob = new("/d/shaolin/obj/xuan-cloth");
                ob->move(this_object());
                ob->wear();
        }
        return 1;
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

        case "合字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/riyue-bian/he",
                           "name"    : "合字诀",
                           "sk1"     : "riyue-bian",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "gongxian": 1000, ]));
                break;

        default:
                return 0;
        }
}

#include "/kungfu/class/shaolin/du.h"
