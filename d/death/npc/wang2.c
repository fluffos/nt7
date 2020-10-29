#include <ansi.h>

inherit NPC;
inherit F_DEALER;

mixed ask_xiongba();

void create()
{
        set_name("王方平", ({ "wang fangping", "wang", "fangping" }));
        set("nickname", WHT "鬼王" NOR);
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 475);
        set("long", "王方平本是山中道士，后在丰都山修炼成仙，御封「鬼王」。\n");

        set_skill("unarmed", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("magic", 500);
        set_temp("apply/damage", 2000);
        set_temp("apply/parry", 2000);
        set_temp("apply/dodge", 2000);
        set_temp("apply/attack", 2000);
        set_temp("apply/force", 2000);

        set("combat_exp", 20000000);
        set("attitude", "friendly");
        /*
        set("vendor_goods", ({
                "/d/death/obj/weapon1",
                "/d/death/obj/weapon2",
                "/d/death/obj/weapon3",
                "/d/death/obj/weapon4",
                "/d/death/obj/weapon5",
                "/d/death/obj/weapon6",
                "/d/death/obj/weapon7",
                "/d/death/obj/weapon8",
                "/d/death/obj/weapon9",
                "/d/death/obj/weapon10",
                "/d/death/obj/weapon11",
                "/d/death/obj/weapon12",
                "/d/death/obj/weapon13",
                "/d/death/obj/weapon14",
                "/d/death/obj/weapon15",
                "/d/death/obj/weapon16",
                "/d/death/obj/weapon17",
                "/d/death/obj/weapon18",
                "/d/death/obj/weapon19",
                "/d/death/obj/weapon20",
                "/d/death/obj/weapon21",
                "/d/death/obj/weapon22",
                "/d/death/obj/weapon23",
                "/d/death/obj/weapon24",
                "/d/death/obj/weapon25",
                "/d/death/obj/weapon26",
                "/d/death/obj/weapon27",
                "/d/death/obj/weapon28",

                "/d/death/obj/weapon29",
                "/d/death/obj/weapon30",
                "/d/death/obj/weapon31",
                "/d/death/obj/weapon32",
                "/d/death/obj/weapon33",
                "/d/death/obj/weapon34",
                "/d/death/obj/weapon35",
                "/d/death/obj/weapon36",
                "/d/death/obj/weapon37",
                "/d/death/obj/weapon38",
                "/d/death/obj/weapon39",
                "/d/death/obj/weapon40",
                "/d/death/obj/weapon41",
                "/d/death/obj/weapon42",
                "/d/death/obj/weapon43",
                "/d/death/obj/weapon44",
                "/d/death/obj/weapon45",
                "/d/death/obj/weapon46",
                "/d/death/obj/weapon47",
                "/d/death/obj/weapon48",
                "/d/death/obj/weapon49",
                "/d/death/obj/weapon50",
                "/d/death/obj/weapon51",
                "/d/death/obj/weapon52",
                "/d/death/obj/weapon53",
                "/d/death/obj/weapon54",
                "/d/death/obj/weapon55",
                "/d/death/obj/weapon56",
                "/d/death/obj/weapon57",
                "/d/death/obj/weapon58",
                "/d/death/obj/weapon59",
                "/d/death/obj/weapon60",
                "/d/death/obj/weapon61",
                "/d/death/obj/weapon62",
                "/d/death/obj/weapon63",
                "/d/death/obj/weapon64",
                "/d/death/obj/weapon65",
                "/d/death/obj/weapon66",
                "/d/death/obj/weapon67",
                "/d/death/obj/weapon68",
                "/d/death/obj/weapon69",
                "/d/death/obj/weapon70",
                "/d/death/obj/weapon71",
                "/d/death/obj/weapon72",
                "/d/death/obj/weapon73",
                "/d/death/obj/weapon74",
                "/d/death/obj/weapon75",
                "/d/death/obj/weapon76",
                "/d/death/obj/weapon77",
                "/d/death/obj/weapon78",
                "/d/death/obj/weapon79",
                "/d/death/obj/weapon80",
        }));
        */
        set("inquiry", ([
                "锁阳丹" : "锁阳丹乃地狱神品，只有牛头王懂得制作，不过没有本王的允许他也不敢擅自制作锁阳丹。\n",
                "允许"   : "本王生前有一遗憾，愧对了自己的女儿，使之饱受轮回之苦，天下只有圣物\n" + 
                           "锦镧袈裟方可助她脱离苦海，重新投胎做人，如果阁下能帮助本王找到锦镧袈裟，本王到\n" +
                           "是可以破例一次，让牛头王帮你制作锁阳丹。\n",
                "锦镧袈裟" : "此乃袈裟中的上品，穿戴者可不坠地狱，不入轮回！\n"
                             "不过，听说世间上也只有莫邪能制作出锦镧袈裟。\n",  
                "雄霸天下" : (: ask_xiongba :),
                "霸刀"     : "霸刀乃当世绝学，练成之人当可雄霸天下，不过此间仍无人练成...\n",
        ]));

        setup();
        carry_object(__DIR__"obj/cloth4")->wear();
}
/*
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
*/


