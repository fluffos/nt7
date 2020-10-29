// dongfang.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
    set_name("东方不败", ({"dongfang bubai", "dongfang", "bubai"}));
    set("nickname", HIY "天下无敌" NOR);
    set("title", HIM "日月神教教主" NOR);
    set("gender", "男性");
    set("shen_type", -1);
    set("age", 42);
    set("long",
        "他就是日月神教教主。号称无人可敌，因此有一称号为「东方不败」。\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 21);
    set("int", 30);
    set("con", 26);
    set("dex", 30);

    set("chat_chance", 1);
    set("chat_msg", ({
          "东方不败叹了口气道：“唉 …… 我的杨大哥....他怎么还不回来,我好\n"
         "挂念他 ……东方不败眼中流露无限迷茫。\n",
    }));
    set("inquiry", ([
        "杨莲亭"   : "你敢直称我爱人的名字,想找死呀？ \n",
        "葵花宝典" : "如果你能帮我取得葵花宝典上册，我一定重重谢你。\n",
    ]));

    set("qi", 4000);
    set("max_qi", 4000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 4500);
    set("max_neili", 4500);
    set("jiali", 400);

    set("combat_exp", 2500000);
    set("score", 0);

    set_skill("force", 290);             // 基本内功
    set_skill("finger", 290);            // 基本指法
    set_skill("unarmed", 290);           // 基本拳脚
    set_skill("dodge", 300);             // 基本躲闪
    set_skill("parry", 290);             // 基本招架
    set_skill("sword", 290);             // 基本剑法
    set_skill("pixie-jian", 300);        // 辟邪剑法
    set_skill("changquan", 280);         // 太祖长拳
    set_skill("literate", 120);          // 读书识字
    set_skill("kuihua-xinfa", 290);      // 葵花心法

    map_skill("force", "kuihua-xinfa");
    map_skill("sword", "pixie-jian");
    map_skill("unarmed", "changquan");
    map_skill("dodge", "pixie-jian");
    map_skill("parry", "pixie-jian");

    create_family("日月神教", 2, "教主");

    setup();
    carry_object("/d/fuzhou/obj/xiuhua")->wield();
    carry_object("/d/wanjiegu/npc/obj/qi-dress")->wear();
    carry_object("/d/heimuya/obj/yuxiao");
}
