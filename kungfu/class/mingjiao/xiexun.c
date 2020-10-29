// This program is a part of NT MudLIB
// xie.c 谢逊

#include <ansi.h>
#include "mingjiao.h"

inherit NPC;
inherit F_MASTER;

string ask_me();
string ask_dao();
string ask_boat();

void create()
{
        object ob;
        set_name("谢逊",({"xie xun","xie","xun"}));
        set("title", HIG "明教" HIY "金毛狮王" NOR);

        set("long", "他就是明教的四大护法之一的金毛狮王。\n"+
                    "他身材魁伟异常，满头金发散披肩头。但双目已瞎。\n"+
                    "在你面前一站，威风凛凛，真如天神一般。\n");
        set("age", 56);
        set("attitude", "peaceful");
        set("shen", -13000);
        set("str", 30);
        set("per", 16);
        set("int", 29);
        set("con", 35);
        set("dex", 27);
        set("max_qi", 2500);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 70);
        set("combat_exp", 1350000);
        set("level", 40);

        set_skill("cuff",460);
        set_skill("dodge",460);
        set_skill("force", 460);
        set_skill("blade",460);
        set_skill("hand", 460);
        set_skill("literate",410);
        set_skill("qingfu-shenfa", 460);
        set_skill("qishang-quan",480);
        set_skill("shenghuo-shengong", 460);
        set_skill("pili-shou", 460);
        set_skill("parry", 460);
        set_skill("lieyan-dao",460);
        set_skill("martial-cognize", 300);

        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "qingfu-shenfa");
        map_skill("cuff", "qishang-quan");
        map_skill("parry", "qishang-quan");
        map_skill("blade", "lieyan-dao");
        map_skill("hand", "pili-shou");

        prepare_skill("cuff","qishang-quan");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: command("perform cuff.shang") :),
                (: command("perform cuff.fei") :),
        }) );

        set("inquiry", ([
                 "张无忌"  : "他是我的义子，我已很久没有见到他了。",
                 "七伤拳经": (: ask_me :),
                 "屠龙刀": (: ask_dao :),
                 "船"    : (: ask_boat :),
                 "船舶"  : (: ask_boat :),
                 "造船"  : (: ask_boat :),
                 "中原"  : (: ask_boat :),
                 "成昆"  : "他就是我那狗贼师傅，他杀了我一家四口，此仇不共戴天！",
        ]));

        create_family("明教", 36, "护法法王");

        set("master_ob",5);
        setup();

        // carry_object("/d/mingjiao/obj/tulong-dao")->wield();
        carry_object("/clone/weapon/tulongdao")->wield();
        carry_object("/d/mingjiao/obj/xiongpi")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 老夫不收弟子。");
        command("say 这位"+RANK_D->query_respect(ob)+"还是请回吧。");
        return;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("can_learn/xiexun/qishang-quan", ob) && 
            skill == "qishang-quan")
                return 1;

        if( query("can_learn/xiexun/qishang-quan", ob) && 
            skill == "cuff")
                return 1;

        if( query("can_learn/xiexun/qishang-quan", ob) && 
            skill == "hand")
                return 1;

        if( query("can_learn/xiexun/qishang-quan", ob) && 
            skill == "pili-shou")
                return 1;

        if( !query("can_learn/xiexun/qishang-quan", ob) )
                return -1;

        command("say 你到底学不学我的七伤拳？不想学就快滚！");
        return -1;
}

