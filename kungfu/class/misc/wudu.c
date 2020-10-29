#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("无毒隐士", ({ "yin shi", "yin", "shi" }));
        set("long",  "他就是无毒派的高手，据说长年隐藏于山中。\n");
        set("gender", "男性");
        set("age", 55);
        set("attitude", "peaceful");
               set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 30);

        set("max_qi", 5000);
        set("max_jing", 4000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 250);
        set_skill("wudu-shengong", 250);
        set_skill("xiuluo-yinshagong", 250);
        set_skill("dodge", 250);
        set_skill("wudu-yanluobu", 250);
        set_skill("strike", 250);
           set_skill("tianchan-zhang", 250);
        set_skill("hand", 250);
        set_skill("qianzhu-wandushou", 250);
        set_skill("claw", 250);
        set_skill("wusheng-zhao", 250);
        set_skill("parry", 250);
        set_skill("sword", 250);
        set_skill("jinwu-goufa", 250);
        set_skill("whip", 250);
        set_skill("ruanhong-zhusuo", 250);
        set_skill("xiewei-bian", 250);
        set_skill("throwing", 250);
        set_skill("hansha-sheying", 250);
        set_skill("literate", 250);
        set_skill("poison", 250);
        set_skill("wudu-qishu", 250 );
        set_skill("martial-cognize", 250);
        set_skill("wudu-jing", 250);

        map_skill("force", "xiuluo-yinshagong");
        map_skill("dodge", "wudu-yanluobu");
        map_skill("strike", "tianchan-zhang");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("claw", "wusheng-zhao");
        map_skill("throwing", "hansha-sheying");
        map_skill("parry", "jinwu-goufa");
        map_skill("sword", "jinwu-goufa");
        map_skill("whip", "ruanhong-zhusuo");
        map_skill("poison", "wudu-qishu");

        prepare_skill("claw", "wusheng-zhao");

        prepare_skill("strike", "tianchan-zhang");

        create_family("五毒教", 0, "隐士");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
               
                (: perform_action, "whip.teng" :),
                (: perform_action, "whip.pan" :),
                (: perform_action, "whip.bohu" :),
                (: perform_action, "whip.suo" :),
                (: perform_action, "claw.lian" :),
                (: perform_action, "strike.chan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );


        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();
        carry_object("/clone/weapon/whip")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}
