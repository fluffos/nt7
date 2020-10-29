// fansong.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

mixed ask_pfm();

void create()
{
    set_name("范松", ({"fan song", "fan", "song"}));
    set("nickname", HIW "大力神魔" NOR );
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

    set_skill("force", 150);
    set_skill("riyue-xinfa", 150);
    set_skill("dodge", 150);
    set_skill("piaomiao-shenfa", 150);
    set_skill("hand", 150);
    set_skill("huanmo-longtianwu", 150);
    set_skill("cuff", 150);
    set_skill("xuwu-piaomiao", 150);
    set_skill("parry", 150);
    set_skill("literate", 110);
    set_skill("sword",150);
    set_skill("riyue-jian",150);
    set_skill("claw", 180);
    set_skill("shiying-shenzhao", 180);

    map_skill("force", "riyue-xinfa");
    map_skill("dodge", "piaomiao-shenfa");
    map_skill("hand", "huanmo-longtianwu");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("sword", "riyue-jian");
    map_skill("parry", "shiying-shenzhao");
    map_skill("claw", "shiying-shenzhao");

    create_family("日月神教", 2, "长老");

    set("inquiry", ([
        "绝命"  : (: ask_pfm :),
        "绝招"  : (: ask_pfm :),
    ]));

    set("master_ob",3);
        setup();
    carry_object("/d/heimuya/npc/obj/dafu");
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
    set("title", HIM"日月神教"HIG"大力护法"NOR, ob);
}

mixed ask_pfm()
{
      object me = this_player();

      if( query("can_perform/shiying-shenzhao/jueming", me) )
              return "你是不是想和我切磋一下？";

      if( query("family/family_name", me) != query("family/family_name") )
              return "我神教武功独步武林，这位" + RANK_D->query_respect(me) +
                     "既然想学，不如入我神教如何？";

      if (me->query_skill("shiying-shenzhao", 1) < 150)
              return "你的弑鹰神爪还练不到家，让我怎么教你呢！";

      message_vision(HIC "$n" HIC "对$N" HIC "点了点头：注意看清楚了。\n" HIC
                     "只见$n" HIC "手臂青筋暴起，左手微拳，右手成爪，" HIC
                     "挟一股劲风直向$N" HIC "前胸抓来。\n" HIR
                     "$N" HIR "一楞，欲避不及，只听“嗤啦”一声，" HIR
                     "前胸已被抓出五条血痕。\n" NOR,
                     me, this_object());
      command("say 哈哈，果然不错。你若是闪开，这招恐怕就再也难以领悟了。");
      me->receive_damage("qi",query("eff_qi", me)/4);
      me->receive_wound("qi",query("eff_qi", me)/6);
      tell_object(me, HIY "你学会了"HIR"「绝命」"HIY"这一招。\n" NOR);
      if (me->can_improve_skill("claw"))
            me->improve_skill("claw", 160000);
      set("can_perform/shiying-shenzhao/jueming", 1, me);
      return 1;
}
