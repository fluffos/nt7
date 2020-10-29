// dunan.c

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#define HEISUO          "/clone/lonely/heisuo2"
#define CAOJIE          "/clone/lonely/caojie"

mixed ask_me();
mixed ask_cao();

void create()
{
        object ob1, ob2;
        set_name("渡难", ({ "du nan", "nan" }) );
        set("title", "少林长老");
        set("gender", "男性");
        set("age", 90);
        set("long",
                "这是一个面颊深陷，瘦骨零丁的老僧，他脸色漆黑，象是生铁铸成。\n");

        set("attitude", "peaceful");
        set("class", "bonze");
        set("combat_exp", 2500000);

        set("str", 33);
        set("int", 32);
        set("con", 34);
        set("dex", 31);

        set("qi", 5200);
        set("max_qi", 2600);
        set("neili", 7400);
        set("max_neili", 7400);
        set("level", 40);
        set("jiali", 100);

        create_family("少林派", 35, "弟子");
        assign_apprentice("弟子", 0);

        set_skill("buddhism", 300);
        set_skill("force", 260);
        set_skill("whip", 260);
        set_skill("parry", 260);
        set_skill("dodge", 250);

        set_skill("hunyuan-yiqi", 260);
        set_skill("shaolin-xinfa", 260);
        set_skill("riyue-bian", 260);
        set_skill("shaolin-shenfa", 250);

        map_skill("force", "hunyuan-yiqi");
        map_skill("whip",  "riyue-bian");
        map_skill("parry", "riyue-bian");
        map_skill("dodge", "shaolin-shenfa");

        set_skill("strike", 260);
        set_skill("xumishan-zhang", 260);
        set_skill("claw", 250);
        set_skill("hand", 250);
        set_skill("longzhua-gong", 250);
        set_skill("qianye-shou", 250);
        set_skill("martial-cognize", 220);

        map_skill("strike", "xumishan-zhang");

        prepare_skill("strike", "xumishan-zhang");

        set_skill("medical", 220);
        set_skill("shaolin-yishu", 220);

        set("inquiry", ([
                "菩提子"     : (: ask_me :),
                "神草结"     : (: ask_cao :),
        ]));

        set("count", 0);
        if (random(16) == 8) addn("count", 1);

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

                ob2 = find_object(CAOJIE);
                if (! ob2) ob2 = load_object(CAOJIE);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wear();
                }
        }
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
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

        if (uptime() < 1800)
                return "菩提子乃天地之灵物，制炼艰难无比，我现在可没有。";

        if ( present("puti zi", this_player()) )
                return RANK_D->query_respect(this_player()) +
                "菩提子只有一颗，而且就在你身上，真是贪得无餍！";

        if ( present("puti zi", environment()) )
                return RANK_D->query_respect(this_player()) +
                "菩提子只有一颗，而且就在这里任你取走，真是贪得无餍！";

        if (query("count") < 1)
                return "菩提子乃天地之灵物，采集艰难无比，我这里现在可没有。";

        ob = new("/d/shaolin/obj/puti-zi");
        ob->move(this_player());

        addn("count", -1);

        message_vision("\n渡难惨然一笑，接着长叹一声，从树洞里取出个白玉磁瓶，倒出菩提子递给$N。\n\n", this_player());

        return "我等昔年于佛祖座前发下宏愿，每十年遍访名山大川，历尽艰险，\n" +
               "方采得数颗菩提子，君乃有缘人，能得此造化奇物，望好自为之！";
}

mixed ask_cao()
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

        ob = find_object(CAOJIE);
        if (! ob) ob = load_object(CAOJIE);

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
                return "此时神草结并不在老衲手中。";

        ob->move(this_object());

        command("sigh");
        command("giveshencaojieto"+query("id", me));
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

        case "伤字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/riyue-bian/shang",
                           "name"    : "伤字诀",
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
