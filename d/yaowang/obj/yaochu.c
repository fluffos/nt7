#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_wayao", "dig");
}

void create()
{
        set_name("药锄", ({"yao chu", "chu"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("no_drop","不要乱丢，这东西打到人会痛的！\n");
                set("no_put",1);
                set("long", "这是一把很重的药锄，你可以用它来挖药（dig yao）。\n");
                set("value", 5000);
        }
        setup();
}

int do_wayao(string arg)
{       object ob;
        object me=this_player();
        if( me->is_busy() || query_temp("pending/exercising", me))return notify_fail("你现在正忙着呢。\n");
        if (!arg||arg!="yao") return notify_fail("你要挖什么呢？！\n");
        if( (query("jing", me)<20))return notify_fail("你的精力不能集中，挖了也是白挖！\n");
        if( query("qi", me)<40)return notify_fail("你太累了，怎么都拿不动这把药锄！\n");
        if (present("zhengui yaocai", environment(this_object()))||present("putong yaocai",environment(this_object()))) return notify_fail("别不知足,你已经挖到药了！\n");
        if(environment(this_object()) != me)  return notify_fail("你是在看别人挖吧？\n");
        if( query_temp("wayao1", environment(me)) )
        {
        me->start_busy(random(3)+1);
        message_vision("$N挥动药锄“呼哧、呼哧”地在地上挖了起来,似乎在找什么东西。\n",me);
        addn("jing", -10, me);
        addn("qi", -20, me);
        if(random(7)<3)
        {
        message_vision(YEL"$N挖了半天，终于把那颗药材小心翼翼地掘了出来。\n"NOR,me);
        new(__DIR__"obj/yaocai")->move(me);
        addn_temp("wayao1", -1, environment(me));
        destruct(this_object());
        me->start_busy(1);
        }
      return 1;
   }
      else
        if( query_temp("wayao2", environment(me)) )
        {
        me->start_busy(1+random(4));
        message_vision(CYN"$N挥动药锄开始在地上挖了起来。\n"NOR,me);
        addn("kee", -20, me);
        addn("sen", -30, me);
             if(random(7)<4)
      {
        message_vision(YEL"$N挖了半天，终于把那颗药材小心翼翼地掘了出来。\n"NOR,me);
//        new(__DIR__"obj/yaocai")->move(me);
        addn_temp("wayao2", -1, environment(me));
        destruct(this_object());
        me->start_busy(1);
      }
        return 1;
    }
      return notify_fail("这里什么都没有,原来是你看花了眼。\n");
}