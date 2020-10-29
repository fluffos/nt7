inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "xingxiu.h"

string ask_me();
int ask_ding(object me);
int do_sou(string arg);
void create()
{
        set_name("阿紫", ({ "a zi", "a", "zi"}));
        set("nickname", "星宿派小师妹");
        set("long", 
                "她就是丁春秋弟子阿紫。\n"
                "她容颜俏丽，可眼神中总是透出一股邪气。\n");
        set("gender", "女性");
        set("age", 15);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("shen_type", -1);
        set("str", 18);
        set("int", 28);
        set("con", 20);
        set("dex", 24);
        
        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 10);
        set("combat_exp", 45000);

        set_skill("force", 60);
        set_skill("guixi-gong", 60);
        set_skill("huagong-dafa", 20);
        set_skill("dodge", 40);
        set_skill("zhaixing-gong", 40);
        set_skill("strike", 40);
        set_skill("chousui-zhang", 40);
        set_skill("claw", 40);
        set_skill("sanyin-zhua", 40);
        set_skill("whip", 80);
        set_skill("chanhun-suo", 80);
        set_skill("parry", 40);
        set_skill("poison", 50);
        set_skill("staff", 10);
        set_skill("tianshan-zhang", 10);

        set("no_teach", ([
                "huagong-dafa" : "化功大法让老仙教你吧，我可不愿被他罚。",
        ]));

        map_skill("force", "guixi-gong");
        map_skill("dodge", "zhaixinggong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-zhua");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");
        map_skill("whip", "chanhun-suo");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");

        create_family("星宿派", 2, "弟子");

        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: perform_action, "whip.suo" :),
                (: exert_function, "recover" :),
        }) );

        set("swmuding", 1);
        set("inquiry", ([
                "木鼎" : "仓库里面一大堆，你自己去找吧！",
                "神木王鼎" : (: ask_ding :),
        ]));

        set("master_ob", 4);
        setup();

        carry_object("/clone/weapon/rousisuo")->wield();
        carry_object("/d/xingxiu/obj/xxqingxin-san");
        carry_object("/d/xingxiu/obj/xxqingxin-san");
}

void attempt_apprentice(object ob)
{
        command("say 我不收徒弟！");
        return;
        welcome(ob);
        command("recruit "+query("id", ob));
}

int ask_ding(object me)
{
        if( query_temp("sou/done", me) == 1 )
                return notify_fail("阿紫瞅了你一眼道：“你还想干什么？”\n");
        
        if( query("family/family_name", me) != "星宿派" )
        {  
                say("阿紫说道：“这东西可不是给你用的。”\n");
                return 0;
        }  
        
        if( query_temp("mark/ding", me)<1 )
                set_temp("mark/ding", 1, me);
        
        addn_temp("mark/ding", 1, me);
        if( query_temp("mark/ding", me) >= 5+random(5) )
        {
                say("阿紫说道：你这个人怎么这么烦？神木王鼎就是不在我身上，不信你搜（sou）我好了。\n");
                add_action("do_sou","sou");
                return 1;
        }
        else
                say("阿紫说道：什么神木王鼎，我可没拿……，你别冤枉好人！\n");
        return 1;
}

int do_sou(string arg)
{
    object me,ob1,ob2;
    ob2=this_object();
    me = this_player();
    if( !arg || arg=="" )
        return 0;
    
    if( arg=="a zi" ) 
    {
        message("vision",
            me->name() + "狞笑着说道：“好，那我就不客气了。”\n",
            environment(me),({me}));
        ob2->kill_ob(me);
        set_temp("last_damage_from", me, ob2);
        set_temp("azi/killer2", 1, me);
  
        ob1=present("xiao feng");
        if( !ob1 && !query_temp("xiaofeng/done", me) )
        {
                say(HIY+"阿紫大声喊道：“姐夫救我，这个臭贼想非礼我！！”"NOR+"\n");
                ob1=new("/kungfu/class/xingxiu/xiaofeng");

                ob1->move(environment());
                message_vision(HIY+"\n忽地传来一声怒喝：“何人如此大胆!阿紫不用怕，有姐夫在看谁敢欺负你？”\n"+NOR,me);
                ob1->kill_ob(me);
                me->fight_ob(ob1);
                me->fight_ob(ob2);
                set_temp("xiaofeng/done", 1, me);
                set_temp("sou/done", 1, me);
                remove_action("do_sou","sou");          
                return 1; 
        }
        return 1;
    }
}


int accept_kill(object me)
{ 
        object ob;
        object ob1;
        if( is_fighting()) return;
        if( query_temp("you/done", me) == 1 && query_temp("xiaofeng/done", me) == 1 )
        {
                this_object()->kill_ob(me);
                me->fight_ob(this_object());
        } 
        say("\n阿紫大叫：“救命啊，有人要杀我！！\n\n");
//      this_object()->kill_ob(me);
//      me->fight_ob(this_object());
        set_temp("azi/killer", 1, me);
        set_temp("last_damage_from", me, this_object());
        ob1=present("xiao feng");
        ob=present("you tanzhi");
        if( !ob && !query_temp("you/done", me) )
        {
                ob=new("/kungfu/class/xingxiu/you");
                ob->move(environment());
                ob->kill_ob(me);
                me->fight_ob(ob);
                message_vision("游坦之大喝一声，挡住了你的去路！\n",me);
                        
        }
        if( !ob1 && !query_temp("xiaofeng/done", me) )
        {
                ob1=new("/kungfu/class/xingxiu/xiaofeng");
                ob1->move(environment());
                ob1->kill_ob(me);
                me->fight_ob(ob1);
                message_vision("萧峰大喝一声，挡住了你的去路！\n",me);
        }
        return 1;
}
/*
int accept_kill(object who)
{
        object ob;
        object *obs;

        if (! living(this_object()))
                return 1;

        if (! query("swmuding"))
        {
                command("say 神王木鼎原来的确在我这里，可是后来被人抢走啦！");
                command("inn"+query("id", who));
                tell_object(who, "你看到阿紫一副楚楚可怜的样子，不禁心头一软。\n");
                return -1;
        }

        if( query("family/family_name", who) != 
            query("family/family_name"))
                return 1;

        obs = children("/clone/misc/swmuding");
        obs = filter_array(obs, (: ! clonep($1) :));
        if (sizeof(obs))
        {
                command("say 呜呜，神王木鼎真的被人抢走啦！");
                tell_object(who, "你看阿紫神情不象是作伪，不由得叹了一口气。\n");
                return -1;
        }

        if( count_gt(query("combat_exp", who),500000) && 
            query("shen", who)<-10000 )
        {
                message_vision("$N大叫：别动手，别动手！我给你木鼎就是！\n",
                               this_object());
                ob = new("/clone/misc/swmuding");
                ob->move(this_object());
                command("give"+query("id", ob)+"to"+query("id", who));
                set("swmuding", 0);
                return -1;
        }

        command("say 我说了没有木鼎了，你怎么不信！");
        return 1;
}
*/

void accept_fight(object me)
{
        say("阿紫眼睛一瞪：“我才没空和你胡闹呢！”\n");
        return;
}
