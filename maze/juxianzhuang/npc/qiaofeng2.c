
// Written by Lonely@nitan.org
// xiaofeng.c 萧峰(乔峰)

#include <ansi.h>
inherit NPC;

int check_out(object ob, object me);

void create()
{
        set_name("乔峰", ({"qiao feng", "qiao", "feng"}));
        set("gender", "男性");
        set("nickname",HIB"铁掌降龙"NOR);
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
        set("per", 19);
        set("dex", 30);
        set("chat_chance", 1);
        set("chat_msg", ({
                "萧峰叹了口气道：“唉……想不到我萧峰大好男儿，居然保护不了一个阿朱！\n",
        }));

        set("qi", 4000000);
        set("max_qi", 4000000);
        set("jing", 1500000);
        set("max_jing", 1500000);
        set("neili", 4000000);
        set("max_neili", 4000000);
        set("jiali", 2000);

        set("combat_exp", 1800000000);
        set("shen", 200000);

        set_skill("force", 1200);             // 基本内功
        set_skill("huntian-qigong", 1200);    // 混天气功
        set_skill("strike", 1200);           // 基本拳脚
        set_skill("dragon-strike", 1200);   // 降龙十八掌
        set_skill("dodge", 1200);             // 基本躲闪
        set_skill("xiaoyaoyou", 1200);        // 逍遥游
        set_skill("parry", 1200);             // 基本招架
        set_skill("begging", 500);            // 叫化绝活
        set_skill("checking", 500);           // 道听途说

        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dragon-strike");

        //set("master_ob", 4);
        set("auto_perform", 1);
        //set("clear_fuben", 1);
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        ::init();
        if( interactive(this_player()) && !is_fighting() )
                call_out("check_move", 2, this_object(), this_player());
}

int check_move(object ob, object me)
{
        remove_call_out("check_move");

        if( environment(ob)->query("short") == "游府后院" )
        {
                call_out("check_out", 180, ob, me);
                return 1;
        }

        if( !me || environment(ob) != environment(me) )
                call_out("check_move", 1, ob, me);
        else
        if( !ob->is_fighting() && !ob->is_busy() )
                ob->command("go west");
        else
                call_out("check_move", 1, ob, me);

        return 1;
}

int check_out(object ob, object me)
{
        if( !me || environment(me) != environment(ob) )
                die();

        me->remove_all_enemy(1);
        ob->remove_all_enemy(1);
        message_vision(HIY "$N终因寡不敌众，身受重伤。这时候一位黑衣老僧突然出现，将$N救走。\n" NOR,
                ob, me);
        me->set_temp("juxianzhuang_step", 14);
        return 1;
}

void die()
{
        object usr;
        string dir;
        string quest, userid;

        dir = base_name(environment(this_object()));
        if (sscanf(dir,"/f/%s/%s/maze",quest,userid)==2) {
                usr = find_player("userid");
                if( objectp(usr) )
                        usr->delete_temp("juxianzhuang_step");
                FUBEN_D->delay_clear_fuben(quest, userid);
        }
}