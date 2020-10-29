#include <ansi.h>

int valid_leave(object me, string dir)
{
       if( dir == "north")addn_temp("mark/steps", 1, me);
       if( dir == "south")addn_temp("mark/steps", -1, me);
       if( dir == "east")addn_temp("mark/step", 1, me);
       if( dir == "west")addn_temp("mark/step", -1, me);
        
       if( query_temp("mark/steps", me) <= -10 && 
          query_temp("mark/step", me) <= -10){
            me->move("/d/baituo/gebi");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            tell_room(environment(me), me->name()+"拖着疲惫不堪的身子从戈壁沙漠走了过来。\n",  ({ me }));  
            tell_object(me, "突然你眼前出现了一坐小山，形状宛如驼峰。\n");
            return -1;
            }       
           
       if( query_temp("mark/steps", me) == -12){
            me->move(__DIR__"senlin");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            tell_room(environment(me), me->name()+"拖着疲惫不堪的身子从戈壁沙漠走了过来。\n",  ({ me }));  
            tell_object(me, "突然你走出了大戈壁，来到一森林处。\n");
            return -1;
            }       
           
       if( query_temp("mark/step", me) == 11){
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            me->move(__DIR__"gebi5");
            return -1;
            }  
       if( query_temp("mark/steps", me) == 11 && 
          query_temp("mark/step", me)<-10){
            me->move(__DIR__"room-ji");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            tell_room(environment(me), me->name()+"拖着疲惫不堪的身子从戈壁沙漠走了过来。\n",  ({ me }));  
            tell_object(me, "啊，出来了！你终于走出大戈壁了！\n");
            return -1;
            }  

       if( (query_temp("mark/steps", me) == 7 && query_temp("gc_n", me)) || 
          (query_temp("mark/steps", me) == -7 && query_temp("gc_s", me)) || 
          (query_temp("mark/step", me) == -7 && query_temp("gc_w", me)) || 
          (query_temp("mark/step", me) == 7 && query_temp("gc_e", me))){
            me->move(__DIR__"lvzhou");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            delete_temp("gc_n", me);
            delete_temp("gc_s", me);
            delete_temp("gc_w", me);
            delete_temp("gc_e", me);
            tell_room(environment(me), me->name()+"拖着疲惫不堪的身子从戈壁沙漠走了过来。\n",  ({ me }));  
            tell_object(me, "运气真好，你找到了一处沙漠绿洲！\n");
            return -1;
            }
 
       if( (query_temp("mark/steps", me) == 7 && (query_temp("mark/step", me) == 3 || 
           query_temp("mark/step", me) == -3) && query_temp("gc1_n", me)) || 
          (query_temp("mark/steps", me) == -7 && (query_temp("mark/step", me) == 3 || 
           query_temp("mark/step", me) == -3) && query_temp("gc1_s", me)) || 
          (query_temp("mark/step", me) == 7 && (query_temp("mark/steps", me) == 3 || 
           query_temp("mark/steps", me) == -3) && query_temp("gc1_e", me)) || 
          (query_temp("mark/step", me) == -7 && (query_temp("mark/steps", me) == 3 || 
           query_temp("mark/steps", me) == -3) && query_temp("gc1_w", me))){
            me->move(__DIR__"shulin");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            delete_temp("gc1_n", me);
            delete_temp("gc1_s", me);
            delete_temp("gc1_w", me);
            delete_temp("gc1_e", me);
            tell_room(environment(me), me->name()+"拖着疲惫不堪的身子从戈壁沙漠走了过来。\n",  ({ me }));  
            tell_object(me, "咦，你发现这里已经不是戈壁沙漠了！\n");
            return -1;
            }       
        return ::valid_leave(me, dir);
}

void init()
{
       object me, *ob, *inv, ob1;
       string msg, msg1;
       int i, j;
       me = this_player();
       ob = all_inventory(environment(me));
       msg = YEL"\n突然一股疾风刮到，带著一大片黄沙，只吹得众人满口满鼻都是沙土，在无边无际的大沙漠之中，
在那遮天铺地的大风沙下，便如大海洋中的一叶小舟一般，只能听天由命，全无半分自主之力。\n"NOR;
       msg1 = HIR"你觉得自己已经筋疲力尽了，身上的黄沙却越堆越厚……\n"NOR;

       if(ob1 = present("bai shoujuan", me)){
          write(WHT"你依照白手绢上的提示，很快便走出了大戈壁。\n"NOR);
          me->move(__DIR__"caoyuan",1);
          destruct(ob1);
          delete_temp("mark/steps", me);
          delete_temp("mark/step", me);
          tell_room(environment(me), me->name()+"神秘兮兮地从戈壁沙漠走了过来。\n",  ({ me }));  
          write("突然你一不留神，白手绢被风吹走了！\n");
          return;
          }  
       if(userp(me)){ 
         if( query_temp("li_meet", me) == 2){
              message_vision(msg, me); 
              tell_object(me, msg1);
              delete_temp("mark/steps", me);
              delete_temp("mark/step", me);
              me->unconcious();             
              me->move(__DIR__"shulin");
              tell_room(environment(me), "突然一阵轻风吹过，好象有人在你背后出现！\n", ({ me }));  
              return;
              }
         else if( query("water", me)<20 )
              { 
              message_vision(msg1, me);              
                  me->unconcious();
                  me->move(__DIR__"caoyuan"+(1+random(7)));
                  tell_room(environment(me), HIR"突然一阵狂风吹过，掉下一个人来！\n"NOR,  ({ me }));  
                  delete_temp("mark/steps", me);
                  delete_temp("mark/step", me);
                  delete_temp("gc_n", me);
                  delete_temp("gc_s", me);
                  delete_temp("gc_w", me);
                  delete_temp("gc_e", me);
                  delete_temp("gc1_n", me);
                  delete_temp("gc1_s", me);
                  delete_temp("gc1_w", me);
                  delete_temp("gc1_e", me);
              return;
              }
         else if(me->query_skill("dodge", 1) <= 150) { 
              addn("jing", -15, me);
              if( objectp(present("bigu fu", me)) && query("reborn/times", me) < 3 )
              addn("water", -10, me);
              }
         else {
              addn("jing", -5, me);
              if( objectp(present("bigu fu", me)) && query("reborn/times", me) < 3 )
              addn("water", -5, me);
              }
      }
}
