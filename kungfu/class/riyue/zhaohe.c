// zhaohe.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

mixed ask_pfm();

void create()
{
    set_name("赵鹤", ({"zhao he", "zhao", "he"}));
    set("nickname", HIC "飞天神魔" NOR );
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
    set_skill("hand", 180);
    set_skill("huanmo-longtianwu", 150);
    set_skill("tianmo-shou", 180);
    set_skill("cuff", 150);
    set_skill("xuwu-piaomiao", 150);
    set_skill("parry", 150);
    set_skill("literate", 110);
    set_skill("sword",150);
    set_skill("riyue-jian",150);

    map_skill("force", "riyue-xinfa");
    map_skill("dodge", "piaomiao-shenfa");
    map_skill("hand", "tianmo-shou");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("sword", "riyue-jian");
    map_skill("parry", "tianmo-shou");

    create_family("日月神教", 2, "长老");

    set("inquiry", ([
        "催魂"  : (: ask_pfm :),
        "绝招"  : (: ask_pfm :),
    ]));

    set("master_ob",3);
        setup();
    carry_object("/d/heimuya/npc/obj/leizhendang");
    carry_object("/clone/misc/cloth")->wear();
    carry_object("/d/heimuya/npc/obj/yancao");
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
    set("title", HIM"日月神教"HIC"飞天护法"NOR, ob);
}

mixed ask_pfm()
{
      object me = this_player();

      if( query("can_perform/tianmo-shou/cui", me) )
              return "你是不是想和我切磋一下？";

      if( query("family/family_name", me) != query("family/family_name") )
              return "我神教武功独步武林，这位" + RANK_D->query_respect(me) +
                     "既然想学，不如入我神教如何？";

      if (me->query_skill("tianmo-shou", 1) < 150)
              return "你的天魔手还练不到家，让我怎么教你呢！";

      message_vision(HIC "$n" HIC "对$N" HIC "点了点头：注意看好了。\n" HIC
                     "只见$n" HIC "左跨一步，右跨一步，瞬间便来到$N" HIC
                     "的面前，“呼”地拍出一掌。\n" HIC
                     "$N" HIC "一楞，顿时豁然贯通。\n" NOR,
                     me, this_object());
      command("say 看懂没有？");
      tell_object(me, HIR "你学会了「催魂」这一招。\n" NOR);
      if (me->can_improve_skill("hand"))
            me->improve_skill("hand", 160000);
      set("can_perform/tianmo-shou/cui", 1, me);
      return 1;
}
