#include <ansi.h>

// 模拟对话模式输出信息
varargs void broadcast_story(object ob, object me, string *msg, int index, int next, int flag)
{
        string char_name;
        string char_id;
        mixed line;

        if( !objectp(ob) || !objectp(me) ) return;
        
        if( index == 0 )
        {
                // 禁止quit之类的操作
                set_temp("in_skybook_story", 1, me);
        }
        
        // 对话结束
        if( index >= sizeof(msg) )
        {
                ob->go_on_process(me, next); 
                delete_temp("in_skybook_story", me);
                return;
        }
        
        char_name = me->query_name(1);
        char_id = me->query_id(1);
        
        line = msg[index];
        if( functionp(line) ) catch(line = evaluate(line));
        if( stringp(line) )
        {
                line = replace_string(line, "$N", char_name);
                line = replace_string(line, "$ID", char_id);
        }
        
         /*
        if( index % 2 == 1 )    
                line = HIY + "=" + line + "\n" NOR;
        else
         */
                line = HIM + "=" + line + "\n" NOR;
   
        if( !flag )
                tell_object(me, line);                  // 玩家一个人能看到
        else if( flag == 1 )
                message_vision(line, me);               // 玩家周围的人都能看到
        else
                message("skybook", line, users());      // 所有的人都可以看到
                
        call_out("broadcast_story", 0.5, ob, me, msg, ++index, next, flag);

        return;
}
