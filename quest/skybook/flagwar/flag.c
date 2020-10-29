// business.c

inherit F_CLEAN_UP;

#define PAY_MONEY        500000 
nomask int main(object me, string arg)
{
	   int tt;
     string msg;
     if(!find_object(FWAR_D)) return notify_fail("目前抢旗战尚未开始。\n");
    switch(arg) {
    	case "join":
    		if(!FWAR_D->query_flagwar_data("can_accept")) return notify_fail("本场抢旗战尚未开放报名。\n");
    		if(member_array(me->query("id"), FWAR_D->query_flagwar_data("all_player")) != -1) return notify_fail("你已经报名本场的抢旗战了。\n");
          switch(MONEY_D->player_pay(me, PAY_MONEY)) {
           case 0:
           case 2:
           	return notify_fail("参加抢旗战需支付"+MONEY_D->money_str(PAY_MONEY)+"。\n");
           break;
           default:
           if(!FWAR_D->add_player(me, PAY_MONEY)) return notify_fail("报名抢旗战出现问题，请使用 sos post 回报。\n");
           break;           
           }
    	break;
    	case "leave":
    		// 报名阶段
    		if(!FWAR_D->query_flagwar()) {
    			if(member_array(me->query("id"), FWAR_D->query_flagwar_data("all_player")) == -1) return notify_fail("你本来就没有报名抢旗战。\n");
    			FWAR_D->leave_player(me->query("id"));
    		} else {
    			if(member_array(me->query("id"), FWAR_D->query_flagwar_data("all_player")) == -1) return 0;
    			FWAR_D->leave_player(me->query("id"));
    		}
    	break;
    	default:
     if(!FWAR_D->query_flagwar()) {
     	tt = FWAR_D->query_flagwar_time();
      if(tt == -1) return notify_fail("抢旗战已经在报名阶段。\n");
      else if(tt == -2) return notify_fail("抢旗战正在准备。\n");
     	else return notify_fail("目前抢旗战尚未开始，距离下次开始还有"+CHINESE_D->chinese_period(tt)+"。\n");
     }
     msg = " "+FWAR_D->query_party_score_total();
     msg += "┌─────────────────────────────────┐\n";
     msg += " "+FWAR_D->query_party_score("red");
     msg += " ────────────────────────────────── \n";
     msg += " "+FWAR_D->query_party_score("blue");
     msg += "└─────────────────────────────────┘\n";
     me->start_more(msg);    		
    	break;
    }
     
     
     
     return 1;
}

int help(object me)
{
        write(@HELP
指令格式：flag score | join | leave

此指令用来查看抢旗战的状况。

参数： score : 查看抢旗战的状况。
       join  : 报名参加抢旗战。
       leave : 离开抢旗战或取消报名。
HELP);
        return 1;
}