string ask_me()
{
        mapping fam;
        object me = this_player();

        if( !(fam=query("family", me)) || fam["family_name"] != "明教" )
                return "七伤拳经？没听说过。";

        if (fam["master_name"] != "张无忌")
                return RANK_D->query_respect(me) + "还是请回吧，你说的是崆峒派的绝技，我怎么会知道？";

        if( query("can_lean/xiexun/qishang-quan", me) )
                return "我不是答应传了你这拳经了吗？怎么还要问！";

        if( !query_temp("marks/七伤", me) )
                return "我这七伤拳经除了我义子，不传外人！";

        command("consider");
        command("say 无忌这孩子，怎么可将七伤拳传予他人呢！");
        command("say 也罢，无忌既然让你来到这里，我就传了你吧。");
        set("can_learn/xiexun/qishang-quan", 1, me);
        delete_temp("marks/七伤", me);
        command("whisper"+query("id", me)+"五行之气调阴阳，损心伤肺摧肝肠，藏离精失意恍惚，三焦齐逆兮魂魄飞扬！");
        return "你学完了就可以回去吧。";
}

string ask_boat()
{
        object me = this_player();

        if( !query("can_learn/xiexun/qishang-quan", me) )
                return "船？这极北冰火岛离开中原万里，哪来的船舶？";

        command("say 当年我帮义弟义妹他们在后山丛林中砍伐(chop)树木，然后才搬到海边造船(make)。");
        return "也不知道现在他们和我那无忌孩儿都怎么样了。";
}

string ask_dao()
{
        mapping fam;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "明教" )
                return RANK_D->query_respect(this_player())+"与本教素无来往，不知此话从何谈起？";

        if (present("tulong dao", this_object()))
        {
                command("wield dao");
                command("say 武林至尊，宝刀屠龙，号令天下，莫敢不从，倚天不出，谁与争锋。");
                write("\n谢逊棒着屠龙宝刀，低头冥思刀口之秘。\n\n");
                set_temp("xie_tld", 1, this_player());
                return "不寻到宝刀中之秘，我之大仇如何得报？唉......";
        } else
                return "武林至尊，宝刀屠龙，号令天下，莫敢不从！";
}

int accept_object(object who, object ob)
{
        object obj;
        object me = this_object();

        if ((! ob->is_head() && ! ob->is_corpse()) ||
            !stringp(query("owner_id", ob)) || 
          query("owner_id", ob) != "cheng kun" )
        {
                command("say 老夫对这样东西没什么兴趣……");
                return 0;
        }

        command("say 啊……成昆的人头！ 成昆的人头！");
        command("chat 哈哈哈！……成昆的人头！ 成昆的人头！");
        call_out("destroy", 1, ob);

        if( query("killed_by", ob) != query("id", who) )
        {
                command("say 但他好象不是你杀的吧？你是怎么得到这块人头的？");
                return 1;
        }
          if( query_temp("xie_tld", who) && present("tulong dao",me) )
        {
                command("say 你让我大仇得报，这把刀就算我的谢礼，只可惜不能手刃了那恶贼。");
                command("unwield dao");
                  command("give tulong dao to "+query("id", who));
                delete_temp("xie_tld", who);
                return 1;
        } else
        {
                command("say 你让我大仇得报，我这里只有我的金毛送给你了，只可惜不能手刃了那恶贼。");
                obj = new ("/d/mingjiao/obj/jinmao");
                obj->move(this_player());
                return 1;
        }
}

void destroy(object ob)
{
        destruct(ob);
        return;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "天地混元" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/pili-shou/hun",
                           "name"    : "天地混元",
                           "sk1"     : "pili-shou",
                           "lv1"     : 140,
                           "force"   : 240,
                           "gongxian": 550,
                           "shen"    : 48000, ]));
                break;

        case "魂魄飞扬" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qishang-quan/fei",
                           "name"    : "魂魄飞扬",
                           "sk1"     : "qishang-quan",
                           "lv1"     : 140,
                           "neili"   : 2000,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        case "伤字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qishang-quan/shang",
                           "name"    : "伤字诀",
                           "sk1"     : "qishang-quan",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        case "天地混元" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/pili-shou/hun",
                           "name"    : "天地混元",
                           "sk1"     : "pili-shou",
                           "lv1"     : 160,
                           "neili"   : 2200,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        default:
                return 0;
        }
}
