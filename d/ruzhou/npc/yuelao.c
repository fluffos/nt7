// Npc:/d/suzhou/npc/yuelao.c
// llm 99/02
inherit NPC;

void create()
{
        set_name("月老", ({ "yue lao","yue","lao"}) );
        set("gender", "男性");
        set("age", 90);
        set("long",
                "只见他长得鹤发童颜，身材高大，面目慈祥。\n");
        set("combat_exp", 150000);
   set("qi",1000);
   set("jing",1000);
   set("neili",1000);
   set("jiali",10);
   set("shen_type", 0);
        set("attitude", "heroism");
   set("channel_id", "月老");

        set_skill("unarmed", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);

        setup();
   carry_object("/clone/misc/cloth")->wear();
}
