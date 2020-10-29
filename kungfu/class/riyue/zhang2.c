// zhang2.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

mixed ask_pfm();

void create()
{
    set_name("张乘云", ({"zhang chengyun", "zhang", "chengyun"}));
    set("nickname", HIW "白猿神魔" NOR );
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
    set_skill("cuff", 180);
    set_skill("xuwu-piaomiao", 180);
    set_skill("fengyun-bianhuan", 180);
    set_skill("parry", 150);
    set_skill("literate", 110);
    set_skill("sword",150);
    set_skill("riyue-jian",150);

    map_skill("force", "riyue-xinfa");
    map_skill("dodge", "piaomiao-shenfa");
    map_skill("hand", "huanmo-longtianwu");
    map_skill("cuff", "fengyun-bianhuan");
    map_skill("sword", "riyue-jian");
    map_skill("parry", "fengyun-bianhuan");

    create_family("日月神教", 2, "长老");

    set("inquiry", ([
        "风起云涌"  : (: ask_pfm :),
        "绝招"      : (: ask_pfm :),
    ]));

    set("master_ob",3);
        setup();
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
    set("title", HIM"日月神教"HIW"白猿护法"NOR, ob);
}

mixed ask_pfm()
{
      object me = this_player();

      if( query("can_perform/fengyun-bianhuan/fengyun", me) )
              return "你是不是想和我切磋一下？";

      if( query("family/family_name", me) != query("family/family_name") )
              return "我神教武功独步武林，这位" + RANK_D->query_respect(me) +
                     "既然想学，不如入我神教如何？";

      if (me->query_skill("fengyun-bianhuan", 1) < 150)
              return "你的风云变幻还练不到家，让我怎么教你呢！";

      message_vision(HIW "$n" HIW "对$N" HIW "点了点头：注意看清楚了。\n" HIW
                     "只见$n" HIW "双拳一错，顿时一股气旋向$N" HIW
                     "卷来，$N" HIW "感觉胸口似有重压，不由连退数步。\n" NOR,
                     me, this_object());
      command("say 看懂没有？");
      tell_object(me, HIC "你学会了「风起云涌」这一招。\n" NOR);
      if (me->can_improve_skill("cuff"))
            me->improve_skill("cuff", 160000);
      set("can_perform/fengyun-bianhuan/fengyun", 1, me);
      return 1;
}
