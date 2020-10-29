// This program is a part of NITAN MudLIB

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "gumu.h"

int ask_xinjing();
string ask_yunv();

void create()
{
        set_name("林朝英", ({"lin chaoying", "lin", "chaoying" }));
        set("gender", "女性");
        set("age", 42);
        set("long", @LONG
她就是古墓派的开山祖师林朝英，虽然已经是
四十许人，望之却还如同三十出头。当年她与
全真教主王重阳本是一对痴心爱侣，只可惜有
缘无份，只得独自在这古墓上幽居。
LONG);

        set("attitude", "friendly");

        set("book_count", 1);
        set("str", 30);
        set("int", 38);
        set("con", 34);
        set("dex", 34);
        set("shen_type", 1);

        set("qi", 6500);
        set("max_qi", 6500);
        set("jing", 3400);
        set("max_jing", 3400);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 120);

        set("combat_exp", 4000000);
        set_skill("force", 600);
        set_skill("yunv-xinjing", 600);
        set_skill("yunv-xinfa", 600);
        set_skill("suxin-jue", 600);
        set_skill("sword", 620);
        set_skill("yunv-jian", 600);
        set_skill("yunv-jian", 600);
        set_skill("dodge", 600);
        set_skill("yunv-shenfa", 600);
        set_skill("parry", 600);
        set_skill("unarmed",600);
        set_skill("meinv-quan", 600);
        set_skill("strike", 60);
        set_skill("tianluo-diwang", 600);
        set_skill("whip", 600);
        set_skill("yinsuo-jinling", 600);
        set_skill("literate", 600);
        set_skill("taoism", 600);
        set_skill("throwing", 600);
        set_skill("yufeng-zhen", 600);
        set_skill("qufeng", 600);
        set_skill("medical", 600);
        set_skill("taishang-wangqing", 600);

        map_skill("force", "yunv-xinfa");
        map_skill("sword", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");
        map_skill("strike", "tianluo-diwang");

        prepare_skill("unarmed", "meinv-quan");
        prepare_skill("strike", "tianluo-diwang");

        create_family("古墓派", 1, "开山祖师");

        set("inquiry", ([
                "王重阳"     :  "大胆后辈小子，也敢直呼重阳祖师之名？\n",
                "重阳祖师"   :  "重阳是全真教的掌教，自号“活死人”。\n",
                "古墓派"     :  "是啊，这里就是我一手创下的古墓派\n",
                "玉蜂针"     :  "我这儿没有，别问我。\n",
                "玉女心经"   :  ( : ask_xinjing :),
                "玉女心经秘籍" : (: ask_yunv :),
        ]));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.feng" :),
                (: perform_action, "sword.kai" :),
                (: perform_action, "unarmed.you" :),
                (: perform_action, "strike.wang" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("master_ob", 5);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/qingyi")->wear();

}
void attempt_apprentice(object ob)
{
        object me = this_player();

        if (! permit_recruit(ob) )
                return;

        if( query("family/master_name", me) == "李莫愁" )
        {
                command("sneer");
                command("say 我林朝英可不收那叛徒的徒弟。");
                return;
        }

        if (ob->query_int() < 35) {
                command("say 我古墓派的功夫最讲一个悟字，你的资质不够。");
                return;
        }

        if ((int)ob->query_skill("yunv-xinfa", 1) < 120 ) {
                command("say 玉女心法乃本门绝学，你因该在这方面多加练习。");
                return;
        }

        command("say 好吧，看你也是性情中人，我就收下你这个徒弟了。");
        command("recruit "+query("id", ob));
}
int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "连环剑术" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yunv-jian/lian",
                           "name"    : "连环剑术",
                           "sk1"     : "yunv-jian",
                           "lv1"     : 120,
                           "dodge"   : 100,
                           "gongxian": 600, ]));
                break;

            case "双剑交错" :
                    return MASTER_D->teach_pfm(me, this_object(),
                            ([ "perform" : "can_perform/yunv-jian/jiao",
                               "name"    : "双剑交错",
                             "sk1"     : "yunv-jian",
                             "lv1"     : 80,
                             "dodge"   : 100,
                             "gongxian": 600, ]));
                  break;

          case "素心诀" :
                  return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/yunv-jian/su",
                             "name"    : "素心诀",
                             "sk1"     : "yunv-jian",
                             "lv1"     : 220,
                             "dodge"   : 100,
                             "gongxian": 800, ]));
                  break;

        case "风神诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yinsuo-jinling/feng",
                           "name"    : "风神诀",
                           "sk1"     : "yinsuo-jinling",
                           "lv1"     : 140,
                           "force"   : 180,
                           "gongxian": 700, ]));
                break;

        case "开天辟地" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yinsuo-jinling/kai",
                           "name"    : "开天辟地",
                           "sk1"     : "yinsuo-jinling",
                           "lv1"     : 130,
                           "force"   : 180,
                           "gongxian": 800, ]));
                break;
        default:
                return 0;
        }
}

int ask_xinjing()
{
        object me = this_player();
        string msg;

        if( query("family/master_name", me) != "林朝英" )
        {
               command("say 玉女心经的口诀我只传授给我的弟子。\n");
               return 1;
        }
        if( query("can_learn/yunv-xinfa/wall", me) )
        {
               command("say 玉女心经的口诀我不是已经传授给你了吗？\n");
               return 1;
        }

        if (me->query_skill("yunv-xinfa", 1) < 180)
        {
               command("say 你玉女心经的修为还不够，现在不能传授给你口诀。\n");
               return 1;
        }

        command("nod");
        msg = HIC"林朝英说道：“好吧，现在我就将玉女心经的口诀传授给你，你可记好了！”";
        msg += HIY"\n林朝英在悄悄地将玉女心经的口诀传授给$N。\n" NOR;

        message_vision(msg, me);

        set("can_learn/yunv-xinfa/wall", 1, me);

        return 1;

}


string ask_yunv()
{
        mapping fam;
        object ob;
        int lvl_yunv;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "古墓派")
                return RANK_D->query_respect(this_player()) +
                "与本派毫无瓜葛，何以问起本派的心经？";
        if (!(lvl_yunv = this_player()->query_skill("yunv-xinfa",1)) ||
                lvl_yunv < 55)
                return RANK_D->query_respect(this_player()) +
                "的玉女心法火候不足，我不能将玉女心经交给你";
        if (query("book_count") < 1)
                return "你来晚了，本派的玉女心经已经被人取走了。";
        addn("book_count", -1);
        ob = new("/clone/book/yunvjing2");
        ob->move(this_player());
        return "好吧，这本「玉女心经」你拿回去好好研读。";
}


/*
void unconcious()
{
        die();
}
*/
