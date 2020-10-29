inherit NPC;

void create()
{
   set_name("蛇",({ "she"}) );
        set("race", "野兽" );
     set("long", "这是一条凶猛的蛇。\n");
         set("verbs",({"bite"}));
     set("limbs",({"头","尾巴","七寸"}));
         set("attitude","aggressive");
         set("combat_exp",20000);
  setup();

}

void die()
{
        object ob,corpse;
        ob=this_object();
        message_vision("$N躺在地上晃了晃，死了过去。\n",ob);
    corpse=new(__DIR__"obj/shedan");
        corpse->move(environment(ob));
        destruct(ob);
        return;
}