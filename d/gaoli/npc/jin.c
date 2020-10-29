// 大唐双龙传
// jin.c 金满柜
 
inherit NPC;
inherit F_BANKER;
void create()
{
   set_name("金满柜", ({"jin mangui", "jin", "boss"}));
   set("shop_id",({"jin mangui", "jin", "boss"}));
   set("gender", "男性");
   set("age", 47);
   set("kee", 500); 
   set("max_qi", 500);
   set("sen", 200);
   set("max_jing", 200); 
   set("max_mana", 200); 
   set("mana", 200); 
   set("combat_exp", 50000);
   set("attitude", "friendly");
   set("rank_info/respect", "掌柜的");
   set("env/wimpy", 50);
   set("chat_chance", 10);
   set_skill("parry", 60);
   set_skill("unarmed", 60);
   set_skill("dodge", 60);

   setup();
        carry_object("/d/gaoli/obj/pao2")->wear();

   add_money("silver", 10);
}
void init()
{
        add_action("do_check", "check");
        add_action("do_check", "chazhang");
        add_action("do_convert", "convert");
        add_action("do_convert", "duihuan");
        add_action("do_deposit", "deposit");
        add_action("do_deposit", "cun");
        add_action("do_withdraw", "withdraw");
        add_action("do_withdraw", "qu");
        delete_temp("busy");
}