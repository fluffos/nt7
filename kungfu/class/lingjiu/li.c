// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
int auto_perform();
int ask_youming();
int ask_guizhao();
int ask_guiying();

void create()
{
        set_name("李秋水", ({ "li qiushui", "li", "qiushui" }));
        set("long",
            "她身着白色衣衫，身形苗条婀娜，脸上蒙了块白绸，瞧不见她面容。\n");
        set("title", "西夏国皇太妃");
        set("gender", "女性");
        set("per", 13);
        set("age", 80);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 30);

        set("max_qi", 6000);
        set("max_jing", 3200);
        set("neili", 7500);
        set("max_neili", 7500);
        set("jiali", 100);
        set("level", 60);
        set("combat_exp", 3500000);

        set_skill("force", 350);
        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_skill("hand",350);
        set_skill("strike", 350);
        set_skill("sword",350);
        set_skill("blade",350);
        set_skill("literate",100);
        set_skill("music",350);
        set_skill("claw",350);

        set_skill("youming-guizhao",350);
        set_skill("zhemei-shou",350);
        set_skill("liuyang-zhang",350);
        set_skill("tianyu-qijian",350);
        set_skill("yueying-wubu",350);
        set_skill("bahuang-gong", 350);

        map_skill("force", "bahuang-gong");
        map_skill("strike","liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("hand", "zhemei-shou");
        map_skill("parry", "youming-guizhao");
        map_skill("sword", "tianyu-qijian");
        map_skill("claw", "youming-guizhao");

        prepare_skill("claw", "youming-guizhao");

        set("inquiry", ([
                "幽冥鬼爪" : (: ask_youming :),
                "亡魂鬼爪" : (: ask_guizhao :),
                "幽冥鬼影" : (: ask_guiying :),
        ]));

        create_family("灵鹫宫", 1, "弟子");

        set("master_ob",4);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        object ob = this_player();

        ::init();
        if( ob->query_skill("beiming-shengong") && query("id", ob) != "xiaoyaozi" || 
                ob->query_skill("lingbo-weibu") && query("id", ob) != "xiaoyaozi" )
        {
                message_vision(HIY "$N突然对$n喝到：居然擅闯琅寰福地，留下你的命吧！\n"NOR, this_object(), ob );
                kill_ob(ob);
        }
}

int ask_youming()
{
        object ob = this_player();
        
        if( query("family/family_name", ob) != "灵鹫宫"){
                command("sneer");
                command("say 师姐却不知我练了这幽冥鬼爪，等她闭关还童之时要叫她受点苦头。");
                return 1;
        }
        
        if( query("family/master_name", ob) == "天山童姥"){
                command("say 师姐派你来偷学我的幽冥鬼爪？那就让你见识见识！");
                kill_ob(ob);
                return 1;
        }     
        if( query("can_learn/li/youming-guizhao", ob)){
                command("say 我不是已经开始教你了么？");
                return 1;
        }
        if (ob->query_skill("claw", 1) < 99) {
                command("say 要使用这样的武功需要高深的爪法，你还是多练习练习再说吧。");
                return 1;
        }
        
        command("say 好，我就教你这套“幽冥鬼爪”，将来帮我对付那个贱人！\n");
        set("can_learn/li/youming-guizhao", 1, ob);
        return 1;
}

int ask_guizhao()
{
        object ob = this_player();
        
        if( query("family/family_name", ob) != "灵鹫宫"){
                command("sneer");
                command("say 师姐却不知我练了这幽冥鬼爪，等她闭关还童之时要叫她受点苦头。");
                return 1;
        }
        if( query("family/master_name", ob) == "天山童姥"){
                command("say 师姐派你来偷学我的幽冥鬼爪？那就让你见识见识！");
                kill_ob(ob);
                return 1;
        }     
        if( !query("can_learn/li/youming-guizhao", ob)){
                command("say 谁叫你来偷学我武功的？");
                return 1;
        }
        if (ob->query_skill("claw", 1) < 180) {
                command("say 要使用这样的绝招需要高深的爪法，你还是多练习练习再说吧。");
                return 1;
        }
        if (ob->query_skill("youming-guizhao", 1) < 180) {
                command("say 要使用这样的绝招需要高深的爪法，你还是多练习练习“幽冥鬼爪”再说吧。");
                return 1;
        }

        command("say 好，我就教你一式“亡魂鬼爪”，将来帮我对付那个贱人！\n");
        set("can_perform/youming-guizhao/guizhao", 1, ob);
        tell_object(ob, "你学会了亡魂鬼爪。\n");
        return 1;
}

int ask_guiying()
{
        object ob = this_player();
        
        if( query("family/family_name", ob) != "灵鹫宫"){
                command("sneer");
                command("say 师姐却不知我练了这幽冥鬼爪，等她闭关还童之时要叫她受点苦头。");
                return 1;
        }
        if( query("family/master_name", ob) == "天山童姥"){
                command("say 师姐派你来偷学我的幽冥鬼爪？那就让你见识见识！");
                kill_ob(ob);
                return 1;
        }     
        if( !query("can_learn/li/youming-guizhao", ob)){
                command("say 谁叫你来偷学我武功的？");
                return 1;
        }
        if (ob->query_skill("claw", 1) < 180) {
                command("say 要使用这样的绝招需要高深的爪法，你还是多练习练习再说吧。");
                return 1;
        }
        if (ob->query_skill("youming-guizhao", 1) < 180) {
                command("say 要使用这样的绝招需要高深的爪法，你还是多练习练习“幽冥鬼爪”再说吧。");
                return 1;
        }

        command("say 好，我就教你一式“幽冥鬼影”，将来帮我对付那个贱人！\n");
        set("can_perform/youming-guizhao/youming", 1, ob);
        tell_object(ob, "你学会了幽冥鬼影。\n");
        return 1;
}
int recognize_apprentice(object ob, string skill)
{
        if( !query("can_learn/li/youming-guizhao", ob) )
        {
                command("say 我答应传授你了吗？");
                return -1;
        }     
        if (skill != "youming-guizhao" && skill != "claw")
        {
                command("say 我只传授你一些爪法方面的知识，你不学就算了。");
                return -1;
        }

        return 1;
}
