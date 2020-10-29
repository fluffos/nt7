inherit NPC;

void create()
{
   set_name("安南小姐",({ "xiaojie"}) );
        set("gender", "女性" );
        set("age", 18);
   set("long", "她是安南城内的小姐。\n");
       
   set("combat_exp", 10000);
   set("str", 14);
   set("per", 25);
   set("attitude", "friendly");
   setup();
   carry_object(__DIR__"obj/shayi")->wear();
   add_money("coin", 50);
}
