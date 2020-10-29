
#include <ansi.h>
#ifndef MYGIFT_D
#define MYGIFT_D    "/adm/daemons/mygiftd.c"
#endif

int main(object me, string arg)
{
        string nquest;
        mapping tmap;

        if( arg && arg == "skip" )
        {
                if( !query("newbie_mygift/cur_quest_number", me) ) return 0;

                if( query("newbie_mygift/is_running_gift_list_send", me) ) return 0; 
                
                nquest=query("newbie_mygift/cur_quest_number", me);
                tmap = MYGIFT_D->query_gift_list(nquest); 
                tell_object(me, HIC "你决定放弃当前辅助任务，获取新的辅助任务。\n" NOR);
                MYGIFT_D->give_mygift(me, tmap["下个奖励"]); 
                return 1;
        }
	return MYGIFT_D->mygift(me, arg);
}

