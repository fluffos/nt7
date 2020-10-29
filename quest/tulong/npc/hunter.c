inherit NPC;
#include <ansi.h>

void create()
{
        set_name("精灵猎人", ({ "spirit hunter", "hunter"}));
        set("long",
                "他眉目清秀，手持弓箭，似乎正在等待着什么。\n");
        set("gender", "男性");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("no_get", 1);

        set("str", 20);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 1100);
        set("max_jing", 1600);
        set("neili", 1600);
        set("max_neili", 600);

        set("combat_exp", 900000);
        set("score", 6000);

        set_skill("force", 390);
        set_skill("dodge", 300);
        set_skill("unarmed", 390);
        set_skill("parry", 300);
        set_skill("throwing", 310);
        set_skill("xuanyuan-arrow", 310);

        map_skill("parry", "xuanyuan-arrow");
        map_skill("sword", "xuanyuan-arrow");

        set("chat_chance",3);
        set("chat_msg", ({
            "精灵猎人说道：这里是个大猎场，只要耐心打猎(hunting)，一定会有大收获。\n"
        }));

        setup();
      carry_object("/quest/tulong/obj/arrow")->wield();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_hunting","hunting");
}

void greeting(object ob)
{ 
int change=0;
if( !ob || environment(ob) != environment() ) return;
message_vision( "\n$N微笑道：这位"+RANK_D->query_respect(ob) + "，来到这里一定很辛苦，歇歇再走吧。\n",this_object());
}

int do_hunting()
{
        object me=this_player();
        object* ob;
        int i;

        if( query_temp("in_hunting", me) )
           return notify_fail("精灵猎人对你说：专心狩猎，不要东张西望。\n");
        ob = users();
        for (i=sizeof(ob); i>0; i--)
        {
                if (query_temp("in_hunting", ob[i-1]))
                return notify_fail("精灵猎人对你说：已经有人在狩猎了，你先休息一下吧。\n");
        }
        tell_room(environment(me),query("name", me)+"开始隐藏起来，准备狩猎。\n");
        set("hunter", HIY"猎人"NOR, me);
        set_temp("in_hunting", "1", me);
        me->save();
        remove_call_out("end_hunting");
        call_out("end_hunting", 150, me);
        remove_call_out("clone_beast");
        call_out("clone_beast", 30, me);
        return 1;
}
void clone_beast(object me)
{
        object ob;
        if (! me) return;
        tell_room(environment(me),"几只野兽从树林里警惕地走出来，要打猎就是现在了！\n");
        switch (random(6)) {
         case 0: 
        ob=new("/quest/tulong/npc/wolf");
        ob->move("/d/dragon/liechang"); 
        ob=new("/quest/tulong/npc/huananhu");
        ob->move("/d/dragon/liechang");         call_out("clone_beast", 100, me); 
          break;
         case 1: 
        ob=new("/quest/tulong/npc/dog");
        ob->move("/d/dragon/liechang"); 
        ob=new("/quest/tulong/npc/fox");
        ob->move("/d/dragon/liechang");
         call_out("clone_beast", 100, me);  
          break;
         case 2: 
        ob=new("/quest/tulong/npc/huananhu");
        ob->move("/d/dragon/liechang"); 
        ob=new("/quest/tulong/npc/wolf");
        ob->move("/d/dragon/liechang");
         call_out("clone_beast", 100, me);  
          break;
         case 3: 
        ob=new("/quest/tulong/npc/dog");
        ob->move("/d/dragon/liechang"); 
        ob=new("/quest/tulong/npc/fox");
        ob->move("/d/dragon/liechang");
         call_out("clone_beast", 100, me);  
          break; 
         case 4: 
        ob=new("/quest/tulong/npc/dog");
        ob->move("/d/dragon/liechang"); 
        ob=new("/quest/tulong/npc/huananhu");
        ob->move("/d/dragon/liechang");
         call_out("clone_beast", 100, me);  
          break; 
         case 5: 
        ob=new("/quest/tulong/npc/dog");
        ob->move("/d/dragon/liechang"); 
        ob=new("/quest/tulong/npc/songshu");
        ob->move("/d/dragon/liechang");
         call_out("clone_beast", 100, me);  
          break;
             }
}
void end_hunting(object me)
{
        if (! me) return;
        delete("hunter", me);
        addn("guarded", 1, me);
        addn("combat_exp", 250+random(200), me);
        addn("potential", 200, me);
        delete_temp("in_hunting", me);
        me->save();
        remove_call_out("clone_beast");
        tell_room(environment(me),query("name", me)+"结束了狩猎。\n");
        tell_object(me,"你得到了一引起经验和潜能。\n");
        tell_object(me,"你结束了狩猎。\n");
}
void die()
{
        object *me;
        int i;

        me = users();
        for (i = 0; i < sizeof(me); i ++)
            delete_temp("in_hunting", me[i]);

        ::die();
}
