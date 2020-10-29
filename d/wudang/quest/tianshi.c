// tianshi.c 李天师
// Modified by haiyan

#include <ansi.h>
inherit NPC;

mixed ask_ghost();
string ask_fail();
int accept_object(object me, object ob);

void create()
{
        set_name("李天师", ({ "li tianshi", "li", "tianshi" }));
        set("long", "这是一位仙风道骨的法师，身上的道袍上画着一些驱魔符号。\n");
        set("nickname", HIY"镇妖真人"NOR);
        set("gender", "男性");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 20);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 5000);
        set("max_jing", 500);
        set("neili", 3000);
        set("max_neili", 3000);

        set("combat_exp", 800000);
        set("score", 1000);

        set_skill("force", 200);
        set_skill("wudang-xinfa", 200);
        set_skill("dodge", 200);
        set_skill("strike", 200);
        set_skill("wudang-zhang", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("wudang-jian", 200);
        set_skill("taoism", 300);

        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        set("inquiry", ([
                "job"   : (: ask_ghost :),
                "捉鬼"  : (: ask_ghost :),
                "失败"  : (: ask_fail :),
                "fail"  : (: ask_fail :),
                "桃木剑": "桃木剑是捉鬼的必备之物，自己去做一把好了。",
        ]));

        setup();
        carry_object("/clone/cloth/dao-cloth")->wear();
        carry_object("/d/taohua/obj/taojian")->wield();
}

#include "dirs.h"
#include "gui.h"

mixed ask_ghost()
{
      string *kp, p, room;
      object me, ob, ghost;
      int dam;
      me = this_player();

      if( query("family/family_name", me) != "武当派" && 
          query("family/family_name", me) != "全真教" )
           return "这位" + RANK_D->query_respect(me) + "也有捉鬼的本事吗？";

      if (me->query_skill("taoism", 1) < 50)
           return "还是算了吧！你这点道行只怕给鬼捉了。";

      if( query("combat_exp", me)>400000 )
           return "你身手那么高，这种小事怎么敢劳你动手！";

      if( query_temp("gui/shougui", me) )
           return "刚才不是让你去捉鬼了嘛？怎么又回来了？";

      kp = keys(dirs);
      p = kp[random(sizeof(kp))];
      room = dirs[p][random(sizeof(dirs[p]))];
      if( wizardp(me) )  tell_object(me,sprintf("<鬼出现在 %s 地点>\n",room));

      dam = me->query_skill("taoism", 1) + random(10) - random(10);
      ghost = new(gui[random(sizeof(gui))] );
      ghost->move(room);
      set_temp("player",query("id",  me), ghost);
      set_temp("born_time", time(), ghost);
      set_temp("damage", dam*2/5, ghost);
      ghost->set_skill("claw", dam);

      tell_object(me, this_object()->name() + "对你道：据说最近" +
                  p + "常有" + ghost->name() + "出没，附近居民"
                  "深受其害。你去把它收了吧。\n");
      message("vision", this_object()->name() + "在" + me->name() + "耳边吩咐着什么，" +
              me->name() + "一边听，一边不住地点头。\n", environment(me), me);
      ob = new("/d/wudang/quest/obj/fuzhi");
      ob->move(this_object());
      command("give fu zhi to "+query("id", me));
      tell_object(me, this_object()->name() + "继续道：" + ob->name() +
                  "可以让鬼魂现身，可别弄丢了。\n");
      message_vision("$n对$N说道：快动身吧，多加小心。\n", me, this_object());
      set_temp("gui/shougui", 1, me);
      return 1;
}

string ask_fail()
{
      object me = this_player();

      if( !query_temp("gui/shougui", me) )
           return "我没有给你什么任务啊？";

      if (present("fu zhi", me))
          destruct(present("fu zhi", me));
      delete_temp("gui/shougui", me);
      delete_temp("gui/base", me);
      command("sigh"+query("id", me));
      addn("weiwang", -random(20), me);
      if( query("weiwang", me)<0)set("weiwang", 0, me);
      tell_object(me, HIR"你的江湖威望降低了！\n"NOR);
      return "你不能干，我只好请别人去了！";
}


int accept_object(object me, object ob)
{
    int base, exp, pot;
    if( !me || environment(me) != environment() ) return 0;
    if ( !objectp(ob) ) return 0;
    if ( !present(ob, me) ) return notify_fail("你身上没有这样东西。");
    if( query("id", ob) == "fuzhi" )
    {
         if( !query_temp("gui/finish", me) )
         {
             command("sneer"+query("id", me));
             command("say 想蒙骗本天师吗？");
             addn("weiwang", -random(50), me);
             if( query("weiwang", me)<0)set("weiwang", 0, me);
             tell_object(me, HIR"你的威望降低了！\n"NOR);
             return 1;
         }

         base=query_temp("gui/base", me);
         exp = base + random(base/2);
         pot = exp/3 + random(exp/3);
         if( query("potential", me) >= me->query_potential_limit())pot=1;
         message_vision("$n对$N点了点头：不错，不错。\n", me, this_object());
         tell_object(me, HIG "通过这次煅炼，你获得了" + chinese_number(exp) +
                     "点经验和" + chinese_number(pot) + "点潜能。\n" NOR);
         tell_object(me, HIC"你对道学心法有了新的领悟！\n"NOR);
         me->improve_skill("taoism", me->query_int()*2);
         addn("combat_exp", exp, me);
         addn("shen", exp/2+random(exp/2), me);
         addn("potential", pot, me);
         delete_temp("gui/base", me);
         delete_temp("gui/shougui", me);
         delete_temp("gui/finish", me);
         destruct(ob);
         return 1;
    }
    else
    {
        command("say 你给我这种东西干什么？");
        return 0;
    }
}
