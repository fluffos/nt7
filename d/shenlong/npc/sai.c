// 赛神龙

#include <ansi.h>

inherit NPC;

string ask_renjiandao();
string ask_shedong();
string ask_zhen();
string give_lhd();

void create()
{
        set_name("赛神龙", ({ "sai shenlong", "sai", "shenlong" }) );
        set("gender", "男性");
        set("age", 999999);
        set("long", "此人仙风道骨，眉目菱角分明，气宇轩昂。\n");
        set("attitude", "peaceful");
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 10000000);
        set("max_jing", 10000000);
        set("max_jingli", 10000000);        
        set("neili", 600000);
        set("max_neili", 600000);
        set("jiali", 100);

        set("combat_exp", 1000000000);

        set("inquiry", ([
                "蛇精" : "那九头蛇精就躲在蛇精洞内，只有用童男童女可将其引出。\n",
                "童男童女" : "如要找到蛇精可在蛇精洞用一对童男童女将其引出，但是，此法有违人道，\n" +
                             "当年我也是请张天师施法制作出童男童女符才将其引出的。\n",
                "人间道"   : (: ask_renjiandao :),   
                "蛇精洞"   : (: ask_shedong :),     
                "蛇精鳞片" : "当你打中蛇精时，会有一定几率掉出蛇精鳞片。\n",
                "真·六道轮回" : (: ask_zhen :),
                 //"轮回点"   : (: give_lhd :),
        ]));

        set_skill("unarmed", 2000);
        set_skill("sword", 2000);
        set_skill("blade", 2000);
        set_skill("staff", 2000);
        set_skill("hammer", 2000);
        set_skill("club", 2000);
        set_skill("whip", 2000);
        set_skill("dagger", 2000);
        set_skill("throwing", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
        set_skill("force", 2000);
        set_skill("lingbo-weibu", 2000);
        set_skill("lunhui-sword", 2000);  
        set_skill("never-defeated", 2000);  
        set_skill("martial-cognize", 2000);

        map_skill("sword", "lunhui-sword");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "lunhui-sword");
        map_skill("dodge", "lingbo-weibu");
        map_skill("force", "lunhui-sword");

        prepare_skill("unarmed", "never-defeated"); 
        
         set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
              (: perform_action, "sword.xiuluo" :),
              (: perform_action, "sword.lan" :),
              (: perform_action, "sword.zhen" :),              
              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "sword" :),                             
        }));
        
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhujian")->wield();

}

string ask_shedong()
{
        string msg;
        
        command("say 这蛇精洞内满布毒蛇，地形错综复杂，一不小心就会迷路。");
        command("say 如果要进蛇洞还是先熟悉下蛇精洞的地图吧：");
        
        write(@LONG
                              蛇王洞
                                |
                              毒蛇窟
                                |
                              毒蛇窟
                                |
                              毒蛇窟
                                |
                              毒蛇窟               
                                |
              毒蛇窟—毒蛇窟—神龙洞—out—蛇洞外
                                |
                              毒蛇窟
                                |
                              毒蛇洞
                                |
                              千蛇洞                             
                                |
                              千蛇洞
                                |
                              千蛇洞
                                |
                              千蛇洞—九头蛇洞—九头蛇洞
                                                   |
                                                蛇精洞外
                                                   |
                                                 蛇精洞
LONG);                                                 
        return "怎么样，记熟了吗？\n";
        
}

