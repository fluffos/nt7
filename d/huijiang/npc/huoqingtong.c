// huo.c 霍青桐

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

mixed ask_me();

void create()
{
        set_name("霍青桐", ({ "huo qingtong", "huo","qingtong" }));
        set("long", 
"这女郎秀美中透着一股英气，光彩照人，当真是丽若春梅绽雪，神如
秋蕙披霜，两颊融融，霞映澄塘，双目晶晶，月射寒江。腰插匕首，
长辨垂肩，一身鹅黄衫子，头戴金丝绣的小帽，帽边插了一根长长的
翠绿羽毛，革履青马，旖旎如画。\n");
        set("nickname", HIG"翠羽"HIY"黄衫"NOR);
        set("gender", "女性");
        set("class", "swordsman");
        set("age", 18);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 30);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 2000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 600000);

        set_skill("literate", 150);
        set_skill("force", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("sword", 150);
        set_skill("hand", 150);
        set_skill("claw", 150);
        set_skill("yunlong-xinfa", 150);
        set_skill("yunlong-shengong", 150);
        set_skill("sanfen-jianshu", 150);
        set_skill("yunlong-shenfa", 150);
        set_skill("yunlong-shou", 150);
        set_skill("yunlong-zhua", 150);

        map_skill("dodge", "yunlong-shenfa");
        map_skill("force", "yunlong-shengong");
        map_skill("hand", "yunlong-shou");
        map_skill("parry", "sanfen-jianshu");
        map_skill("claw", "yunlong-zhua");
        map_skill("sword", "sanfen-jianshu");

        prepare_skill("hand","yunlong-shou");
        prepare_skill("claw","yunlong-zhua");

        set("inquiry", ([
                "三分剑术": (: ask_me :),
                "绝招"  : (: ask_me :),
                "海市蜃楼": (: ask_me :),
                "绝迹"  : (: ask_me :),
                "绝技"  : (: ask_me :),
        ]));

        set("env/wimpy", 60);
        set_temp("is_riding", HIC"青骢马"NOR); 
        set("env/wimpy", 40);

        setup();
        carry_object("/d/hangzhou/honghua/obj/cuiyu")->wear();
        carry_object("/d/hangzhou/honghua/obj/huangshan")->wear();
        carry_object("/d/hangzhou/honghua/obj/shortsword")->wield();
        carry_object("/d/hangzhou/honghua/obj/horse");
        // carry_object("/clone/cloth/yellow_cloth");
}

void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        command("ride horse");
}
mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/sanfen-jianshu/haishi", me) )
                return "咦？你不是已经会了吗？";

        if( !query("story/sanfenjian", me) )
                return "你这是什么意思？";

        if (me->query_skill("sanfen-jianshu", 1) < 150)
                return "你的三分剑术还不到家，要多练练！";

        message_vision(HIY "$n" HIY "点了点头，拔出手中" NOR +
                       HIC "短剑" NOR + HIY "，突然圈转，一"
                       "招之中另蕴涵三招，招式繁复狠辣，剑"
                       "招虚虚\n实实，正是三分剑术的独得之秘"
                       "——「海市蜃楼」。\n" NOR,
                       me, this_object());
        command("nod");
        command("say 你可明白了？");
        tell_object(me, HIC "你学会了「海市蜃楼」这一招。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 350000);
        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 350000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 350000);
        if (me->can_improve_skill("sanfen-jianshu"))
                me->improve_skill("sanfen-jianshu", 350000);
        set("can_perform/sanfen-jianshu/haishi", 1, me);
        return 1;
}

