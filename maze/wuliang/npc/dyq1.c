// cool980310
// 段延庆
// cool980724
// Modify By River 98/12
inherit NPC;

void create()
{
        set_name("段延庆", ({ "duan yanqing", "duan","yanqing"}) );
        set("nickname", "恶贯满盈");
	set("title", "四大恶人");
        set("gender", "男性" );
        set("age", 52);
        set("str", 26);
        set("con", 23);
        set("dex", 5);
        set("int", 25);
        set("per", 10);
   	set("attitude", "friendly");

        set("max_qi", 7000);
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("neili", 10000);
        set("qi", 7000);
        set("max_neili", 10000);
        set("jiali", 100);         
        
        set("long","这人是个老者，长须垂胸，面目漆黑。\n");
        set("combat_exp", 2100000);
       set("env/一阳指","三叠");
        set("shen", -20000);

        set("chat_chance_combat", 30);
        set("chat_msg_combat",({ 
          (: perform_action, "finger.sandie" :),
        }));

        set_skill("parry", 210);
        set_skill("dodge", 160);
        set_skill("force", 210);
        set_skill("finger", 160);
        set_skill("buddhism", 100);
        set_skill("literate", 120);
        set_skill("sword", 130);
        set_skill("duanjia-jian", 120);
        set_skill("qiantian-yiyang", 210);
        set_skill("sun-finger", 210);
        set_skill("tianlong-xiang", 50);
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "sun-finger");
        map_skill("finger", "sun-finger");
        map_skill("force", "qiantian-yiyang");
        prepare_skill("finger","sun-finger");

        set("inquiry", ([
           "段誉" : "嘿嘿，他被我关在石屋里啦",
           "name" : "老夫便是段延庆",
           "段延庆" : "老夫便是段延庆",
        ]) );

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{       
        object me,ob;
        ob = this_player();
	me = this_object();
        ::init();
        if( interactive(ob)
          && query_temp("kill", ob)){
         call_out("kill_ob", 0, ob); 
         }
}