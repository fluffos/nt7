// This program is a part of NT MudLIB

#include <ansi.h>
inherit NPC;

inherit F_DEALER;

int ask_xueyi();
string ask_xiao();

void create()
{
        set_name("曲三", ({ "qu san", "san", "qu" }));
        set("title", "酒店老板");
        set("nickname", "跛子");
        set("gender", "男性");
        set("age", 25);
        set("long",
                "他是最近新搬到此地的一个跛子。他无精打彩地招呼着客人，"
                "眼睛不时呆呆地看着天空。\n");
        set("attitude", "friendly");
        set("class", "scholar");
        set("str", 30);
        set("int", 24);
        set("con", 27);
        set("dex", 23);
        set("shen_type",1);
        set("max_qi", 4500);
        set("max_jing", 2500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 120);
        set("level", 20);
        set("combat_exp", 1000000);

        set_skill("force", 200);
        set_skill("bibo-shengong", 200);
        set_skill("unarmed", 180);
        set_skill("xuanfeng-tui", 180);
        set_skill("strike", 180);
        set_skill("luoying-shenzhang", 180);
        set_skill("finger", 200);
        set_skill("throwing", 200);
        set_skill("tanzhi-shentong", 200);
        set_skill("dodge", 200);
        set_skill("luoying-shenfa", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("luoying-shenjian", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 180);

        map_skill("force", "bibo-shenfa");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike", "luoying-shenzhang");
        map_skill("finger", "tanzhi-shengong");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "luoying-shenjian");
        map_skill("sword", "luoying-shenjian");

        prepare_skill("finger", "tanzhi-shentong");

        set("xiao_count", 1);

        set("attitude", "friendly");
        set("inquiry", ([
                "黄药师" : "我师…，什么？我这里不卖药。\n",
                "卖药"   : "不卖药就是不卖药。\n",
                "曲灵风" : "啊！我，……你说的人我不认识。\n",
                "生意"   : "这个么……。\n",
                "学艺"   : (: ask_xueyi :),
                "古玩"   : (: ask_xiao :),
        ]));

        // create_family("桃花岛", 2, "弟子");
        set("vendor_goods", ({
                "/d/city/obj/peanut",
        }));

        setup();
        carry_object("/d/city/obj/cloth")->wear();
        carry_object("/d/taohua/obj/bagua");
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if (!ob || environment(ob) != environment())
                return;

        say("曲三有气无力地说道：这位" + RANK_D->query_respect(ob) +
            "，买点五香花生下酒吧。\n");
}

/*
void unconcious()
{
        object ob;
        object who = this_player();

        message_vision("\n突然，只见曲三用尽最后一丝气力向$N打出一个铁八卦！\n",
                who);
        who->receive_damage("qi",100);
        who->receive_wound("qi",100);
        ob = new (__DIR__"obj/tiebagua");
        ob->move(environment(this_object()));
        :: unconcious();
}
*/

int accept_object(object me, object obj)
{
        call_out("accept_obj", 1, me, obj);
        return 1;
}

int accept_obj(object me, object obj)
{
        if( query("name", obj) == "黄药师手谕" )
        {
                command("ah");
                message_vision(CYN "$N双手颤抖的展开书信，急匆匆的读了起来。\n", this_object());
                message_vision(CYN "$N一边读，一边热泪盈眶！\n", this_object());
                command("cry");
                command("say 多谢"+ RANK_D->query_respect(me) + "了。\n");
                set_temp("huang_shouyu", 1, me);
        }

        if( query("name", obj) == "长命锁" )
        {
                command("ah");
                command("say 这不是我女儿的东西吗？她现在怎麽样了？！");
                set_temp("shagu_amulet", 1, me);
        }

        if( query_temp("huang_shouyu", me )
             && query_temp("shagu_amulet", me) )
        {
                command("say 曲某不肖，不为师父分忧，反劳师父日夜牵挂；有劳" +
                        RANK_D->query_respect(me) + "费心奔走了。\n");

                command("thank "+query("id", me));

                if( query("family/family_name", me) == "桃花岛" )
                // &&  me->query("family/master_name") != "黄药师")
                {
                        command("say " + RANK_D->query_respect(me) + "天资不错，在下身无" +
                                "长物，唯有一身武艺，若不嫌我武功低浅，可点拨" + RANK_D->query_respect(me) + "一二。");
                        command("say " + RANK_D->query_respect(me) + "只需向我询问『学艺』即可。");
                        set("help_lingfeng", 1, me);
                        delete_temp("huang_shouyu", me);
                        delete_temp("shagu_amulet", me);
                        set_temp("lingfeng_teach", 1, me);
                }
        }
        destruct(obj);
        return 1;
}

int ask_xueyi()
{
        object me, *ob;
        int i, k = 0;

        me = this_player();
        if( !query_temp("lingfeng_teach", me )
         && (query("family/master_name", me) != "曲灵风") )
        {
                command("say " + RANK_D->query_respect(me) + "说笑了，在下只是个穷卖酒的，有啥可教的？");
                return 1;
        }

        if (base_name(environment(me)) != "/d/jiaxing/xiaodian")
        {
                command("say 这得回到酒店再说。");
                return 1;
        }

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! living(ob[i]))
                        continue;
                k++;
        }

        if (k > 2)
        {
                command("whisper "+query("id", me)+
                        "这里耳目众多，实不是传功授艺之所，还是先打发了周围闲人再说。");
                return 1;
        }

        command("say " + RANK_D->query_respect(me) + "随我来。");
        tell_object(me, CYN "曲三脱下破旧的布衣，换上一身青袍，在脸上摸了几把。\n" NOR);
        tell_object(me, CYN "曲三打开碗橱，将一只碗向右旋转，忽听得喀喇喇一声响，"
                        "橱壁向两旁分开，露出黑黝黝的一个洞来。\n" NOR);
        set_temp("taohua/master", this_object()->name(), me);
        me->move("/d/jiaxing/mishi");

        return 1;
}


string ask_xiao()
{
        object me = this_player();
        object ob;
        mapping myfam;

        myfam=query("family", me);
        if (! myfam || myfam["family_name"] != "桃花岛")
        {
                command("xixi");
                return RANK_D->query_respect(me) + "有什么古玩要卖给在下？";
        }


        if (query("xiao_count") < 1)
                return "最近生意不好，哪里有钱买古玩？";

        if( present("tongxiao",this_player()) || query_temp("get_xiao", this_player()) )
                return RANK_D->query_respect(me) + "还没有把古玩交给黄岛主？";

        command("say " + RANK_D->query_respect(me) + "是从桃花岛来的？");

        if (me->query_skill("bibo-shengong", 1) < 100)
                return "久闻黄岛主收藏奇珍异宝，我有些古玩，想请他老人家鉴赏。";

        if (me->query_skill("yuxiao-jianfa", 1) < 100)
                return "久闻黄岛主收藏奇珍异宝，我有些古玩，想请他老人家鉴赏。";


        command("touch"+query("id", me));
        ob = new("/clone/weapon/tongxiao");
        ob->move(this_player());
        addn("xiao_count", -1);
        set_temp("get_xiao", 1, this_player());

        message_vision("曲三递给$N一支青铜箫。\n", this_player());

        return "我近日得到一件古玩，麻烦你带给黄岛主鉴赏鉴赏。";
}
