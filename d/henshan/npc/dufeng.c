#include <ansi.h>
inherit BUNCHER;
inherit F_DEALER;

string ask_eguidao();

void create()
{
        set_name("杜凤鄂", ({ "du fenge", "du", "fenge" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long", "杜凤鄂一脸惆怅，不知道他心中所烦为何事。\n");
        set("combat_exp", 400000);
        set("attitude", "friendly");
        set("no_get", "1");
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_temp("apply/damage", 25);

        set("inquiry", ([
                "狐仙"   : "听说狐能化成狐仙，我倒是遇见过一回。\n",
                "绯胭"   : "绯胭姑娘好久没有来买我的画了，不知道她现在怎么样了？\n",
                "饿鬼道" : (: ask_eguidao :),
                
        ]));
        set("vendor_goods", ({
                "/clone/tattoo/face1",
                "/clone/tattoo/face2",
                "/clone/tattoo/face3",
                "/clone/tattoo/face4",
                "/clone/tattoo/face5",
                "/clone/tattoo/face6",
                "/clone/tattoo/face7",
                "/clone/tattoo/face8",
                "/clone/tattoo/face9",
                "/clone/tattoo/face10",
                "/clone/tattoo/face11",
                "/clone/tattoo/face12",
                "/clone/tattoo/face13",
                "/clone/tattoo/face14",
                "/clone/tattoo/face15",
                "/clone/tattoo/face16",
                "/clone/tattoo/face17",
                "/clone/tattoo/face18",
                "/clone/tattoo/face19",
                "/clone/tattoo/face20",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

// 饿鬼道
// 需要100张狐狸皮
string ask_eguidao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "你的先天属性还不足以修炼饿鬼道，我看你还是先回去吧。\n";

        if( query("reborn/times", me)<3 )
                return "哼，我看你才像个什么饿鬼，没事别来烦我，走开！\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "阁下武功已经独步天下，恭喜恭喜！\n";

        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此贪心！\n";
                                
        // 是否阅读过狐仙书
        if( !query("lunhui-sword_quest/read_huxian_book", me) )
        {
                    
                command("tan");
                return "你听过" HIM "狐仙" NOR "的故事吗？\n";
        }
        
        // 已经完成任务
        if( query("lunhui-sword_quest/eguidao/finish", me) )
                return "呵呵，你上次找的那些狐狸皮质地不错，绯胭她很是喜欢。\n";

        // 分配任务
        if( !query("lunhui-sword_quest/eguidao/give_quest", me) )
        {
                command("tan");
                command("say 我现在急需五十张白狐皮来缝制狐皮大衣，绯胭应该会很高兴的！");
                command("ke");
                command("say 能帮我完成这个心愿吗？");
                tell_object(me, this_object()->name() + HIG "让你帮他搜集50张白狐皮，赶快去吧！\n" NOR);
                set("lunhui-sword_quest/eguidao/give_quest", 1, me);
                me->save();
                return "事成之后，我会告诉你一个天大的秘密！";
        }
        
        // 完成任务
        
        if (! objectp(ob_hlp = present("baihu pi", me)))
                return "怎么样，50张白狐皮搜集够了吗？\n";
                
        if (base_name(ob_hlp) != "/clone/quarry/item/lipi2")
                return "怎么样，50张白狐皮搜集够了吗？\n";
 
        if (ob_hlp->query_amount() >= 50)
        {
                ob_hlp->add_amount(-50);
                if (ob_hlp->query_amount() < 1)destruct(ob_hlp);
        }
        else
        {
                return "怎么样，50张白狐皮搜集够了吗？\n";
        }
        
        command("hehe");
        command("nod");
        command("say 既然你帮我了这个忙，我就告诉你一个秘密 ...");
        
        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳边悄悄说了几句，然后又拿出一本书，指指点点，"
                     "$n" HIC "不住地点头，忽而眉头深锁，忽而低头沉思 ……\n良久，$n" HIC "大笑一声，似乎"
                     "对刚才的疑虑有所顿悟。\n", this_object(), me);
                     
        
        tell_object(me, HIG "恭喜你领悟了「饿鬼道」剑法，目前等级为10级。\n");
        me->set_skill("egui-dao", 10);
        set("lunhui-sword_quest/eguidao/finish", 1, me);
        
        return "明白了？";
        
                
}

void init()
{       
        object ob; 

        ob = this_player();

        ::init();
        if (interactive(ob) && ! is_fighting()) 
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        say(CYN "杜凤鄂摇了摇头道：这位" + RANK_D->query_respect(ob) +
            "你相信狐能化成狐仙吗？\n" NOR);

        return;
}
