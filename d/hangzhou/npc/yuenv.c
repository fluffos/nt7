// yuenv.c 越女

#include <ansi.h>

inherit NPC;

int ask_me();

void create()
{
        set_name("越女", ({ "yue nv", "yuenv" }));
        set("long", @LONG
她是一位年轻的牧羊女，脸上挂着一丝与年龄不相称的哀思。
LONG );
        set("gender", "女性");
        set("class", "swordsman");
        set("age", 18);
        set("attitude", "friendly");
        set("per", 29);
        set("str", 19);
        set("int", 35);
        set("con", 32);
        set("dex", 35);
        
        set("max_qi", 5000);
        set("max_jing", 2500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 50);
        set("combat_exp", 2500000);

        set_skill("force", 250);
        set_skill("dodge", 270);
        set_skill("parry", 270);
        set_skill("sword", 270);
        set_skill("yunv-xinfa", 250);
        set_skill("yuenv-jian", 270);
        set_skill("feiyan-huixiang", 250);

        map_skill("dodge", "feiyan-huixiang");
        map_skill("force", "yunv-xinfa");
        map_skill("sword", "yuenv-jian");

        set("inquiry", ([
                "绝招" : (: ask_me :),
                "绝技" : (: ask_me :),
                "西子捧心" : (: ask_me :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: perform_action, "sword.pengxin" :),
        }));

         setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhujian")->wield();
}

int recognize_apprentice(object ob, string skill)
{
        if( query_temp("can_learn/yuenv/yuenv-jian", ob) && 
            skill == "yuenv-jian")
                return 1;

        if( query_temp("can_learn/yuenv/sword", ob) && 
            skill == "sword")
                return 1;

        if (skill == "yuenv-jian")
        {
                if( query("gender", ob) == "女性" )
                {
                        message_vision("$N眼圈一红，对$n道：也好。\n",
                                       this_object(), ob);
                        set_temp("can_learn/yuenv/yuenv-jian", 1, ob);
                        return 1;
                }
                message_vision("$N瞥了$n一眼，没有理$n。\n", this_object(), ob);
                return -1;
        }

        if (skill == "sword")
        {
                message_vision("$N看了看$n，点点头道：剑术也没有什么难学的。\n",
                               this_object(), ob);
                set_temp("can_learn/yuenv/sword", 1, ob);
                return 1;
        }

        command("say 我只懂得一点剑术，你可不要为难我。");
        return -1;
}

int ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/yuenv-jian/pengxin", me) )
        {
                command("say 你很喜欢开玩笑么？学过了还来找我？");
        } else
        if( query("gender", me) != "女性" )
        {
                command("say 你们男人没有什么好东西，还是别说什么花言巧语了。");
        } else
        if( query("per", me) >= 30 )
        {
                message_vision("$N看着$n，幽幽的叹了一口气，似乎想起了什么。\n",
                               this_object(), me);
        } else
        if (me->query_skill("force") < 120)
        {
                command("say 你的内功底子这么差，还谈什么绝招，笑死人家了。");
                return 1;
        } else
        if (me->query_skill("yuenv-jian", 1) < 100)
        {
                command("say 你还是练好我的剑术再说吧，不要好高鹜远，反而一事无成。");
                return 1;
        } else
        {
                command("nod");
                command("say 好吧，我就叫你这一招“西子捧心”，以后你若见到... 还是算了吧。");
                tell_object(me, "你听了越女的指点，明白了如何运用这一绝技。\n");
                set("can_perform/yuenv-jian/pengxin", 1, me);
        }
        return 1;
}