string give_lhd()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
      if( query("reborn/times", me) < 3 ) 
                return "走开，走开，没看我正忙吗？\n";
        
        if( query("scborn/get_lhd_sai", me) )
                return "轮回点你不是已经领取了吗？\n";
        
        if( query("scborn/total_lunhui_point", me) >= 18 )
                return "你的轮回点已经达到18点了，无法再领取。\n";
        
        if( query("scborn/total_lunhui_point", me)+3>18 )
                return "你如果领取轮回点就会超过18点了，无法再领取，如有BUG请速与本站管理员联系。\n";
                                
        // 已经完成任务
        if( query("scborn/lunhuidian/finish", me) )
                return "不错，不错，能从蛇精身上拿到鳞片的人少之有少，阁下算是其中一个。\n";

        // 分配任务
        if( !query("scborn/lunhuidian/give_quest", me) )
        {
                command("look"+query("id", me));
                command("say 这轮回点异常珍贵，只赠勇者，如果阁下能证明给我看，轮回点自当奉上。");
                command("say 前方不远处有一个蛇精洞，几百年前我将这妖孽镇压在此，使之无法在人间兴风作浪。");
                command("ke");
                command("say 如果阁下能从它身上取得50片蛇精鳞片，那就证明阁下必为勇者。");
                command("say 不过，蛇精乃千年妖孽，道行高深，你可要想清楚了！");
                
                tell_object(me, this_object()->name() + HIG "让你从蛇精身上取得鳞片，证明你是勇者。\n" NOR);
                set("scborn/lunhuidian/give_quest", 1, me);
                me->save();
                return "怎么样，有胆量去吗？";
        }
        
        // 完成任务        
        if (! objectp(ob_hlp = present("shejing linpian", me)))
                return "怎么样，50片蛇精鳞片取到了吗？\n";
                
        if (base_name(ob_hlp) != "/d/shenlong/npc/obj/linpian")
                return "怎么样，50片蛇精鳞片取到了吗？\n";
        
        if ("/adm/daemons/stored"->get_ob_amount(me, ob_hlp) >= 50)
        {
                for (i = 1; i <= 50; i++)
                {
                        destruct(ob_hlp);
                        ob_hlp = present("shejing linpian", me);
                }
        }
        else
        {
                return "怎么样，50片蛇精鳞片取到了吗？\n";
        }
        
        command("hehe");
        command("nod"+query("id", me));
        command("say 不错，既然是勇者，这轮回点就奉送给你了。");        
                             
        tell_object(me, HIG "恭喜你获得了 3 点轮回点。\n");

        set("scborn/lunhuidian/finish", 1, me);
        addn("scborn/cur_lunhui_point", 3, me);
        addn("scborn/total_lunhui_point", 3, me);
        set("scborn/get_lhd_sai", 1, me);

        me->save();
        
        return "佩服，佩服！";        
}

string ask_renjiandao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "你的先天属性还不足以修炼人间道，我看你还是先回去吧。\n";

        if( query("reborn/times", me) < 3 )
                return "此处不是尔等驻留之地，还是速速离去吧。\n";
                
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me) < 4 )
                return "哼，凡夫俗子，竟然如此贪心！\n";

        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此贪心！\n";
                
        if (me->query_skill("renjian-dao", 1))
                return "怎么样，这招你练熟了吗？\n";
                
        command("nod");
        command("say 千百年来，我在此镇守蛇精，洞外毒蛇密布，非等闲之辈能够进入。");
        command("look "+query("id", me));
        command("say 阁下武艺超群，既然到此，你我也算一场缘分，这「人间道」就传你吧！");

        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳边悄悄说了几句，然后又拿出一本书，指指点点，"
                     "$n" HIC "不住地点头，忽而眉头深锁，忽而低头沉思 ……\n良久，$n" HIC "大笑一声，似乎"
                     "对刚才的疑虑有所顿悟。\n", this_object(), me);

        command("nod "+query("id", me));

        tell_object(me, HIG "恭喜你领悟了「人间道」剑法，目前等级为10级。\n" NOR);
        me->set_skill("renjian-dao", 10);
        
        return "好自为知吧！";
        
                
}
int accept_kill(object me)
{
        command("heng");
        command("say 很好！");
        return 1;
}

void unconcious()
{
       die();
}

void die()
{
        command("chat 不可能，不可能 ……");
        destruct(this_object());
}

