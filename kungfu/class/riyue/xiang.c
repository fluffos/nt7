// xiang.c
//Update by haiyan

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

#define CHILONG    "/clone/lonely/chilongsuo"
#define XINGLV     "/clone/item/xiaoao/xinglvtu"
#define SHUAIYI     "/clone/item/xiaoao/shuaiyitie"
int ask_kill();
mixed ask_pfm();

void create()
{
        object ob1, ob2;
    set_name("向问天", ({ "xiang wentian", "xiang"}));
    set("nickname", HIR "天王老子" NOR );
    set("gender", "男性");
    set("title", "日月神教光明右使");
    set("long", "他就是日月神教的光明右使。为人极为豪爽。\n");
    set("age", 56);
    set("shen_type", -1);
    set("attitude", "peaceful"); 

    set("str", 21);
    set("per", 28);
    set("int", 30);
    set("con", 26);
    set("dex", 30);
    set("chat_chance", 1);
    set("inquiry", ([
      "杨莲亭"     : "这种人，该杀！\n",
      "东方不败"   : "篡位叛徒，我非杀了他不可！\n",
      "任我行"     : "教主被困，已历十年......\n",
      "杀东方不败" : (: ask_kill :),
      "望断秋水"   : (: ask_pfm :),
      "绝招"       : (: ask_pfm :),
    ]));
    set("qi", 4000);
    set("max_qi", 4000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3500);
    set("max_neili", 3500);
    set("jiali", 350);

    set("combat_exp", 2500000);
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
    set_skill("whip", 180);
    set_skill("liushui-bian", 180);
    set_skill("literate", 110);

    set_skill("sword", 150);
    set_skill("riyue-jian", 150);
    map_skill("sword", "riyue-jian");
    map_skill("force", "riyue-xinfa");
    map_skill("dodge", "piaomiao-shenfa");
    map_skill("hand", "huanmo-longtianwu");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("parry", "liushui-bian");
    map_skill("whip", "liushui-bian");

    prepare_skill("hand", "huanmo-longtianwu");
    prepare_skill("cuff", "xuwu-piaomiao");

    create_family("日月神教", 2, "光明右使");
    set("have_ling",1);
    set("master_ob",3);
        setup();
        if (clonep())
        {
                ob1 = find_object(XINGLV);
                if (! ob1) ob1 = load_object(XINGLV);
                if (! environment(ob1)) ob1->move(this_object());

                ob1 = find_object(SHUAIYI);
                if (! ob1) ob1 = load_object(SHUAIYI);
                if (! environment(ob1)) ob1->move(this_object());

                ob2 = find_object(CHILONG);
                if (! ob2) ob2 = load_object(CHILONG);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wield();
                } else
                {
                        ob2 = new("/clone/weapon/changbian");
                        ob2->move(this_object());
                        ob2->wield();
                }
        }
    carry_object("/d/heimuya/npc/obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
    if( query("family/family_name", ob) == "日月神教" )
        command("say 老夫已不收弟子，不过我这里有一套鞭法，你若想学，我可以教你。");
    else
        command("say 我不收弟子。");
    return;
}

int recognize_apprentice(object ob, string skill)
{
     if( query("family/family_name", ob) == "日月神教" )
     {
         if (skill != "whip" && skill != "liushui-bian")
         {
             command("say 我只会点鞭法，其他的找你师傅去学！");
             return -1;
         }

         if( query("character", ob) == "光明磊落" && skill == "liushui-bian" )
         {
             command("say 你不适合学我这门绝技！");
             return -1;
         }

         if( query("shen", ob)>0 )
         {
             command("heng");
             command("say 你既然自命正派君子，来学我这种雕虫小技做什么？");
             return -1;
         }

         if (skill == "liushui-bian" && ob->query_skill("whip", 1) < 150)
         {
             command("say 你对基本鞭法的理解也未免太差了点。");
             return -1;
         }

         if (skill == "whip")
         {
             if( !query("can_learn/xiang/whip", ob) )
             {
                  command("say 好吧，我就教你一点关于鞭法的基本知识。");
                  set("can_learn/xiang/whip", 1, ob);
             }
             return 1;
         }

         if (skill == "liushui-bian")
         {
             if( !query("can_learn/xiang/liushui-bian", ob) )
             {
                  command("say 很好，我这就传你流水鞭法！");
                  set("can_learn/xiang/liushui-bian", 1, ob);
             }
             return 1;
         }
     }
     return 0;
}

mixed ask_pfm()
{
      object me = this_player();

      if( query("can_perform/liushui-bian/wang", me) )
              return "你要跟老夫切磋一下吗？";

      if( query("family/family_name", me) != query("family/family_name") )
              return "我神教武功独步武林，这位" + RANK_D->query_respect(me) +
                     "既然想学，不如入我神教如何？";

      if (me->query_skill("liushui-bian", 1) < 180)
              return "你的流水鞭法还练不到家，让我怎么教你呢！";

      message_vision(HIY "$n" HIY "对$N" HIY "点了点头：你看那块巨石。\n" HIY
                     "只见$n" HIY "手中长鞭一荡，骤然向上挥出，只见长鞭" HIY
                     "划出一道弧线，直向巨石击去。\n" HIW
                     "“叭”的一声，巨石已被打成碎片，四下飞散。\n" NOR,
                     me, this_object());
      command("say 你看懂了没有？");
      tell_object(me, HIY "你学会了「望断秋水」这一招。\n" NOR);
      if (me->can_improve_skill("whip"))
            me->improve_skill("whip", 160000);
      set("can_perform/liushui-bian/wang", 1, me);
      return 1;
}

int ask_kill()
{
      object ob, me = this_player();
      if (!query("have_ling"))
            command("say 我的天香堂令牌已经给别人了，怎么还不去？");
      else
      {
            command("tell"+query("id", me)+"你要去杀东方不败？\n");
            message_vision(HIC "向问天对$N点了点头说：我助你一臂之力。\n" NOR, me);
            ob=new("/d/heimuya/npc/obj/card4");
            ob->move(me);
            delete("have_ling");
            tell_object(me, "向问天从怀里摸出一块令牌塞到你的手上。\n");
      }
      return 1;
}

void reset()
{
      set("have_ling",1);
}
