// This program is a part of NITAN MudLIB 
// redl 2015/10
#include <ansi.h> 
#include <room.h> 
#include <transmsg.h>

inherit ROOM;

int valid_leave(object me, string dir)
{
        if (random(2) && me->is_fighting())
        {
                tell_object(me, "你还是先解决目前的敌人吧！\n"); 
                return 0;
        }
                
        return ::valid_leave(me, dir);
}

int discmds() 
{ 
        tell_object(this_player(), "你不能在这里毛手毛脚。\n");  
        return -1;  
} 

int do_esc() 
{ 
        if (!query_temp("jinchuan/iesc", this_player())) {
                tell_object(this_player(), "你已经没有小乾坤符了。\n");  
                return -1;
        }
        if (strsrch(base_name(this_object()), "yuanjiang/chuan7")!=-1) {//处于10天干船舱时
                tell_object(this_player(), "你没法在这里使用小乾坤符。\n");  
                return -1;
        }
        addn_temp("jinchuan/iesc", -1, this_player());
        message_vision(HIY "$N" HIY "一挥衣袖，洒出一片金光突然消失了。\n" NOR, this_player());
        this_player()->move(get_object(__DIR__"chuan" + (string)random(50)));
        message_vision(HIY "$N" HIY "随着一片金光突然出现在这个船舱里。\n" NOR, this_player());
        return 1;  
} 

int do_get()
{
        if (this_player()->is_fighting())
             {
                if (strsrch(base_name(this_object()), "yuanjiang/chuan7")!=-1) {//处于10天干船舱时不能在战斗结束前get胜利品
                tell_object(this_player(), "战斗里没法去捡东西！\n"); 
                return -1;
            }
        }
    return 0;
}

int do_chou()
{
        object me = this_player();
        int rnd = random(5)+1;
        int num = query("yuan_ci_num", this_object());
        string msg = "";
        
        if (num<1) {
                tell_object(me, NOR "此地元磁真气已经匮乏。\n" NOR); 
                return -1;
        }
        
        if (me->is_busy())
        {
                tell_object(me, NOR BUSY_MESSAGE NOR); 
                return -1;
        }
        else if (!random(3))
                me->start_busy(1);      
                        
        addn("gcjinchuan_yuancizhenqi/" + (string)rnd, 1, me);
        addn("yuan_ci_num", -1, this_object());
        tell_object(me, NOR "你伸掌从舱底的破洞处，向着元江漩涡下面的地肺运功一吸，得到一条" + HIY + ({"","金","木","土","水","火"})[rnd] + NOR "行元磁真气。\n" NOR); 
        for (int i = 1; i <= 5; i++) {
                msg += ({"","金","木","土","水","火"})[i] + "." + (string)(query("gcjinchuan_yuancizhenqi/" + (string)i, me)) + "  ";
        }
                tell_object(me, NOR + msg + "\n" + NOR);
        return 1;
}

void init()
{
        object room, who, *objs, *doors;
        
        add_action("do_esc", ({"esc", "escape"})); 
        add_action("do_get", ({"get", "eat"})); 
        if (!playerp(this_player())) return;
        set("trans_msg_to", __DIR__"chuancenter");
        set("trans_msg_id", query("id", this_player()));
        add_action("do_chou", "xi"); 
        if (wiz_level(this_player()) < 2) add_action("discmds", ({  
                        "steal", "cast", "conjure", "array", "fight", "hit",   
                        "home", "ansuan", "touxi", "ride", "qi", "stab", "fbattle",
                        "surrender", "array", "battle", "accept", "swear",
                        "recall", "quit", "exit", "miss", "rideto", "chatroom",
        }));  
        room = this_object();
        doors = filter_array( all_inventory(room), (: strsrch(base_name($1), "yuanjiang/npc/obj/door")!=-1 :) );
        if (sizeof(doors)>0) {
                tell_object(this_player(), NOR"\n你发现了一个神秘的舱门(door)。\n\n"NOR); 
                return;
        }

        if ( query("env/invisible", this_player()) ) return;//wiz

        if(!query_temp("apply/shade_vision", this_player()) || query_temp("apply/shade_vision", this_player())<1 ) {            
                objs = filter_array(all_inventory(room), (: playerp($1) && (query("id", $1)!=query("id", this_player())) :));
                if (sizeof(objs)>0) {
                        who = objs[random(sizeof(objs))];
                        if(!query_temp("apply/shade_vision", who) || query_temp("apply/shade_vision", who)<1 ) {
                                this_player()->kill_ob(who);
                                who->kill_ob(this_player());
                        }
                }
        }
        
        if ( query("stop_run") ) return;
        tell_object(this_player(), NOR"\n金船轰隆一摇，你摔了一跤崴了脚，半天都爬不起来。\n\n"NOR); 
        if (query_temp("apply/shade_vision", this_player()) && !random(4)) {
                delete_temp("apply/shade_vision", this_player());
        message_vision(HIK "$N" HIK "的身形逐渐显露出来，变的清晰可见。\n" NOR, this_player());
        }
        this_player()->start_busy(2+ random(4));
        set("stop_run", random(3), room);
        
}


