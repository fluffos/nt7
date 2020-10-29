// zhong.c

#include <ansi.h>

inherit "/inherit/char/punisher";

string *lonelysword = ({
      "staff",
      "sword",
      "hammer",
      "club",
      "dagger",
      "blade",
      "force",
      "whip",
      "throwing",
      "unarmed",
      "finger",
      "claw",
      "strike",
      "hand",
      "cuff"
});

void create()
{
        set_name("高处不胜寒", ({ "gaochu bushenghan" }));
        set("title", HIY "王者麾下灭天骑士团" NOR "破天王");
        set("nickname",HIR "天地交征" NOR);
        set("long", "别惹！你惹不起！\n" );
        set("gender", "男性");
        set("age", 30);

        set("str", 200);
        set("int", 200);
        set("con", 200);
        set("dex", 200);

        set("max_qi", 100000);
        set("qi", 100000);
        set("max_jing", 100000);
        set("jing", 100000);
        set("neili", 100000); 
        set("max_neili", 100000);
        set("jiali", 5000);
        set("score", 100000000);

        set("combat_exp", 1000000000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("buddhism",1000);
        set_skill("force", 1000);
        set_skill("claw", 1000);
        set_skill("dodge", 1000);
        set_skill("parry", 1000);
        set_skill("sword", 1000);
        set_skill("strike", 1000);
        set_skill("jiuyang-shengong", 1000);
        set_skill("jiuyin-baiguzhao", 1000);
        set_skill("douzhuan-xingyi", 1000);
        set_skill("lingbo-weibu", 1000);
        set_skill("cuixin-zhang", 1000);
        set_skill("lonely-sword", 1000);

        map_skill("force", "jiuyang-shengong");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("strike", "cuixin-zhang");
        map_skill("sword", "lonely-sword");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("dodge", "lingbo-weibu");

        prepare_skill("claw", "jiuyin-baiguzhao");
        prepare_skill("strike", "cuixin-zhang");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.zhua" :),
                (: perform_action, "strike.cuixin" :),
                (: perform_action, "sword.po" :),
                (: exert_function, "recover" :),
        }));

        set("can_perform/jiuyin-baiguzhao/shenzhao",1);
        set("can_perform/lonely-sword", lonelysword);

        create_family("泥潭", 1, "创世神将");

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
