// tangbiao

inherit NPC;

int give_job();
int give_anqi();

void create()
{
        set_name("唐镖", ({ "tang biao", "tang", "biao"}));
        set("long", 
"唐门中所有的绝门镖法，他都会用。\n");        
        set("gender", "男性");
        set("gender", "男性");
        set("age", 32);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 28);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("max_qi", 8000);
        set("max_jingli", 2500);
        set("max_douzhi", 600);
        set("douzhi", 600);
        set("neili", 4500);
        set("max_neili", 4500);
        set("yanli", 200);
        set("jiali", 120);
        set("combat_exp", 900000);
        set("level", 15);
        set("score", 8000);

        set_skill("force", 80);
        set_skill("throwing", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_skill("literate", 80);
        set_skill("hand", 80);
        set_skill("sword", 80);
        set_skill("boyun-suowu", 80);
        set_skill("biyun-xinfa", 80);
        set_skill("qiulin-shiye", 80);
        set_skill("wuzhan-mei", 80);
        set_skill("tangmen-throwing", 80);
        set_skill("tangmen-poison", 80);
        set_skill("tangmen-medical", 80);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "boyun-suowu");
        map_skill("sword", "wuzhan-mei");        
        map_skill("hand", "boyun-suowu");
        
        prepare_skill("hand", "boyun-suowu");
        
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);  
        
        create_family("唐门世家", 2, "弟子");

        set("inquiry", ([
                "job" : ( : give_job  : ),
                "工作": ( : give_job  : ),
                "anqi": ( : give_anqi : ),
                "暗器": ( : give_anqi : ),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));  
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
}

int give_job()
{
        object me, biao;
        string msg, targ;
        int coun;

        string *tar = ({
                "","铁矿石",
        });

        me = this_player();
        biao = this_object();

        if( !environment() || base_name(environment()) != query("startroom") )
        {
                say("唐镖说道:“我现在没心情给你派活，等我回制镖房再说吧！”\n");
                return 0;
        }

        if( !query_temp("tangmen/biao", me) )
                command("say “这里没有活能给你干，你听谁说的？”");
        else
        {
                if( query_temp("biao", me) )
                {
                        command("say “你还没有完成刚才给你的任务呢！”");
                        return 1;
                }
                coun = 1 + random(sizeof(tar));
                if ( coun == sizeof(tar) )
                        coun = ( sizeof(tar) - 1 );
                targ = tar[coun];
                printf("%d/%d\n",coun,sizeof(tar));
                say("唐镖说道:“我这里上好的" + targ + "不多了，你去后山给我找一些来吧！”\n");
                set_temp("biao", coun, me);
        }
        return 1;
}

int give_anqi()
{
        object me = this_player();
        object ob;
        
        if( query("family/family_name", me) != "唐门世家" )
        {
                command("say 你不是我唐门中人，我无法给你七子刚镖！\n");
                return 1;
        } else
        {
                command("say 此七子刚镖威力无穷，配合唐门奇毒使用的话，效果更好！\n");
                ob = new("/kungfu/class/tangmen/obj/biao");
//                ob->move(this_object());
//                command("give qizi gangbiao to"+query("id", me));
                ob->move(me, 1);
                return 1;
        }
                
}

int accept_object(object who, object ob)
{
        command("say 要是找到了，就放到储藏室去吧！给我干什么?");
        write("唐镖冲着你不耐烦的挥了挥手，低着头接着研究暗器图谱。\n");
        return 0;
}
