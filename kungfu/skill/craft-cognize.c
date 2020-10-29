#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
    return 1;
}

void skill_improved(object me)
{
        int lvl;

        lvl = me->query_skill("craft-cognize", 1);

        if (lvl > 100
         && !query("craft/infantry/fenzhan", me) )
        {
                set("craft/infantry/fenzhan", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "步兵系兵法" HIC "」中「" HIW "奋战" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 110
         && !query("craft/infantry/fendou", me) )
        {
                set("craft/infantry/fendou", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "步兵系兵法" HIC "」中「" HIW "奋斗" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 120
         && !query("craft/infantry/fenxun", me) )
        {
                set("craft/infantry/fenxun", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "步兵系兵法" HIC "」中「" HIW "奋迅" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 130
         && !query("craft/archer/qishe", me) )
        {
                set("craft/archer/qishe", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "弓骑系兵法" HIC "」中「" HIW "骑射" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 140
         && !query("craft/archer/benshe", me) )
        {
                set("craft/archer/benshe", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "弓骑系兵法" HIC "」中「" HIW "奔射" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 150
         && !query("craft/archer/feishe", me) )
        {
                set("craft/archer/feishe", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "弓骑系兵法" HIC "」中「" HIW "飞射" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 160
         && !query("craft/crossbow/qishe", me) )
        {
                set("craft/crossbow/qishe", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "弓弩系兵法" HIC "」中「" HIW "齐射" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 170
         && !query("craft/crossbow/lianshe", me) )
        {
                set("craft/crossbow/lianshe", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "弓弩系兵法" HIC "」中「" HIW "连射" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 180
         && !query("craft/crossbow/liannu", me) )
        {
                set("craft/crossbow/liannu", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "弓弩系兵法" HIC "」中「" HIW "连弩" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 190
         && !query("craft/cavalry/tupo", me) )
        {
                set("craft/cavalry/tupo", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "骑兵系兵法" HIC "」中「" HIW "突破" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 200
         && !query("craft/cavalry/tujin", me) )
        {
                set("craft/cavalry/tujin", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "骑兵系兵法" HIC "」中「" HIW "突进" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 210
         && !query("craft/cavalry/tuji", me) )
        {
                set("craft/cavalry/tuji", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "骑兵系兵法" HIC "」中「" HIW "突击" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 220
         && !query("craft/siegecity/jinglan", me) )
        {
                set("craft/siegecity/jinglan", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "攻城系兵法" HIC "」中「" HIW "井阑" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 230
         && !query("craft/siegecity/chongche", me) )
        {
                set("craft/siegecity/chongche", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "攻城系兵法" HIC "」中「" HIW "冲车" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 240
         && !query("craft/siegecity/fashi", me) )
        {
                set("craft/siegecity/fashi", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "攻城系兵法" HIC "」中「" HIW "发石" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 250
         && !query("craft/siegecity/xiangbing", me) )
        {
                set("craft/siegecity/xiangbing", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "攻城系兵法" HIC "」中「" HIW "象兵" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 260
         && !query("craft/siegecity/luoshi", me) )
        {
                set("craft/siegecity/luoshi", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "守城系兵法" HIC "」中「" HIW "落石" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 270
         && !query("craft/siegecity/shetai", me) )
        {
                set("craft/siegecity/shetai", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "守城系兵法" HIC "」中「" HIW "射台" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 280
         && !query("craft/ruse/hunluan", me) )
        {
                set("craft/ruse/hunluan", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "谋略系兵法" HIC "」中「" HIW "混乱" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 290
         && !query("craft/ruse/xianjing", me) )
        {
                set("craft/ruse/xianjing", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "谋略系兵法" HIC "」中「" HIW "陷阱" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 300
         && !query("craft/ruse/gongxin", me) )
        {
                set("craft/ruse/gongxin", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "谋略系兵法" HIC "」中「" HIW "攻心" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 310
         && !query("craft/ruse/huanshu", me) )
        {
                set("craft/ruse/huanshu", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "谋略系兵法" HIC "」中「" HIW "幻术" HIC "」的奥秘。\n" NOR);
        }
        
        if (lvl > 320
         && !query("craft/brightness/yingzao", me) )
        {
                set("craft/brightness/yingzao", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "智略系兵法" HIC "」中「" HIW "营造" HIC "」的奥秘。\n" NOR);
        }
        
        if (lvl > 330
         && !query("craft/brightness/poxian", me) )
        {
                set("craft/brightness/poxian", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "智略系兵法" HIC "」中「" HIW "破陷" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 340
         && !query("craft/brightness/jiaoyu", me) )
        {
                set("craft/brightness/jiaoyu", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "智略系兵法" HIC "」中「" HIW "教谕" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 350
         && !query("craft/resource/ruma", me) )
        {
                set("craft/resource/ruma", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "策略系兵法" HIC "」中「" HIW "辱骂" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 360
         && !query("craft/resource/guwu", me) )
        {
                set("craft/resource/guwu", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "策略系兵法" HIC "」中「" HIW "鼓舞" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 370
         && !query("craft/resource/zhiliao", me) )
        {
                set("craft/resource/zhiliao", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "策略系兵法" HIC "」中「" HIW "治疗" HIC "」的奥秘。\n" NOR);
        }

        if (lvl > 380
         && !query("craft/resource/yaoshu", me) )
        {
                set("craft/resource/yaoshu", 1, me);
                tell_object(me, HIC "你通晓了「" HIW "兵法" HIC "」之「" HIW
                        "策略系兵法" HIC "」中「" HIW "妖术" HIC "」的奥秘。\n" NOR);
        }
}

