// tongji.c

#include <ansi.h>

inherit F_CLEAN_UP;

int sort_skill(object a, object b, string str);
int main(object me, string str)
{
        object *players;
        object *users;
        int j;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;                      

        if (! str)
                return notify_fail("你要统计什么技能？\n");

        if (file_size("/kungfu/skill/" + str + ".c") == -1)
                return notify_fail("没有这个技能存在！\n");                

        // users = all_interactive();
        users = users();

        j = 0;
        write(HIW "\n以下为本 MUD 中掌握 " + HIM + CHINESE_D->chinese(str) + HIW + " 的在线玩家。\n" NOR);
        write(HIY "-------------------------------------------------------------------------\n" NOR);

        players = ({});
        foreach (object player in users)
        {
                if (player->query_skill(str, 1))
                {
                        players += ({ player });
/*
                        write(sprintf(HIC "%-21s年龄：%-10d所属门派：%-16s等级：%-10d\n" NOR,
                                      player->name()+"("+query("id", player)+")",
                                      query("age", player),
                                      query("family/family_name", player),
                                      player->query_skill(str, 1)));
                        j ++;
*/
                }
         
        }

        players = sort_array(players, (: sort_skill :), str);    
        foreach (object player in players)
        {
                if (player->query_skill(str, 1))
                {
                        write(sprintf(HIC "%-21s年龄：%-10d所属门派：%-16s等级：%-10d\n" NOR,
                                      player->name()+"("+query("id", player)+")",
                                      query("age", player),
                                      query("family/family_name", player),
                                      player->query_skill(str, 1)));
                        j ++;
                }
         
        }
        write(HIW "\n总共 " HIR + j + HIW " 位玩家掌握" + HIM + CHINESE_D->chinese(str) + "\n" NOR);
        write(HIY "-------------------------------------------------------------------------\n" NOR);

        return 1;
}

int sort_skill(object a, object b, string str)
{
        return b->query_skill(str, 1) - a->query_skill(str, 1);
}