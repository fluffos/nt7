// poorman.c

inherit NPC;

void create()
{
        set_name("穷汉", ({ "poor man", "man" }) );
        set("gender", "男性" );
        set("age", 33);
        set("long", "一个骨瘦如柴，满脸菜色的穷汉。\n");
        set("attitude", "friendly");
        set("combat_exp", 250);
//      set("shen", 50);
        set("shen_type", 1);
        set("str", 20);
        set("dex", 18);
        set("con", 17);
        set("int", 13);
        setup();
        set("chat_chance", 15);
        set("chat_msg", ({
"穷汉懒洋洋地打了个哈欠。\n",
      "穷汉懒洋洋地打了个哈欠道：这洞里适合建筑和潜伏隐修。\n", 
      "穷汉懒洋洋地打了个哈欠道：剑侠，剑仙... 可惜，仙缘难求啊。\n",  
"穷汉伸手捉住了身上的虱子，骂道：长眉老儿说这洞里封着血神子，真他妈胡扯。 \n",
                (: random_move :)
        }) );
        carry_object("/d/emei/npc/obj/cloth")->wear();
}

