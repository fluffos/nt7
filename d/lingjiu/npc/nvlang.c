// /NPC 蒙面女郎

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("蒙面女郎", ({ "nv lang", "nv"}));
        set("long",
            "这是个身材娇好的女郎, 轻纱遮面,\n"
            "一双秀目中透出一丝杀气。\n"
           );
        set("gender", "女性");
        set("age", 20);
        set("shen_type",0);
        set("attitude", "peaceful");

        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("qi", 5000);
        set("max_qi", 5000);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 100);

        set("combat_exp", 500000);
        set("score", 100000);
        set_skill("force", 170);
        set_skill("unarmed", 170);
        set_skill("dodge", 170);
        set_skill("parry", 170);
        set_skill("hand",170);
        set_skill("strike", 170);
        set_skill("sword",170);

        set_skill("zhemei-shou",170);
        set_skill("liuyang-zhang",170);
         set_skill("tianyu-qijian",170);
        set_skill("yueying-wubu",170);
        set_skill("lingjiu-xinfa", 170);

        map_skill("force", "lingjiu-xinfa");
        map_skill("strike","liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("unarmed", "liuyang-zhang");
        map_skill("hand", "zhemei-shou");
        map_skill("parry", "liuyang-zhang");
        map_skill("sword", "tianyu-qijian");

        set_temp("apply/damage", 150);
        set_temp("apply/armor", 150);
        set_temp("apply/defense", 150);

        create_family("灵鹫宫",3,"弟子");
        setup();

        carry_object("/d/lingjiu/obj/qingyi")->wear();
        carry_object("/d/lingjiu/obj/doupeng")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("silver",15);
}