int accept_object(object me, object ob)
{

        if (base_name(ob) != "/clone/lonely/book/dugubook")
        {
                command("say 你给我这种东西干什么？");
                return 0;
        }


        destruct(ob);
        return 1;
}

// 真·六道轮回
string ask_zhen()
{
        object *obs; 
        object ob;
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("reborn/times", me) < 3)
                return "走开，走开，没看我正忙吗？\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me) < 4 )
                return "阁下武功已经独步天下，何必如此贪心?\n";

        if( query("max_neili", me)<10000 )
                return "你的内力修为不够，这招我还不能传你。\n";

        if ((int)me->query_skill("buddhism", 1) < 200)
                return "你对禅宗心法参悟不够，这招我还不能传你。\n";

        if ((int)me->query_skill("lunhui-sword", 1) < 900)
                return "你六道轮回剑火候不够，这招我还不能传你。\n";

        // 已经完成任务
        if( query("lunhui-sword_quest/zhen/finish", me) )
                return "不错，不错，能从蛇精身上拿到鳞片的人少之有少，阁下算是其中一个。\n";
        
        /*
        // 检查轮回点        
        if( query("scborn/cur_lunhui_point", me)<6 && !query("thborn/ok", me) )
                return "可惜啊，你轮回点不足，无法领悟到此招。\n";
        */
        
        // 分配任务
        if( !query("lunhui-sword_quest/zhen/give_quest", me) )
        {
                command("look "+query("id", me));
                command("say 学此招者，必为勇者，如果阁下能证明给我看，此招便倾囊相受。");
                command("say 前方不远处有一个蛇精洞，几百年前我将这妖孽镇压在此，使之无法在人间兴风作浪。");
                command("ke");
                command("say 如果阁下能从它身上取得10片蛇精鳞片，那就证明阁下必为勇者。");
                command("say 不过，蛇精乃千年妖孽，道行高深，你可要想清楚了！");
                
                tell_object(me, this_object()->name() + HIG "让你从蛇精身上取得鳞片，证明你是勇者。\n" NOR);
                set("lunhui-sword_quest/zhen/give_quest", 1, me);
                me->save();
                return "怎么样，有胆量去吗？";
        }
        
        // 完成任务        
        if (! objectp(ob_hlp = present("shejing linpian", me)))
                return "怎么样，10片蛇精鳞片取到了吗？\n";
                
        if (base_name(ob_hlp) != "/d/shenlong/npc/obj/linpian")
                return "怎么样，10片蛇精鳞片取到了吗？\n";
        
        obs = all_inventory(me); 
        obs = filter_array(obs, (: base_name($1) == "/d/shenlong/npc/obj/linpian" :)); 
        if( sizeof(obs) < 10 ) 
                return "怎么样，10片蛇精鳞片取到了吗？\n";

        for (i = 0; i < 10; i++) 
        { 
                ob = obs[i]; 
                obs[i] = 0; 
                destruct(ob); 
        }
        
        command("hehe");
        command("nod "+query("id", me));
        command("say 不错，既然是勇者，这「真·六道轮回」就传你了，你可听好了 ……");
        
        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳边悄悄说了几句，然后又拿出一本书，指指点点，"
                     "$n" HIC "不住地点头，忽而眉头深锁，忽而低头沉思 ……\n良久，$n" HIC "大笑一声，似乎"
                     "对刚才的疑虑有所顿悟。\n", this_object(), me);
                             
        tell_object(me, HIG "恭喜你学会了「真·六道轮回」。\n");
        set("can_perform/lunhui-sword/zhen", 1, me);
        set("lunhui-sword_quest/zhen/finish", 1, me);
        
        /*
        // 扣除轮回点
        if( !query("thborn/ok", me) )
                addn("scborn/cur_lunhui_point", -6, me);

        // 设置扣除轮回点的出处
        if( !query("thborn/ok", me) )
                set("scborn/perform_zhen_saishenlong", 1, me);
        */
        me->save();
        
        return "佩服，佩服！";
        
                
}