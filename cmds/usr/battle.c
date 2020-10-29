// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me)
{
        write(@HELP
战场指令，可以报名与离开战场

battle info                          - 显示目前战争资讯
battle join                          - 报名参加下一场次的战场
battle cancel                        - 取消报名

HELP );
        return 1;
}

int main(object me, string arg)
{
        switch(arg)
        {
                case "info":
                {
                        string msg;
                        string *players = BATTLEFIELD_D->get_sorted_players();
                        string score = "";
                        string ppl = "";
                        int count = 0;
                        
                        msg = "目前共 "+sizeof(players)+" 位玩家参与战争，"+(member_array(me->query_id(1), players)==-1?"你未参与战争":"你是其中之一")+"。\n";
                                                
                        if( sizeof(players) > 0 )
                        {
                                object player;
                
                                foreach(string id in players)
                                {
                                        if( !objectp(player = find_player(id)) )
                                                continue;
                        
                                        if( ++count <= 3 )
                                                score += player->query_idname()+"、";
                                        
                                        ppl += player->query_idname()+NOR"("+BATTLEFIELD_D->get_player_score(id)+")、";
                                        if( count % 5 == 0 )
                                                ppl += "\n";
                                                                                                      
                                }
                                
                                msg += "参与者战绩统计：\n"+ppl[0..<3]+"。\n";
                                
                                msg += "目前战争绩分排名前三名为："+score[0..<3]+"。\n";
                        }
                        
                        tell_object(me, msg);
                        break;
                }
                case "join":
                        BATTLEFIELD_D->join_battle(me);
                        break;
                case "cancel":
                        BATTLEFIELD_D->cancel_battle(me);
                        break;
                default:
                        tell_object(me, "请输入正确的指令格式(help battle)。\n");
                        break;
        }
        return 1;
}
