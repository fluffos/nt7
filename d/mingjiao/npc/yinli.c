// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// yinli.c 殷离

inherit NPC;
#include <ansi.h>

mixed ask_qianzhu();
mixed ask_he();

string *qianzhu_message = ({
        "千蛛万毒手虽是一门毒功, 其实它包括指法, 内功, 轻功, 招架在内, 一通百通。\n",
        "练千蛛万毒手极为费时费力, 非穷毕生之力不可。\n",
        "千蛛万毒手练起来极为枯燥, 要不是为了报仇, 我才不练呢。\n",
        "千蛛万毒手入门容易, 可越到后来越难练, 我也不过练了百来只花蛛而已。\n",
        "修练千蛛万毒手时凶险万分, 非有一定的内力为基础不可。\n",
        "江湖人物只知道打打杀杀, 实战经验虽丰富, 可又怎么奈何得了我的千蛛万毒手?\n",
        "咱们练千蛛万毒手的, 只求毒功深湛, 跟实战经验倒没什么关系。\n",
        "千蛛万毒手一旦施展, 无药可救, 只有中毒者自己靠深厚的内力化解。\n",
        "千蛛万毒手乃是我的家传武功, 虽说没什么名气, 可等我练成了, 连张无忌怕也挡不住我一指。\n",
        "练了千蛛万毒手以后容貌尽毁, 那是不必说了。\n",
        "要说功夫深哪, 练个几千只花蛛也不算多。\n",
        "等练到几百只毒蜘蛛以后，突袭(tuxi)敌人的效果可就利害了。\n",
});

void create()
{
        set_name("殷离", ({ "yin li", "yin", "li" }));
        set("gender", "女性");
        set("age", 19);
        set("long","她是个十七八岁的少女，荆钗布裙，是个乡村贫女，\n"+
                   "面容黝黑，脸上肌肤浮肿，凹凹凸凸，生得极是丑陋，\n"+
                   "只是一对眸子颇有神采，身材也是苗条纤秀。\n");
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 26);
        set("per", 6);
        set("unique", 1);
        set("location", 1);
        set("combat_exp", 300000);
        set("shen", -500);
        set("attitude", "peaceful");
        set("max_qi",600);
        set("max_jing",600);
        set("neili",800);
        set("max_neili",800);
        set("jiali",20);
        set_temp("no_return", 1);
        set_skill("unarmed", 60);
        set_skill("parry",60);
        set_skill("qingfu-shenfa",60);
        set_skill("dodge", 60);
        set_skill("throwing",60);
        set_skill("duoming-jinhua",60);
        set_skill("qianzhu-wandushou", 60);
        set_skill("finger", 60);
        set_skill("force",60);
        set_skill("shenghuo-shengong",60);
        map_skill("force","shenghuo-shengong");
        map_skill("finger","qianzhu-wandushou");
        map_skill("dodge","qingfu-shenfa");
        map_skill("throwing","duoming-jinhua");
        map_skill("parry","duoming-jinhua");
        prepare_skill("finger","qianzhu-wandushou");
        set("inquiry", ([
                "千蛛万毒手" : (: ask_qianzhu :),
                "报仇" : "哼, 我要叫天下负心薄辛的男子个个不得好死。\n",
                "殷野王" : "他是我爹。\n",
                "殷天正" : "他是我爷爷。\n",
                "殷素素" : "他是我姑姑。\n",
                "金花婆婆" : "唉, 婆婆去波斯啦。\n",
                "银叶先生" : "银叶先生我也没见过。\n",
                "胡青牛" : "哼, 这个臭医生, 要不是他, 银叶先生也不会死。\n",
                "王难姑" : "嗯, 难姑的毒技是极高的, 可我的千蛛万毒手却也另有一功。\n",
                "周芷若" : "小姑娘人长的漂亮, 可心眼不怎么好。\n",
                "赵敏" : "赵姑娘心机敏捷, 令人佩服。\n",
                "张无忌" : "这没良心的、狠心短命的死鬼, 我到处都找不到他。\n",
                "锦盒" : (: ask_he :), 

        ]));
        
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        setup();
        carry_object("/d/mingjiao/obj/green-cloth")->wear();
        carry_object("/clone/weapon/feihuangshi")->wield();
}

mixed ask_qianzhu() 
{
        object he, player = this_player(), me = this_object();
        int flags, level, idx;

        if (player->is_busy()) 
        {
                return "刚问完又来，你有没有听懂我说的啊？\n";
        }

        flags=query_temp("qianzhu-wandushou/flags", player);
        level = player->query_skill("qianzhu-wandushou", 1);

        if (flags >= 1023 && level < 10) 
        {
                command("say 好吧, 看你这么诚心, 我就教你这门功夫吧。\n");
                player->set_skill("qianzhu-wandushou", 10);
                message_vision("$N指点了$n一些基本的千蛛万毒手。\n", me, player);
                tell_object(player, "师傅领进门, 修行看各人, 今后就你自己练啦。如果没有锦盒，可以来问我要。\n");
                return 1;
        }else 
        {
                player->start_busy(1 + random(3));
                idx = random(sizeof(qianzhu_message));
                if (idx < 10) 
                {
                        flags = flags | (1 << idx);
                   }
                set_temp("qianzhu-wandushou/flags", flags, player);
                return qianzhu_message[idx];
        }
}

mixed ask_he() 
{
        object player = this_player();
        object he;

        if (player->query_skill("qianzhu-wandushou", 1) < 10) 
        {
                return "你我素不相识, 问来也不冒昧么？\n";
        }

        if (objectp(present("jin he", player))) {
                return "你已经有锦盒了。\n可以找个偏僻的所在, 抓一只毒蜘蛛, 自己就可以修练啦。\n";
        }
        he = new ("/clone/misc/jinhe");
        he->move(player);
        tell_object(player, "你怎么这么不小心, 好吧, 我再给你一个。\n");
        message_vision("$N给$n一个锦盒。\n", this_object(), player);
        return 1;
}
