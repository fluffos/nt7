// tangfang.c 唐方

#include <ansi.h>
#include "tangmen.h"

string ask_me();
int carry_qian();

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("唐方", ({ "tang fang", "tang" }));
        set("long", 
"唐方身材娇小，长的极为清秀，又带几分英气，清劲多于柔弱。\n"
"她是唐门长房宗主唐尧舜之女，唐大之妹，后又得唐老太太亲授衣钵，在唐门地位颇高。\n"
"她面容苍白，神情憔悴，清丽的面庞仿佛还带着泪痕。\n");                
        set("gender", "女性");
        set("age", 20);
        set("class", "tangmen");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 20);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 800);
        set("max_jing", 2000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 60);
        set("combat_exp", 900000);
        set("level", 15);
        set("score", 80000);

        set_skill("force", 200);
        set_skill("biyun-xinfa", 200);
        set_skill("dodge", 200);
        set_skill("qiulin-shiye", 200);
        set_skill("hand", 200);
        set_skill("boyun-suowu", 180);
        set_skill("parry", 200);
        set_skill("throwing", 200);
        set_skill("sword", 200);
        set_skill("wuzhan-mei", 200);
        set_skill("tangmen-throwing", 200);
        set_skill("literate", 100);
        set_skill("poison", 200);
        set_skill("medical", 200);
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);          

        map_skill("force", "biyun-xinfa");
        map_skill("dodge", "qiulin-shiye");
        map_skill("hand", "boyun-suowu");
        map_skill("parry","boyun-suowu");
        map_skill("sword", "wuzhan-mei");
        map_skill("throwing","tangmen-throwing");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");

        prepare_skill("hand", "boyun-suowu");
                
        create_family("唐门世家", 3, "弟子");
        
        set("chat_chance" , 20);
        set("chat_msg", ({
                "我的萧哥哥到哪儿去，到现在还不来看我！\n",
                "唐方幽幽叹口气，轻轻按住琴弦，出神得看着远方的湖面。\n",
                "唐方漫不经心地拨弄了几下琴弦，自言自语道：也不知道萧郎现在是生是死....。\n",
                "唐方轻轻吹了一下渺渺升起的檀香，两行清泪缓缓流下面颊。 \n",                
                ( : command("shy") : ),
                ( : command("sigh") : ),
                ( : command("drop qianqian") : ),
                ( : command("wield all") : ),
                ( : command("drop qianqian") : ),
        }) );
        
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                ( : command("yun recover") : ),
                ( : command("yun recover") : ),
                ( : carry_qian : ),
                ( : carry_qian : ),
                ( : command("use qian") : ),
                ( : command("use qian") : ),
                ( : command("wield all") : ),
                ( : command("wield all") : ),
        }) );

        set("inquiry", ([
                "千千结" : "问问老太太去啊！\n",
                "千千"   : "问问老太太去啊！\n",
                "萧郎" : (: ask_me :),
        ]) );                 

        set("master_ob", 2);
        setup();
        carry_object("/d/tangmen/obj/mcloth")->wear();
        carry_object("/d/tangmen/obj/mshoe")->wear();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));          
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  
                return;

        if( query("family/family_name", ob) != "唐门世家" )
        {
                command("say “我四川唐门乃是武林世家，你已是武林中人，我不能收你为徒！”\n");
                return;
        }
                                        
        if ((int)ob->query_skill("biyun-xinfa", 1) < 80) {
                command("say 唐门虽然以暗器为主，但还是要辅以内力。"); 
                command("say " + RANK_D->query_respect(ob) + 
                        "是否还应该在碧云心法上多下点功夫？");
                return;
        }

        if ( ob->query_skill("biyun-xinfa", 1) < 80 && ob->query_skill("tangmen-throwing", 1) < 80 )
        {
                command("say “你的心法和暗器不太熟练，要加油啊！”\n");
                return;
        }                                   
        if( query("int", ob)<28){
                command("say 唐门历来注重弟子的文学修为。");
                command("say 本派功夫要能熟练运用，必须能体会其中所含深远意境，悟性差了是不行的。");
                command("say " + RANK_D->query_respect(ob) + "的悟性还大有潜力可挖，还是请回吧。");
                return;
        }
        command("say 好吧，我就收下你吧...");
        command("recruit "+query("id", ob));
}
string ask_me()
{
        object me;
        me = this_player();
        
        if( query_temp("marks/萧", me) )
        {
                return "算了吧，看来你也不知道萧郎的消息，你走吧。\n";
        }
        command("ah"+query("id", this_player()));
        command("say 你知道萧郎吗！？自从他上次大闹唐门后就失去了消息。\n");
        command("sigh");
        set_temp("marks/萧", 1, this_player());
        return "老太太为这事非常生气，再也不许我见他了。\n";
           

}
        
int accept_object(object who, object ob)
{
        object book;
        if( playerp(ob) ) return 0;
        book = new("/d/tangmen/obj/throwbook");
        if( query("name", ob) == "玉佩" )
        {
                if(!query("yl_trigger")) 
                {
                        say(
"唐方说道：这不是萧郎的玉佩吗？太谢谢你了，虽然没有见到萧郎，\n"
"能见到他的信物,我已经很欣慰了。\n"
"唐方悠悠地叹了一口气：这里有一本暗器总诀，就算是给你的酬谢吧。\n"
"唐方把"+query("name", book)+"交给了"+query("name", who)+"。\n");
                        book->move(who);
                        set("yl_trigger", 1);
                }
                else say("唐方杏目圆睁，说道：你这个人怎么这样讨厌啊。\n");
                call_out("destroy", 1, ob);
                return 1;
        }
        return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}

int carry_qian()
{
        object ob;

        ob = new("/kungfu/class/tangmen/obj/jie.c");
        ob->move(this_object());
        return 1;
}        
