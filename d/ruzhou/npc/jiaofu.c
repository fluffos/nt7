// jiaofu.c

inherit NPC;

void create()
{
        set_name("脚夫", ({ "jiao fu", "fu" }) );
        set("gender", "男性" );
        set("age", 20+random(15));
        set("long",
                "这是个老实巴交的中年人，专门帮人挑东西，长得膀阔腰圆，一身肌肉。\n");
        set("combat_exp", random(10000));
   set("str", 25);
   set("dex", 22);
   set("con", 20);
   set("int", 15);
        set("attitude", "heroism");

        setup();
   carry_object("clone/misc/cloth")->wear();
}