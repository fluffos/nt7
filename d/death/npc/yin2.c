#include <ansi.h>

inherit NPC;
inherit F_DEALER;

#define BADAO "/clone/lonely/book/badao"

void create()
{
        object ob;
        
        
        set_name("阴长生", ({ "yin changsheng", "yin", "changsheng" }));
        set("title", HIR "冥府地藏王殿前" NOR);
        set("nickname", HIB "阴王" NOR);
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 475);
        set("long","阴长生本是个落弟秀才，后在丰都山修练成仙，御封「阴王」。\n");

        set("str", 60);
        set("int", 80);
        set("con", 60);
        set("dex", 60);

        set("max_qi", 9000000);
        set("eff_qi", 9000000);
        set("qi", 9000000);
        
        set("max_jing", 30000000);
        set("jing", 30000000);
        set("eff_jing", 30000000);
        set("max_jingli", 30000000); 
        set("jingli", 30000000);  

        set("neili", 2000000);
        set("max_neili", 150000);
        set("jiali", 600);
        set("combat_exp", 1100000000);

        set_skill("unarmed", 1000);
        set_skill("finger", 1000);
        set_skill("claw", 1000);
        set_skill("strike", 1000);
        set_skill("hand", 1000);
        set_skill("cuff", 1000);
        set_skill("parry", 1000);
        set_skill("dodge", 1000);
        set_skill("force", 1000);
        set_skill("sword", 1000);
        set_skill("zuoyou-hubo", 1000);
         
        set_skill("jiuyin-shengong", 1000);
        set_skill("martial-cognize", 1200);
        set_skill("literate", 1000);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");
        
        // yun perform
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({                                
              // 九阴神功
              (: command("perform claw.zhua twice") :), 
              (: command("perform claw.xin") :), 
              (: command("perform shou twice") :), 
              (: command("perform quan twice") :),                                                                            
              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "roar" :),  
        }));    

        set("vendor_goods", ({
                "/d/death/obj/armor1",
        }));

        setup();
        carry_object(__DIR__"obj/cloth5")->wear();
}

void init()
{
        object me;

        me = this_player();
        
        if (! wizardp(me) && userp(me))
        {
                command("say 哼，擅闯禁地者死！");
                this_object()->kill_ob(me);
        }
}


int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

void unconcious()
{
        die();
}

void die()
{
        
        object ob;
        ob = find_object(BADAO);
        if (! ob) ob = load_object(BADAO);
        
        command("heng");
        command("say 看来人间也有如此厉害的角色，本王先行告辞，改日再来讨教！");
        
        if (! environment(ob) && random(10) == 1)
        {
                message_vision(HIW "叮~~的一声，从阴长生身上掉出一本书，落在地上。\n" NOR, this_object());
                ob->move(environment(this_object()));
        }
        destruct(this_object());
        
        return;                                 
        
}

int accept_object(object me, object ob)
{
        if (! objectp(me) || ! objectp(ob))return 0;
        
        if( query("id", ob) != "tianyi shenjiu" )
        {
                return 0;
        }
        
        command("yi");

        if( !query("can_perform/badao/san-1", me) )
        {
                command("say 这不是天乙神酒吗！太感谢了，呵呵！");
                command("tan");
                command("say 可惜我无以为报，不能要你的美酒，等你学会阿鼻道第一刀再来吧！");
                return 0;
        }
        
        if( query("can_perform/badao/san-2", me) )
        {
                command("say 谢谢你上次的美酒。");
                tell_object(me, HIR "听说神龙岛观龙亭隐藏着一位高人，要学阿鼻道第三刀可以找他试试。\n" NOR);
                return 0;
        }

        command("say 这不是天乙神酒吗！既然你能找到这失传已久的美酒，我便传你阿鼻道第二刀，你可听好了 ...");

        tell_object(me, HIG "恭喜你，领悟了阿鼻道第二刀！\n" NOR);
        tell_object(me, HIR "听说神龙岛观龙亭隐藏着一位高人，要学阿鼻道第三刀可以找他试试。\n" NOR);
        set("can_perform/badao/san-2", 1, me);

        me->save();
        
        destruct(ob);
        
        return 1;
}
