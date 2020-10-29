#include <ansi.h> 
#include <room.h>  
inherit CREATE_CHAT_ROOM; 
int is_chat_room() { return 1; }  

void create()
{
        set("short", "蛇精洞");
        set("long",@LONG
此处乃蛇精洞，洞内幽深恐怖，四处可见黑色的骸骨，周围尽是
毒蛇，洞顶不时地滴下发臭的液体，置身此地，心中有一种莫名的恐
惧，据说，九头蛇精就藏在此洞深处。

LONG);


        set("exits", ([
                "out"  : __DIR__"shedong4.8",
        ]));

        set("no_rideto",1);
        set("no_flyto", 1);
        set("no_clean_up", 1);
        setup();

}

// 检查今天是否已经参加过蛇精战
void init()
{
        object me = this_player();

        // 24小时只能参加一次
        if (time() - query("boss/shejing", me) < 2 * 3600 && userp(me) && !wizardp(me)  || query("schedule", me) || query("doing", me) == "trigger")
        {
                tell_object(me, HIG "\n对不起，你参加蛇精对抗战间隔时不足2小时(也不准计划练功请你取消计划及所有触发)。\n");
                tell_object(me, HIC "你距离上次参加蛇精对抗战间隔： " + HIY +
                                  sprintf("%d", (time() - query("boss/shejing", me)) / 3600) + HIC " 小时。\n\n" NOR);
                me->move(__DIR__"shedong4.8");
                return;
        }

        // 设置参加时间
        tell_object(me, HIG "\n你进入蛇精洞准备参加对抗蛇精战斗，请不要离开，否则2小时内无法再次进入。\n" NOR);
        set("boss/shejing", time(), me);

        me->save();

        return;
}

void start_move()
{
        object *ob;
        int i;

        ob = all_inventory(this_object());

        // 清出清场标志
        delete("doing");

        if (! sizeof(ob))return;

        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character())
                {
                        destruct(ob[i]);
                        continue;
                }

                if( query("id", ob[i]) == "jiutou shejing" )
                        continue;

                ob[i]->move("/d/shenlong/shedong4.8");
        }

        return;
}

// 来自蛇精文件的呼叫，当蛇精死亡后延迟将所有房间内的ID
// 移动到蛇精洞外，如delay_time = 0 则不延迟
void move_all_player_out(int delay_time)
{
        if (! delay_time)
        {
                start_move();
        }
        else
        {
                remove_call_out("start_move");
                call_out("start_move", delay_time);
        }

        return;

}
