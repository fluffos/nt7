#include <ansi.h>
inherit NPC;
void create()
{
        set_name("吴六破", ({ "wu liupo","wu","liupo"}) );
        set("long",@LONG
他高瘦笔直、傲然挺立，自有一股书香世家的气质．苍白的脸带着浓烈的
书卷气，看上去很年青，但两鬓偏已斑自，他的儒服两袖高高捋趄，露出雪白
的手臂，手十指尖长，尤胜女孩儿家的手。尤其使人注目的是他耳朵上挟着一
根银光闪闪长若五寸的针。
LONG
         );

        set("title",MAG"神箭八雄"NOR);
       set("nickname","散毒箭");
        set("max_jing", 6000);
        set("max_qi", 6000);                    
        set("max_sen", 6000);
        set("max_neili",6000); 
        set("neili",6000);
        set("jiali",180);     
        set("combat_exp",4500000);
        set("cor",100);
        set("age",65);

        set_skill("force", 400);
        set_skill("huagong-dafa", 480);
        set_skill("dodge", 480);
        set_skill("zhaixinggong", 410);
        set_skill("unarmed", 450);
        set_skill("xingxiu-duzhang", 400);
        set_skill("parry", 450);
        set_skill("staff", 470);
        set_skill("tianshan-zhang", 415);
        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("unarmed", "xingxiu-duzhang");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");
        set_temp("apply/attack",50);
        setup();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player())) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
         if(random(15) < 2)
                this_object()->set_leader(ob);
        }
}
