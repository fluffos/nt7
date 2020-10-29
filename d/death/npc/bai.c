#include <ansi.h>
#include <command.h>
#include <login.h>

inherit NPC;

string ask_diyudao();

string *death_msg = ({
        HIW "白无常说道：喂！新来的，你叫什么名字？\n\n" NOR,
        HIW "白无常用奇异的眼光盯著你，好像要看穿你的一切似的。\n\n" NOR,
        HIW "白无常「哼」的一声，从袖中掏出一本像帐册的东西翻看著。\n\n" NOR,
        HIW "白无常合上册子，说道：咦？阳寿未尽？怎么可能？\n\n" NOR,
        HIW "白无常搔了搔头，叹道：罢了罢了，你走吧。\n\n"
                "一股阴冷的浓雾突然出现，很快地包围了你。\n\n" NOR,
});

void create()
{
        set_name("白无常", ({ "bai wuchang", "bai", "wuchang" }));
        set("title", HIR "冥府地藏王殿前" NOR);
        set("long", "\n白无常瞪著你，焦黄的脸上看不出任何喜怒哀乐。\n");
        set("attitude", "peaceful");
        set("chat_chance", 15);
        set("chat_msg", ({
                CYN "白无常狠狠的敲了敲你的脑袋，你觉得头晕晕的。\n", NOR,
                CYN "白无常嘿嘿奸笑两声。\n" NOR,
        }) );
        set("age", 217);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 250);

        set("combat_exp", 50000000);

        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("blade", 500);
        set_skill("staff", 500);
        set_skill("hammer", 500);
        set_skill("club", 500);
        set_skill("whip", 500);
        set_skill("dagger", 500);
        set_skill("throwing", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("never-defeated", 1000);
        set_skill("magic", 1000);

        map_skill("sword", "never-defeated");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "never-defeated");
        map_skill("dodge", "never-defeated");
        map_skill("force", "never-defeated");

        set("inquiry", ([
                "地狱道" : (: ask_diyudao :),
                "锦镧袈裟" : "此乃袈裟中的上品，穿戴者可不坠地狱，不入轮回！\n",                
        ]));
        setup();

        carry_object(__DIR__"obj/cloth1")->wear();
        carry_object(__DIR__"obj/suolian")->wield();
        set_temp("handing", carry_object(__DIR__"obj/book"));
}

void init()
{
        ::init();
        if (! previous_object() ||
            ! userp(previous_object()) ||
            ! previous_object()->is_ghost() ||
            wizardp(previous_object())) return;
        call_out("death_stage", 5, previous_object(), 0);
}

void death_stage(object ob, int stage)
{
        int i;
        object *inv, mailbox;
        if (! ob || ! present(ob)) return;

        tell_object(ob, death_msg[stage]);
        if (++stage < sizeof(death_msg))
        {
                call_out( "death_stage", 5, ob, stage );
                return;
        } else
                ob->reincarnate();

        if( query("reborn_offer", ob) && query("reborn_offer", ob) == "finish" )
        {
               ob->move("/d/death/youmingjie");
               return;
        }

        /*
        if (! wizardp(ob))
        {
                    inv = all_inventory(ob);
                    for (i = 0; i < sizeof(inv); i++)
                            DROP_CMD->do_drop(ob, inv[i]);
        }
        */
        
        ob->move(REVIVE_ROOM);
        set("startroom", REVIVE_ROOM, ob);
        message("vision", HIW "你忽然发现前面多了一个人影，不过那人影又好像已经在那里\n"
                          "很久了，只是你一直没发觉。\n" NOR, environment(ob), ob);
}

string ask_diyudao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "你的先天属性还不足以修炼地狱道，我看你还是先回去吧。\n";

        if( query("reborn/times", me)<3 )
                return "走开，走开，没看我正忙吗？\n";
                
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "哼，凡夫俗子，竟然如此贪心！\n";

        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此贪心！\n";        
                
        if (me->query_skill("diyu-dao", 1))
                return "怎么样，这招你练熟了吗？\n";
                
        command("nod");
        command("say 阎王爷吩咐过了，叫我在此等候有缘者，既然如此，这「地狱道」就传你吧！");
        
        message_sort(HIC "\n$N" HIC "掏出一根哭丧棒，挥舞了几下，然后猛然点向$n" HIC "周身大穴，招式"
                     "$n" HIC "平凡简单之极，但却蕴藏着任何人难以招架的力量，$n" HIC "倒退几步，双手"
                     "捂住胸口，一口鲜血吐出 ……。\n" NOR, this_object(), me);
                        
        command("heng");
        command("say 这些凡人还真是不中用，就这么几下就抵受不住了，哎~。");
        command("say 好了，这「地狱道」的功力已经传授给你了，此地不是你等长留之地，你还是速速离开吧！");
        
        tell_object(me, HIG "恭喜你领悟了「地狱道」剑法，目前等级为10级。\n" NOR);
        me->set_skill("diyu-dao", 10);
        
        return "好自为知！";
        
                
}
