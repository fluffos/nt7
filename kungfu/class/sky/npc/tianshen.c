// 通天老仙 掌管转世
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

#define MEMBER_D   "/adm/daemons/memberd"
#define FUBEN_D    "/adm/daemons/fuben_daemonsd"

mixed start_thborn();

void create()
{
        set_name(HIY "炎黄天神" NOR, ({ "yanhuang tianshen", "yanhuang", "tianshen" }));
        set("long", HIY "    炎黄天神威风凛凛，在此恭候您多时了，想要\n"
                        "通过二次转生，必须接受天神的考验。\n" NOR);

        set("gender", "男性");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "二转"   :   (: start_thborn :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/xianpao")->wear();
}

mixed start_thborn()
{
        object me = this_player();
        
        string item1, item2;
        object ob1, ob2;
        
        string *keys_item1, *keys_item2;        
        object ob_taixu, ob_boss;
        
        mapping  ob_list1 = ([
                "将军令"            : "/clone/misc/boss_item/jiangjun-ling",
                "富士山风景画"      : "/clone/misc/boss_item/fengjing-hua",
                "暗杀名单"          : "/clone/misc/boss_item/ansha-mingdan",
                "交子"              : "/clone/misc/boss_item/jiaozi",
                "《樱花赞》"        : "/clone/misc/boss_item/yinghua-zan",
                "安守阁地图"        : "/clone/misc/boss_item/anshouge-tu",
                "天师鬼符"          : "/clone/misc/boss_item/tianshi-guifu",            
        ]);        
                
        mapping  ob_list2 = ([
                "将军令"            : "/clone/misc/boss_item/jiangjun-ling",
                "富士山风景画"      : "/clone/misc/boss_item/fengjing-hua",
                "暗杀名单"          : "/clone/misc/boss_item/ansha-mingdan",
                "交子"              : "/clone/misc/boss_item/jiaozi",
                "《樱花赞》"        : "/clone/misc/boss_item/yinghua-zan",
        ]);                
        
        // 检查转世条件
        if (! me->query("scborn/ok"))
                return "你还没有通过转世，不能进行二转！\n";
        
        if (me->query("thborn/ok"))
        {
                if (me->query("thborn/repeat"))// 重新2转
                {
                        tell_object(me, HIG "\n你可以进入重新二转！\n" NOR);
                        me->move("/kungfu/class/sky/sky2zhuan");
                        return 1;
                }
                return "你不是已经二转了吗，还来干什么！\n";
        }

        if (me->query("combat_exp") < 380000000)
                return "你的实战经验不足3.8亿，不能进行二转！\n";
                
        if (me->query_skill("force", 1) < 1500)
                return "你基本内功不足1500级别，不能进行二转！\n";

        if (me->query_skill("dodge", 1) < 1500)
                return "你基本轻功不足1500级别，不能进行二转！\n";
                
        if (me->query_skill("parry", 1) < 1500)
                return "你基本招架不足1500级别，不能进行二转！\n";

        if (! MEMBER_D->is_valib_member(me->query("id")))
                return "你不是有效会员，不能进行二转！\n";
                          
        // 已经接了任务                          
        if (sizeof(me->query("scborn/thborn_item1_id")))
        {
                if (! objectp(ob1 = present(me->query("scborn/thborn_item1_id"), me)) && ! me->query("scborn/item_ok"))
                {
                        return me->query("scborn/thborn_item1_name") + NOR "你找到了吗！\n";
                }
                if (! objectp(ob2 = present(me->query("scborn/thborn_item2_id"), me)) && ! me->query("scborn/item_ok"))
                {
                        return me->query("scborn/thborn_item2_name") + NOR "你找到了吗！\n";
                }
                /*
                // 测试期间不开放挑战BOSS
                if (me->query("id") != "rcwiz" && me->query("id") != "axiao" && me->query("id") != "mrhy")
                {
                        message_sort(HIM "\n$N" HIM "对$n" HIM "说道：不错！不错！看来你已经通过了第一"
                                         "轮考验，现在我将送你进入无尽太虚之中挑战二转守护神，打败守护"
                                         "神便可开启二转之门！\n", this_object(), me);
                        tell_object(me, HIG "无尽太虚之门还未开启，请保留好你的任务物品，开放日程请留意系统通告！\n" NOR);                                 
                        return 1;
                }
                */
                // 两样都找到了
                if (! me->query("scborn/item_ok"))
                {
                        destruct(ob1);
                        destruct(ob2);
                }
                
                me->set("scborn/item_ok", 1);
                
                message_sort(HIM "\n$N" HIM "对$n" HIM "说道：不错！不错！看来你已经通过了第一"
                                 "轮考验，现在我将送你进入无尽太虚之中挑战二转守护神，打败守护"
                                 "神便可开启二转之门！\n\n", this_object(), me);

                CHANNEL_D->do_channel(this_object(), "rumor", HIY +  me->name() + "(" + me->query("id") + ")" HIM "被炎黄天神"
                                                              "送入无尽太虚，挑战二转守护神！" NOR);        
                                                                              
                ob_taixu = new("/kungfu/class/sky/wujin-taixu");
                ob_boss = new("/kungfu/class/sky/npc/shouhushen");
                ob_boss->move(ob_taixu);
                ob_boss->set("myroom", ob_taixu);
                
                FUBEN_D->move_lonely_fb_room(me, ob_taixu, "系统提示：进入无尽太虚，离开请进入 out 出口！", "", "");        
                
                me->save();                                              
                return 1;                                                              
        }
        else
        {
                keys_item1 = keys(ob_list1);
                keys_item2 = keys(ob_list2);
                
                if (me->query_skill("force", 1) < 1800)
                {                        
                        item1 = keys_item2[random(sizeof(ob_list2))];
                        ob1 = new(ob_list2[item1]);                        
                        //ob_list2 -= ([ item1 ]);
                        keys_item2 -= ({ item1 });
                        item2 = keys_item2[random(sizeof(keys_item2))];                        
                        me->set("scborn/thborn_item1_name", item1);

                        me->set("scborn/thborn_item1_id", ob1->query("id"));
                        me->set("scborn/thborn_item2_name", item2);
                        ob2 = new(ob_list2[item2]);
                        me->set("scborn/thborn_item2_id", ob2->query("id"));
                        destruct(ob1);
                        destruct(ob2);        
                }
                else
                {
                        item1 = keys_item1[random(sizeof(ob_list1))];
                        ob1 = new(ob_list1[item1]);                        
                        //ob_list1 -= ([ item1 ]);
                        keys_item1 -= ({ item1 });
                        item2 = keys_item1[random(sizeof(keys_item1))];
                        
                        me->set("scborn/thborn_item1_name", item1);
                        me->set("scborn/thborn_item1_id", ob1->query("id"));
                        me->set("scborn/thborn_item2_name", item2);
                        ob2 = new(ob_list1[item2]);
                        me->set("scborn/thborn_item2_id", ob2->query("id"));
                        destruct(ob1);
                        destruct(ob2);
                }

                message_sort(HIM "\n$N" HIM "对$n" HIM "说道：天道有序，即使阁下通过第一次转生"
                                 "获取了超越常人的能力，但是，第二次转生需要自身达到意识上的超"
                                 "脱激发体内蕴藏的巨大能量，从而真正的摆脱天道的束缚，脱胎换骨。"
                                 "看来你已经获得了二次转生的基本条件，现在，你只需要接受最后的"
                                 "考验，本大神便可协助你完成二次转生。\n"
                                 HIM "$N" HIM "顿了顿继续道：如果你能找到" + item1 + HIM "和" +
                                 item2 + HIM "交给本大神，我便可以协助你进入无尽太虚，挑战二转"
                                 "守护神！\n", this_object(), me);
                     
                tell_object(me, HIG "提示：如果你找到" + item1 + HIG "和" + item2 + HIG "请再次来与天神对话！\n" NOR);
        }
        
        me->save();

        return 1;
}

void unconcious()
{
        die();
}
