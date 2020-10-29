#include <ansi.h> 

inherit F_CLEAN_UP; 

int main(object me, string arg)
{
       if( me->is_busy() )
               return notify_fail("你正忙著呢。\n");

       if( me->is_fighting() )
               return notify_fail("你现在正在战斗！\n"); 

       if( me->is_ghost() )  
               return notify_fail("等你还了阳再说吧。\n");

       if( me->is_in_prison() )
               return notify_fail("你正在做牢呢。\n");

       if( query("doing", me) ) 
               return notify_fail("你还想干什么？！\n"); 

        if (base_name(environment(me)) == "/d/city/kedian4") 
                return notify_fail("你已经在聊天室了。\n"); 

       if( query("no_magic", environment(me)) )
               return notify_fail("你发现从这里不能进入聊天室！\n");

       if( query_temp("warquest/party", me) )
               return notify_fail("你还想在战争中使用？！\n"); 

        if( sscanf(base_name(environment(me)), "/d/register/%*s") )
                return notify_fail("你还没有出生呢，不能施展！\n");

        if( sscanf(base_name(environment(me)), "/d/newbie/%*s") ) 
                return notify_fail("你在古村中，不能施展！\n"); 

        message("vision", me->name() + "举起右手在面前极速画了一个圆，竟划破了面前的" 
                "空间，\n只见圆内的空间真空将" + me->name() + "给吸了进去。\n", 
                environment(me), ({me})); 

        tell_object(me, "你从聊天室的某个角落空间裂缝中钻出。\n"); 
        me->move("/d/city/kedian4"); 
        MYGIFT_D->check_mygift(me, "newbie_mygift/chatroom"); 

        message("vision", me->name() + "从聊天室的某个角落空间裂缝中钻出。\n", 
                environment(me), ({me})); 

        return 1; 
}
