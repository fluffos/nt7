// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;

mixed ask_me();

void create()
{
        set_name("冯阿三", ({ "feng asan", "feng" , "asan"}));
        set("long", "据说他就是鲁班的后人，当代的第一巧匠。是\n"
                    "设计机关的能手。\n");
        set("title", "逍遥派函谷八友");
        set("nickname", HIY "巧匠" NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "friendly");
        set("class", "alchemist");
        set("shen_type", 1);
        set("str", 38);
        set("int", 28);
        set("con", 30);
        set("dex", 28);

        set("max_qi", 1800);
        set("max_jing", 1400);
        set("neili", 2200);
        set("max_neili", 2200);
        set("jiali", 70);
        set("level", 10);
        set("combat_exp", 500000);

        set_skill("force", 120);
        set_skill("xiaowuxiang", 120);
        set_skill("dodge", 120);
        set_skill("feiyan-zoubi", 120);
        set_skill("strike", 100);
        set_skill("liuyang-zhang", 100);
        set_skill("hand", 100);
        set_skill("qingyun-shou", 100);
        set_skill("parry", 120);
        set_skill("blade", 120);
        set_skill("ruyi-dao", 120);
        set_skill("literate", 100);
        set_skill("construction", 180);
        set_skill("martial-cognize", 100);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "qingyun-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "ruyi-dao");
        map_skill("blade", "ruyi-dao");

        prepare_skill("hand", "qingyun-shou");
        prepare_skill("strike", "liuyang-zhang");

        set("inquiry", ([
                "机关"   : (: ask_me :),
        ]));

        if (random(5) > 3)
                set("bagua_count", 1);

        if (random(4) > 2)
                set("xiang_count", 1);

        create_family("逍遥派", 3, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhuo" :),
                (: perform_action, "strike.pan" :),
                (: perform_action, "blade.ruyi" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 26)
        {
                command("say 你脑袋又不灵光，能跟我做什么？");
                return;
        }

        command("say 好吧，我就收下你了，多干活，少说话！");
        command("recruit "+query("id", ob));
}

mixed ask_me()
{
        object ob;

        ob = this_player();
        if (random(100) < 70)
                return "我在设计机关方面是有点特长，让大家见笑了。";

        command("laugh");
        return "别吵着我，我在看书呢。哈哈，芝麻开门。。。。这书真好笑\n";
}
