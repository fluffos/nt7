// This program is a part of NT MudLIB

#include <ansi.h>
inherit NPC;

int ask_skill1();
int ask_skill2();
void destroying(object, object);

void create()
{
        set_name("丁典", ({ "ding dian", "ding" }));
        set("long",
                "这人满脸虬髯，头发长长的直垂至颈，衣衫破烂不堪，简直如同荒山中的野人。\n");
        set("gender", "男性");
        set("age", 35);

        set_skill("unarmed", 120);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("ding-dodge", 120);
        set_skill("ding-force", 120);
        set_skill("ding-unarmed", 120);
        set_skill("shenzhaojing", 300);
        map_skill("force", "shenzhaojing");
        map_skill("parry", "shenzhaojing");
        map_skill("unarmed", "shenzhaojing");
        map_skill("dodge","ding-dodge");
        prepare_skill("unarmed","shenzhaojing");
        set("max_neili",2000);
        set("neili",2000);
        set("jiali",100);

        set("combat_exp", 600000);
        set("shen_type", 1);
        set("chat_chance", 10);
        set("chat_msg", ({
                "丁典轻轻叹了一口气。那叹息中，竟有忧伤、温柔之意。\n",
                "丁典嘴角挂着一丝微笑，痴望远处高楼纱窗上那一盆鲜花。\n",
                "丁典大声道：怎么会忘记？决不会的！难道……难道是生了病？\n",
                "丁典喃喃道：就算是生了病，也会叫人来换花啊！\n",
        }) );
        set("inquiry", ([
                "凌霜华" : "“唉……”，然后指了指牢外那座小楼的窗口，啥也不说了。\n",
                "唤醒"   : (: ask_skill1 :),
                "疗精"   : (: ask_skill2 :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

int accept_object(object me, object obj)
{
        object key;
        if( query("id", obj) == "green flower" && 
             filter_color(query("name", obj),1) == "绿玉如意"){
                message("vision",me->name()+"给丁典一盆绿菊花。\n",environment(me),
                        ({me}));
                key = new("/clone/book/shenzhaojing");
                if (!key){
                        command("say 我已经托人把书带给霜华了，不劳您大驾了。");
                        return 0;
                }

                command("touch "+query("id", me));
                command("say 这位"+RANK_D->query_respect(me)+"是霜华派来送信的吧。");
                key->move(me);
                addn("book_count", -1);
                message_vision("$n递给$N一本书。\n", me, this_object() );
                command("say 这本书就是我练功打坐用的《神照经》，你拿去带给霜华吧。");
                command("rumor "+query("name", me)+"弄到了一册神照经。");
                remove_call_out("destroying");
                call_out("destroying", 1, this_object(), obj);
                return 1;
        }
        if( query("id", obj) == "green flower" && 
            filter_color(query("name", obj),1) == "春水碧波" )
        {
                message("vision",me->name()+"给丁典一盆绿菊花。\n",environment(me),
                        ({me}));
                message_vision("丁典同意指点$N一些武功的问题。\n",me);
                addn_temp("mark/丁", 1000, me);
                return 1;
        }
        return 0;
}

void destroying(object me,object obj)
{
        destruct(obj);
        return;
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/丁", ob) )
                return 0;
        addn_temp("mark/丁", -1, ob);
        return 1;
}

int ask_skill1()
{
        object ob = this_object();
        object who = this_player();

        if( !query_temp("mark/丁", who))return 0;
        if (!who->query_skill("shenzhaojing",1)) return 0;
        if( query("can_perform/shenzhaojing/wakeup", who))return 0;
        if (who->query_skill("shenzhaojing",1) < 100)
        {
                command("say 你的神照经功力还不够高，多学学吧。");
                return 1;
        }
        command("sign");
        command("say 不知你学得神照经是福是祸了。也罢，随你去吧。");
        tell_object(who,HIC"丁典在你耳边悄悄说了几句运功的口诀，你急忙用心一一记下。\n"NOR);
        tell_object(who,HIC "你学会了「唤醒」。\n" NOR);
        set("can_perform/shenzhaojing/wakeup", 1, who);
        return 1;
}
int ask_skill2()
{
        object ob = this_object();
        object who = this_player();

        if( !query_temp("mark/丁", who))return 0;
        if (!who->query_skill("shenzhaojing",1)) return 0;
        if( query("can_perform/shenzhaojing/jingheal", who))return 0;
        if (who->query_skill("shenzhaojing",1) < 50)
        {
                command("say 你的神照经功力还不够高，多学学吧。");
                return 1;
        }
        command("sign");
        command("say 不知你学得神照经是福是祸了。也罢，随你去吧。");
        tell_object(who,HIC"丁典在你耳边悄悄说了几句运功的口诀，你急忙用心一一记下。\n"NOR);
        tell_object(who,HIC "你学会了「疗精」。\n" NOR);
        set("can_perform/shenzhaojing/jingheal", 1, who);
        return 1;
}
