// dizangwang

#include <ansi.h>
#define QILIN_XUE    "/d/death/obj/qilinxue"

inherit NPC;

mixed ask_xue();
mixed ask_reborn();

void create()
{
        set_name("地藏王", ({ "dizang", }));
        set("long", "他容貌威严，不可一世。哇！他可是掌管人间生死的神仙。\n");
        set("gender", "男性");
        set("age", 99);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("per", 18);
        set("attitude", "peaceful");
        set("str", 31);
        set("int", 39);
        set("con", 34);
        set("dex", 36);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 800);

        set("combat_exp", 50000000);
                
        set_skill("unarmed", 1500);
        set_skill("finger", 1500);
        set_skill("parry", 1500);
        set_skill("dodge", 1500);
        set_skill("force", 1500);
        set_skill("sword", 1500);
        set_skill("count", 1500);
        set_skill("kuihua-mogong", 1500);
        set_skill("martial-cognize", 1500);
        set_skill("literate", 220);

        map_skill("parry", "kuihua-mogong");
        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("finger", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");

        prepare_skill("finger", "kuihua-mogong");     
           
        set("inquiry", ([
                "麒麟靴"   : (: ask_xue :),
                "转世"     : (: ask_reborn :),                
                "重生"     : (: ask_reborn :),
                "转生"     : (: ask_reborn :),
                "转世重生" : (: ask_reborn :),
        ]));
        
        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
        carry_object("/clone/misc/spin")->wield();
                
        create_family("冥府地藏王殿前", 1, "幽冥之主");
        set("title", HIR "幽冥之主" NOR);
}

int attempt_apprentice(object ob)
{
        if( !query("born", ob) )
        {
                command("say 你快投胎去，在这里瞎搅和什么？");
                return 0;
        }

        command("say 滚！给我一边儿去！");
}

mixed ask_xue()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( !query("hell_quest/锁阳丹", me) )
                return "其麒麟靴是我的宝物，你打听它干什么？";

        ob = find_object(QILIN_XUE);
        if (! ob) ob = load_object(QILIN_XUE);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "麒麟靴不是在你的手中么，怎么反而来找我呢？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "我已经把麒麟靴已经借出去了。";

                        return "麒麟靴现在落在"+query("name", owner)+
                               "手中，你去把他找回来吧。";
        }

        ob->move(this_object());
        message_vision("$N点点头道：“好，既然你是为了老夫的锁阳丹之事，老夫就借给你吧！”\n", 
                       this_object(), me);
 command("give boots to "+query("id", me));
        return 1;
}

mixed ask_reborn()
{
        object who;
        
        who = this_player();

        if( !query("reborn_lunhui", who)){
                message_vision( BLU "$N" BLU "对$n" BLU "一拱手，道：你想转世先过了六道守卫佛这一关再说！\n", 
                                this_object(), who );
                return 1;
        }      
          
        if( query("betrayer", who) )
        {
                message_vision("$N对$n怒道：你还是先把与判师门派中的纠葛解决了再来！\n",
                               this_object(), who);
                return 1;
        }

        message_vision( BLU "$N" BLU "点点头道：“好，既然你闯过地府的考验，老夫就送你上天界直接面见佛祖！”\n"
                        BLU "$N" BLU "随手一招，突然刮起一阵阴风，将$n" BLU "带到极乐世界。\n" NOR, 
                        this_object(), who );                            
                 
        who->move("/d/reborn/heaven");
        set("startroom", "/d/reborn/heaven", who);
        return 1;
}
