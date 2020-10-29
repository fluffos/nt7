// shop.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        if( !wizardp(me) && time()-query_temp("last_combat", me)<10 )
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");   

        set_temp("last_combat", time(), me);
        MYGIFT_D->check_mygift(me, "newbie_mygift/combat");
        SKILLS_D->query_skill_power(me, arg);
        return 1;
}

int help (object me)
{
        write(@HELP
查看武功各种参数值
    combat attack             查看命中力排名
    combat dodge              查看躲闪力排名
    combat parry              查看招架力排名
    combat damage             查看伤害力排名
    combat force              查看内功的排名
    combat difficult          查看难度的排名
    combat ultimate           查看终极的武功
    combat expert             查看超级的武功
    combat advance            查看高级的武功
    combat normal             查看普通的武功
    combat public             查看公共的武功
    combat family             查看门派的武功
    combat private            查看自创的武功
    combat <门派名称>         查看该门派武功
    combat <技能名称>         查看该武功参数
    combat <技能种类>         查看可激发武功

HELP);
        return 1;
}
