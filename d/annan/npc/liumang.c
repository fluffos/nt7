inherit NPC;

void create()
{
   set_name("流氓",({ "liu mang","liu","mang" }) );
        set("gender", "男性" );
        set("age", 22);
   set("long", "这是一个安南城内的流氓。\n");
       
   set("combat_exp", 50000);
   set("str", 23);
   set("per", 18);
   set("attitude", "peaceful");
   set("chat_chance",50);
   set("chat_msg",({
           "流氓说道：这里就是我们说了算！\n",
           "流氓吐了口吐沫：都给我闪开，看什么看！\n",
   }));
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}
