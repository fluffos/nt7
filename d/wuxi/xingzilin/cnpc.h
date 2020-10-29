#include <ansi.h>

//奖励频道
#define CHANL_NAME "news"

#define GIVEHEAD_GIFT_EXP 20000 //老乞丐任务赏经验

//all npc
#define HP_JING_PERCENT 1.6             //精和气的比例
#define HP_NEILI_PERCENT 2              //内力和气的比例
//赫连铁树
#define BOSS1_LEVEL 150
#define BOSS1_SKILL_LV 4800
#define BOSS1_QI_BASE 30000000
#define BOSS1_GIFT_EXP 2500000
//努尔海
#define BOSS2_LEVEL 140
#define BOSS2_SKILL_LV 3000
#define BOSS2_QI_BASE 12000000
#define BOSS2_GIFT_EXP 2500000
//武士2345
#define WU2345_LEVEL 120
#define WU2345_LEVEL_INCREASE 3
#define WU2345_SKILL_LV 2000
#define WU2345_SKILL_INCREASE 500
#define WU2345_QI_BASE 8000000
#define WU2345_GIFT_EXP 15000  //买了双倍的情况下，1.8*2*4=14.4万/分钟，过节期间除外
//恶人，根据武士2345变化
#define EREN_LEVEL 130
#define EREN_GIFT_EXP 90000
//外围武士，注意个数是2~3，所以不能单个太高
#define WU9_LEVEL 50
#define WU9_GIFT_EXP 1000
#define WU8_LEVEL 60
#define WU8_GIFT_EXP 1900
#define WU7_LEVEL 70
#define WU7_GIFT_EXP 2200
#define WU6_LEVEL 80
#define WU6_GIFT_EXP 2500





int invert_reborngiftd(object me, int exp)
{
        //if (query("reborn/times", me)) exp *= 2;//抵消转世的奖励惩罚
        return exp;
}


int get_show_giftexp(object me, int exp)//在news频道用来显示的经验奖励值
{
        int quest_times;
        if (MEMBER_D->is_double_reward(me)) exp *= 2;
        quest_times = "/adm/daemons/actiond"->query_action("event_reward");
        if (quest_times) exp *= quest_times;
        if( me->query_bunch() && BUNCH_D->query_bunch_efficient(me->query_bunch(), "exp") ) exp *= 2;        
        else if( me->query_family() && FAMILY_D->query_family_efficient(me->query_family(), "exp") ) exp *= 2;
        return exp;
}


