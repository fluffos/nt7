// dbshan.c 冰山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"冰山"NOR);
        set("long", @LONG
大冰山在日光的照射下发出刺眼的光芒，显得十分奇丽，这里到
处都是冰雪，冰山颇大，如陆地上之山丘，一眼望去，横百余丈，纵
长几十丈，冰山上滑不留步。海中不时有几块小浮基(fubing)正在向
北飘流。
LONG );
	set("outdoors", "极北");
        set("exits", ([  
              "east" : __DIR__"dbshan1",
        ]));
        set("item_desc", ([
                "fubing" : "旁边的海水里面漂浮着几块浮冰，但是相隔很远，看来还没法过去\n",
        ]));
        setup();
}

void init()
{
      remove_call_out("change");
      remove_call_out("change1");
      call_out("change", random(150) + 50); 
      add_action("do_jump", "jump");
}

void change()
{
      tell_room(this_object(),HIW"便在此时，只听得丁冬、丁冬数声，极是清脆动听，几块浮冰飘近了。\n"NOR);    
      this_object()->set_temp("fubing", 1);    
      remove_call_out("change1");
      call_out("change1", 10);  
}

void change1()
{
      tell_room(this_object(),"海中潮流涌过，那清脆之声又渐渐远去了。\n");    
      this_object()->delete_temp("fubing");    
      remove_call_out("change");
      call_out("change", 50+random(150));  
}

int do_jump(string arg)
{
     object me = this_player();
     if(!query_temp("fubing")) return 0;
     if( ! arg || arg=="fubing" ) {
         message("vision",me->name() + "一纵身，整个人已到了浮冰上。\n",environment(me), ({me}) );
         me->move(__DIR__"foubing");
         message("vision",me->name() + "从冰山上飞身而来。\n",environment(me), ({me}) );
         if(random(me->query_dex()) < 50){
             message_vision("结果$N一不小心脚下一滑，仰天一个大摔跤！\n",me);
             me->set_temp("last_damage_from", "摔倒在冰山上，脑溢血而");
             me->receive_wound("qi", 50);
             me->receive_damage("qi", 100);
         }
         return 1;
     }
     return 0;
}       

void reset()
{
       change1();
       remove_call_out("change");
       remove_call_out("change1");
       call_out("change", random(150) + 50); 
        ::reset();
}
