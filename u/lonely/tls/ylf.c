#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"应乐峰"NOR);
        set("long", @LONG
点苍山最高峰应乐峰，山峰直插云霞，雄伟壮丽。这里寒风刺骨，
夹杂着冰雪向你扑面吹来。脚下山路上的积雪都已结冰，你走在上面不
住地打滑。
LONG);
        set("outdoors", "dali");

        set("exits", ([             
           "northdown" : __DIR__"ylf2",
           "southdown" : __DIR__"ylf1",
        ]));

        set("coor/x",-350);
  set("coor/y",-390);
   set("coor/z",30);
   setup();
}

void init()
{
       object me = this_player();
       mapping my_fam  = me->query("family");

       if( random(me->query_skill("dodge",1)) <= 40 && me->query("kar") <5){
               me->receive_damage("qi", 100);
               me->receive_wound("qi",  100);
               message_vision(HIR"$N一不小心脚下一滑，... 啊...！\n"NOR, me);
               me->move(__DIR__"ylf1");
               message("vision", HIR"只见" + me->query("name") + "从山上骨碌碌地滚了过来，又骨碌碌地滚了下去！\n"NOR, environment(me), me);               
               me->move(__DIR__"dc1");
               message("vision", HIR"只见" + me->query("name") + "从山上骨碌碌地滚了过来，又骨碌碌地滚了下去！\n"NOR, environment(me), me);
               me->move(__DIR__"dc2");
               message("vision", HIR"只见" + me->query("name") + "从山上骨碌碌地滚了过来，又骨碌碌地滚了下去！\n"NOR, environment(me), me);
               me->move(__DIR__"dc3");
               tell_object(me, HIR"你从山上滚了下来，只觉得浑身无处不疼，还受了几处伤。\n"NOR);
               message("vision", HIR"只见" + me->query("name") + "从山上骨碌碌地滚了下来，躺在地上半天爬不起来！\n"NOR, environment(me), me);
               me->start_busy(2);
               }
            
   else{
       if (my_fam)
       if (my_fam["family_name"] == "天龙寺"&&random(10)<2) { 
       me->set_temp("wait", 1);
       call_out("do_wait", 30 + random(10), me);
           }
       }
}

void do_wait(object me)
{
        if (!me) return;
        if(environment(me) && me->query_temp("wait") && 
           me->query_skill("literate", 1) > 100){
           tell_object(me,HIY"\n你站在峰顶，放眼望去，只见满天金霞，照耀着千万座起伏山峰，
松柏青翠，景物若洗，朝露如珠，闪闪生光。\n"NOR);
           me->del_temp("wait");
           me->add("potential", random(3));
                   me->set("jing",me->query("max_jing"));
           message_vision("\n$N站起身来，深深地吸了口气，只觉心中一片明静、神清意爽。\n", me);
          
          }
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("wait"))
                me->delete_temp("wait");     
        return 1;
}
