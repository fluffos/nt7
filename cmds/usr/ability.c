// This program is a part of NT MudLIB

#include <ansi.h>
#ifndef F_ABILITY;
#define F_ABILITY        "/adm/daemons/abilityd"
#endif

inherit F_ABILITY;
int main(object me, string arg)
{
        string *lists,temp,id;
        int ab, n;
        int i, a_num, learned_ability;
        object ob;
        string arg1, myclass;

        MYGIFT_D->check_mygift(me, "newbie_mygift/ability");
        if( wizardp(me) )
        {
                if( arg && sscanf(arg, "-%s", id) == 1 )
                {
                        ob = present(id, environment(me));
                        if (!ob) ob = find_player(id);
                        if (!ob) ob = find_living(id);
                        if (!ob) return notify_fail("你要察看谁的能力？\n");
                } else
                        ob = me;
        } else
                ob = me;

        ab = query("ability", ob);

        learned_ability=query("learned_ability", ob);

        if( arg && ob == me )
        {
                if( !sscanf(arg, "+ %d", a_num) )
                        return notify_fail("提高能力的格式：ability + 能力名称 \n");

                if( a_num < 1 || a_num > 50 )
                        return notify_fail("没有此代码的能力（请输入1-35）\n");

                if( a_num < 21 )
                {
                        arg1 = bas_ability[a_num-1];

                        if( !valid_ability_improve(ob, arg1, 0) )
                                return notify_fail("你的经验等级还不足以掌握更高的该项能力。\n");

                        if( !do_ability_cost(ob, arg1, 0) )
                                return notify_fail("你没有足够的能力点和潜能储蓄来提高此项能力。\n");

                        improve_ability( ob, arg1, 0);
                        tell_object(ob, "该第"+ (a_num) + "能力提高完毕。\n");
                        return 1;
                }

                if( !stringp(myclass=query("family/family_name", ob)) )
                        return notify_fail("你无门无派，如何能够领会门派武功的精髓？\n");

                if( !arrayp(fam_ability[myclass]) || (n = sizeof(fam_ability[myclass])) < a_num-20 )
                {
                         return notify_fail("OOPS，你所在的门派的此项特色还没写好耶。\n");

                } else
                {
                        arg1 = fam_ability[myclass][a_num-21];
                        if( !valid_ability_improve(ob, arg1, 1) )
                                return notify_fail("你的经验等级还不足以掌握更高的该项能力。\n");

                        if( !do_ability_cost(ob, arg1, 1) )
                                return notify_fail("你没有足够的能力点储蓄来提高此项能力。\n");

                        improve_ability(ob, arg1, 1);
                        tell_object(ob, "该第"+ (a_num) + "能力提高完毕。\n");
                }

                return 1;
        }


        write("\n");
        write(HIC    "序号              功效                      等级          升级点数\n"NOR);
        write(HIG "——————————————————————————————————\n" NOR);
        write(HIC"基本能力进阶：\n\n"NOR);

        for(i=0; i<sizeof(bas_ability); i++)
                write(sprintf(WHT"("WHT"%3d"WHT")", (i+1)) + HIC"\t"+ get_ability_info(ob, bas_ability[i], 0) + NOR);
        write("\n");

        write(HIG "——————————————————————————————————\n" NOR);
        write(HIC"门派能力进阶：\n\n"NOR);

        if( !stringp(myclass=query("family/family_name", ob)) )
                write("无门无派无特色。\n");
        /*
        else if( query("betrayer", ob) )
                write("你有叛师前科，无法领会新门派的精髓。\n");
        */
        else if( !arrayp(fam_ability[myclass]) )
                write("OOPS，你所在的门派的特色还没写好耶。\n");
        else
                for( i=0; i<30; i++ )
                {
                        if( i > sizeof(fam_ability[myclass])-1 ) break;
                        write(sprintf(WHT"("WHT"%3d"WHT")", (i+21)) + HIC"\t"+ get_ability_info(ob, fam_ability[myclass][i],1) + NOR);
                }

        write("\n");
        write(HIG "——————————————————————————————————\n" NOR);

        write(HIW"你现在总共获得 "HIC + ab + NOR+HIW" 点能力。\n" NOR);
        write(HIW"你已经用去了 " RED+ learned_ability +NOR+HIW" 点能力，还剩下 "HIG+ (ab-learned_ability) + NOR+HIW" 点可供分配。\n" NOR);
        //write(HIG "——————————————————————————————————\n" NOR);
        write("\n\n");
        return 1;
}


int help(object me)
{
write(@HELP

----------------------------------------------------------------
指令格式 :     ability
----------------------------------------------------------------

ability         让你知道你目前所学过的一切能力，
ability + n     提高第ｎ项能力的等级。

能力是泥潭游戏中除经验值、技能值以外提高自身的一个重要途径。
相同经验等级的，能力高的人会有更多的气血，造成更大的伤害力，
或者可以有更高的学习效率。如何合理分配能力点是成为高手的一
大基本要求。

当你的人物等级升级而获得能力点，就可以提高自身的各项能力了！
输入ａｂｉｌｉｔｙ就可以看到一个清晰的列表。分两大类，第一
类共有２０项，所有门派都可以修习，大多是提高基本属性的；第
二类有五项，属于门派武功的精髓所在，不同门派各有特色。

每项能力共分十级，每级的功效都有详细说明。

该修习什么呢？这就是由各个不同门派的特点或者个人喜好所决定
了。如果你想在战斗中持久，就多提高些增长精气神的能力，如果
你要提高杀伤力，就提高些力量。。。。



能力点重置：
    玩家可以在泥潭商城处购买龙晶可用来重置已经分配好的能力点。
重置后，所有能力进阶还原为能力点。第一次重置能力会消耗一个龙
晶；之后每重置一次，会再额外消耗一个龙晶；第25次及之后的重置
将不会再额外增加消耗，固定每次25个龙晶。

----------------------------------------------------------------
HELP
    );

        MYGIFT_D->check_mygift(me, "newbie_mygift/ability");
        return 1;
}
