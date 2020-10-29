// tangyao

inherit NPC;

int give_job();
int give_yao();

void create()
{
        set_name("唐药", ({ "tang yao", "tang", "yao"}));
        set("long",
"唐门二代弟子，在唐门地位颇高。\n");
        set("gender", "男性");
        set("age", 55);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 28);
        set("max_qi", 8000);
        set("max_jingli", 1500);
        set("max_douzhi", 500);
        set("douzhi", 500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("yanli",200);
        set("jiali", 100);
        set("combat_exp", 800000);
        set("level", 15);
        set("shen",3000);
        set("score", 7000);

        set_skill("force", 180);
        set_skill("throwing", 180);
        set_skill("dodge", 180);
        set_skill("parry", 180);
        set_skill("literate", 180);
        set_skill("hand", 180);
        set_skill("sword", 180);
        set_skill("boyun-suowu", 180);
        set_skill("biyun-xinfa", 180);
        set_skill("qiulin-shiye", 180);
        set_skill("wuzhan-mei", 180);
        set_skill("tangmen-throwing", 180);
        set_skill("tangmen-poison", 180);
        set_skill("tangmen-medical", 180);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        
        prepare_skill("hand", "boyun-suowu");
        
        create_family("唐门世家", 2, "弟子");

        set("inquiry", ([
                "job" : ( : give_job  : ),
                "工作": ( : give_job  : ),
                "散花天雨": ( : give_yao : ),
        ]));

        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);          

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));   
}

int give_job()
{
        object me;

        me = this_player();

        if( !environment() || base_name(environment()) != query("startroom") )
        {
                say("唐药说道:“我现在没心情给你派活，等我回制药房再说吧！”\n");
                return 0;
        }

        if( !query_temp("tangmen/yao", me) )
                command("say “这里没有活能给你干，你听谁说的？”");
        else
        {
                if( query_temp("yao", me) )
                {
                        command("say “你还没有完成刚才给你的任务呢！”");
                        return 1;
                }
                write("唐药说道:“我这里正缺一味草药，快去药圃给我找(zhao)一株草药(yao)来吧！”\n");
                set_temp("yao", 1, me);
        }
        return 1;
}

int give_yao()
{
        object me = this_player();
        object ob;
        
        if( query("family/family_name", me) != "唐门世家" )
        {
                command("say 你不是我唐门中人，我无法给你散花天雨！\n");
                return 1;
        } else
        {
                command("say 此散花天雨威力无穷，配合唐门奇毒使用的话，世上没有对手！\n");
                ob = new("/kungfu/class/tangmen/obj/san");
//                ob->move(this_object());
//                command("givesanhuatianyuto"+query("id", me));
                ob->move(me, 1);
                message_vision("$N对$n点了点头。\n", this_object(), me); 
                return 1;
        }
                
}

int accept_object(object who, object ob)
{
        command("say 要是找到了，就放到储藏室去吧！给我干什么?");
        write("唐药冲着你摇了摇头，然后又小心翼翼的反弄着一株碧绿色的药草。\n");
        return 0;
}
