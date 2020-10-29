// shiao.c
#include <ansi.h>

inherit NPC;

void create()
{
        set_name("妙手郎中", ({ "immortal doctor", "doctor" }) );

        set("nickname", "半仙");
        set("gender", "男性");
        set("age", 30);
        set("long",
                "仙医能治各种疑难杂症,端的是手到病除.\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("con", 30);
        set("int", 24);
        set("dex", 30);

        set("inquiry", ([
                "自宫": "哦....你要自宫?没问题,包你无痛!(accept zigong)?\n",
        ]) );
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_accept", "accept");
}

int  do_accept(string arg){

      object me;

      me=this_player();

      if (arg!="zigong") return 0;
      if( query("gender", me) != "男性" )
      {
         CHANNEL_D->do_channel(this_object(), "chat",
                sprintf("%s想自宫可惜办不到,哈哈..\n",query("name", me)));
         return 0;
      }
      CHANNEL_D->do_channel(this_object(), "chat", sprintf( "%s 自宫练辟邪剑法啦! \n",
        me->name(1)));
        set("marks/自宫", 1, me);
        set("gender", "无性", me);
      return 1;
}

int accept_fight(object me)
{
        command("say 我怎么能打得过您？\n");
        return 0;
}
