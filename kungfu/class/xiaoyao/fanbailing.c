// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("范百龄", ({ "fan bailing", "fan", "bailing" }));
        set("long", "他是苏星河的二弟子，通晓棋技。\n");
        set("gender", "男性");
        set("title", "逍遥派函谷八友");
        set("nickname", HIR "棋迷" NOR);
        set("age", 53);
        set("class", "shaman");
        set("attitude", "peaceful");
        set("str", 25);
        set("int", 27);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 2800);
        set("max_jing", 2800);
        set("neili", 3600);
        set("max_neili", 3600);
        set("jiali", 100);
        set("level", 10);
        set("combat_exp", 1200000);

        set_skill("force", 180);
        set_skill("xiaowuxiang", 180);
        set_skill("dodge", 160);
        set_skill("feiyan-zoubi", 160);
        set_skill("strike", 160);
        set_skill("liuyang-zhang", 160);
        set_skill("hand", 160);
        set_skill("qingyun-shou", 160);
        set_skill("parry", 160);
        set_skill("blade", 160);
        set_skill("ruyi-dao", 160);
        set_skill("chess", 240);
        set_skill("literate", 160);
        set_skill("martial-cognize", 160);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "qingyun-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "liuyang-zhang");
        map_skill("blade", "ruyi-dao");

        prepare_skill("hand", "qingyun-shou");
        prepare_skill("strike", "liuyang-zhang");

        create_family("逍遥派", 3, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhuo" :),
                (: perform_action, "strike.pan" :),
                (: exert_function, "recover" :),
        }));
        set("inquiry", ([
                "棋谱":(:ask_me:),
        ]) );
        set("book_count", 1);
        set("master_ob", 3);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 27)
        {
                command("sigh");
                command("say 学习棋道要求悟性极高之人，我看你并不适合。");
                return;
        }

        if (ob->query_skill("xiaowuxiang", 1) < 30)
        {
                command("sigh");
                command("say 你连本门的入门心法都没有学好，教我如何收你？");
                return;
        }

        command("say 好吧，既然如此，我就收下你了。");
        command("recruit "+query("id", ob));
}

string ask_me()
{
        object me,ob;
        ob=this_player();
        if (query("book_count") < 1)
                return "你来晚了，棋谱我已经赠送给别入了。";

        addn("book_count", -1);
        command("say 好吧，那我就把它送给你了。\n");
        message_vision(HIY"范百龄微笑着从怀中拿出了一本书，交了给$N\n\n"NOR,ob);
        me=new("/clone/book/hand_book");
        me->move(ob);
        return "这本棋谱可千万不要随便给别人。\n";
}
