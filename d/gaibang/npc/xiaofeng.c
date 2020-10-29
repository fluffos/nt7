// xiaofeng.c 萧峰(乔峰)

#include <ansi.h>

inherit NPC;

void check_skills(object ob);
int waiting(object me, object dest);
int checking(object me, object dest);
int do_back(object me);
int do_kill(object me, object dest);

void create()
{
        set_name("萧峰", ({"xiao feng", "xiao", "feng"}));
        set("gender", "男性");
        set("nickname",HIB "铁掌降龙" NOR);
        set("age", 28);
        set("long", 
                "他就是丐帮前任帮主，因被发现是契丹人而众叛亲离。\n"
                "在江湖上与燕子坞的慕荣复并称为「北乔峰，南慕荣」。\n"
                "他身穿一件普通的粗布褂子，腰间用一条麻绳随便一系。\n"
                "他身高六尺有余，体格十分魁梧，长有一张线条粗旷、十\n"
                "分男性化的脸庞，双目如电，炯炯有神。\n");
        set("attitude", "peaceful");
        
        set("str", 45);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("chat_chance", 1);
        set("chat_msg", ({
                "萧峰叹了口气道：“唉……想不到我萧峰大好男儿，居然被马夫人这样一个女子所骗！\n",
                "萧峰喃喃道：“我们丐帮的「降龙十八掌」是天下最霸道的掌法。”\n",
                (: random_move :),
        }));
        set("inquiry", ([
                "青竹林" : "东北西北东西北。\n",
                "丐帮"   : "东北西北东西北。\n",
                "拜师"   : "你可以去东城门的我帮总舵拜鲁有脚。\n",
        ]));

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 100);
        
        set("combat_exp", 180000);
        set("score", 20000);
         
        set_skill("force", 120);             // 基本内功
        set_skill("huntian-qigong", 120);    // 混天气功
        set_skill("strike", 120);            // 基本拳脚
        set_skill("dragon-strike", 120);     // 降龙十八掌
        set_skill("dodge", 120);             // 基本躲闪
        set_skill("xiaoyaoyou", 120);        // 逍遥游
        set_skill("parry", 120);             // 基本招架
        set_skill("begging", 50);            // 叫化绝活
        set_skill("checking", 50);           // 道听途说
        
        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dragon-strike");
        
        prepare_skill("strike", "dragon-strike"); 
        
        setup();
        
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) )
        {
                if( !is_killing(query("id", ob)) && living(this_object()) )
                        remove_call_out("check_skills");
                        call_out("check_skills", 1, ob);
        }
}

void check_skills(object ob)
{
        mapping skl; 
        object  me;
        string *sname;
        int i, counter, ob_shen;

        me = this_object();
        skl = ob->query_skills();
        
        if (! mapp(skl) || sizeof(skl) < 1) return;   
        
        sname  = sort_array( keys(skl), (: strcmp :) );
        ob_shen=query("shen", ob);

        counter = 0;
        for (i = 0; i < sizeof(skl); i++)
        {
                if (skl[sname[i]] >= 100)
                        counter++;
        }

        if ((counter >= 3) && (ob_shen < -1000))
        {
                me->set_leader(ob);
        
                if( !query("no_fight", environment(me)) )
                {
                        call_out("do_kill", 1, me, ob);
                        return ;
                }
                else
                {
                        call_out("waiting", 0, me, ob);
                        return ;
                }
        }
        return ;
}

int do_kill(object me, object dest)
{
        if( !query("yipin/joined", dest) )
                return 1;
                
        if (objectp(dest) && present(dest, environment(me))
         && !query("no_fight", environment(me)) )
        {
                message_vision(HIR "$N对$n说道：老子一见一品堂高手就生气。"
                        +RANK_D->query_rude(dest)+"，纳命来！\n" NOR, me, dest);
                me->set_leader(dest);
                me->kill_ob(dest);
                dest->fight_ob(me);

                call_out("checking", 0,  me, dest);
        }
        else  
                call_out("waiting", 1, me, dest);
        
        return 1;
}

int waiting(object me, object dest)
{
        if (objectp(dest))
        {
                if (dest->is_ghost())
                {
                        call_out("do_back", 1, me);
                        return 1;
                }
                else if (me->is_fighting() && present(dest, environment(me)))
                {
                        call_out("checking", 0, me);
                        return 1;
                }
                else if( living(me) && !query("no_fight", environment(dest)) )
                {
                        call_out("do_chase", 0, me);
                        return 1;
                }
        }               
        
        remove_call_out("waiting");
        call_out("waiting", 60, me);
        return 1;
}

int checking(object me, object dest)
{
        object ob;

        if (me->is_fighting()) 
        {
                call_out("checking", 1, me);
                return 1;
        }

        if (objectp(ob = present("corpse", environment(me)))
         && query("victim_name", ob) == query("name", dest) )
        {
                call_out("do_back", 1, me);
                return 1;
        }
        
        call_out("waiting", 0, me, dest);
        return 1;
}

int do_back(object me)
{

        me->move("/d/city/dongdajie2");
        set("combat_exp", 1000000, me);
        message("vision", "萧峰走了过来，拍了拍身上的尘土，微微一笑说道：又除了一个坏蛋。\n", 
                environment(), me );

        me->set_leader(0);
        return 1;
}
