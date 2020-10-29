// zhang1.c

#include <ansi.h>
#include "riyue.h"

#define SHENMU    "/clone/lonely/shenmu"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER; 

mixed ask_gun();
int shang_ya();
mixed ask_pfm();

void create()
{
        object ob;
    set_name("张乘风", ({"zhang chengfeng", "zhang", "chengfeng"}));
    set("nickname", HIY "金猴神魔" NOR );
    set("title", "日月神教长老");
    set("gender", "男性");
    set("age", 42);
    set("shen_type", -1);
    set("long", "他是日月神教长老。\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);

    set("qi", 3000);
    set("max_qi", 3000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("jiali", 300);

    set("combat_exp", 1500000);
    set("score", 0);
    set("inquiry", ([
        "黑木崖"   : "本教弟子或持教主令牌方能上崖！\n",
        "日月神教" : "本教弟子或持教主令牌方能上崖！\n",
        "黑木令"   : "那是本教教主令牌，见牌如见教主亲临！\n",
                "南海神木" : (: ask_gun :),
        "上崖"     : (: shang_ya :),
        "绝招"     : (: ask_pfm :),
        "天旋地转" : (: ask_pfm :),
    ]) );

    set_skill("force", 150);
    set_skill("riyue-xinfa", 150);
    set_skill("dodge", 150);
    set_skill("piaomiao-shenfa", 150);
    set_skill("hand", 150);
    set_skill("huanmo-longtianwu", 150);
    set_skill("cuff", 150);
    set_skill("xuwu-piaomiao", 150);
    set_skill("parry", 150);
    set_skill("club", 180);
    set_skill("tianmo-gun", 180);
    set_skill("literate", 110);
    set_skill("sword",150);
    set_skill("riyue-jian",150);

    map_skill("force", "riyue-xinfa");
    map_skill("dodge", "piaomiao-shenfa");
    map_skill("hand", "huanmo-longtianwu");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("sword", "riyue-jian");
    map_skill("parry", "tianmo-gun");
    map_skill("club", "tianmo-gun");

    prepare_skill("hand", "huanmo-longtianwu");
    prepare_skill("cuff", "xuwu-piaomiao");

    create_family("日月神教", 2, "长老");

    set("master_ob",3);
        setup();
        if (clonep())
        {
                ob = find_object(SHENMU);
                if (! ob) ob = load_object(SHENMU);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/d/heimuya/npc/obj/shutonggun");
                        ob->move(this_object());
                        ob->wield();
                }
        }
    carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object ob)
{
    if(! permit_recruit(ob))  return;

    if((int)ob->query_skill("riyue-xinfa", 1) < 120)
    {
         command("say 本教的内功心法你还没练好，还要多下苦功才行！");
         return;
    }

    command("recruit "+query("id", ob));
    set("title", HIM"日月神教"HIY"金猴护法"NOR, ob);
}

mixed ask_gun()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "日月神教" )
                return "给我滚开！";

        if( query("family/master_id", me) != "renwoxing"
            && query("family/master_id", me) != "xiangwentian" )
                return "你还不配！";

        if( query("shen", me)>-80000 )
                return "你这样心慈手软，拿了神木又有什么用？";

        if (me->query_skill("tianmo-gun", 1) < 120)
                return "你连日月天魔棍都没学好，就算神兵在手又有何用？";

        ob = find_object(SHENMU);
        if (! ob) ob = load_object(SHENMU);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "南海神木现在不就在你手里吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你来晚了一步，南海神木我已经借出去了。";

                if( query("family/family_name", owner) == "日月神教" )
                        return "老夫的南海神木现在是"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "老夫的南海神木现在落入了"+query("name", owner)+
                               "之手，你去把它取回来吧！";
        }
        ob->move(this_object());

        command("say 既然这样，老夫这根南海神木你就拿去。");
        command("say 你用它多杀几个正派人士，扬扬咋们日月神教的威风。");
        command("givenanhaishenmuto"+query("id", me));

        ob = new("/d/heimuya/npc/obj/shutonggun");
        ob->move(this_object());
        ob->wield();
        return 1;
}
int shang_ya()
{
    object ob, myenv ;
    ob = this_player ( ) ;
    if( query("family/family_name", ob) == "日月神教" )
    {
        message_vision("张乘风一招手，崖上落下一个大吊篮。\n",ob);
        message_vision("$N一弯腰进了吊篮，吊篮缓缓地铰上崖去......\n", ob);
        myenv = environment (ob) ;
        ob->move ("/d/heimuya/basket");
        call_out("goto_heimuya", 10, ob) ;
        return 1;
    }
    else  
    message_vision("张乘风上上下下打量了$N一下：什么！上崖？你的黑木令呢？！\n",ob);
    return 1;
}

int accept_object(object who, object ob)
{
    object myenv ;
    int r;  
    if (r = ::accept_object(who, ob))  
            return r;  

    if( query("id", ob) == "heimuling" )
    {
        message_vision("张乘风对$N说：好！这位" + RANK_D->query_respect(who) + "不错，那就请吧！\n" , who);
        message_vision("张乘风一招手，崖上落下一个大吊篮。\n", who);
        message_vision("$N一弯腰进了吊篮，吊篮缓缓地铰上崖去......\n", who);
        myenv = environment (who) ;
        who->move ("/d/heimuya/basket");
        call_out("goto_heimuya",10,who) ;
        return 1;
    }
/*
    else  
    {
        message_vision("张乘风对$N说：你敢耍我？！\n", who);
        this_object()->kill_ob(who);
    }
*/
    return 0;
}

void goto_heimuya (object ob)
{
    tell_object(ob , "你眼前一亮，一幢幢白色建筑屹立眼前，霎是辉煌。\n");
    ob->move ("/d/heimuya/chengdedian") ;
}

mixed ask_pfm()
{
     object me = this_player();

     if( query("can_perform/tianmo-gun/tian", me) )
           return RANK_D->query_respect(me) + "是想和老夫切磋一下武艺？";

     if( query("family/family_name", me) != query("family/family_name") )
           return "本教武功独步武林，这位" + RANK_D->query_respect(me) +
                  "既然想学，不如入我日月神教如何？";

     if (me->query_skill("tianmo-gun", 1) < 150)
           return "你的天魔棍尚欠火候，再多练练去吧！";

     message_vision(HIY "$n" HIY "对$N" HIY "点了点头：仔细看清楚了。\n" HIY
                    "只见$n" HIY "深吸口气，手中熟铜棍斜起向上，“呼”地一声" HIY
                    "迅疾点出，$N" HIY "只觉灵光闪闪，有如万条灵蛇般漫天飞舞。" NOR,
                    me, this_object());
     command("say 看懂了没有？");
     tell_object(me, HIC "你学会了「天旋地转」这一招。\n" NOR);
     if (me->can_improve_skill("club"))
             me->improve_skill("club", 160000);
     set("can_perform/tianmo-gun/tian", 1, me);
     return 1;
}