mixed ask_xiongba()
{
        object me;
        
        me = this_player();
        
        if (! objectp(me))return;
        
        if( !query("can_perform/badao/can_xiong", me) )
        {
                tell_object(me, HIG "王方平告诉你：我虽已得到锦镧袈裟让我亡女免受轮回之苦，但仍配合‘神圣血清’\n"
                                    "的力量方能成事，如果阁下能帮我找到神圣血清，我便传授你雄霸天下和阿鼻道第\n"
                                    "一招的绝招。\n" NOR);
                return "如何？";                 
        }
        
        if( query("can_perform/badao/xiong", me) )
                return "这绝招看来你已经会了，我没什么好帮你的了。\n";
                
        if (me->query_skill("badao", 1) < 700)
                return "看来你霸刀火候还不够，给你讲了也是白讲。\n";
                
        message_vision(HIY "$N" HIY "说道：既然如此，这雄霸天下的绝招就传你了，你可看好了，我只施展一次 ....\n", 
                       this_object());
                       
        tell_object(me, HIG "恭喜你，领悟了「雄霸天下」！\n" NOR);
        tell_object(me, HIG "恭喜你，领悟了阿鼻道第一刀！\n" NOR);
        
        tell_object(me, HIM "王方平悄悄对你说道：据说，只要你霸刀达到800级，这阿鼻道第二刀可找阴长生学习。\n" NOR);
        tell_object(me, HIM "王方平又对你说道：可是阴长生不会白教你，需要找到天下第一神酒--天乙神酒与他交换。\n" NOR);

        set("can_perform/badao/xiong", 1, me);
        set("can_perform/badao/san-1", 1, me);
        me->save();
        
        return "你我从此互不相欠，各走各路吧！\n";
}

int accept_object(object me, object obj)
{                       
        // 神圣血清
        if( query("id", obj) == "god blood" && 
            base_name(obj) == "/clone/fam/etc/prize5")
        {               
                if( query("can_perform/badao/can_xiong", me) )
                {
                        command("bow"+query("id", me));
                        command("say 多谢阁下仗义相助，了却本王的心愿。");
                        return 0;
                }
                command("nod"+query("id", me));
                command("say 既然你能帮我找到神聖血清，我也会履行我的诺言。");
                command("ke");
                command("say 我得赶去超度我亡女了，多谢！");
                tell_object(me, HIY "一阵声音从远处飘来：这雄霸天下和阿鼻道第刀的绝招你随时可以来找\n"
                                    "我学(ask wang about 雄霸天下)。\n" NOR);

                set("can_perform/badao/can_xiong", 1, me);
                me->save();
                destruct(obj);
                destruct(this_object());
                return 1;
        }
        if( query("badao_quest/suoyangdan_allow", me) )
        {
                command("bow"+query("id", me));
                command("say 多谢阁下仗义相助，了却本王的心愿。");
                return 0;
        }

        if( query("id", obj) == "jinlan jiasha" && 
            base_name(obj) == "/clone/armor/jinlan-jiasha")
        {
                command("yi"+query("id", me));
                command("say 这.. 这.. 不是锦镧袈裟吗，阁下居然能找到 ...");
                command("tan");
                command("say 既然如此，本王心愿已了，你去找牛头王帮你制作锁阳丹吧。");
                
                set("badao_quest/suoyangdan_allow", 1, me);
                me->save();
                destruct(obj);
                return 1;
        }
        else
                return 0;
        
        
                   
}
