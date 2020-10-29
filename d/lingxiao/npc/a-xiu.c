#include <ansi.h>
inherit NPC;

string ask_staff();
void create()
{
        set_name("阿绣", ({"a xiu", "xiu", "a"}));
        set("gender", "女性");
        set("title", "凌霄城主孙女");
        set("age", 16);
        set("long", "她是凌霄城主的孙女，十多岁年纪。聪明伶俐\n"
                    "美丽可人。\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("con", 30);
        set("per", 30);
        set("int", 24);
        set("dex", 30);

        set("max_qi", 800);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 10);
        set("combat_exp", 100000);
        set("score", 2000);
  set("count", 1);

        set("inquiry", ([
                    "石破天"   : "天哥去了侠客岛，也不知道他现在怎么样了。",
                    "大粽子"   : "只有我才能这么叫他，你可不许。",
                    "石中玉"   : "哼，那个家伙，死不足惜。",
                    "白万剑"   : "那是我爹呀。",
                    "白自在"   : "那是我爷爷呀。",
                    "金乌杖" : (: ask_staff :),
        ]) );
        set("chat_chance", 5);
        set("chat_msg", ({
                "阿绣凝视着平静的潭水，说：这潭很奇怪，里面好象有什么东西。\n",
                "阿绣看着远山的悠悠白云，叹道：你要什么时候才从侠客岛回来。\n",
                       CYN "阿绣忽然皱颦不快，好象想起了什么可气之事。\n" NOR,
        }) );

        set_skill("force", 100);
        set_skill("xueshan-neigong", 100);
        set_skill("wuwang-shengong", 80);
        set_skill("dodge", 80);
        set_skill("taxue-wuhen", 80);
        set_skill("cuff", 80);
        set_skill("lingxiao-quan", 80);
        set_skill("strike", 80);
        set_skill("piaoxu-zhang", 80);
        set_skill("sword", 80);
        set_skill("hanmei-jian", 80);
        set_skill("blade", 120);
        set_skill("jinwu-blade", 120);
        set_skill("parry", 80);
        set_skill("literate", 100);
        set_skill("martial-cognize", 20);

        map_skill("force", "wuwang-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "hanmei-jian");
        map_skill("blade", "jinwu-blade");
        map_skill("parry", "jinwu-blade");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("凌霄城", 7, "弟子");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "blade.chi" :),
                (: exert_function, "recover" :)
        }) );

        setup();
        
        carry_object("/clone/weapon/mudao")->wield();
        carry_object("/clone/cloth/xian-cloth")->wear();
        carry_object("/clone/cloth/boots")->wear();
        carry_object("/clone/cloth/belt")->wear();
}

string ask_staff()
{
        object ob;
        object me;
        me = this_player();

        if(query("count") < 1)
                return "这位" +RANK_D->query_respect(me)+"，真是抱歉，金乌杖已经有人帮我给奶奶带去了。";
    if( query("combat_exp", me)<200000 )
                return "你武功尚未到家，我怎敢把金乌杖交给你？";
        addn("count", -1);
        ob=new(WEAPON_DIR"treasure/jinwu-staff");
        if ( ob->violate_unique() )
        {
                destruct( ob );
                return "你武功尚未到家，我怎敢把金乌杖交给你？";
        }
        else
        {
                ob->move(this_player());
                return "这位" +RANK_D->query_respect(me)+"，请帮我把这把金乌杖带给我奶奶，真是多谢了。";
        }
}
void attempt_apprentice(object ob)
{
        command("say 我是不收徒的，你进城找我师兄们好了。");
}
