//yangkang.c
//by zhuifeng 2010

inherit NPC;
string ask_me();
string ask_me2();
#include <ansi.h>;

void create()
{
        set_name("杨康", ({"yang kang", "kang", "yang"}));
        set("gender", "男性");
        set("title", HIC "全真教第三代弟子"NOR );
        set("age", 24);
        set("class", "fighter");
        set("long",
                "他又名完颜康。随母包惜弱嫁完颜洪烈后，成了小王子，贪图富贵，至死不改。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);
        set("per", 28);
        set("kar", 30);
        set("pur", 15);

        set("chat_chance_combat", 350);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "wuqi" :),
                (: exert_function, "ding" :),
                (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "claw.jiuyin" :),
        }));

        set("qi", 100000);
        set("max_qi", 10000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 100000);
        set("eff_jingli",10000);
        set("jingli",10000);
        set("max_neili", 100000);
        set("jiali", 200);
        set("skybook/jiuyin2/pass",1);
        set("skybook/shediao/yangjiaqiang/pass",1);

        set("combat_exp", 4300000);

        set_skill("force", 350);
        set_skill("xiantian-gong", 350);
        set_skill("sword", 350);
        set_skill("quanzhen-jian", 350);
        set_skill("dodge", 350);
        set_skill("jinyan-gong", 350);
        set_skill("yangjia-qiang.c", 120);
        set_skill("spear", 120);
        set_skill("parry", 350);
        set_skill("strike", 350);
        set_skill("haotian-zhang", 350);
        set_skill("claw",350);
        set_skill("jiuyin-baiguzhao", 320);
        set_skill("literate", 200);
        set_skill("taoism", 50);
        set_skill("yinlong-bian", 180);
        set_skill("cuixin-zhang", 200);
        set_skill("whip",200);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("spear", "yangjia-qiang.c");
        map_skill("parry", "quanzhen-jian");
        map_skill("strike", "cuixin-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("whip","yinlong-bian");
        prepare_skill("claw", "jiuyin-baiguzhao");
        
        set("inquiry", ([
                "郭啸天" : "我不认识。",
                "杨铁心" : "我不认识。",
                "郭靖" : "我不认识。",
                "李萍" : "我不认识。",
                "包惜弱" : "她是我娘。",
                "穆念慈" : "她是我的女人，你问她干什么。",
                "黄蓉" : "谁？？？",
                "完颜洪烈" : "你找我父王什么事情？",
                "丘处机" : "他是我师父",
                "梅超风" : "他是我师父",
                "欧阳克" : "这小子三番五次调戏念慈，我不会放过他的！",
                "完颜康" : (: ask_me :),
                "杨康" : (: ask_me2 :),
	]));

        set("chat_chance", 5);
        set("chat_msg", ({
                "谁也不能让我离开我父王，念慈如果每次要我离开，我就先假装答应她，嘿嘿：女人真好骗！\n",
                "师父要我来嘉兴和我义兄比武，此人三番五次坏我好事，这次我要让他好看，哼、哼！\n",
        }) );
        create_family("全真教", 3, "弟子");

        setup();

        //carry_object("/d/fuzhou/npc/obj/txs")->wield();
        carry_object("/clone/cloth/jinduan")->wear();
}

string ask_me()
{
        object me,ob;
	ob  =this_player();
	me = this_object();
        command("unwield shan"); 
	set_name("完颜康", ({ "wanyan kang", "kang","wanyan"}) );
	set("title",HIY"大金国小王爷"NOR);
	return "我便是大金国小王爷，你有什么事情！";
}

string ask_me2()
{
        object me,ob;
	ob = this_player();
	me = this_object();
        command("wield shan");
        set_name("杨康", ({ "yang kang", "kang","yang"}) );
        set("title",HIC"全真教第三代弟子"NOR);
	return "在下便是杨康，你找我何事！";
}

