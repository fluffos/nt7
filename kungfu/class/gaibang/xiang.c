// xiang.c

#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("项长老", ({"xiang zhanglao", "xiang", "zhanglao"}));
        set("nickname", HIR "丐帮六老" NOR);
        set("gender", "男性");
        set("title", "丐帮九袋长老");
        set("age", 59);
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 9);

        set("str", 30);
        set("int", 24);
        set("con", 30);
        set("dex", 24);

        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 200);

        set("combat_exp", 1500000);
        set("score", 200000);
        set("shen", 100000);

        set_skill("force", 150);             // 基本内功
        set_skill("huntian-qigong", 150);    // 混天气功
        set_skill("dodge", 150);                   // 基本躲闪
        set_skill("xiaoyaoyou", 150);        // 逍遥游
        set_skill("parry", 150);             // 基本招架
        set_skill("hand", 150);              // 基本手法
        set_skill("suohou-hand", 150);       // 锁喉擒拿手
        set_skill("blade", 150);             // 基本刀法
        set_skill("liuhe-dao", 150);       // 四象六合刀
        set_skill("begging", 100);           // 叫化绝活
        set_skill("checking", 100);          // 道听途说
        set_skill("training", 100);          // 驭兽术
        set_skill("strike",85);  // 基本掌法
        set_skill("lianhua-zhang",85); // 莲花掌
        set_skill("dragon-strike",85);

        map_skill("strike","lianhua-zhang");
        prepare_skill("strike","lianhua-zhang");

        map_skill("force", "huntian-qigong");
        map_skill("hand",  "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "liuhe-dao");
        prepare_skill("hand",  "suohou-hand");

        //set("party/party_name", HIC"丐帮"NOR);
        //set("party/rank", RED"九袋长老"NOR);
        //set("party/level", 9);
        create_family("丐帮", 18, "长老");

        setup();

        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("hmm");
        command("say 走开，我不收徒。");
}
