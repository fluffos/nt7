#include <ansi.h>
inherit NPC;

mixed teach_hunting();
string ask_chushengdao();

void create()
{
        set_name("猎人", ({"hunter"}));
        set("gender", "男性" );
        set("class", "swordman");
        set("age", 45);
        set("str", 200);
        set("con", 26);
        set("int", 28);
        set("dex", 200);
        set("combat_exp", 12000000);
        set("attitude", "peaceful");

        set_skill("unarmed", 300);
        set_skill("dodge", 300);
        set_skill("hunting", 2000);

        set("max_qi", 4500);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 150);

        set("inquiry", ([
                "hunting" : ( :teach_hunting: ),
                "捕猎"    : ( :teach_hunting: ),
                "畜生道"  : (: ask_chushengdao :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

 }

int accept_object(object me, object ob)
{
        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, me) ) return notify_fail("你没有这件东西。");
        if( query("id", ob) == "bushou jia" )
        {
                command("nod");
                command("say 这个我正用得着，在下无以为报，如果你愿意，我\n可以"
                        "教你一些捕猎的技巧。");
                 set_temp("marks/hunter", 1, me);
                return 1;
        }
        else
        {
                 command("shake");
                 command("say 这是什么东西，我不需要！");
        }

           return 1;
}



mixed teach_hunting()
{
        object me = this_player();
        int jing, add;

        jing=query("jing", me);
        add = me->query_int() + random(me->query_int() / 2 );

        if( !query_temp("marks/hunter", me) )
                return "你我素无往来，何出此言？\n";

        if (me->is_busy() || me->is_fighting())
        {
                write("你现在正忙着。\n");
                return 1;
        }

        if (jing < 20)
        {
                write("你的精神无法集中。\n");
                return 1;
        }

        if( (query("potential", me)-query("learned_points", me))<1 )
        {
                write("你的潜能不够，无法继续学习。\n");
                return 1;
        }
        write(HIW "猎人给你讲解了有关捕猎的一些技巧。\n" NOR);
        write(HIY "你听了猎人的指导，似乎有所心得。\n" NOR);

        addn("learned_points", 1, me);

        me->improve_skill("hunting", add);

        addn("jing", -(5+random(6)), me);

        return 1;

}

string ask_chushengdao()
{
        object me;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "你的先天属性还不足以修炼畜生道，我看你还是先回去吧。\n";


        if( query("reborn/times", me)<3 )
                return "走开，走开，没看我正忙吗？\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "阁下武功已经独步天下，何必如此贪心?\n";
                        
        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此贪心！\n";
                                        
        // 已经完成任务
        if( query("lunhui-sword_quest/chushengdao/finish", me) )
                return "呵呵，阁下武功非凡，世间罕有，令在下佩服、佩服。\n";

        // 分配任务
        // 杀黄金白玉虎
        if( !query("lunhui-sword_quest/chushengdao/give_quest", me) )
        {
                command("look"+query("id", me));
                command("say 阁下看来并非泛泛之辈，既然你有求于我，那你得先帮我一个忙！");
                command("tan");
                command("say 前方不远处有一片树林，在下三代在此狩猎，一直风平浪静，也算落得个丰衣足食，自在快活！");
                command("say 前不久，树林里出现一只猛兽，将树林里的其他动物全都赶跑了，不少猎人也惨糟其毒手。");
                command("say 据说，那是一只存活千年的黄金白玉虎，凶猛非常，不少武林高手前去都无一生还 ……");
                command("look"+query("id", me));
                command("say 阁下如果有本事收拾那畜生，我这祖传绝学便可倾囊相受。");
                tell_object(me, this_object()->name() + HIG "让你帮他解决掉黄金白玉虎！\n" NOR);
                set("lunhui-sword_quest/chushengdao/give_quest", 1, me);
                me->save();
                return "怎么样，敢去吗？";
        }
        
        // 完成任务
        if( !query("lunhui-sword_quest/chushengdao/killed", me) )
                return "怎么样，解决掉黄金白玉虎了吗？\n";

        command("hehe");
        command("nod"+query("id", me));
        command("say 好！好！好！阁下武功非凡，在下佩服，这就传你「畜生道」……");

        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳边悄悄说了几句，然后又拿出一本书，指指点点，"
                     "$n" HIC "不住地点头，忽而眉头深锁，忽而低头沉思 ……\n良久，$n" HIC "大笑一声，似乎"
                     "对刚才的疑虑有所顿悟。\n", this_object(), me);

        tell_object(me, HIG "恭喜你领悟了「畜生道」剑法，目前等级为10级。\n");
        me->set_skill("chusheng-dao", 10);
        set("lunhui-sword_quest/chushengdao/finish", 1, me);
        
        return "保重！";
        
                
}
