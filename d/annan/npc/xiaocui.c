inherit NPC;

void create()
{
   set_name("小翠",({ "xiao cui","xiao","cui"}) );
        set("gender", "女性" );
        set("age", 18);
   set("long", "她是迎君楼的姑娘。\n");
       
   set("combat_exp", 10000);
   set("str", 14);
   set("per", 26);
   set("attitude", "friendly");
   set("chat_chance",40);
   set("chat_msg",({
           "小翠娇笑道：呦，这位客官，来进来坐坐嘛！\n",
           "小翠笑道：呦，客官，进来吧，包你满意！\n",
   }));
   setup();
   carry_object(__DIR__"obj/shayi")->wear();
   add_money("coin", 50);
}
