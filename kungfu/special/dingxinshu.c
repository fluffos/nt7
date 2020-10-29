// 定心术 Create by Rcwiz for yhonline 04/21 2010

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "定心术" NOR; }

int perform(object me, string skill)
{
        // 2转后使用可立即获得180级左右互搏
        // 如果当前等级超过180则显示说明
        if (me->query("thborn/ok") && me->query_skill("zuoyou-hubo",1) < 180)
        {
                me->set_skill("zuoyou-hubo", 180);
                me->save();
                return notify_fail("你获得了左右互搏180级。\n");
        }
        else
        {
                      return notify_fail("定心术可摄定心神,令施展左右互搏不受牵制。\n"
                                        "使用后可获得左右互搏180级,同时可自行\n"
                                        "研究到380级.如绝情去欲技能达到三百级\n"
                                   "可研究左右互搏到400级。\n");
       }
}
