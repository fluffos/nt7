// This program is a part of NT MudLIB

#include <ansi.h>
#ifndef F_ABILITY;
#define F_ABILITY        "/adm/daemons/abilityd"
#endif

inherit F_ABILITY;
int main(object me, string arg)
{
        string *lists,temp,id;
        int ab;
        int i, a_num, learned_energy;
        object ob;
        string arg1, myclass;
        int level;

        MYGIFT_D->check_mygift(me, "newbie_mygift/talent");
        if( wizardp(me) )
        {
                if( arg && sscanf(arg, "-%s", id) == 1 )
                {
                        ob = present(id, environment(me));
                        if (!ob) ob = find_player(id);
                        if (!ob) ob = find_living(id);
                        if (!ob) return notify_fail("你要察看谁的天赋技能？\n");
                } else
                        ob = me;
        } else
                ob = me;

        ab = query("energy", ob);

        learned_energy=query("learned_energy", ob);

        if( arg && ob == me )
        {
                if( !sscanf(arg, "+ %d", a_num) )
                        return notify_fail("提高天赋技能的格式：talent + 天赋技能代号 \n");

                if( a_num < 1 || a_num > 32 )
                        return notify_fail("没有此代码的天赋技能（请输入1-30）\n");

                if( a_num < 33 )
                {
                        arg1 = talent_ability[a_num-1];
                        level = query("yuanshen_level", ob);

                        if( a_num > (level/10 + 1) * 3 )
                                return notify_fail("你的元神境界还不足以掌握更高的天赋技能。\n");

                        if( !valid_ability_improve(ob, arg1, 2) )
                                return notify_fail("你的元神境界还不足以掌握更高的该项能力。\n");

                        if( !do_ability_cost(ob, arg1, 2) )
                                return notify_fail("你没有足够的天赋点储蓄来提高此项能力。\n");

                        improve_ability(ob, arg1, 2);
                        tell_object(ob, "该第"+ (a_num) + "天赋技能提高完毕。\n");
                        return 1;
                }

                return 1;
        }


        write("\n");
        write(HIY+(ob==me?"你":ob->query_idname())+HIY"掌握的天赋技能如下\n"NOR);
        write(HIG"——————————————————\n" NOR);
        write(HIC    "序号              功效                                                等级          升级点数\n"NOR);
        write(HIG "——————————————————————————————————————————————\n" NOR);

        for(i=0; i<sizeof(talent_ability); i++)
                write(sprintf(WHT"("WHT"%3d"WHT")", (i+1)) + HIC"\t"+ get_ability_info(ob, talent_ability[i], 2) + NOR);
        write("\n");

        write(HIG "——————————————————————————————————————————————\n" NOR);

        write(HIW"你现在总共获得 "HIC + ab + NOR+HIW" 点天赋点。\n" NOR);
        write(HIW"你已经用去了 " RED+ learned_energy +NOR+HIW" 点天赋点，还剩下 "HIG+ (ab-learned_energy) + NOR+HIW" 点可供分配。\n" NOR);
        //write(HIG "——————————————————————————————————————————————\n" NOR);
        return 1;
}


int help(object me)
{
write(@HELP

[0;1;37m----------------------------------------------------------------[0m
[0;1;36m指令格式 :     talent [0m
[0;1;37m----------------------------------------------------------------[0m

talnet         让你知道你目前所掌握的一切天赋技能，
talent + n     提高第ｎ项天赋技能的等级。

能力点重置：
    玩家可以在泥潭商城处购买龙晶可用来重置已经分配好的天赋点。
重置后，所有天赋技能还原为天赋点。第一次重置天赋会消耗一个龙
晶；之后每重置一次，会再额外消耗一个龙晶；第25次及之后的重置
将不会再额外增加消耗，固定每次25个龙晶。

[0;1;37m----------------------------------------------------------------[0m
HELP
    );

        MYGIFT_D->check_mygift(me, "newbie_mygift/talent");
        return 1;
}
