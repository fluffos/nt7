// This program is a part of NT MudLIB
// longcheng.c 慕容龙城

#include <ansi.h>

inherit NPC;

mixed ask_me();
mixed try_learn_sk();

void create()
{
        set_name("慕容龙城", ({ "murong longcheng", "murong", "longcheng" }));
        set("long", @LONG
他是姑苏慕容的传人，一手创造了绝世武功斗转星移，从而
使慕容家跻身为武林世家地位。
LONG );
        set("gender", "男性");
        set("age", 54);
        set("attitude", "peaceful");

        set("str", 32);
        set("int", 39);
        set("con", 33);
        set("dex", 34);

        set("qi", 6000);
        set("max_qi", 6000);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 7200);
        set("max_neili", 7200);
        set("jiali", 90);
        set("level", 50);
        set("combat_exp", 2700000);

        set_skill("force", 400);
        set_skill("literate", 350);
        set_skill("strike", 400);
        set_skill("cuff", 400);
        set_skill("finger", 400);
        set_skill("sword", 400);
        set_skill("blade", 400);
        set_skill("dodge", 400);
        set_skill("parry", 400);

        set_skill("shenyuan-gong", 400);
        set_skill("zihui-xinfa", 400);
        set_skill("douzhuan-xingyi", 400);
        set_skill("beidou-xianzong", 400);
        set_skill("xingyi-zhang", 400);
        set_skill("canhe-zhi", 400);
        set_skill("qixing-quan", 400);
        set_skill("murong-jianfa", 400);
        set_skill("murong-daofa", 400);
        set_skill("longcheng-shendao", 400);
        set_skill("martial-cognize", 340);

        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "beidou-xianzong");
        map_skill("cuff",  "qixing-quan");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("finger", "canhe-zhi");
        map_skill("sword", "murong-jianfa");
        map_skill("blade", "longcheng-shendao");

        prepare_skill("finger", "canhe-zhi");
        prepare_skill("cuff", "qixing-quan");

        set("inquiry", ([
                "绝招"   : (: ask_me :),
                "绝技"   : (: ask_me :),
                "风雨交加": (: ask_me :),
        ]));

        create_family("慕容世家", 12, "传人");
        set("chat_chance", 1);
        set("chat_msg",({
                "慕容龙城低头不语。\n",
        }));

        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        if( query("family/family_name", ob) == query("family/family_name") )
        {
                command("say 我早就不收徒弟了，不过你也是我们"
                        "慕容家的传人，我就传你一套刀法(longcheng-shendao)吧！");
        } else
                command("say 我不收徒弟。");
}

int recognize_apprentice(object ob)
{
        return query("family/family_name", ob) == query("family/family_name");
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/longcheng-shendao/feng", me) )
                return "好好练功吧！光复大燕就靠你们这批人啦！！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪儿来的？我可不认识你。";

        if (me->query_skill("longcheng-shendao", 1) < 120)
                return "想学风雨交加首先可得练好我的龙城神刀啊！";

        message_vision(HIC "$n" HIC "缓缓的摸出一根带子，轻轻一抖，立刻"
                       "变得笔直，随即劈出，$N" HIC "只能看得到星光点点。\n$n"
                       HIC "忽的收回刀势，慢慢的又劈出五刀，$N"
                       HIC "看了不禁恍然大悟！\n" NOR,
                       me, this_object());
        command("say 知道了吧？");
        tell_object(me, HIG "你学会了风雨交加。\n" NOR);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 160000);
        set("can_perform/longcheng-shendao/feng", 1, me);
        return 1;
}
