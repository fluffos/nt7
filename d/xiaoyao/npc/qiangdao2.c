// qiangdao.c 强盗
// lag.2000/3/17

inherit NPC;
#include <ansi.h>
void move();

void create()
{       object me;
        int myskill;
        me=this_player();
        if (! me) return; 
        myskill=me->query_skill("force");
        set_name(HIC"逍遥派叛徒首领"NOR,({query("id", me)+"-pantu"}));
        set("title",query("name", me)+"定下的");
        set("gender", "男性");
        set("age", 28);
        set("long", "他是一个逍遥派叛徒。\n");
        
        set("attitude", "peaceful");
        set("qi",query("qi", me));
        set("max_qi",query("max_qi", me));
        set("jing",query("jing", me));
        set("neili",query("neili", me));
        set("max_neili",query("max_neili", me));
        set("max_jing",query("max_jing", me));
        set("str",query("str", me));
        set("dex",query("dex", me));
        set("per",query("per", me));
        set("killer",query("id", me));
        set("combat_exp",query("combat_exp", me));
// 加下面5句是让强盗自动走，增添玩家做机器人的困难！-糖圆SMILE
        set("chat_chance_combat", 60);  
        set("chat_msg_combat", ({
                (: perform_action, "blade.ruyi" :),
                (: perform_action, "blade.ruyi" :),
                (: perform_action, "blade.wanshi" :),
                (: perform_action, "blade.wanshi" :),
                (: perform_action, "dodge.lingbo" :),
                (: perform_action, "dodge.lingbo" :),
                (: exert_function, "strike.zhong" :),                
                (: exert_function, "strike.zhong" :),                
        }) );
             set("chat_chance", 30);
             set("chat_msg", ({
              (: random_move :)
        }) );


        set_skill("hand", myskill * 4 / 5);
        set_skill("dodge", myskill);
        set_skill("unarmed", myskill* 4 / 5);
        set_skill("parry", myskill* 4 / 5);
        set_skill("force", myskill* 4 / 5);
        set_skill("blade", myskill* 4 / 5);
        set_skill("lingbo-weibu", myskill);
        set_skill("ruyi-dao", myskill* 4 / 5);
        set_skill("liuyang-zhang", myskill* 4 / 5);
        set_skill("zhemei-shou", myskill* 4 / 5);
        map_skill("unarmed", "liuyang-zhang");
        map_skill("parry", "ruyi-dao");
        map_skill("blade", "ruyi-dao");
        map_skill("dodge", "lingbo-weibu");
        map_skill("force", "beiming-shengong");
        prepare_skill("hand","zhemei-shou");
        prepare_skill("strike","liuyang-zhang");        
        set_temp("apply/attack", 200);
        set_temp("apply/defense", 200);
        set_temp("apply/armor", 200);
        set_temp("apply/damage", 250);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();

}

void init()
{
        remove_call_out("leave");
        call_out("leave",60);
}

void leave()
{
        object ob = this_object();
        if (!ob->is_fighting()) {
                message_vision(HIC "逍遥派叛徒首领钻进路边的杂草，不见了。\n" NOR,this_object());
                destruct(this_object());
                }
        else call_out("leave",30);
}

void die()
{
        object ob;
        message_vision("$N大叫一声：我不甘心！消失了。\n", this_object());
        ob = new("/d/xiaoyao/obj/zhi");
        ob->move(environment(this_object()));
        destruct(this_object());
}
