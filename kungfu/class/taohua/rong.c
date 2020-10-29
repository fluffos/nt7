// This program is a part of NT MudLIB

#include <ansi.h>
#include "taohua.h"
#include "game.h"

inherit NPC;
inherit F_NOCLONE;

string ask_chicken();
int ask_jiuyin();
int ask_game();

void create()
{
        set_name("黄蓉", ({"huang rong", "huang", "rong"}));
        set("title", "东海桃花岛主之女");
        set("nickname", HIY "丐帮前任帮主" NOR);
        set("gender", "女性");
        set("age", 28);
        set("long", "这便是桃花岛岛主的独生女儿。由于岛主夫人\n"
                    "早死，岛主对这个女儿备加疼爱。她生性跳脱\n"
                    "飞扬，喜欢四处乱跑。\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 28);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("qi", 4800);
        set("max_qi", 4800);
        set("jing", 3500);
        set("max_jing", 3500);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 200);
        set("level", 20);
        set("combat_exp", 3000000);

        set_skill("force", 240);
        set_skill("bibo-shengong", 240);
        set_skill("hand", 240);
        set_skill("strike", 240);
        set_skill("luoying-shenzhang", 240);
        set_skill("dodge", 240);
        set_skill("luoying-shenfa", 240);
        set_skill("parry", 220);
        set_skill("sword", 220);
        set_skill("luoying-shenjian", 220);
        set_skill("yuxiao-jianfa", 220);
        set_skill("lanhua-shou", 240);
        set_skill("staff", 240);
        set_skill("dagou-bang", 240);
        set_skill("unarmed", 200);
        set_skill("xiaoyaoyou", 200);
        set_skill("throwing", 200);
        set_skill("mantianhuayu", 200);
        set_skill("qimen-wuxing", 280);
        set_skill("count", 280);
        set_skill("literate", 280);
        set_skill("mathematics", 280);
        set_skill("cooking", 280);
        set_skill("martial-cognize", 220);

        map_skill("force", "bibo-shengong");
        map_skill("hand", "lanhua-shou");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "lanhua-shou");
        map_skill("staff", "dagou-bang");
        map_skill("sword", "yuxiao-jian");
        map_skill("strike", "xiaoyaoyou");
        map_skill("throwing", "mantianhuayu");

        prepare_skill("hand", "lanhua-shou");
        prepare_skill("strike", "xiaoyaoyou");

        create_family("桃花岛", 2, "爱女");

        set("inquiry", ([
                "九阴真经经义" : (: ask_jiuyin :),
                "游戏"   : (: ask_game :),
                "叫化鸡" : (: ask_chicken :),

        ]) );

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.fu" :),
                (: perform_action, "hand.fei" :),
                (: perform_action, "strike.zhuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 4);
        setup();
        carry_object("/clone/unique/ruanwei-jia")->wear();
        carry_object("/d/taohua/obj/shudai")->wear();
        set("startroom", "/d/wuguan/guofu_huayuan");
        check_clone();
}

void attempt_apprentice(object ob)
{
        command("say 现在国难当头，我哪里有时间收徒啊。");
        return;
}

string ask_chicken()
{
        if( query_temp("marks/鸡", this_player()) )
                return "你这个人怎么这么烦？老说车轱辘话！\n";
        else
        {
                say("蓉儿神往地说：叫化鸡可是杭州著名特产，我爹当年费了好大的劲才搞到了制作\n"
                    "它的秘方。你问它来干什么？\n");

                set_temp("marks/鸡", 1, this_player());

                return "你可以出去了。\n";
        }
}
int ask_jiuyin()
{
        object me = this_player();

        if( query("family/family_name", me) == "白驼山派" && !query("reserve", me )
                 && query("family/master_id", me) == "ouyang feng" )
        {
                if( query("combat_exp", me)>500000 && present("mask_jiuyin",me) )
                {
                        destruct( present("mask_jiuyin", me) );
                        message_vision(HIY "黄蓉眼中闪过一丝狡黠的神色：“你想知道真经的解释么？好吧，我说给你听便是。”\n", me);
                        message_vision("说罢，接过$N手中的经书，轻轻念了起来：\n", me);
                        message_vision("“「忽不尔，肯星多得，斯根六补」这是「善用观相，运作十二种息」的意思。\n", me);
                        message_vision("「吉尔文花思，哈虎」嗯....这个该作「能愈诸患，渐入神通」解...”\n", me);
                        message_vision(HIG "$N大为兴奋，忙凝神倾听，内息早于不知不觉中按照黄蓉所解之法四处游走......\n", me);
                        message_vision("$N的神智渐渐迷糊起来，忽而抓耳挠腮，忽而侧头苦思，种种怪状，令人不解。\n", me);
                        message_vision("突然间，$N反手啪啪啪连打自己三个耳光，双手撑地，倒立了起来，全身真气逆游乱走 \n"NOR, me);
                        if (random(5) == 3)
                        {
                                tell_object(me,"过了半晌，你只觉得全身经脉运行方式大为异常，略一提气，发现阴维，阳维，阴峤， \n");
                                tell_object(me,"阳峤四脉颇有逆行之势，不由得又惊又喜。\n");
                                set("reserve", 1, me);
                                addn("eff_jing", -100, me);
                                addn("max_neili", -2, me);
                        } else {
                                tell_object(me,"过了半晌，你心中一团乱麻，浑身乏力，头痛欲裂。一声嘶吼，晕了过去...\n");
                                addn("eff_jing", -100, me);
                                addn("max_neili", -2, me);
                                me->unconcious();
                        }
                        return 1;
                } else  return notify_fail("黄蓉白了你一眼：“就你这点微末道行，想学九阴真经？也不怕被人笑掉大牙么？”\n");
        } else return 0;
}

int ask_game()
{
        object me = this_player();
        object ob = this_object();

        if( query_temp("match_game/playing", me)){
                write("你已经在玩游戏了。\n");
                return 1;
        }
/*if( query_temp("match_game/lost", me)){
                message_vision( "$n仰起头不屑的对$N说道：你太笨了，我才不跟你玩呢。\n", me, ob );
                return 1;
        }*/
        if( query_temp("match_game/win", me)){
                message_vision( "$n点了点头道：好吧！上次侥幸让你赢了，这回你就没这么好运气了。\n", me, ob );
                delete_temp("match_game/win", me);
        }
        else
                message_vision( "$n眉头一扬，对$N说到：好啊，看看你到底有多聪明。\n", me, ob );
        return play_game(me,ob);
}
